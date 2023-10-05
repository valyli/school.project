/*****************************************************************************

  Copyright (c), 2002-2005, QiDongKai Corp. All rights reserved.

  File name:     LIDP_Date.h

  Author:        LiJia

  Version:       v1.0

  Date:          2003/06/28

  Description:   Deal with time in char

  Others:

  Function List:

  History:
    1. Date:           2003/06/28
       Author:         LiJia
       Modification:   First Created

 *****************************************************************************/



// LIDP_Date.h: interface for the LIDP_Date class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(LIDP_DATE_H__A3ECDCC9_D435_46D8_8288_6006A0C22155__INCLUDED_)
#define LIDP_DATE_H__A3ECDCC9_D435_46D8_8288_6006A0C22155__INCLUDED_


class LIDP_Date  
{
public:
	int Compare(char* time1, char* time2);
	char* LocalTime(void);
	LIDP_Date();
	virtual ~LIDP_Date();

};

#endif // !defined(LIDP_DATE_H__A3ECDCC9_D435_46D8_8288_6006A0C22155__INCLUDED_)
