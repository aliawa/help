//
// C++ Interface: b2buaRef2InvCore
//
// Description:
//
//
// Author: Ali Awais <aawais@edgewaternetworks.com>, (C) 2010
//
// Copyright: See COPYING file that comes with this distribution
//
//


namespace B2BUA
{


    class Refer2InviteCore : public ProxyBase
    {
        public:
            Refer2InviteCore(Dialog * dg1, Dialog * dg2);

        public:
            int initial          ( Event *e);
            int idle             ( Event *e);
            int getOfferFrom2    ( Event *e);
            int getAnswerFrom3   ( Event *e);
            int completeTransfer ( Event *e);

        private:
            sdp_message_t* processSDP(Dialog*, Dialog*, SipMessage& rcvdMsg);

        private:
            DialogManager * m_uaTable[2];
            DialogPtr       m_dialogs[4];
    };
}

