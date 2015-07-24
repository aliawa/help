// ---------------------------------------------------
//
//    Accessing a memory location with a struct
//    that has members smaller than a byte..
//

#include "stdafx.h"
#include <stdio.h>

// intel is little endian
#define LITTLE_ENDIAN


/*
 * Start with standard bit-sized declarations.
 */
typedef unsigned char       u8_t;
typedef unsigned short int  u16_t;
typedef unsigned long int   u32_t;




// The structure containing bit fields

#ifdef LITTLE_ENDIAN

typedef struct 
{
    u8_t  payloadType   :7;
    u8_t  marker        :1;
    u8_t  noOfFrames    :7;
    u8_t  lastIsSilence :1;
    u16_t reserved;

} RTP_BuffElementInfo_t;

#elif defined BIG_ENDIAN

typedef struct 
{
    u16_t reserved;
    u8_t  lastIsSilence :1;
    u8_t  noOfFrames    :7;
    u8_t  marker        :1;
    u8_t  payloadType   :7;

} RTP_BuffElementInfo_t;




//
// test structure : we will access its "ext" member with our 
// bit field structure defined above
//
struct netbuf {
	struct netbuf *next;		/* Pointer to the next netbuf in a list */
	u16_t pos;			        /* Index of the current read/write position */
	u16_t start;			    /* Start of the netbuf (index of the first valid octet of data) */
	u16_t end;			        /* End of the netbuf (index of the next octet after the last octet of data) */
	u32_t ext;			        /* Extension argument - may be used for any purpose but not across layers! */
};



//
// Here's how we will access the "ext" member of the netbuf structure
//
#define RTP_GET_PAYLOAD_TYPE(nb)  (((RTP_BuffElementInfo_t*)(&(nb->ext)))->payloadType)
#define RTP_IS_MARKER_BIT_SET(nb) (((RTP_BuffElementInfo_t*)(&(nb->ext)))->marker)
#define RTP_FRAMES_IN_NETBUF(nb)  (((RTP_BuffElementInfo_t*)(&(nb->ext)))->noOfFrames)  
#define RTP_IS_LAST_SILENCE(nb)   (((RTP_BuffElementInfo_t*)(&(nb->ext)))->lastIsSilence)   




int main(int argc, char* argv[])
{
    netbuf* nb = new netbuf;
    

    // stuff values in the ext member of nb

    // (1) payload =4 and marker set
    nb->ext = 0x84;

    // (2) no of frames is 5;
    nb->ext |= (5<<8);

    // (3) set lastIsSilence
    nb->ext |= 0x8000;

    // (4) nb->ext should now be 0x8584

    // now examine the values;
    u32_t* pN = &(nb->ext);
    RTP_BuffElementInfo_t* pInfo = (RTP_BuffElementInfo_t*)pN ;

    int x = RTP_GET_PAYLOAD_TYPE(nb);       // should be 4
    x = RTP_IS_MARKER_BIT_SET(nb);          // should be 1
    x = RTP_FRAMES_IN_NETBUF(nb);           // should be 5
    x = RTP_IS_LAST_SILENCE(nb);            // should be 1


    return 1;
}
