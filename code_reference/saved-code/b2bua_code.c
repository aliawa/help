
// Does the SDP have content of the
// given type
bool SipMessage::hasContent(const char* contentType)
{
    if (m_msg==NULL||contentType==NULL)
        return false;
    
    int   mtypeLen = strchr(contentType,'/')-contentType;
    char *mSubType = strchr(contentType,'/') + 1;

    osip_content_type_t * content = osip_message_get_content_type(m_msg);
    if (content && content->type && content->subtype)
    {
        return   (strncasecmp(contentType, content->type,  mtypeLen)==0
              && (strcasecmp (mSubType   , content->subtype)==0));
    }
    return false;
}



// Extract a parameter value from a header which is in the format 
// "string;param1=value;param2=value..."
char* SipMessage::getHdrParamValue(const char* header, const char* paramName, char* paramValue, int buffSize)
{
    bzero(paramValue, buffSize);
    char* valStart = strstr(header,paramName);
    if (valStart)
    {
        valStart += strlen (paramName);
        int len = buffSize;
        char* valEnd;
        if ((valEnd = strchr(valStart, ';'))!=NULL && (valEnd-valStart)<buffSize)
            len = valEnd - valStart ;

        strlcpy(paramValue, valStart, len);
    }
    return paramValue;
}


// Enabling OSIP tracing
// ---------------------
// Step 1: Put in Controller::init
TRACE_INITIALIZE ( ( osip_trace_level_t ) 0, stdout ); // OSIP_FATAL
TRACE_INITIALIZE ( ( osip_trace_level_t ) 1, stdout ); // OSIP_BUG
TRACE_INITIALIZE ( ( osip_trace_level_t ) 2, stdout ); // OSIP_ERROR
TRACE_INITIALIZE ( ( osip_trace_level_t ) 3, stdout ); // OSIP_WARNING
TRACE_INITIALIZE ( ( osip_trace_level_t ) 4, stdout ); // OSIP_INFO1
TRACE_INITIALIZE ( ( osip_trace_level_t ) 5, stdout ); // OSIP_INFO2
TRACE_INITIALIZE ( ( osip_trace_level_t ) 6, stdout ); // OSIP_INFO3
TRACE_INITIALIZE ( ( osip_trace_level_t ) 7, stdout ); // OSIP_INFO4

TRACE_ENABLE_LEVEL ( ( osip_trace_level_t ) 0 );
TRACE_ENABLE_LEVEL ( ( osip_trace_level_t ) 1 );
TRACE_ENABLE_LEVEL ( ( osip_trace_level_t ) 2 );
TRACE_ENABLE_LEVEL ( ( osip_trace_level_t ) 3 );
TRACE_ENABLE_LEVEL ( ( osip_trace_level_t ) 4 );
TRACE_ENABLE_LEVEL ( ( osip_trace_level_t ) 5 );
TRACE_ENABLE_LEVEL ( ( osip_trace_level_t ) 6 );
TRACE_ENABLE_LEVEL ( ( osip_trace_level_t ) 7 );

// Step 2:
export EXTRA_DEFINES=-DENABLE_TRACE
find . -name '*.o' | xargs rm -rf 
make




   
//SIP DIALOG and DIALOG ID
//------------------------

bool Dialog::match ( const Event * e )
{
    osip_message_t* pMsg = const_cast<osip_message_t*>(e->m_pOsipMsg);
    int res = osip_dialog_match_as_uas ( m_pOsipDialog, pMsg );
    return ( res == 0 );
}


void Dialog::createId(const char* local_tag, const char* call_id, const char* remote_tag, dialog_id id, int maxlen)
{
    int len;
    len  = strlen(local_tag) + strlen(remote_tag)+ strlen(call_id) + 1;;
    len  = (len > maxlen)? maxlen : len;
    bzero(id, maxlen);

    snprintf ( id, len, "%s%s%s", local_tag, call_id, remote_tag  );
}


bool Dialog::getId(const osip_message_t * msg, dialog_id id, int maxlen )
{
    // from tag
    osip_generic_param_t *fromTag;
    if (osip_from_get_tag ( msg->from, &fromTag ) == -1)
        return false;

    // call id
    char* strCallid;
    osip_call_id_t *callId = osip_message_get_call_id ( msg );
    if (osip_call_id_to_str ( callId, &strCallid ) == -1 )
        return false;

    // to tag
    osip_generic_param_t *toTag;
    if (osip_from_get_tag ( msg->to, &toTag ) == -1)
        return false;

    Dialog::createId(toTag->gvalue, strCallid, fromTag->gvalue, id, maxlen);

    osip_free ( strCallid );
    return true;
}


// USING OSIP LISTS
// -----------------
osip_list_t * trList = (osip_list_t *)osip_malloc(sizeof (osip_list_t));
    if (osip_list_init ( trList ) != 0)
        return false;

osip_list_t * dlgList= (osip_list_t *)osip_malloc(sizeof (osip_list_t));
    if (osip_list_init ( dlgList ) != 0)
        return false;


Stack::postProcess()
{
    int pos = 0;
    while ( !osip_list_eol ( m_zombieTransactions, pos ) )
    {
        osip_transaction_t *tr = ( osip_transaction_t * ) osip_list_get ( m_zombieTransactions, pos );
        osip_list_remove ( m_zombieTransactions, pos );

        osip_transaction_free ( tr );
        pos++;
    }

    pos = 0;
    while ( !osip_list_eol ( m_zombieDialogs, pos ) )
    {
        Dialog *d = ( Dialog * ) osip_list_get ( m_zombieDialogs, pos );
        if (!d->getOwner())
        {
            osip_list_remove ( m_zombieDialogs, pos );
            delete d;
        }
        pos++;
    }
}




// FINDING A TRANSACTION
// ------------------------
Transaction::Transaction * find(const osip_message_t* m)
{
    osip_list_t * transactions;
    struct osip_mutex *mutx = NULL;
    if (MSG_IS_REQUEST(m))
    {
        if (0==strcmp(m->cseq->method, SIP_REQ_INVITE) || 0==strcmp(m->cseq->method, SIP_REQ_ACK))
        {
            transactions = Stack::obj()->osip()->osip_ist_transactions;
            mutx         = ist_fastmutex;
        }
        else
        {
            transactions = Stack::obj()->osip()->osip_nist_transactions;
            mutx         = nist_fastmutex;
        }
    }
    else
    {
        if (0 == strcmp (m->cseq->method, SIP_REQ_INVITE))
        {
            transactions = Stack::obj()->osip()->osip_ict_transactions;
            mutx         = ict_fastmutex;
        }
        else
        {
            transactions = Stack::obj()->osip()->osip_nict_transactions;
            mutx         = nict_fastmutex;
        }
    }

    OsipMutexHelper mh(mutx);

    osip_list_iterator_t iterator;
    osip_transaction_t * tr = (osip_transaction_t *) osip_list_get_first (transactions, &iterator);
    while (osip_list_iterator_has_elem (iterator))
    {
        Transaction* tran = (Transaction*)osip_transaction_get_your_instance(tr);;
        if (tran->matchRequest(m))
            return tran;

        tr = (osip_transaction_t *) osip_list_get_next (&iterator);
    }
    return NULL;
}



// MATCHING A REQUEST TO A TRANSACTION
// -----------------------------------
bool Transaction::matchRequest(const osip_message_t* req) const
{
    osip_generic_param_t *transBr = NULL;
    osip_generic_param_t *reqBr = NULL;

    osip_via_param_get_byname(m_pOsipTrans->topvia, (char*)HDR_PARAM_BRANCH, &transBr);

    osip_via_t *reqVia = (osip_via_t *)osip_list_get(req->vias, 0);

    if (reqVia)
        osip_via_param_get_byname(reqVia, (char*)HDR_PARAM_BRANCH, &reqBr);
    else
        return false;

    // match branch parameters
    if (reqBr != NULL && transBr != NULL && transBr->gvalue != NULL && reqBr->gvalue != NULL)
    {
        if ( 0 != strcmp(reqBr->gvalue, transBr->gvalue))
            return false;
    }

    // match sent-by
    char *reqHost   = via_get_host (reqVia);
    char *transHost = via_get_host (m_pOsipTrans->topvia);
    if ((reqHost == NULL || transHost == NULL))
        return false;
    if (strcmp (transHost, reqHost) != 0 )
        return false;

    const char *reqPort   = via_get_port (reqVia);
    const char *transPort = via_get_port (m_pOsipTrans->topvia);
    if (reqPort   == NULL)   reqPort = SIP_DEFAULT_PORT;
    if (transPort == NULL) transPort = SIP_DEFAULT_PORT;
    if (strcmp(reqPort, transPort) != 0)
        return false;


    // match method
    if (strcmp(req->cseq->method, SIP_REQ_CANCEL)==0 || strcmp(req->cseq->method, SIP_REQ_ACK)==0)
    {
        if ( strcmp (m_pOsipTrans->cseq->method, SIP_REQ_INVITE) != 0)
            return false;
    }
    else if (strcmp (m_pOsipTrans->cseq->method, req->cseq->method) != 0)
        return false;

    return true;
}




// Traversing list of contacts
sip_list_t* contacts = (osip_list_t*)resp.relContacts();
osip_list_iterator_t iterator;

osip_contact_t * cntc = (osip_contact_t *) osip_list_get_first (contacts, &iterator);
while (osip_list_iterator_has_elem (iterator))
{
    char* strCont;
    osip_contact_to_str(cntc, &strCont);
    MAND_LOG(DBG_SIP, "%s", strCont);
    cntc = (osip_contact_t *) osip_list_get_next (&iterator);
}



// Sending a Notify when Refere failed
Request notify;
notify.create(SIP_REQ_NOTIFY, m_dlgSrvr);
notify.AddBody("SIP/2.0 200 OK", "message/sipfrag");
notify.addHeader("Subscription-State", "terminated;reason=noresource");
Transaction::startClient(notify);
FSM_TRAN(&ReferCore::terminate);



IN
