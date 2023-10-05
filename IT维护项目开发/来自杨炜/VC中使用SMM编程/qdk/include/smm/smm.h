/*****************************************************************************

  Copyright (c), 2002-2005, QiDongKai Corp. All rights reserved.

  File name:     smm.h

  Author:        Yang Wei

  Version:       v1.0

  Date:          2003/03/14

  Description:   System Managment Module Definitions

  Others:

  History:
    1. Date:           2003/03/14
       Author:         Yang Wei
       Modification:   First Created

 *****************************************************************************/

#ifndef __SMM_H__
#define __SMM_H__

#ifdef  __cplusplus
extern "C" {
#endif


/* basic include files */
#include <smm/smm_os.h>
#include <smm/smm_type.h>

/* os related include files */
#if ( SMM_USE_OS == SMM_WIN32 )
#include <windows.h>
#elif ( SMM_USE_OS == SMM_LINUX )
#endif

/* ansi standard include files */
#include <stdlib.h>
#include <memory.h>
#include <string.h>
#include <stdio.h>

/* SMM include files */
#include <smm/smm_utility.h>
#include <smm/smm_kernel.h>


#ifdef  __cplusplus
}
#endif

#endif
