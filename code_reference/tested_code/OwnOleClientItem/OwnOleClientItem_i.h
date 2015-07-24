/* this ALWAYS GENERATED file contains the definitions for the interfaces */


/* File created by MIDL compiler version 5.01.0164 */
/* at Fri Apr 07 17:42:40 2000
 */
/* Compiler settings for C:\work\OwnOleClientItem\OwnOleClientItem.idl:
    Oicf (OptLev=i2), W1, Zp8, env=Win32, ms_ext, c_ext
    error checks: allocation ref bounds_check enum stub_data 
*/
//@@MIDL_FILE_HEADING(  )


/* verify that the <rpcndr.h> version is high enough to compile this file*/
#ifndef __REQUIRED_RPCNDR_H_VERSION__
#define __REQUIRED_RPCNDR_H_VERSION__ 440
#endif

#include "rpc.h"
#include "rpcndr.h"

#ifndef __RPCNDR_H_VERSION__
#error this stub requires an updated version of <rpcndr.h>
#endif // __RPCNDR_H_VERSION__

#ifndef COM_NO_WINDOWS_H
#include "windows.h"
#include "ole2.h"
#endif /*COM_NO_WINDOWS_H*/

#ifndef __OwnOleClientItem_i_h__
#define __OwnOleClientItem_i_h__

#ifdef __cplusplus
extern "C"{
#endif 

/* Forward Declarations */ 

#ifndef __IMySink_FWD_DEFINED__
#define __IMySink_FWD_DEFINED__
typedef interface IMySink IMySink;
#endif 	/* __IMySink_FWD_DEFINED__ */


#ifndef __IMyAdviseSink_FWD_DEFINED__
#define __IMyAdviseSink_FWD_DEFINED__
typedef interface IMyAdviseSink IMyAdviseSink;
#endif 	/* __IMyAdviseSink_FWD_DEFINED__ */


#ifndef __ITestSink_FWD_DEFINED__
#define __ITestSink_FWD_DEFINED__
typedef interface ITestSink ITestSink;
#endif 	/* __ITestSink_FWD_DEFINED__ */


#ifndef __MySink_FWD_DEFINED__
#define __MySink_FWD_DEFINED__

#ifdef __cplusplus
typedef class MySink MySink;
#else
typedef struct MySink MySink;
#endif /* __cplusplus */

#endif 	/* __MySink_FWD_DEFINED__ */


#ifndef __MyAdviseSink_FWD_DEFINED__
#define __MyAdviseSink_FWD_DEFINED__

#ifdef __cplusplus
typedef class MyAdviseSink MyAdviseSink;
#else
typedef struct MyAdviseSink MyAdviseSink;
#endif /* __cplusplus */

#endif 	/* __MyAdviseSink_FWD_DEFINED__ */


#ifndef __TestSink_FWD_DEFINED__
#define __TestSink_FWD_DEFINED__

#ifdef __cplusplus
typedef class TestSink TestSink;
#else
typedef struct TestSink TestSink;
#endif /* __cplusplus */

#endif 	/* __TestSink_FWD_DEFINED__ */


/* header files for imported files */
#include "oaidl.h"
#include "ocidl.h"

void __RPC_FAR * __RPC_USER MIDL_user_allocate(size_t);
void __RPC_USER MIDL_user_free( void __RPC_FAR * ); 

#ifndef __IMySink_INTERFACE_DEFINED__
#define __IMySink_INTERFACE_DEFINED__

/* interface IMySink */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_IMySink;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("CFF2B2B4-0AEC-11D4-AFEF-00500413F521")
    IMySink : public IDispatch
    {
    public:
    };
    
#else 	/* C style interface */

    typedef struct IMySinkVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IMySink __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IMySink __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IMySink __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            IMySink __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            IMySink __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            IMySink __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            IMySink __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        END_INTERFACE
    } IMySinkVtbl;

    interface IMySink
    {
        CONST_VTBL struct IMySinkVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IMySink_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IMySink_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IMySink_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IMySink_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IMySink_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IMySink_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IMySink_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IMySink_INTERFACE_DEFINED__ */


#ifndef __IMyAdviseSink_INTERFACE_DEFINED__
#define __IMyAdviseSink_INTERFACE_DEFINED__

/* interface IMyAdviseSink */
/* [unique][helpstring][uuid][local][object] */ 


EXTERN_C const IID IID_IMyAdviseSink;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("CFF2B2B7-0AEC-11D4-AFEF-00500413F521")
    IMyAdviseSink : public IUnknown
    {
    public:
        virtual /* [helpstring] */ void STDMETHODCALLTYPE OnClose( void) = 0;
        
        virtual /* [helpstring] */ void STDMETHODCALLTYPE OnDataChange( 
            FORMATETC __RPC_FAR *pFormatetc,
            STGMEDIUM __RPC_FAR *pStgmed) = 0;
        
        virtual /* [helpstring] */ void STDMETHODCALLTYPE OnRename( 
            IMoniker __RPC_FAR *pmk) = 0;
        
        virtual /* [helpstring] */ void STDMETHODCALLTYPE OnSave( void) = 0;
        
        virtual /* [helpstring] */ void STDMETHODCALLTYPE OnViewChange( 
            DWORD dwAspect,
            LONG lindex) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IMyAdviseSinkVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IMyAdviseSink __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IMyAdviseSink __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IMyAdviseSink __RPC_FAR * This);
        
        /* [helpstring] */ void ( STDMETHODCALLTYPE __RPC_FAR *OnClose )( 
            IMyAdviseSink __RPC_FAR * This);
        
        /* [helpstring] */ void ( STDMETHODCALLTYPE __RPC_FAR *OnDataChange )( 
            IMyAdviseSink __RPC_FAR * This,
            FORMATETC __RPC_FAR *pFormatetc,
            STGMEDIUM __RPC_FAR *pStgmed);
        
        /* [helpstring] */ void ( STDMETHODCALLTYPE __RPC_FAR *OnRename )( 
            IMyAdviseSink __RPC_FAR * This,
            IMoniker __RPC_FAR *pmk);
        
        /* [helpstring] */ void ( STDMETHODCALLTYPE __RPC_FAR *OnSave )( 
            IMyAdviseSink __RPC_FAR * This);
        
        /* [helpstring] */ void ( STDMETHODCALLTYPE __RPC_FAR *OnViewChange )( 
            IMyAdviseSink __RPC_FAR * This,
            DWORD dwAspect,
            LONG lindex);
        
        END_INTERFACE
    } IMyAdviseSinkVtbl;

    interface IMyAdviseSink
    {
        CONST_VTBL struct IMyAdviseSinkVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IMyAdviseSink_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IMyAdviseSink_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IMyAdviseSink_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IMyAdviseSink_OnClose(This)	\
    (This)->lpVtbl -> OnClose(This)

#define IMyAdviseSink_OnDataChange(This,pFormatetc,pStgmed)	\
    (This)->lpVtbl -> OnDataChange(This,pFormatetc,pStgmed)

#define IMyAdviseSink_OnRename(This,pmk)	\
    (This)->lpVtbl -> OnRename(This,pmk)

#define IMyAdviseSink_OnSave(This)	\
    (This)->lpVtbl -> OnSave(This)

#define IMyAdviseSink_OnViewChange(This,dwAspect,lindex)	\
    (This)->lpVtbl -> OnViewChange(This,dwAspect,lindex)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring] */ void STDMETHODCALLTYPE IMyAdviseSink_OnClose_Proxy( 
    IMyAdviseSink __RPC_FAR * This);


void __RPC_STUB IMyAdviseSink_OnClose_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ void STDMETHODCALLTYPE IMyAdviseSink_OnDataChange_Proxy( 
    IMyAdviseSink __RPC_FAR * This,
    FORMATETC __RPC_FAR *pFormatetc,
    STGMEDIUM __RPC_FAR *pStgmed);


void __RPC_STUB IMyAdviseSink_OnDataChange_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ void STDMETHODCALLTYPE IMyAdviseSink_OnRename_Proxy( 
    IMyAdviseSink __RPC_FAR * This,
    IMoniker __RPC_FAR *pmk);


void __RPC_STUB IMyAdviseSink_OnRename_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ void STDMETHODCALLTYPE IMyAdviseSink_OnSave_Proxy( 
    IMyAdviseSink __RPC_FAR * This);


void __RPC_STUB IMyAdviseSink_OnSave_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ void STDMETHODCALLTYPE IMyAdviseSink_OnViewChange_Proxy( 
    IMyAdviseSink __RPC_FAR * This,
    DWORD dwAspect,
    LONG lindex);


void __RPC_STUB IMyAdviseSink_OnViewChange_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IMyAdviseSink_INTERFACE_DEFINED__ */


#ifndef __ITestSink_INTERFACE_DEFINED__
#define __ITestSink_INTERFACE_DEFINED__

/* interface ITestSink */
/* [unique][helpstring][uuid][object] */ 


EXTERN_C const IID IID_ITestSink;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("CFF2B2B9-0AEC-11D4-AFEF-00500413F521")
    ITestSink : public IUnknown
    {
    public:
    };
    
#else 	/* C style interface */

    typedef struct ITestSinkVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            ITestSink __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            ITestSink __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            ITestSink __RPC_FAR * This);
        
        END_INTERFACE
    } ITestSinkVtbl;

    interface ITestSink
    {
        CONST_VTBL struct ITestSinkVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ITestSink_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define ITestSink_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define ITestSink_Release(This)	\
    (This)->lpVtbl -> Release(This)


#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __ITestSink_INTERFACE_DEFINED__ */



#ifndef __OwnOleClientItemLib_LIBRARY_DEFINED__
#define __OwnOleClientItemLib_LIBRARY_DEFINED__

/* library OwnOleClientItemLib */
/* [helpstring][version][uuid] */ 


EXTERN_C const IID LIBID_OwnOleClientItemLib;

EXTERN_C const CLSID CLSID_MySink;

#ifdef __cplusplus

class DECLSPEC_UUID("CFF2B2B5-0AEC-11D4-AFEF-00500413F521")
MySink;
#endif

EXTERN_C const CLSID CLSID_MyAdviseSink;

#ifdef __cplusplus

class DECLSPEC_UUID("CFF2B2B8-0AEC-11D4-AFEF-00500413F521")
MyAdviseSink;
#endif

EXTERN_C const CLSID CLSID_TestSink;

#ifdef __cplusplus

class DECLSPEC_UUID("CFF2B2BA-0AEC-11D4-AFEF-00500413F521")
TestSink;
#endif
#endif /* __OwnOleClientItemLib_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */
EXTERN_C const CLSID CLSID_Instantiater;

#ifdef __cplusplus

class DECLSPEC_UUID("CFF2B2BA-0AEC-11D4-AFEF-00500413F523")
Instantiater;
#endif

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif
