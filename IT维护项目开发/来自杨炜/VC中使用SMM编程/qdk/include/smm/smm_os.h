/*****************************************************************************

  Copyright (c), 2002-2005, QiDongKai Corp. All rights reserved.

  File name:     smm_os.h

  Author:        Yang Wei

  Version:       v1.0

  Date:          2003/03/14

  Description:   This file config operation system that SMM kernel used

  Others:

  History:
    1. Date:           2003/03/14
       Author:         Yang Wei
       Modification:   First Created

 *****************************************************************************/

#ifndef __SMM_OS_H__
#define __SMM_OS_H__

#ifdef  __cplusplus
extern "C" {
#endif


/*****************************************************************************
 Here constant macros definition
 *****************************************************************************/

/* The operation system SMM supported */
#define SMM_WIN32               0x00
#define SMM_LINUX               0x01

/* Cpu supported */
#define SMM_CPU_80X86           0x00
#define SMM_CPU_PPC             0x01

/* Bytes order architecture */
#define SMM_LITTLE_ENDIAN       0x00
#define SMM_BIG_ENDIAN          0x01

/* Compiler supported */
#define SMM_COMPILER_MSC        0x00
#define SMM_COMPILER_GCC        0x01


/*****************************************************************************
 Here define SMM currently used configuration, midify for different usage.
 *****************************************************************************/

/* Modify here to define the operation system SMM currently used */
#define SMM_USE_OS              SMM_WIN32

/* Modify here to define the cpu SMM currently used */
#define SMM_USE_CPU             SMM_CPU_80X86

/* Modify here to define the byte-orders SMM currently used */
#define SMM_BYTE_ORDER          SMM_LITTLE_ENDIAN

/* Modify here to define the compiler SMM currently used */
#define SMM_USE_COMPILER        SMM_COMPILER_MSC


/*****************************************************************************
 Here define SMM macros depend on above configuration.
 *****************************************************************************/

/* Macro for inline assembly language */
#if( SMM_USE_COMPILER == SMM_COMPILER_MSC )
#define SMM_ASM                 __asm
#else
#define SMM_ASM                 __asm
#endif

#define SMM_BEGIN_ASM           SMM_ASM {
#define SMM_END_ASM                     }

/* Macro for inline funtion prefix notation */
#if( SMM_USE_COMPILER == SMM_COMPILER_MSC )
#define SMM_INLINE              __inline
#else
#define SMM_INLINE              inline
#endif


#ifdef  __cplusplus
}
#endif

#endif
