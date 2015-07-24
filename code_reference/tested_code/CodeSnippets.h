// ----------------------------------------------------------------------
//                              CODE SNIPPETS
// ----------------------------------------------------------------------



// ----------------------------------------------------------------------
//                              USING PRAGMA
//                Without pragma the sizeof(udpChannel_t) = 12
//                   With pragma(1) sizeof(udpChannel_t) = 10
//
// ----------------------------------------------------------------------

#pragma pack (1)
typedef struct udpSlotStruct
{
    u32_t udpSendToIpAddr;			    // Destination IP Address for this msg
    u16_t udpSendToPort;			    // Port to send this msg to
    u16_t udpReplyToPort;			    // Port to expect reply from for this msg
    u16_t handlerStateMachine;			// The state machine that will handle incoming messages for this slot
}udpChannel_t;
