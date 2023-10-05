// Machine generated IDispatch wrapper class(es) created with ClassWizard

#include "stdafx.h"
#include "autoserver.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif



/////////////////////////////////////////////////////////////////////////////
// IAutoserver properties

/////////////////////////////////////////////////////////////////////////////
// IAutoserver operations

double IAutoserver::SquareRoot(double dInputVal)
{
	double result;
	static BYTE parms[] =
		VTS_R8;
	InvokeHelper(0x1, DISPATCH_METHOD, VT_R8, (void*)&result, parms,
		dInputVal);
	return result;
}
