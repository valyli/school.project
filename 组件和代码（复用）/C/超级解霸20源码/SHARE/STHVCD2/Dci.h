typedef	int	DCIRVAL;
typedef	struct	DCICMDtag
	{
	DWORD	dwCommand;	//DCI Command
	DWORD	lParam1;	//generic dword sized parameter
	DWORD	lParam2;	//generic dword sized parameter
	DWORD	dwVersion;	//DCI version
	DWORD	dwReserved;	//reserved for system use.
	}DCICMD;
typedef	struct	DCICREATEINPUTtag
	{
	DCICMD	dcicmd;		//DCI Command header
	DWORD	dwCompression;	//format of surface to be created.
	DWORD	dwMask[3];	//for nonstandard RGB surface
	DWORD	dwHeight;	//height of surface to be created.
	DWORD	dwWidth;	//width of input dsurface
	DWORD	dwDCICaps;	//capabilitics of surface wanted
	DWORD	dwBitCount;	//bit depth of the surface
	LPVOID	lpSurface;	//pointer to an associated surface
	}DCICREATEINPUT,FAR * LPDCICREATEINPUT;
typedef	struct	DCIENUMINPUTtag
	{
	DCICMD		dcicmd;		//DCI Command header
	RECT		rSrc;		//source rectangle
	RECT		rDest;		//destination rectangle
	CALLBACK	*EnumCallback;	//Provider calls to return support
	LPVOID		lpContext;	//Provider must pass back to client
	}DCIENUMINPUT,FAR * LPDCIENUMINPUT;
typedef	struct	RECTLTeg
	{
	long	left;
	long	top;
	long	right;
	long	bottom;
	}RECTL;
typedef	struct	RGNDATAHEADERtag
	{
	DWORD		dwSize;		//size of structure
	DWORD		iType;		//type of region,Will be RDH_RECTANGLES
	DWORD		nCount;		//number of rectangles
	DWORD		nRgnSize;	//size of buffer -- can be zero
	RECTL		rcBound;	//bounding rectangle for region
	}RGNDATAHEADER;
typedef	struct	RGNDATAtag
	{
	RGNDATAHEADER	rdh;		//region data header
	char		buffer[1];	//array of retangles
	}RGNDATA,FAR *LPRGNDATA;
typedef	struct	DCISURFACEINFOtag
	{
	DWORD	dwSize;		//Size of surface
	DWORD	dwDCICaps;	//capability flags
	DWORD	dwCompression;	//format of surface to be created
	DWORD	dwMask[3];	//for nonstandard RGB surface
	DWORD	dwWidth;	//Width of surface
	DWORD	dwHeight;	//Height of surface
	LONG	lStride;	//stride of surface
	DWORD	dwBitCount;	//Bit depth of format
	DWORD	dwOffSurface;	//surface offset
	DWORD	dwSelSurface;	//surface selector and alignment
	DWORD	dwReserved1;	//reserved for provider
	DWORD	dwReserved2;	//reserved for DCIMAN
	DWORD	dwReserved3;	//reserved for future
	DCIRVAL	(CALLBACK *BeginAccess)(LPVOID,LPRECT);	//BeginAccess Fn
	DCIRVAL	(CALLBACK *EndAccess)(LPVOID);		//EndAccess Fn
	void	(CALLBACK *DestroySurface)(LPVOID);	//DestroySurface Fn
	}DCISURFACEINFO,FAR * LPDCISURFACEINFO;
typedef	struct	DCIOFFSCREENtag
	{
	DCISURFACEINFO	dciInfo;		//surface info
	void/*DCIRVAL*/	(CALLBACK *Draw)(LPDCISURFACEINFO);	//Execute Draw Fn
	DCIRVAL	(CALLBACK *SetCliplist)(LPVOID,LPRGNDATA);//SetCliplist Fn
	DCIRVAL	(CALLBACK *SetDestination)(LPVOID,LPRECT,LPRECT);//SetDestination Fn
	DWORD	Data[25];	//Not know.
	}DCIOFFSCREEN,FAR *LPDCIOFFSCREEN;
typedef	struct	DCIOVERLAYtag
	{
	DCISURFACEINFO	dciInfo;		//surface info
	DCIRVAL	(CALLBACK *SetCliplist)(LPVOID,LPRGNDATA);//SetCliplist Fn
	DCIRVAL	(CALLBACK *SetDestination)(LPVOID,LPRECT,LPRECT);//SetDestination Fn
	DWORD		dwChromakeyValue;	//Chromakey color value
	DWORD		dwChromakeyMask;	//specifies valid bits of value
	}DCIOVERLAY,FAR *LPDCIOVERLAY;
typedef	DCISURFACEINFO	DCIPRIMARY,FAR *LPDCIPRIMARY;
