/* this file contains the actual definitions of */
/* the IIDs and CLSIDs */

/* link this file in with the server and any clients */


/* File created by MIDL compiler version 5.01.0164 */
/* at Fri Apr 07 17:42:40 2000
 */
/* Compiler settings for C:\work\OwnOleClientItem\OwnOleClientItem.idl:
    Oicf (OptLev=i2), W1, Zp8, env=Win32, ms_ext, c_ext
    error checks: allocation ref bounds_check enum stub_data 
*/
//@@MIDL_FILE_HEADING(  )
#ifdef __cplusplus
extern "C"{
#endif 


#ifndef __IID_DEFINED__
#define __IID_DEFINED__

typedef struct _IID
{
    unsigned long x;
    unsigned short s1;
    unsigned short s2;
    unsigned char  c[8];
} IID;

#endif // __IID_DEFINED__

#ifndef CLSID_DEFINED
#define CLSID_DEFINED
typedef IID CLSID;
#endif // CLSID_DEFINED

const IID IID_IMySink = {0xCFF2B2B4,0x0AEC,0x11D4,{0xAF,0xEF,0x00,0x50,0x04,0x13,0xF5,0x21}};


const IID IID_IMyAdviseSink = {0xCFF2B2B7,0x0AEC,0x11D4,{0xAF,0xEF,0x00,0x50,0x04,0x13,0xF5,0x21}};


const IID IID_ITestSink = {0xCFF2B2B9,0x0AEC,0x11D4,{0xAF,0xEF,0x00,0x50,0x04,0x13,0xF5,0x21}};


const IID LIBID_OwnOleClientItemLib = {0xCFF2B2B2,0x0AEC,0x11D4,{0xAF,0xEF,0x00,0x50,0x04,0x13,0xF5,0x21}};


const CLSID CLSID_MySink = {0xCFF2B2B5,0x0AEC,0x11D4,{0xAF,0xEF,0x00,0x50,0x04,0x13,0xF5,0x21}};


const CLSID CLSID_MyAdviseSink = {0xCFF2B2B8,0x0AEC,0x11D4,{0xAF,0xEF,0x00,0x50,0x04,0x13,0xF5,0x21}};


const CLSID CLSID_TestSink = {0xCFF2B2BA,0x0AEC,0x11D4,{0xAF,0xEF,0x00,0x50,0x04,0x13,0xF5,0x21}};


#ifdef __cplusplus
}
#endif

