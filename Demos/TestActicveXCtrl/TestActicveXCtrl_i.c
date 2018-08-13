

/* this ALWAYS GENERATED file contains the IIDs and CLSIDs */

/* link this file in with the server and any clients */


 /* File created by MIDL compiler version 7.00.0555 */
/* at Mon Aug 13 13:14:17 2018
 */
/* Compiler settings for .\TestActicveXCtrl.idl:
    Oicf, W1, Zp8, env=Win32 (32b run), target_arch=X86 7.00.0555 
    protocol : dce , ms_ext, c_ext, robust
    error checks: stub_data 
    VC __declspec() decoration level: 
         __declspec(uuid()), __declspec(selectany), __declspec(novtable)
         DECLSPEC_UUID(), MIDL_INTERFACE()
*/
/* @@MIDL_FILE_HEADING(  ) */

#pragma warning( disable: 4049 )  /* more than 64k source lines */


#ifdef __cplusplus
extern "C"{
#endif 


#include <rpc.h>
#include <rpcndr.h>

#ifdef _MIDL_USE_GUIDDEF_

#ifndef INITGUID
#define INITGUID
#include <guiddef.h>
#undef INITGUID
#else
#include <guiddef.h>
#endif

#define MIDL_DEFINE_GUID(type,name,l,w1,w2,b1,b2,b3,b4,b5,b6,b7,b8) \
        DEFINE_GUID(name,l,w1,w2,b1,b2,b3,b4,b5,b6,b7,b8)

#else // !_MIDL_USE_GUIDDEF_

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

#define MIDL_DEFINE_GUID(type,name,l,w1,w2,b1,b2,b3,b4,b5,b6,b7,b8) \
        const type name = {l,w1,w2,{b1,b2,b3,b4,b5,b6,b7,b8}}

#endif !_MIDL_USE_GUIDDEF_

MIDL_DEFINE_GUID(IID, LIBID_TestActicveXCtrlLib,0x2ABD00E4,0xF012,0x43F4,0x88,0x68,0x3B,0x75,0x6A,0x37,0x9D,0xD0);


MIDL_DEFINE_GUID(IID, DIID__DTestActicveXCtrl,0xB38B780A,0x1291,0x400C,0x88,0xB2,0x00,0x48,0xAB,0x62,0x9F,0x77);


MIDL_DEFINE_GUID(IID, DIID__DTestActicveXCtrlEvents,0xA4633AC6,0x1B7D,0x4B63,0xB8,0xED,0x1C,0x6F,0xB2,0x64,0xBB,0x74);


MIDL_DEFINE_GUID(CLSID, CLSID_TestActicveXCtrl,0x648573AD,0x951F,0x415F,0x8F,0xBD,0xF4,0x1F,0x73,0x00,0xCB,0x99);

#undef MIDL_DEFINE_GUID

#ifdef __cplusplus
}
#endif



