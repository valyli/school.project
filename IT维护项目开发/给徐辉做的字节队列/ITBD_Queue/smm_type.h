/*****************************************************************************

  Copyright (c), 2002-2005, QiDongKai Corp. All rights reserved.
  
  File name:     smm_type.h

  Author:        xuhui

  Version:       v1.0

  Date:          2003/03/25

  Description:   Basic System Type Definitions

  Others:

  Function List:

  History:
    1. Date:           2003/03/25
       Author:         xuhui
       Modification:   First Created

 *****************************************************************************/


#ifndef __SMM_TYPE_H__
#define __SMM_TYPE_H__
#include <winsock2.h>

#ifdef  __cplusplus
extern "C" {
#endif

/* basic data type definition */
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

/* basic constant definition */
#ifdef TRUE
#undef TRUE
#endif
#define TRUE	        ((SMM_BOOL)1)

#ifdef FALSE
#undef FALSE
#endif
#define FALSE	        ((SMM_BOOL)0)

#ifdef NULL
#undef NULL
#endif
#define NULL            0

/* System Management Module basic error code definition */
#define SMM_OK          0
#define SMM_ERR         (-1)


#ifdef  __cplusplus
}
#endif

#endif
