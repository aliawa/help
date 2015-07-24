#include "util.h"
#include "sipdialplan.h"
#include <arpa/inet.h>
#include <cfg_util.h>


//
// ------------------------------ DEFINES ---------------------------------------
// 

// VNAME: html value name
#define TLS_DOMAIN_NAME_VNAME   "TLS_DOMAIN_NAME"
#define ENUM_SUFFIX_VNAME       "ENUM_SUFFIX"
#define LAN_SIDE_GATEWAY_VNAME  "LAN_SIDE_GATEWAY"
#define KEY_SERVER_VNAME        "KEY_SERVER"
#define ENABLE_SECURE_GW_VNAME  "ENABLE_SECURE_GW"
#define ENABLE_SRTP_VNAME       "ENABLE_SRTP"
#define GET_CERTS_NOW_VNAME     "GET_CERTS_NOW"
#define CERT_SERVER_VNAME       "CERT_SERVER"

// SNAME: script value name
#define TLS_DOMAIN_NAME_SNAME   "tls-domain"
#define ENUM_SUFFIX_SNAME       "enum-suffix"
#define LAN_SIDE_GATEWAY_SNAME  "lan-gateway"
#define KEY_SERVER_SNAME        "key-server"
#define SIP_ALG_ADDRESS_SNAME   "alg-address"
#define REPRO_UDP_PORT_SNAME    "udp"
#define RECORD_ROUTE_SNAME	    "record-route"
#define REPRO_TLS_PORT_SNAME	"tls"
#define SIP_DOMAINS_SNAME		"domains"
#define TLS_CERT_PATH_SNAME		"cert-path" 

// Others
#define ALG_PORT                5060
#define NETRC_PATH              "/etc/config/.netrc"
#define GET_CERTS_SCRIPT        "/etc/conf/bin/getCerts.sh"
#define FTP_LOGIN               "anonymous"
#define FTP_PASSWD              "na"


//
// --------------------------- Helpers Local -------------------------------------
//


static void print_js_alternateRowColor()
{
    // import style sheet
    printf("<style type=\"text/css\"> @import \"../img/table.css\"; </style>"); 
    
    // manipulte row colors
    printf("<SCRIPT LANGUAGE=\"JavaScript\" type=\"text/javascript\">\n\n");
    printf( "function onPageLoad(){\n"\
            "   if(document.getElementsByTagName){\n"\
            "      var table = document.getElementById(\"layoutTable\");\n"\
            "      var rows = table.getElementsByTagName(\"tr\"); \n"\
            "      for(i = 1; i < rows.length-2; i++){ \n"\
            "         if(i %% 2 == 0){\n"\
            "            rows[i].className = \"even\";\n"\
            "         }else{\n"\
            "            rows[i].className = \"odd\";\n"\
            "         }\n"\
            "      }"\
            "   }"\
            "}");
    printf("    </SCRIPT>\n");
}
    
static void print_input_str_hidden(char *vname, char *value, int   size, int   maxlen, char *display)
{
    printf("<tr id='%s_id' style='display:none'>", vname);
    printf("<td>%s</td><td><input type=text name=%s value='%s' size=%d></td>", display, vname, value, size);
    printf("</tr>");  
}  


static void print_error_border(const char* errorMsg)
{
    printf("<tr><td colspan=2 style='border:thin solid red'>Error: %s </td></tr>",errorMsg);
}


static int  createLanGateway(char* name, int addr, int port)
{
    sip_loadDialPlanOnly();
    sip_CreateDefTarget(name, addr, port, 0);
    sip_saveDialPlan();
	return 0;
}


static int getTLSCerts(char* certServer, char* tlsDomainName, char* certsDir)
{
    char buf[255];
    int ret;
    
    sprintf (buf, "default login %s password %s\n\n", FTP_LOGIN, FTP_PASSWD);
    qSaveStr(buf, strlen(buf), NETRC_PATH, "w"); 
    
    sprintf(buf, "%s %s %s %s", GET_CERTS_SCRIPT, certServer, tlsDomainName, certsDir);
    ret = system(buf);
    unlink(NETRC_PATH);
    return ret;
}


static int configFirewall(Q_Entry *repro_config)
{
	char buf[55];
    int tcpPort		 = qfiValue(repro_config, REPRO_TLS_PORT_SNAME);
	sprintf(buf, "\"%d\"", tcpPort);
	return ((save_str(FW_CONF, ALLOW_TCP_PORT_SNAME, buf) != TRUE));
}
		
		
static void restart()
{
	system("/etc/conf/bin/config_alg > /dev/null");
    system("killall -9 repro         > /dev/null");
	system("/etc/conf/bin/config_fw  > /dev/null");
}

 



//
// --------------------------- Create Page  -------------------------------------
//

void display_secure_gw_page()
{
    // initialize the variables
    char*   tlsDomainName   = "";
    char*   enumSuffix      = "";
    char*   lanGatewayAdr   = "";
    char*   certServer      = "";
    char*   errorStr        = NULL;
    char*   wanIpAddr       = "";
	char* 	domainName		= "";
    int     lanGatewayPrt   = 5060;
    int     getCerts        = 0;
    int     enableSecureGW  = 0;
    int     enableSRTP      = 0;
    int     submit          = qValue(SUBMIT_BUTTON_VNAME) != NULL;
	
    Q_Entry *repro_conf     = qfDecoder(REPRO_CONF);
    Q_Entry *ip_conf        = NULL;
    
    
    // Load Submitted values
    if (submit)
    {
        tlsDomainName   = qValue  (TLS_DOMAIN_NAME_VNAME);
        enumSuffix      = qValue  (ENUM_SUFFIX_VNAME);
        lanGatewayAdr   = qValue  (LAN_SIDE_GATEWAY_VNAME);
        enableSecureGW  = qiValue (ENABLE_SECURE_GW_VNAME);
        enableSRTP      = qiValue (ENABLE_SRTP_VNAME);
        getCerts        = qValue  (GET_CERTS_NOW_VNAME) != NULL;
        certServer      = qValue  (CERT_SERVER_VNAME);
        
		// for now domainName=tlsDomainName
		domainName 		= tlsDomainName;
		
        // validate
        if (strlen(tlsDomainName) == 0)
            errorStr = "TLS Domain Name missing";
        if (strlen(enumSuffix) == 0 )
            errorStr = "Enum Suffix missing";
        if (getCerts && strlen(certServer)==0)
            errorStr = "certServer missing";
        
        if ((ip_conf = qfDecoder(IP_CONF)))
            wanIpAddr = qfValue(ip_conf, WAN_IP_SNAME);
        else
            errorStr = "WAN-IP Address not configured";
 
    }
    // or Load from config
    else if (repro_conf)
    {
        tlsDomainName   =  qfValue (repro_conf, TLS_DOMAIN_NAME_SNAME); 
        enumSuffix      =  qfValue (repro_conf, ENUM_SUFFIX_SNAME);
        lanGatewayAdr   =  qfValue (repro_conf, LAN_SIDE_GATEWAY_SNAME);
		enableSecureGW  =  qfiValue(repro_conf, ENABLE_SECURE_GW_SNAME);
        enableSRTP      =  qfiValue(repro_conf, ENABLE_SRTP_SNAME);
    }
    
    // save
    if (submit && !errorStr)
    {
        qfValueAdd(repro_conf, TLS_DOMAIN_NAME_SNAME,     "%s"	  , tlsDomainName);
        qfValueAdd(repro_conf, ENUM_SUFFIX_SNAME,         "%s"    , enumSuffix);
        qfValueAdd(repro_conf, LAN_SIDE_GATEWAY_SNAME,    "%s"	  , lanGatewayAdr);
        qfValueAdd(repro_conf, ENABLE_SECURE_GW_SNAME,    "%d"	  , enableSecureGW);
        qfValueAdd(repro_conf, ENABLE_SRTP_SNAME,         "%d"	  , enableSRTP);
        qfValueAdd(repro_conf, SIP_ALG_ADDRESS_SNAME,  "sip:%s:%d", wanIpAddr, ALG_PORT);
        qfValueAdd(repro_conf, RECORD_ROUTE_SNAME, 	   "sip:%s"   , domainName);
		qfValueAdd(repro_conf, SIP_DOMAINS_SNAME, 	   	  "%s"    , domainName);

		qfSave(repro_conf, REPRO_CONF);
        
        if (createLanGateway("LanGateway", ntohl(inet_addr(lanGatewayAdr)), lanGatewayPrt))
			errorStr = "Failed to create LAN Gateway";

		if (configFirewall(repro_conf))
			errorStr = "Failed to configure Firewall";
		
        if (getCerts && getTLSCerts(certServer, tlsDomainName, qfValue(repro_conf, TLS_CERT_PATH_SNAME)))
            errorStr= "Failed to get TLS Certificates"; 
	
		
        getCerts=0;
	   	restart();
    }
    
    //
    // ------------------ START CREATING PAGE --------------------------------------------------
    //
    print_js_alternateRowColor();
            
    // start page
    print_common_header(SECURE_GW_PG_NUM, "Secure Gateway Configuration", NULL, "SecureGWConfig");
    print_text("<hr>");
    if (errorStr) print_error_border(errorStr);
    
    print_checkbox_int  ( ENABLE_SECURE_GW_VNAME, enableSecureGW, "Enable Secure Gateway");
    print_input_str     ( TLS_DOMAIN_NAME_VNAME, tlsDomainName, 25, 25,"TLS Domain name");
    print_input_str     ( ENUM_SUFFIX_VNAME, enumSuffix, 25, 25,"Enum Suffix");;
    print_input_str     ( LAN_SIDE_GATEWAY_VNAME, lanGatewayAdr, 25, 25,"LAN-Side Gateway");
    print_checkbox_int  ( ENABLE_SRTP_VNAME, enableSRTP, "Enable SRTP");
    print_checkbox_with_action (GET_CERTS_NOW_VNAME, getCerts, "Get Certificates now", CERT_SERVER_VNAME"_id.style.display=''");
    print_input_str_hidden(CERT_SERVER_VNAME, certServer, 25, 25, "Certificate server");
    print_common_footer(SUBMIT_BUTTON_VNAME);
    
    //
    // ------------------- END CREATING PAGE --------------------------------------------------
    //
    
    
    // Close the repro_conf file
    qfFree(repro_conf);
    if (ip_conf)
        qfFree(ip_conf);
}
