/**
 * @file b2buaRef2InvCore.cpp
 *
 * @brief Implements logic for handling refer to re-invite conversion
 *
 */

#include "b2buaCore.h"
#include "b2bua.h"

namespace B2BUA
{
    enum {CLNT2=0, CLNT3, SERV2, SERV3};

    // TODO: Make part of proxybase
    void ackDialog(DialogPtr dg)
    {
        Request ack;
        ack.create(SIP_REQ_ACK, dg);
        Transport::send(ack);
    }


    Refer2InviteCore::Refer2InviteCore(Dialog * dlgReferer, Dialog * dlgReplaces) : ProxyBase((FsmState)&Refer2InviteCore::idle)
    {
        bzero(m_dialogs, sizeof(m_dialogs));
        bzero(m_uaTable, sizeof(m_uaTable));

        m_dialogs[SERV2] = dlgReferer;
        m_dialogs[SERV3] = dlgReplaces;

        if (dlgReferer != NULL && dlgReplaces != NULL)
        {
            m_dialogs[CLNT2] = dlgReferer->getPartner();
            m_dialogs[CLNT3] = dlgReplaces->getPartner();
        }
    }





    sdp_message_t* Refer2InviteCore::processSDP(Dialog*, Dialog*, SipMessage& rcvdMsg)
    {
        // for now only handling the case where phone2 and phone3 are
        // reachable from the same interface so we dont need to
        // change the SDP.

        return rcvdMsg.getSdp();
    }



    //            Event                         Dialogs
    // ----------------------------------   --------------
    // 1. Phone1 calls phone2               SERV2 & CLNT2
    // 2. Phone1 puts phone2 on hold
    // 3. Phone1 calls phone3               SERV3 & CLNT3
    // 4. Phone1 refers phone2 to phone3
    // ----------------------------------   -------------

    int  Refer2InviteCore::idle ( Event *e)
    {
        MAND_LOG(DBG_SIP,  "state:idle: event: %s", e->toString());

        switch (e->m_type)
        {
            case EVT_ENTER:
                EWN_NEW(m_uaTable[CLNT2], UAClientCore(this/*, (int)CLNT2*/));
                EWN_NEW(m_uaTable[CLNT3], UAClientCore(this/*, (int)CLNT3*/));
                m_uaTable[CLNT2]->init();
                m_uaTable[CLNT3]->init();
                return 0;

            case EVT_EXIT : return 0;
            default       : return 1;

            case EVT_NEW_REFER:
            {
                if (m_dialogs[CLNT2] == NULL || m_dialogs[CLNT3] == NULL ||
                    m_uaTable[CLNT2] == NULL || m_uaTable[CLNT3] == NULL )
                    return 1;

                Request invite2;
                invite2.create(SIP_REQ_INVITE, m_dialogs[CLNT2]);
                //Transaction::startClient(invite2, m_uaTable[CLNT2]);

                FSM_TRAN(&Refer2InviteCore::getOfferFrom2);
                return 0;
            }
        }
    }


    int  Refer2InviteCore::getOfferFrom2 ( Event *e)
    {
        MAND_LOG(DBG_SIP,  "state:getOfferFrom2: event: %s", e->toString());
        switch (e->m_type)
        {
            case EVT_ENTER: return 0;
            case EVT_EXIT : return 0;
            default       : return 1;
            case EVT_INT_CALL_ANSWERED:
            {
                // it should be a response from Phone2
                if (e->m_fsm != m_uaTable[CLNT2])
                    return 1;

                // Now we take the sdp from phone2 and send
                // it to phone3
                Response rcvdMsg(e->m_pOsipMsg);
                Request invite3;
                invite3.create(SIP_REQ_INVITE, m_dialogs[CLNT3]);

//                SdpMsg sdp(processSDP(m_dialogs[CLNT2], m_dialogs[CLNT3], rcvdMsg));

//                invite3.AddSdp(sdp);

//                Transaction::startClient(invite3, m_uaTable[CLNT3]);

                FSM_TRAN(&Refer2InviteCore::getAnswerFrom3);
                return 0;
            }
        }
    }


    int  Refer2InviteCore::getAnswerFrom3 ( Event *e)
    {
        MAND_LOG(DBG_SIP,  "state:getAnswerFrom3: event: %s", e->toString());
        switch (e->m_type)
        {
            case EVT_ENTER: return 0;
            case EVT_EXIT : return 0;
            default       : return 1;
            case EVT_INT_CALL_ANSWERED:
            {
                // it should be a response from Phone3
                if (e->m_fsm != m_uaTable[CLNT3])
                    return 1;

                // Take the sdp from the response of phone3
                // and send it to phone2
                Response rcvdResp(e->m_pOsipMsg);
                Request ack2;
                ack2.create(SIP_REQ_ACK, m_dialogs[CLNT2]);

//                 SdpMsg sdp(processSDP(m_dialogs[CLNT2], m_dialogs[CLNT3], rcvdResp));
//                 ack2.AddSdp(sdp);

                Transport::send(ack2);

                ackDialog(m_dialogs[CLNT3]);

                FSM_TRAN(&Refer2InviteCore::completeTransfer);
                return 0;
            }
        }
    }

    int  Refer2InviteCore::completeTransfer ( Event *e)
    {
        MAND_LOG(DBG_SIP,  "state:completeTransfer: event: %s", e->toString());
        switch (e->m_type)
        {
            case EVT_ENTER:
            {
                Request notify;
                notify.create(SIP_REQ_NOTIFY, m_dialogs[SERV2]);
                notify.AddBody("SIP/2.0 200 OK", "message/sipfrag");
                notify.addHeader("Subscription-State", "terminated;reason=noresource");
//                Transaction::startClient(notify, this);
                return 0;
            }
            case EVT_2XX_RCVD:
            {
                //closeDialog(m_dialogs[SERV2]);
                //closeDialog(m_dialogs[SERV3]);
                m_dialogs[SERV2]->close(this);
                m_dialogs[SERV3]->close(this);


                FSM_TRAN(&Refer2InviteCore::idle);
                return 0;
            }

            case EVT_EXIT : return 0;
            default       : return 1;
        }
    }

}


