/*****************************************************************************

  Copyright (c), 2002-2005, QiDongKai Corp. All rights reserved.

  File name:     smm_type.h

  Author:        Yang Wei

  Version:       v1.0

  Date:          2003/03/14

  Description:   Basic System Type Definitions

  Others:

  History:
    1. Date:           2003/03/14
       Author:         Yang Wei
       Modification:   First Created

 *****************************************************************************/

#ifndef __SMM_TYPE_H__
#define __SMM_TYPE_H__

#ifdef  __cplusplus
extern "C" {
#endif


/*****************************************************************************
 Check Opertion System Configuration File
 *****************************************************************************/

#ifndef __SMM_OS_H__
#error "Please include os config file smm_os.h first!"
#endif


/*****************************************************************************
 Basic Data Type Definition
 *****************************************************************************/

typedef void            SMM_VOID;
typedef char            SMM_CHAR;
typedef unsigned char   SMM_UCHAR;
typedef signed   short  SMM_WCHAR;
typedef short           SMM_SHORT;
typedef unsigned short  SMM_USHORT;
typedef long            SMM_LONG;
typedef unsigned long   SMM_ULONG;

typedef int             SMM_INT;
typedef unsigned int    SMM_UINT;

typedef signed char     SMM_INT8;
typedef unsigned char   SMM_UINT8;
typedef signed   short  SMM_INT16;
typedef unsigned short  SMM_UINT16;
typedef signed   long   SMM_INT32;
typedef unsigned long   SMM_UINT32;

typedef int             SMM_BOOL;

typedef float           SMM_FLOAT;
typedef double          SMM_DOUBLE;

typedef union
{
    #if( SMM_BYTE_ORDER == SMM_LITTLE_ENDIAN )
    struct
    {
        SMM_UINT32  m_ui32Lo;
        SMM_INT32   m_i32Hi;
    };
    #else
    struct
    {
        SMM_INT32   m_i32Hi;
        SMM_UINT32  m_ui32Lo;
    };
    #endif
} SMM_INT64;

typedef union
{
    #if( SMM_BYTE_ORDER == SMM_LITTLE_ENDIAN )
    struct
    {
        SMM_UINT32  m_ui32Lo;
        SMM_UINT32  m_ui32Hi;
    };
    #else
    struct
    {
        SMM_UINT32  m_ui32Hi;
        SMM_UINT32  m_ui32Lo;
    };
    #endif
} SMM_UINT64;

/* 64-bit integer evaluation macro, application should use these notations */
#define SMM_I64_HI( i )         ( ( SMM_INT32 )( ( i ).m_i32Hi ) )
#define SMM_U64_HI( i )         ( ( SMM_UINT32 )( ( i ).m_ui32Hi ) )
#define SMM_I64_LO( i )         ( ( SMM_UINT32 )( ( i ).m_ui32Lo ) )
#define SMM_U64_LO( i )         ( ( SMM_UINT32 )( ( i ).m_ui32Lo ) )
#define SMM_I64_HSET( i, h )    ( i ).m_i32Hi = ( SMM_INT32 )( h )
#define SMM_U64_HSET( i, h )    ( i ).m_ui32Hi = ( SMM_UINT32 )( h )
#define SMM_I64_LSET( i, l )    ( i ).m_ui32Lo = ( SMM_UINT32 )( l )
#define SMM_U64_LSET( i, l )    ( i ).m_ui32Lo = ( SMM_UINT32 )( l )
#define SMM_I64_SET( i, h, l )  { SMM_I64_HSET( i, h ); SMM_I64_LSET( i, l ); }
#define SMM_U64_SET( i, h, l )  { SMM_U64_HSET( i, h ); SMM_U64_LSET( i, l ); }


/*****************************************************************************
 Basic Constant Definition
 *****************************************************************************/

#ifdef TRUE
#undef TRUE
#endif
#define TRUE            ((SMM_BOOL)1)

#ifdef FALSE
#undef FALSE
#endif
#define FALSE           ((SMM_BOOL)0)

#ifdef NULL
#undef NULL
#endif
#define NULL            0


/*****************************************************************************
 Basic Error Code Definition, Should <= 0
 *****************************************************************************/

#define SMM_OK                  0
#define SMM_ERR                 (-1)
#define SMM_ERR_BAD_PARA        (-2)
#define SMM_ERR_NO_MEM          (-3)


#ifdef  __cplusplus
}
#endif

#endif
