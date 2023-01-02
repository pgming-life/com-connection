

/* this ALWAYS GENERATED file contains the RPC client stubs */


 /* File created by MIDL compiler version 8.01.0622 */
/* at Tue Jan 19 12:14:07 2038
 */
/* Compiler settings for RpcIdlRcv.idl:
    Oicf, W4, Zp8, env=Win32 (32b run), target_arch=X86 8.01.0622 
    protocol : dce , ms_ext, c_ext, robust
    error checks: allocation ref bounds_check enum stub_data 
    VC __declspec() decoration level: 
         __declspec(uuid()), __declspec(selectany), __declspec(novtable)
         DECLSPEC_UUID(), MIDL_INTERFACE()
*/
/* @@MIDL_FILE_HEADING(  ) */

#if !defined(_M_IA64) && !defined(_M_AMD64) && !defined(_ARM_)


#if _MSC_VER >= 1200
#pragma warning(push)
#endif

#pragma warning( disable: 4211 )  /* redefine extern to static */
#pragma warning( disable: 4232 )  /* dllimport identity*/
#pragma warning( disable: 4024 )  /* array to pointer mapping*/
#pragma warning( disable: 4100 ) /* unreferenced arguments in x86 call */

#pragma optimize("", off ) 

#include <string.h>

#include "RpcIdlRcv.h"

#define TYPE_FORMAT_STRING_SIZE   19                                
#define PROC_FORMAT_STRING_SIZE   113                               
#define EXPR_FORMAT_STRING_SIZE   1                                 
#define TRANSMIT_AS_TABLE_SIZE    0            
#define WIRE_MARSHAL_TABLE_SIZE   0            

typedef struct _RpcIdlRcv_MIDL_TYPE_FORMAT_STRING
    {
    short          Pad;
    unsigned char  Format[ TYPE_FORMAT_STRING_SIZE ];
    } RpcIdlRcv_MIDL_TYPE_FORMAT_STRING;

typedef struct _RpcIdlRcv_MIDL_PROC_FORMAT_STRING
    {
    short          Pad;
    unsigned char  Format[ PROC_FORMAT_STRING_SIZE ];
    } RpcIdlRcv_MIDL_PROC_FORMAT_STRING;

typedef struct _RpcIdlRcv_MIDL_EXPR_FORMAT_STRING
    {
    long          Pad;
    unsigned char  Format[ EXPR_FORMAT_STRING_SIZE ];
    } RpcIdlRcv_MIDL_EXPR_FORMAT_STRING;


static const RPC_SYNTAX_IDENTIFIER  _RpcTransferSyntax = 
{{0x8A885D04,0x1CEB,0x11C9,{0x9F,0xE8,0x08,0x00,0x2B,0x10,0x48,0x60}},{2,0}};


extern const RpcIdlRcv_MIDL_TYPE_FORMAT_STRING RpcIdlRcv__MIDL_TypeFormatString;
extern const RpcIdlRcv_MIDL_PROC_FORMAT_STRING RpcIdlRcv__MIDL_ProcFormatString;
extern const RpcIdlRcv_MIDL_EXPR_FORMAT_STRING RpcIdlRcv__MIDL_ExprFormatString;

#define GENERIC_BINDING_TABLE_SIZE   0            


/* Standard interface: RpcIdlRcv, ver. 1.0,
   GUID={0x8e2bdce4,0xef76,0xcced,{0x4f,0x67,0xeb,0x72,0x37,0xd2,0xb1,0x22}} */



static const RPC_CLIENT_INTERFACE RpcIdlRcv___RpcClientInterface =
    {
    sizeof(RPC_CLIENT_INTERFACE),
    {{0x8e2bdce4,0xef76,0xcced,{0x4f,0x67,0xeb,0x72,0x37,0xd2,0xb1,0x22}},{1,0}},
    {{0x8A885D04,0x1CEB,0x11C9,{0x9F,0xE8,0x08,0x00,0x2B,0x10,0x48,0x60}},{2,0}},
    0,
    0,
    0,
    0,
    0,
    0x00000000
    };
RPC_IF_HANDLE RpcIdlRcv_v1_0_c_ifspec = (RPC_IF_HANDLE)& RpcIdlRcv___RpcClientInterface;

extern const MIDL_STUB_DESC RpcIdlRcv_StubDesc;

static RPC_BINDING_HANDLE RpcIdlRcv__MIDL_AutoBindHandle;


CONTEXT_HANDLE_RCV OpenRcv( 
    /* [in] */ handle_t hBinding,
    /* [in] */ int result)
{

    CLIENT_CALL_RETURN _RetVal;

    _RetVal = NdrClientCall2(
                  ( PMIDL_STUB_DESC  )&RpcIdlRcv_StubDesc,
                  (PFORMAT_STRING) &RpcIdlRcv__MIDL_ProcFormatString.Format[0],
                  ( unsigned char * )&hBinding);
    return ( CONTEXT_HANDLE_RCV  )_RetVal.Pointer;
    
}


void SendRcv( 
    /* [in] */ CONTEXT_HANDLE_RCV hContext)
{

    NdrClientCall2(
                  ( PMIDL_STUB_DESC  )&RpcIdlRcv_StubDesc,
                  (PFORMAT_STRING) &RpcIdlRcv__MIDL_ProcFormatString.Format[40],
                  ( unsigned char * )&hContext);
    
}


void CloseRcv( 
    /* [out][in] */ CONTEXT_HANDLE_RCV *phContext)
{

    NdrClientCall2(
                  ( PMIDL_STUB_DESC  )&RpcIdlRcv_StubDesc,
                  (PFORMAT_STRING) &RpcIdlRcv__MIDL_ProcFormatString.Format[76],
                  ( unsigned char * )&phContext);
    
}


#if !defined(__RPC_WIN32__)
#error  Invalid build platform for this stub.
#endif
#if !(TARGET_IS_NT60_OR_LATER)
#error You need Windows Vista or later to run this stub because it uses these features:
#error   compiled for Windows Vista.
#error However, your C/C++ compilation flags indicate you intend to run this app on earlier systems.
#error This app will fail with the RPC_X_WRONG_STUB_VERSION error.
#endif


static const RpcIdlRcv_MIDL_PROC_FORMAT_STRING RpcIdlRcv__MIDL_ProcFormatString =
    {
        0,
        {

	/* Procedure OpenRcv */

			0x0,		/* 0 */
			0x48,		/* Old Flags:  */
/*  2 */	NdrFcLong( 0x0 ),	/* 0 */
/*  6 */	NdrFcShort( 0x0 ),	/* 0 */
/*  8 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 10 */	0x32,		/* FC_BIND_PRIMITIVE */
			0x0,		/* 0 */
/* 12 */	NdrFcShort( 0x0 ),	/* x86 Stack size/offset = 0 */
/* 14 */	NdrFcShort( 0x8 ),	/* 8 */
/* 16 */	NdrFcShort( 0x24 ),	/* 36 */
/* 18 */	0x44,		/* Oi2 Flags:  has return, has ext, */
			0x2,		/* 2 */
/* 20 */	0x8,		/* 8 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 22 */	NdrFcShort( 0x0 ),	/* 0 */
/* 24 */	NdrFcShort( 0x0 ),	/* 0 */
/* 26 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter result */

/* 28 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 30 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 32 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Return value */

/* 34 */	NdrFcShort( 0x30 ),	/* Flags:  out, return, */
/* 36 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 38 */	NdrFcShort( 0x2 ),	/* Type Offset=2 */

	/* Procedure SendRcv */

/* 40 */	0x0,		/* 0 */
			0x48,		/* Old Flags:  */
/* 42 */	NdrFcLong( 0x0 ),	/* 0 */
/* 46 */	NdrFcShort( 0x1 ),	/* 1 */
/* 48 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 50 */	0x30,		/* FC_BIND_CONTEXT */
			0x40,		/* Ctxt flags:  in, */
/* 52 */	NdrFcShort( 0x0 ),	/* x86 Stack size/offset = 0 */
/* 54 */	0x0,		/* 0 */
			0x0,		/* 0 */
/* 56 */	NdrFcShort( 0x24 ),	/* 36 */
/* 58 */	NdrFcShort( 0x0 ),	/* 0 */
/* 60 */	0x40,		/* Oi2 Flags:  has ext, */
			0x1,		/* 1 */
/* 62 */	0x8,		/* 8 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 64 */	NdrFcShort( 0x0 ),	/* 0 */
/* 66 */	NdrFcShort( 0x0 ),	/* 0 */
/* 68 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter hContext */

/* 70 */	NdrFcShort( 0x8 ),	/* Flags:  in, */
/* 72 */	NdrFcShort( 0x0 ),	/* x86 Stack size/offset = 0 */
/* 74 */	NdrFcShort( 0x6 ),	/* Type Offset=6 */

	/* Procedure CloseRcv */

/* 76 */	0x0,		/* 0 */
			0x48,		/* Old Flags:  */
/* 78 */	NdrFcLong( 0x0 ),	/* 0 */
/* 82 */	NdrFcShort( 0x2 ),	/* 2 */
/* 84 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 86 */	0x30,		/* FC_BIND_CONTEXT */
			0xe0,		/* Ctxt flags:  via ptr, in, out, */
/* 88 */	NdrFcShort( 0x0 ),	/* x86 Stack size/offset = 0 */
/* 90 */	0x0,		/* 0 */
			0x0,		/* 0 */
/* 92 */	NdrFcShort( 0x38 ),	/* 56 */
/* 94 */	NdrFcShort( 0x38 ),	/* 56 */
/* 96 */	0x40,		/* Oi2 Flags:  has ext, */
			0x1,		/* 1 */
/* 98 */	0x8,		/* 8 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 100 */	NdrFcShort( 0x0 ),	/* 0 */
/* 102 */	NdrFcShort( 0x0 ),	/* 0 */
/* 104 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter phContext */

/* 106 */	NdrFcShort( 0x118 ),	/* Flags:  in, out, simple ref, */
/* 108 */	NdrFcShort( 0x0 ),	/* x86 Stack size/offset = 0 */
/* 110 */	NdrFcShort( 0xe ),	/* Type Offset=14 */

			0x0
        }
    };

static const RpcIdlRcv_MIDL_TYPE_FORMAT_STRING RpcIdlRcv__MIDL_TypeFormatString =
    {
        0,
        {
			NdrFcShort( 0x0 ),	/* 0 */
/*  2 */	0x30,		/* FC_BIND_CONTEXT */
			0x30,		/* Ctxt flags:  out, ret, */
/*  4 */	0x0,		/* 0 */
			0x0,		/* 0 */
/*  6 */	0x30,		/* FC_BIND_CONTEXT */
			0x41,		/* Ctxt flags:  in, can't be null */
/*  8 */	0x0,		/* 0 */
			0x0,		/* 0 */
/* 10 */	
			0x11, 0x4,	/* FC_RP [alloced_on_stack] */
/* 12 */	NdrFcShort( 0x2 ),	/* Offset= 2 (14) */
/* 14 */	0x30,		/* FC_BIND_CONTEXT */
			0xe1,		/* Ctxt flags:  via ptr, in, out, can't be null */
/* 16 */	0x0,		/* 0 */
			0x0,		/* 0 */

			0x0
        }
    };

static const unsigned short RpcIdlRcv_FormatStringOffsetTable[] =
    {
    0,
    40,
    76
    };


static const MIDL_STUB_DESC RpcIdlRcv_StubDesc = 
    {
    (void *)& RpcIdlRcv___RpcClientInterface,
    MIDL_user_allocate,
    MIDL_user_free,
    &RpcIdlRcv__MIDL_AutoBindHandle,
    0,
    0,
    0,
    0,
    RpcIdlRcv__MIDL_TypeFormatString.Format,
    1, /* -error bounds_check flag */
    0x60001, /* Ndr library version */
    0,
    0x801026e, /* MIDL Version 8.1.622 */
    0,
    0,
    0,  /* notify & notify_flag routine table */
    0x1, /* MIDL flag */
    0, /* cs routines */
    0,   /* proxy/server info */
    0
    };
#pragma optimize("", on )
#if _MSC_VER >= 1200
#pragma warning(pop)
#endif


#endif /* !defined(_M_IA64) && !defined(_M_AMD64) && !defined(_ARM_) */

