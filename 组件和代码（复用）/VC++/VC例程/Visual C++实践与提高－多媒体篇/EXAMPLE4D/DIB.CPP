// Dib.cpp: implementation of the CDib class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Dib.h"
#include "math.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
IMPLEMENT_DYNAMIC(CDib,CGdiObject);
CDib::CDib()
{
	m_pBMI=NULL;
	m_pDIBData=NULL;
}

CDib::~CDib()
{
	if(m_pBMI != NULL)
		delete m_pBMI;
	if(m_pDIBData != NULL)
		delete m_pDIBData;
}

//从位图句柄得到位图GDI对象指针
CDib* PASCAL CDib::FromHandle(HBITMAP hDib)
{
	return (CDib*)CGdiObject::FromHandle(hDib);
}
//////////////////////////////////////////////////////////////////
// 完成功能://     读入图像文件
// 输入参数://	   位图文件名 filename
// 返回参数://	   是否成功(-1为不成功, 1为不成功)
//////////////////////////////////////////////////////////////////
int CDib::LoadBmp(LPCSTR filename)
{
	CFile file;
	//打开文件
	if(!file.Open(filename,CFile::modeRead|CFile::shareDenyNone))
	{
		AfxMessageBox("Can not open the file!");
		return -1;
	}
	
	//读入文件头
	BITMAPFILEHEADER bfh;
	file.Read(&bfh,sizeof(BITMAPFILEHEADER));

	//判断文件类型
	if(bfh.bfType!=0x4d42)//'BM'
	{
		AfxMessageBox("Not a BMP file!");
		file.Close();
		return -1;
	}

	//判断文件头大小
	if(bfh.bfSize!=file.GetLength())
	{
		AfxMessageBox("Read bitmapfileheader error!");
		file.Close();
		return -1;
	}

	//bfOffBits与BITMAPFILEHEADER结构大小相减计算出位图信息头和颜色表的大小
	UINT uBMIandCOLORLen	=(UINT) bfh.bfOffBits-sizeof(BITMAPFILEHEADER);
	LPBITMAPINFO lpBMI		=(LPBITMAPINFO) new BYTE[uBMIandCOLORLen];
	file.Read((LPVOID)lpBMI, uBMIandCOLORLen);

	DWORD dwBitlen	=bfh.bfSize - bfh.bfOffBits;
	BYTE* lpBits	=new BYTE[dwBitlen];
	file.ReadHuge(lpBits,dwBitlen);
	file.Close();

	int iCreateSucceed=CreateDIBIndirect(lpBMI, lpBits);
	
	m_pBMI		=lpBMI;
	m_pDIBData	=lpBits;
	
	if(!iCreateSucceed)
	{
		AfxMessageBox("Create BMP file failed!");
		return -1;
	}
	else
		return 1;
}

////////////////////////////////////////

void CDib::ShowDIB(CDC* pDC,int nLeft,int nTop,int nWidth, int nHeight)
{
	pDC->SetStretchBltMode(COLORONCOLOR);

	StretchDIBits(pDC->GetSafeHdc(),//向下移动
						nLeft,nTop,nWidth,nHeight,
						0, 0, GetDIBWidth(),GetDIBHeight(),
						m_pDIBData, m_pBMI,
						DIB_RGB_COLORS,SRCCOPY);
}

//////////////////////////////////////////////////////////////////
// 完成功能://     得到位图句柄
// 输入参数://	   无
// 返回参数://	   位图句柄
//////////////////////////////////////////////////////////////////
CDib::operator HBITMAP() const
{
	return (HBITMAP)(this == NULL ? NULL : m_hObject);
}

//////////////////////////////////////////////////////////////////////////////
//完成功能:	创建DIB位图
//输入参数:	图像宽度 iWdith,	图像高度 iHeight,	图像位数 iBitCount,	图像数据 lpBits 
//返回参数:	是否成功
//////////////////////////////////////////////////////////////////
BOOL CDib::CreateDIB(int iWidth, int iHeight, UINT iBitCount, const void* lpBits) 
{
	//判断位图的位数
	if(iBitCount<=1)
		iBitCount=1;
	else if(iBitCount<=4)
		iBitCount=4;
	else if(iBitCount<=8)
		iBitCount=8;
	else if (iBitCount<=16)
		iBitCount=16;
	else if (iBitCount<=24)
		iBitCount=24;
	else if(iBitCount<=32)
		iBitCount=32;
	else
		iBitCount=4;
	//创建位图信息,计算位图信息的大小,申请空间,赋初值
	LPBITMAPINFO lpBMI;
	int iSize = sizeof(BITMAPINFOHEADER)+GetColorNumber(iBitCount)*sizeof(RGBQUAD);
	lpBMI= (BITMAPINFO*) new BYTE[iSize];
	memset(lpBMI, 0, iSize);
	
	//设置BITMAPINFOHEADER的各成员的值
	lpBMI->bmiHeader.biSize		=	sizeof(BITMAPINFOHEADER);
	lpBMI->bmiHeader.biWidth		=	iWidth;
	lpBMI->bmiHeader.biHeight		=	iHeight;
	lpBMI->bmiHeader.biBitCount		=	iBitCount;
	lpBMI->bmiHeader.biPlanes		=	1;//必须为1
	lpBMI->bmiHeader.biCompression	=	BI_RGB; // to use this flag.
	lpBMI->bmiHeader.biSizeImage	=	0;
	lpBMI->bmiHeader.biSizeImage	=	0;

	int iCreateSucceed	=	CreateDIBIndirect(lpBMI, lpBits);
	delete lpBMI;
	
	if(!iCreateSucceed)
		return -1;
	
	return 1;
}

//////////////////////////////////////////////////////////////////
// 完成功能:	根据pBMI创建DIB位图
// 输入参数:	位图信息结构指针 pBMI,	图像数据 lpBits 
// 返回参数:	是否成功
//////////////////////////////////////////////////////////////////
int CDib::CreateDIBIndirect(LPBITMAPINFO pBMI, const void* lpBits)
{
	//删除内存中的原有GDI对象
	DeleteObject();

	//创建 DIB section.
	CDC *pDC = new CDC;
	pDC->CreateCompatibleDC(NULL);
	LPVOID pBits;
	HBITMAP hBitmap	=	::CreateDIBSection(
							pDC->GetSafeHdc(),
							pBMI,
							DIB_RGB_COLORS,
                           	&pBits,
                           	NULL,
                           	0);
	delete pDC;

	ASSERT(hBitmap);
	ASSERT(pBits);

	//设置图像数据,将 lpBits 的数据拷贝至图像,位图数据大小 dwCount,图像数据 lpBits
	//返回拷贝的数据大小
	Attach(hBitmap);
	BITMAP bmp;
	GetBitmap(&bmp);
	DWORD dwCount=(DWORD)(bmp.bmWidthBytes * bmp.bmHeight);

	if(SetDIBBits(dwCount,lpBits)!=dwCount)
	{
		AfxMessageBox("DIB Create Error!");
		return -1;
	}
	return 1;
}

// GetBitmap(BITMAP* pBitMap)
// 完成功能:	得到位图
// 输入参数:	位图指针 pBitMap
// 返回参数:	是否成功
//////////////////////////////////////////////////////////////////

//得到位图
int CDib::GetBitmap(BITMAP* pBitMap)
{
	return(::GetObject(m_hObject, sizeof(BITMAP), pBitMap));
}

int CDib::GetColorNumber(WORD iBitCount)
{
	//判断位图的位数
	if(iBitCount<=1)
		iBitCount=1;
	else if(iBitCount<=4)
		iBitCount=4;
	else if(iBitCount<=8)
		iBitCount=8;
	else if (iBitCount<=16)
		iBitCount=16;
	else if (iBitCount<=24)
		iBitCount=24;
	else if(iBitCount<=32)
		iBitCount=32;
	else
		iBitCount=4;

	switch(iBitCount)
	{
	case 1:
		return 2;
	case 4:
		return 16;
	case 8:
		return 256;
	default:
		return 0;
	}
}

//////////////////////////////////////////////////////////////////
// SetDIBBits(DWORD dwCount,const void * lpBits)
// 完成功能:
//     设置图像数据,将 lpBits 的数据拷贝至图像
// 输入参数:
//	   位图数据大小 dwCount
//     图像数据 lpBits 
// 返回参数:
//	   拷贝的数据大小
//////////////////////////////////////////////////////////////////
DWORD CDib::SetDIBBits(DWORD dwCount,const void * lpBits)
{
	if(lpBits != NULL)
	{
		LPVOID pBits = GetBits();
		memcpy(pBits,lpBits,dwCount);
		return dwCount;
	}
	return 0;
}


//////////////////////////////////////////////////////////////////
// 完成功能:
//     得到图像数据.
//     如果 lpBits 为空,则返回图像数据指针;
//	   如果 lpBits 不为空,
//             则将图像数据拷贝至该指针,
//             并返回图像数据指针;
//
// 输入参数://	   拷贝的位图数据大小 dwCount
			//     图像数据 lpBits 
// 返回参数://	   图像数据指针
//////////////////////////////////////////////////////////////////
LPVOID CDib::GetDIBBits(DWORD dwCount, LPVOID lpBits)
{
	LPVOID pBits = GetBits();
	if(lpBits != NULL)
	{
		memcpy(lpBits,pBits,dwCount);
		return pBits;
	}
	else
	{
		return pBits;
	}
}

//////////////////////////////////////////////////////////////////
// 完成功能://     得到图像数据
// 输入参数://	   无
// 返回参数://	   图像数据
//////////////////////////////////////////////////////////////////
LPVOID CDib::GetBits(void)
{
	BITMAP bmp;
	GetBitmap(&bmp);
	return(bmp.bmBits);
}

//////////////////////////////////////////////////////////////////
// 完成功能://     保存位图文件
// 输入参数://	   文件名 filename
// 返回参数://	   是否成功
//////////////////////////////////////////////////////////////////
int CDib::SaveBmp(LPCSTR filename)
{
	BITMAPFILEHEADER hdr;

	//打开文件
	CFile file(filename,CFile::modeWrite|CFile::modeCreate);

	//文件头
	hdr.bfType = ((WORD)'M'<<8) + 'B';
	LPBITMAPINFO pbi = GetBitmapInfo(); 
	PBITMAPINFOHEADER pbih = (PBITMAPINFOHEADER) pbi; 

	hdr.bfSize = (DWORD) (sizeof(BITMAPFILEHEADER) + 
                 pbih->biSize + pbih->biClrUsed 
                 * sizeof(RGBQUAD) + pbih->biSizeImage); 

    hdr.bfReserved1 = 0; 
    hdr.bfReserved2 = 0; 

    // Compute the offset to the array of color indices. 
    hdr.bfOffBits = (DWORD) sizeof(BITMAPFILEHEADER) + 
                    pbih->biSize + pbih->biClrUsed 
                    * sizeof (RGBQUAD); 
	
    //写入文件头
	file.Write((LPVOID) &hdr, sizeof(BITMAPFILEHEADER));

	//写入信息头
    file.Write((LPVOID) pbih, sizeof(BITMAPINFOHEADER) 
                  + pbih->biClrUsed * sizeof (RGBQUAD)); 

    // Copy the array of color indices into the .BMP file. 
	//写入数据
    int nTotal = pbih->biSizeImage; 
    LPVOID lpBits = GetBits(); 
    file.WriteHuge(lpBits, nTotal);

	//关闭文件
	file.Close();	
	
	delete pbi;

	return 1;
}

//////////////////////////////////////////////////////////////////
// 完成功能://     设置调色板
// 输入参数://	   调色板开始索引 uStartIndex
			//     调色板入口 cEntries
			//     颜色数据 pColors
// 返回参数://	   无
//////////////////////////////////////////////////////////////////
void CDib::SetPalette(UINT uStartIndex, UINT cEntries, CONST RGBQUAD *pColors)
{
	HDC hdc = ::CreateCompatibleDC(NULL);
	HBITMAP hOld = (HBITMAP)::SelectObject(hdc, m_hObject);

	::SetDIBColorTable(hdc, uStartIndex, cEntries, pColors);
	
	::SelectObject(hdc, hOld);
	::DeleteObject(hdc);
}


//////////////////////////////////////////////////////////////////
// 完成功能://     设置调色板
// 输入参数://	   调色板结构指针 pPal
// 返回参数:
//////////////////////////////////////////////////////////////////
void CDib::SetPalette(CPalette* pPal)
{
    ASSERT(pPal);

    // get the colors from the palette
    int iColors = 0;
    pPal->GetObject(sizeof(iColors), &iColors);
    ASSERT(iColors > 0);
    PALETTEENTRY* pPE = new PALETTEENTRY[iColors];
    pPal->GetPaletteEntries(0, iColors, pPE);

    // Build a table of RGBQUADS
    RGBQUAD* pRGB = new RGBQUAD[iColors];
    ASSERT(pRGB);
    for (int i = 0; i < iColors; i++) {
        pRGB[i].rgbRed = pPE[i].peRed;
        pRGB[i].rgbGreen = pPE[i].peGreen;
        pRGB[i].rgbBlue = pPE[i].peBlue;
        pRGB[i].rgbReserved = 0;
    }

	SetPalette(0, iColors, pRGB);

    delete [] pRGB;
    delete [] pPE;
}

//////////////////////////////////////////////////////////////////
// 完成功能://     得到DibSection
// 输入参数://	   DibSection指针 pDibSection
// 返回参数://	   是否成功
//////////////////////////////////////////////////////////////////
int CDib::GetDibSection(DIBSECTION *pDibSection)
{
	return(::GetObject(m_hObject, sizeof(DIBSECTION), pDibSection));
}

//////////////////////////////////////////////////////////////////
// 完成功能://     得到宽度
// 输入参数://	   无
// 返回参数://	   宽度
//////////////////////////////////////////////////////////////////
int CDib::GetWidth(void)
{
	BITMAP bmp;
	GetBitmap(&bmp);
	return(bmp.bmWidth);
}


//////////////////////////////////////////////////////////////////
// 完成功能://     得到高度
// 输入参数://	   无
// 返回参数://	   高度
//////////////////////////////////////////////////////////////////
int CDib::GetHeight(void)
{
	BITMAP bmp;
	GetBitmap(&bmp);
	return(bmp.bmHeight);
}


//////////////////////////////////////////////////////////////////
// GetSize(void)
// 完成功能://     得到尺寸
// 输入参数://	   无
// 返回参数://	   尺寸
//////////////////////////////////////////////////////////////////
SIZE CDib::GetSize(void)
{
	BITMAP bmp;
	GetBitmap(&bmp);
	CSize size(bmp.bmWidth, bmp.bmHeight);
	return(size);
}

//////////////////////////////////////////////////////////////////
// 完成功能://     得到每行字节数
// 输入参数://	   无
// 返回参数://	   每行字节数
//////////////////////////////////////////////////////////////////
int CDib::GetWidthBytes(void)
{
	BITMAP bmp;
	GetBitmap(&bmp);
	return(bmp.bmWidthBytes);
}


//////////////////////////////////////////////////////////////////
// 完成功能://     得到图像位数
// 输入参数://	   无
// 返回参数://	   图像位数
//////////////////////////////////////////////////////////////////
int CDib::GetBitCount(void)
{
	BITMAP bmp;
	GetBitmap(&bmp);
	return(bmp.bmBitsPixel);
}


//////////////////////////////////////////////////////////////////
// 完成功能://     得到位图信息
// 输入参数://	   无
// 返回参数://	   位图信息指针,用完应释放
//////////////////////////////////////////////////////////////////
LPBITMAPINFO CDib::GetBitmapInfo(void)
{
	DIBSECTION DibSection;
	GetDibSection(&DibSection);
	int nSize = DibSection.dsBmih.biClrUsed*sizeof(RGBQUAD) + sizeof(BITMAPINFOHEADER);
	
	BYTE *pByte = new BYTE[nSize];
	memcpy(pByte, &(DibSection.dsBmih), sizeof(BITMAPINFOHEADER));
//?	CDC *pdc = GetDC();
	CDC *pdc=new CDC;
	::GetDIBColorTable(pdc->GetSafeHdc(), 0, DibSection.dsBmih.biClrUsed,
						(RGBQUAD*)(pByte+sizeof(BITMAPINFOHEADER)));
//?	ReleaseDC(pdc);
	delete pdc;
	BITMAPINFO *pBMI = (BITMAPINFO*)pByte;
	return(pBMI);
}
//////////////////////////////////
//	以下是用于特效显示的函数	//
//////////////////////////////////

//函数功能:		延时
//参数说明:		time 以毫秒为单位的时间
void CDib::Wait(double time)
{
	clock_t start, finish;
	double 	time_i =0.0;
	start = clock();
	while(time_i<=time)
	{
		finish=clock();
		time_i=finish-start;
	}
}
/////////////////////////////////////
//函数功能:
//		位图扫描显示
//参数说明：
//		pDC		设备上下文
//		nLeft	显示区域的左上角x坐标
//		nTop	显示区域的左上角y坐标
//		nWidth	显示区域的右上角x坐标
//		nHeight	显示区域的右上角y坐标
/////////////////////////////////////
void CDib::ShowSweep(CDC* pDC,int nLeft,int nTop,int nWidth, int nHeight)
{
	//创建画刷和画笔，用于清除
	CBrush brush(RGB(0,0,255));
	CBrush* oldBrush=pDC->SelectObject(&brush);
	CPen pen(PS_SOLID,1,RGB(0,0,255));
	CPen* oldPen=pDC->SelectObject(&pen);
	pDC->Rectangle(0,0,nWidth,nHeight);

	//每次扫描的幅度
	int nSweepWidth=25;
	//扫描起始行的上下高度
	int nStart=0;
	int nEnd=25;
	for(nEnd=25; nEnd<nHeight+25; nEnd=nEnd+25)
	{
		int temp1=GetDIBHeight();
		int dibWidth=int(25*temp1/nHeight);
		int dibEnd=int(nEnd*temp1/nHeight);
		int dibStart=int(nStart*temp1/nHeight);
		//利用StretchDIBits函数绘制位图
		StretchDIBits(pDC->GetSafeHdc(),
					nLeft, nStart,
					nWidth, 25,
					0,temp1-dibEnd,
					GetDIBWidth(),dibWidth,
					m_pDIBData, m_pBMI,
					DIB_RGB_COLORS,SRCCOPY);
		nStart=nEnd;
		//延时0.1秒
		Wait(100);
	}
	
	//延时0.5秒
	Wait(500);
	//清除
	oldBrush=pDC->SelectObject(&brush);
	oldPen=pDC->SelectObject(&pen);
	for(int j=0;j<=nHeight;j++)
	{	
		//绘制矩形
		pDC->Rectangle(0,nHeight-j,nWidth,nHeight);
	}
	pDC->SelectObject(oldBrush);
	pDC->SelectObject(oldPen);
}

/////////////////////////////////////
//函数功能:
//		位图移动显示
//参数说明：
//		pDC		设备上下文
//		nLeft	显示区域的左上角x坐标
//		nTop	显示区域的左上角y坐标
//		nWidth	显示区域的右上角x坐标
//		nHeight	显示区域的右上角y坐标
/////////////////////////////////////
void CDib::ShowMove(CDC* pDC,int nLeft,int nTop,int nWidth, int nHeight)
{
	//创建画刷和画笔，用于清除
	CBrush brush(RGB(0,0,255));
	CBrush* oldBrush=pDC->SelectObject(&brush);
	CPen pen(PS_SOLID,1,RGB(0,0,255));
	CPen* oldPen=pDC->SelectObject(&pen);
	//恢复背景
	pDC->Rectangle(0,0,nWidth,nHeight);
	
	//向下平移
	for(int i=0;i<nHeight+15;i=i+15)
	{
		int temp1=GetDIBHeight();
		int temp=int(i*temp1/nHeight);
		StretchDIBits(pDC->GetSafeHdc(),
					nLeft, nTop,
					nWidth, i,
					0,0,
					GetDIBWidth(),temp,
					m_pDIBData, m_pBMI,
					DIB_RGB_COLORS,SRCCOPY);
		//延时1.0秒
		Wait(1000);
	}
	//延时1.0秒
	Wait(1000);

	//清除
	for(int j=0;j<=nHeight;j++)
	{
		pDC->Rectangle(0,j,nWidth,0);
	}
	pDC->SelectObject(oldBrush);
	pDC->SelectObject(oldPen);

	//向上平移
	for( i=0;i<nHeight+15;i=i+15)
	{
		int temp1=GetDIBHeight();
		int temp=int(i*temp1/nHeight);
		StretchDIBits(pDC->GetSafeHdc(),
					nLeft, nTop+nHeight-i,
					nWidth, i,
					0,GetDIBHeight()-temp,
					GetDIBWidth(),temp,
					m_pDIBData, m_pBMI,
					DIB_RGB_COLORS,SRCCOPY);
		//延时0.1秒
		Wait(100);	
	}
	//延时1.0秒
	Wait(1000);

	//清除
	oldBrush=pDC->SelectObject(&brush);
	oldPen=pDC->SelectObject(&pen);
	for(j=0;j<=nHeight;j++)
	{
		pDC->Rectangle(0,nHeight-j,nWidth,nHeight);
	}
	pDC->SelectObject(oldBrush);
	pDC->SelectObject(oldPen);
	//结束平移
}

/////////////////////////////////////
//函数功能:
//		位图百叶窗显示
//参数说明：
//		pDC		设备上下文
//		nLeft	显示区域的左上角x坐标
//		nTop	显示区域的左上角y坐标
//		nWidth	显示区域的右上角x坐标
//		nHeight	显示区域的右上角y坐标
/////////////////////////////////////
void CDib::ShowWindow(CDC* pDC,int nLeft,int nTop,int nWidth, int nHeight)
{
	//垂直百叶窗
	CBrush brush(RGB(0,0,255));
	CBrush* oldBrush=pDC->SelectObject(&brush);
	CPen pen(PS_SOLID,1,RGB(0,0,255));
	CPen* oldPen=pDC->SelectObject(&pen);
	//恢复背景
	pDC->Rectangle(0,0,nWidth,nHeight);

	//每一叶的宽度
	int nScanLine=20;
	int w=GetDIBWidth();

	//temp1和temp表示目标对象和源位图宽度的比,
	//客户区比源位图宽
	int temp,temp1;
	if(w>nWidth)
	{
		if(fmod(w,nWidth)!=0)
			temp=int(w/nWidth)+1;
		else
			temp=int(w/nWidth);
		temp1=1;
	}
	//源位图比客户区宽
	else
	{
		if(fmod(nWidth,w)!=0)
			temp1=int(nWidth/w)+1;
		else
			temp1=int(nWidth/w);
		temp=1;	
	}

	//依次对每个条状区域拷贝位图,间隔由i的增幅确定
	for(int i=0;i<nScanLine;++i)
	{
		for(int j=i; j<nWidth; j=j+nScanLine)
		{
			StretchDIBits(pDC->GetSafeHdc(),
						j,0,
						temp1,nHeight,
						j*GetDIBWidth()/nWidth,0,
						temp,GetDIBHeight(),
						m_pDIBData, m_pBMI,
						DIB_RGB_COLORS,SRCCOPY);
		}
		Wait(500);
	}
	
	//依次对每个条状区域绘制矩形来清除,间隔由i的增幅确定
	for(i=0; i<nScanLine;++i)
	{
		for(int j=i; j<nWidth; j=j+nScanLine)
			pDC->Rectangle(j,0,j+1,nHeight);
				
		Wait(500);
	}
	pDC->SelectObject(oldBrush);
	pDC->SelectObject(oldPen);	
}

/////////////////////////////////////
//函数功能:
//		位图栅条显示
//参数说明：
//		pDC		设备上下文
//		nLeft	显示区域的左上角x坐标
//		nTop	显示区域的左上角y坐标
//		nWidth	显示区域的右上角x坐标
//		nHeight	显示区域的右上角y坐标
/////////////////////////////////////
void CDib::ShowGrid(CDC* pDC,int nLeft,int nTop,int nWidth, int nHeight)
{
	CBrush brush(RGB(0,0,255));
	CBrush* oldBrush=pDC->SelectObject(&brush);
	CPen pen(PS_SOLID,1,RGB(0,0,255));
	CPen* oldPen=pDC->SelectObject(&pen);
	//恢复背景
	pDC->Rectangle(0,0,nWidth,nHeight);

	//栅条的宽度
	int nScanLine=25;
	int w=GetDIBWidth();
	int h=GetDIBHeight();
	//客户区和源位图的变换比例
	double wScale=(double)w/(double)nWidth;//
	double hScale=(double)h/(double)nHeight;//
	//
	for(int i=0;i<nHeight+1;i=i+1)
	{
		for(int j=0; j<nWidth; j=j+2*nScanLine)
		{
			StretchDIBits(pDC->GetSafeHdc(),//向下移动
						j, 0, nScanLine, (i+1),
						(int)(j*wScale), 0, (int)(nScanLine*wScale), (int)(hScale*(i+1)),
						m_pDIBData, m_pBMI,
						DIB_RGB_COLORS,SRCCOPY);
			
			int k=j+nScanLine;
			StretchDIBits(pDC->GetSafeHdc(),//向上移动
						k, nHeight-i, nScanLine, i,
						(int)(k*wScale),(int)((nHeight-i)*hScale), (int)(nScanLine*wScale),(int)(i*hScale),//(int)((nHeight)*wScale)
						m_pDIBData, m_pBMI,
						DIB_RGB_COLORS,SRCCOPY);
		}
	}

	Wait(250);	
	
	for(i=0; i<nHeight+1;i=i+1)
	{
		for(int j=0; j<nWidth; j=j+2*nScanLine)
		{
			StretchDIBits(pDC->GetSafeHdc(),//向下清除
						j, i, nScanLine,nHeight-i,
						(int)(j*wScale), (int)(i*hScale), (int)(nScanLine*wScale), (int)(hScale*(nHeight-i)),
						m_pDIBData, m_pBMI,
						DIB_RGB_COLORS,SRCCOPY);			
			pDC->Rectangle(j,i-1,j+nScanLine,i);
			int k=j+nScanLine;
			StretchDIBits(pDC->GetSafeHdc(),//向上清除
						k, 0, nScanLine, nHeight-i,
						(int)(k*wScale),0, (int)(nScanLine*wScale),  (int)((nHeight-i)*hScale),//(int)(hScale*i),
						m_pDIBData, m_pBMI,
						DIB_RGB_COLORS,SRCCOPY);			
			pDC->Rectangle(k, nHeight-i,k+nScanLine,nHeight-i+1);
		}
	}
	pDC->SelectObject(oldBrush);
	pDC->SelectObject(oldPen);	
}

/////////////////////////////////////
//函数功能:
//		位图马赛克显示
//参数说明：
//		pDC		设备上下文
//		nLeft	显示区域的左上角x坐标
//		nTop	显示区域的左上角y坐标
//		nWidth	显示区域的右上角x坐标
//		nHeight	显示区域的右上角y坐标
/////////////////////////////////////
void CDib::ShowMasic(CDC* pDC,int nLeft,int nTop,int nWidth, int nHeight)
{
	CBrush brush(RGB(0,0,255));
	CBrush* oldBrush=pDC->SelectObject(&brush);
	CPen pen(PS_SOLID,1,RGB(0,0,255));
	CPen* oldPen=pDC->SelectObject(&pen);
	//恢复背景
	pDC->Rectangle(0,0,nWidth,nHeight);
	Wait(500);

	pDC->SetStretchBltMode(COLORONCOLOR);
	//马赛克方块的大小
	int nDividedSize=25;
	int nWidthAppend=0;
	int nHeightAppend=0;
	//如果不能整除,横纵方块的数量要加1
	if((nWidth%nDividedSize)!=0)
		nWidthAppend=1;
	if((nHeight%nDividedSize)!=0)
		nHeightAppend=1;
	//划分的方块数量
	long lDividedNum=(nWidth/nDividedSize+nWidthAppend)*(nHeight/nDividedSize+nHeightAppend);
	//申请数组，存储方块的坐标
	POINT *point=new POINT[lDividedNum];
	//为数组赋值的临时变量
	long mx=0; 
	long my=0; 
	//源位图的尺寸
	int w=GetDIBWidth();
	int h=GetDIBHeight();
	double wScale=(double)w/(double)nWidth;//
	double hScale=(double)h/(double)nHeight;//
	//为数组赋值
	for(long mi=0;mi<lDividedNum;mi++)
	{
		point[mi].x=mx;
		point[mi].y=my;
		mx=mx+nDividedSize;
		if(mx>nWidth)
		{
			mx=0;
			my=my+nDividedSize;
		}
	}
	//RAND_MAX是系统定义的最大随机数,是0x7fff,即32767
	double fmax=RAND_MAX;
	for(mi=lDividedNum-1;mi>=0;mi--)
	{
		//产生随机数
		int randNum=rand();
		//计算要随机显示的方块
		int n=(int)((double)randNum*(double)lDividedNum/fmax);
		//得到此方块的位置
		mx=point[n].x;
		my=point[n].y;
		//随机显示方块
		StretchDIBits(pDC->GetSafeHdc(),
						mx, my, nDividedSize, nDividedSize,
						(int)(mx*wScale), (int)((nHeight-my-nDividedSize)*hScale), (int)(nDividedSize*wScale), (int)(nDividedSize*hScale),
						m_pDIBData, m_pBMI,
						DIB_RGB_COLORS,SRCCOPY);
		Wait(100);
		//将显示过的方块设置标志,以补充绘制
		point[n].x=-1;
		point[n].y=-1;
	}
	//补充绘制上面没有绘制到的方块
	for(mi=lDividedNum-1;mi>=0;mi--)
	{
		if(point[mi].x!=-1&&point[mi].y!=-1)
		{
			mx=point[mi].x;
			my=point[mi].y;
			StretchDIBits(pDC->GetSafeHdc(),
						mx, my, nDividedSize, nDividedSize,
						(int)(mx*wScale), (int)((nHeight-my-nDividedSize)*hScale), (int)(nDividedSize*wScale), (int)(nDividedSize*hScale),
						m_pDIBData, m_pBMI,
						DIB_RGB_COLORS,SRCCOPY);		
		}
	}
	delete []point;
	Wait(1000);

	//清除
	POINT *erasePoint=new POINT[lDividedNum];
	mx=0; 
	my=0; 
	for(mi=0;mi<lDividedNum;mi++)
	{
		erasePoint[mi].x=mx;
		erasePoint[mi].y=my;
		mx=mx+nDividedSize;
		if(mx>nWidth)
		{
			mx=0;
			my=my+nDividedSize;
		}
	}
	//利用随机数清除	
	for(mi=lDividedNum-1;mi>=0;mi--)
	{
		int randNum=rand();
		int n=(int)((double)randNum*(double)lDividedNum/fmax);

		mx=erasePoint[n].x;
		my=erasePoint[n].y;
		pDC->Rectangle(mx,my,mx+nDividedSize,my+nDividedSize);
		Wait(1);
		erasePoint[n].x=-1;//设置标志
		erasePoint[n].y=-1;
	}
	for(mi=lDividedNum-1;mi>=0;mi--)//补充绘制
	{
		if(erasePoint[mi].x!=-1&&erasePoint[mi].y!=-1)
		{
			mx=erasePoint[mi].x;
			my=erasePoint[mi].y;
			pDC->Rectangle(mx,my,mx+nDividedSize,my+nDividedSize);		
		}
	}
	delete []erasePoint;
}