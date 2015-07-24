

/**
 * @file html_forms_api.c
 *
 * @brief API for writing HTML forms
 *
 */


#include "html_forms_api.h"
#include "defines.h"

#include <string.h>
#include <stdarg.h>
#include <lib_log.h>


int HTML_SELECT_POPUP = 0;
int HTML_SELECT_MULTI = 1;
const char* const HTML_INPUT_RADIO      = "radio";
const char* const HTML_INPUT_TEXT       = "text";
const char* const HTML_INPUT_CHECK      = "checkbox";
const char* const HTML_INPUT_SUBMIT     = "submit";
const char* const HTML_INPUT_RESET      = "reset";
const char* const HTML_INPUT_PASSWORD   = "password";

const char* const SPACER                = "&nbsp;";



// ----------------------------------------------------------------------------
//
//                                   UTILITY
//
// ----------------------------------------------------------------------------


char* unquote(char* str, char stripch) {
    if (str != NULL) {
        // Strip off the quotation marks
        if ((*str == stripch) && (*(str + (strlen(str) - 1)) == stripch)) {
            *(str + (strlen(str) - 1)) = '\0';
            str++;
        }
    }
    return str;
}


const char* getCellClass(int id)
{
    const char* cellclasses[]={"maxwidth", "lalign", "ralign"};
    if (id > sizeof(cellclasses))
        id = 0;
    return cellclasses[id];
}



// ----------------------------------------------------------------------------
//
//                                   SELECT
//
// ----------------------------------------------------------------------------



void HtmlSelect_init(HtmlSelect* pSel, int type, char* name, List* values)
{
    bzero(pSel, sizeof(HtmlSelect));
    pSel->type = type;
    pSel->name = name;
    pSel->values = values;
}



char* HtmlSelect_toStr(HtmlSelect* pSel, char* buff, int buffSz)
{
    Buffer_t buffr={0,0};
    char* buffPtr = buff;

    int ret = snprintf(buff, buffSz, "<select name='%s'", pSel->name);
    buffPtr+=ret;
    buffSz-=(ret>0)? ret:buffSz;

    if (pSel->size && buffSz){
        ret = snprintf(buffPtr, buffSz, " size='%d'", pSel->size);
        buffPtr+=ret;
        buffSz-=(ret>0)? ret:buffSz;
    }

    if (pSel->style && buffSz){
        ret = snprintf(buffPtr, buffSz, " style='%s'", pSel->style);
        buffPtr+=ret;
        buffSz-=(ret>0)? ret:buffSz;
    }

    if (pSel->type == HTML_SELECT_MULTI){
        if (buffSz > 11){
            strncat(buff, " MULTIPLE>\n", buffSz);
            buffPtr+=11;
            buffSz-=11;
        }
    } else {
        if (buffSz > 2) {
            strncat(buff, ">\n", buffSz);
            buffPtr+=2;
            buffSz-=2;
        }
    }

    if (buffSz > 1){
        buffr.ptr = buffPtr;
        buffr.size = buffSz;
        list_For_Each(pSel->values, (void*)(&buffr), fn_appendSelOption);
        buffSz = buffr.size;
        buffPtr= buffr.ptr;
    }

    if (buffSz > 10){
        strncat(buffPtr, "</select>\n", buffSz);
    }
    return buff;
}



void fn_appendSelOption(ListNode* n, void* data)
{
    SelectElement* el = (SelectElement*)n;
    Buffer_t* buff = (Buffer_t*)data;

    if (buff->size > 0){
        int ret = snprintf(buff->ptr, buff->size, "  <option value=\"%d\" %s>%s</option>\n",
                           el->value,
                           (el->selected)? " SELECTED": "",
                           el->display);
        buff->ptr+=ret;
        buff->size-= (ret >0)? ret:buff->size;
    }
}


// Load a list of HTML SELECT OPTIONs from config file
// Will load all values where the name matches the pattern
// formed by "fmt" and an index. So if fmt="PBX%d"
// then it will load PBX0, PBX1 ...
// sel determines which element should be selected. If
// no elements are to be selected then sel should be -1

// IMPROVEMENTS:
// HTML Select multi can have multiple options selected
// more flexible patterns.
void loadList(Q_Entry* conf, List* var_didLst, const char* fmt, int sel)
{
    int i = 0;
    char* did = qfValue(conf, (char*)fmt, i);
    for (; did; ++i, did = qfValue(conf, (char*)fmt, i)) {
        SelectElement *el;
        EWN_MALLOC(SelectElement*, el, sizeof(SelectElement));
        el->value = i;
        el->display = unquote(did, '"');
        if (i==sel){
            el->selected=TRUE;
        } else {
            el->selected=FALSE;
        }
        list_ChainNodeLast(var_didLst, (ListNode*)el);
    }
}



// ----------------------------------------------------------------------------
//
//                                   INPUT
//
// ----------------------------------------------------------------------------

void HtmlInput_init(HtmlInput* pInp, const char* type, char* name, char* value)
{
    bzero(pInp, sizeof(HtmlInput));
    pInp->type = (char*)type;
    pInp->name = name;
    pInp->value = value;
}



char* HtmlInput_toStr(HtmlInput* pInp, char* buff, int buffSz)
{
    char* buffPtr = buff;
    int len;
    if (pInp->value == NULL){
        pInp->value = EMPTY_STR;
    }
    int ret = snprintf(buffPtr, buffSz, "<input type='%s' name='%s' value='%s'", pInp->type, pInp->name, pInp->value);
    buffSz-= (ret>0)? ret:buffSz;
    buffPtr+=ret;
    len = strlen(buff);

    if (pInp->maxlen){
        ret = snprintf(buffPtr, buffSz, " maxlength='%d'", pInp->maxlen);
        buffSz-= (ret>0)? ret:buffSz;
        buffPtr+=ret;
    }

    if (pInp->checked && buffSz>8){
        strncat(buffPtr, " checked", buffSz);
        buffSz-= 8;
        buffPtr+=8;
    }

    if (pInp->readonly && buffSz>8){
        strncat(buffPtr, " readonly", buffSz);
        buffSz-= 8;
        buffPtr+=8;
    }

    if (pInp->disabled && buffSz>8){
        strncat(buffPtr, " disabled", buffSz);
        buffSz-= 8;
        buffPtr+=8;
    }

    if (pInp->onChange && buffSz>strlen(pInp->onChange)){
        ret = snprintf(buffPtr, buffSz, " onChange=\"%s\"", pInp->onChange);
        buffSz-= ret;
        buffPtr+=ret;
    }

    if (buffSz >1){
        strncat(buffPtr, ">", buffSz);
        buffSz-= 1;
        buffPtr+=1;
    }

    return buff;
}






// ----------------------------------------------------------------------------
//
//                                   SPAN
//
// ----------------------------------------------------------------------------


void HtmlSpan_init(HtmlSpan* pSpn, const char* cls, char* value)
{
    bzero(pSpn, sizeof(HtmlSpan));
    pSpn->cls = cls;
    pSpn->value = value;
}


char* HtmlSpan_toStr(HtmlSpan* pSpn, char* buff, int buffSz)
{
    if (pSpn->value == NULL){
        pSpn->value = EMPTY_STR;
    }
    snprintf(buff, buffSz, "<span class='%s'>%s</span>", pSpn->cls, pSpn->value);
    return buff;
}





// ----------------------------------------------------------------------------
//
//                                   TEXT
//
// ----------------------------------------------------------------------------


char* HtmlText_toStr(const char* txt, char* buff, int buffSz)
{
    snprintf(buff, buffSz, "%s", txt);
    return buff;
}





// ----------------------------------------------------------------------------
//
//                                   IMG
//
// ----------------------------------------------------------------------------



void HtmlImg_init(HtmlImg* pImg, const char* cls, const char* src)
{
    bzero(pImg, sizeof(HtmlImg));
    pImg->cls = cls;
    pImg->src = src;
}


char* HtmlImg_toStr(HtmlImg* pImg, char* buff, int buffSz)
{
    snprintf(buff, buffSz, "<img class='%s' src='%s'/>", pImg->cls, pImg->src);
    return buff;
}



// ----------------------------------------------------------------------------
//
//                                  FORM LAYOUT
//
// ----------------------------------------------------------------------------


// The format is %<colspan><class><conversion>
void print_tabl_row(const char* class, const char* fmt, ...)
{
    va_list ap;
    va_start(ap, fmt);
    const char* p;
    char buff[1024];
    int col=0;

    printf ("<tr class=%s>\n", class);

    for (p=fmt; *p!='\0'; p++, col++) {
        if (*p == '%'){
            int a =0;
            if (col!=0){
                printf("  </td>\n");
            }

            printf ("  <td");
            for (a=0; isdigit(*(p+1)); ++a){
                if (a==0)
                    printf (" colspan='%c'", *++p);
                else if (a==1)
                    printf (" class='%s'", getCellClass(*++p));
            }
            printf (">\n");
            continue;
        }

        switch (*p)
        {
            case 'i':
                HtmlInput_toStr(va_arg(ap, HtmlInput *), buff, sizeof(buff));
                break;
            case 's':
                HtmlSelect_toStr(va_arg(ap, HtmlSelect *), buff, sizeof(buff));
                break;
            case 'n':
                HtmlSpan_toStr(va_arg(ap, HtmlSpan *), buff, sizeof(buff));
                break;
            case 'm':
                HtmlImg_toStr(va_arg(ap, HtmlImg *), buff, sizeof(buff));
                break;
            default:
                HtmlText_toStr(va_arg(ap, char *), buff, sizeof(buff));

        }
        printf("    %s\n", buff);
    }
    if (col){
        printf("  </td>\n");
    }
    printf ("</tr>\n");
    va_end(ap);
}




void print_styles()
{
    // IE does not support display:table-cell therefore for IE
    // we will use display:inline-block
    char*  isIE = strstr(qGetenvDefault(EMPTY_STR, "HTTP_USER_AGENT"), "MSIE");

    printf("<style type=\"text/css\">\n"
            "  td.maxwidth{ width:100%% }\n"
            "  td.fieldLabel { white-space:nowrap }\n"
            "  td.helpText { font-size: small }\n"
            "  span.notice { color:red; display:%s}\n"
            "  span.helpText { font-size: 10pt}\n"
            "  span.info { font-style: italic; font-weight:bold}\n"
            "  span.Heading { font-style: italic; font-weight:bold}\n"
            "  tr.notice td { border: 1px solid grey;  }\n"
            "  tr.notice img { float:left; position:relative; top:5px }\n"
            "  tr.info img { float:left; position:relative; top:5px}\n"
            "  tr.info td { vertical-align: bottom}\n"
            "  tr.norm { color:black }\n"
            "  tr.Heading td { border-bottom:medium groove lightgrey; vertical-align:bottom}\n"
            "  tr.Heading td { height:60px; }\n"
            "</style>\n",
          (isIE)?"inline-block":"table-cell");
}






