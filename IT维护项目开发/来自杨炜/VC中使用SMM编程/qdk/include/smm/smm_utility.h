/*****************************************************************************

  Copyright (c), 2002-2005, QiDongKai Corp. All rights reserved.

  File name:     smm_utility.h

  Author:        Yang Wei

  Version:       v1.0

  Date:          2003/03/14

  Description:   System Public Utility Function Definitions

  Others:

  History:
    1. Date:           2003/03/14
       Author:         Yang Wei
       Modification:   First Created

 *****************************************************************************/

#ifndef __SMM_UTILITY_H__
#define __SMM_UTILITY_H__

#ifdef  __cplusplus
extern "C" {
#endif


/*****************************************************************************
 Constant Macro Definition
 *****************************************************************************/

/* 64-bit integer arithmetic macro, application should use these notations */
#define SMM_I64_ADD( a, b )     SMM_INT64_Add( a, b )
#define SMM_U64_ADD( a, b )     SMM_UINT64_Add( a, b )
#define SMM_I64_SUB( a, b )     SMM_INT64_Sub( a, b )
#define SMM_U64_SUB( a, b )     SMM_UINT64_Sub( a, b )
#define SMM_I64_MUL( a, b )     SMM_INT64_Mul( a, b )
#define SMM_U64_MUL( a, b )     SMM_UINT64_Mul( a, b )
#define SMM_I64_DIV( a, b )     SMM_INT64_Div( a, b )
#define SMM_U64_DIV( a, b )     SMM_UINT64_Div( a, b )
#define SMM_I64_MOD( a, b )     SMM_INT64_Mod( a, b )
#define SMM_U64_MOD( a, b )     SMM_UINT64_Mod( a, b )
#define SMM_I64_SHL( a, s )     SMM_INT64_Shl( a, s )
#define SMM_U64_SHL( a, s )     SMM_UINT64_Shl( a, s )
#define SMM_I64_SHR( a, s )     SMM_INT64_Shr( a, s )
#define SMM_U64_SHR( a, s )     SMM_UINT64_Shr( a, s )

#define SMM_I64_INC( a ) \
{ \
    SMM_INT64   i64One; \
    SMM_I64_SET( i64One, 0, 1 ); \
    a = SMM_INT64_Add( a, i64One ); \
}

#define SMM_U64_INC( a ) \
{ \
    SMM_UINT64  ui64One; \
    SMM_U64_SET( ui64One, 0, 1 ); \
    a = SMM_UINT64_Add( a, ui64One ); \
}

#define SMM_I64_DEC( a ) \
{ \
    SMM_INT64   i64One; \
    SMM_I64_SET( i64One, 0, 1 ); \
    a = SMM_INT64_Sub( a, i64One ); \
}

#define SMM_U64_DEC( a ) \
{ \
    SMM_UINT64  ui64One; \
    SMM_U64_SET( ui64One, 0, 1 ); \
    a = SMM_UINT64_Sub( a, ui64One ); \
}

#define SMM_I64_CMP( a, b ) \
( \
    ( SMM_I64_HI( a ) == SMM_I64_HI( b ) && SMM_I64_LO( a ) == SMM_I64_LO( b ) ) ? 0 : \
    ( \
        ( SMM_I64_HI( SMM_INT64_Sub( a, b ) ) < 0 ) ? -1 : 1 \
    ) \
)

#define SMM_U64_CMP( a, b ) \
( \
    ( SMM_U64_HI( a ) < SMM_U64_HI( b ) ) ? -1 : \
    ( \
        ( SMM_U64_HI( a ) > SMM_U64_HI( b ) ) ? 1 : \
        ( \
            ( SMM_U64_LO( a ) < SMM_U64_LO( b ) ) ? -1 : \
            ( ( SMM_U64_LO( a ) > SMM_U64_LO( b ) ) ? 1 : 0 ) \
        ) \
    ) \
)


/*****************************************************************************
 Function Declaration
 *****************************************************************************/

/* 64-bit integer arithmetic funtion */
extern SMM_INT64 SMM_INT64_Add( SMM_INT64, SMM_INT64 );
extern SMM_UINT64 SMM_UINT64_Add( SMM_UINT64, SMM_UINT64 );
extern SMM_INT64 SMM_INT64_Sub( SMM_INT64, SMM_INT64 );
extern SMM_UINT64 SMM_UINT64_Sub( SMM_UINT64, SMM_UINT64 );
extern SMM_INT64 SMM_INT64_Mul( SMM_INT64, SMM_INT64 );
extern SMM_UINT64 SMM_UINT64_Mul( SMM_UINT64, SMM_UINT64 );
extern SMM_INT64 SMM_INT64_Div( SMM_INT64, SMM_INT64 );
extern SMM_UINT64 SMM_UINT64_Div( SMM_UINT64, SMM_UINT64 );
extern SMM_INT64 SMM_INT64_Mod( SMM_INT64, SMM_INT64 );
extern SMM_UINT64 SMM_UINT64_Mod( SMM_UINT64, SMM_UINT64 );
extern SMM_INT64 SMM_INT64_Shl( SMM_INT64, SMM_UINT8 );
extern SMM_UINT64 SMM_UINT64_Shl( SMM_UINT64, SMM_UINT8 );
extern SMM_INT64 SMM_INT64_Shr( SMM_INT64, SMM_UINT8 );
extern SMM_UINT64 SMM_UINT64_Shr( SMM_UINT64, SMM_UINT8 );


#ifdef  __cplusplus
}
#endif

#endif
