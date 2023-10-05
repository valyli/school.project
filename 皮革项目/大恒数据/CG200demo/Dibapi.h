// dibapi.h
#include "math.h"
#include <conio.h>
#ifndef _INC_DIBAPI
#define _INC_DIBAPI
#define MAX_FILENAME 80
#define M_PI  3.1415926

// Handle to a DIB
//	DECLARE_HANDLE(HANDLE);

// DIB constants
#define PALVERSION   0x300

typedef struct
{
	HANDLE      hDIB;                // Handle to the DIB
	HPALETTE    hPal;                // Handle to the bitmap's palette.
	HBITMAP     hBitmap;             // Handle to the DDB.
	
	WORD        wDIBType;            // DIB's type - RGB, RLE4, RLE8, PM
	WORD        wDIBBits;            // Bits per pixel
	WORD        wDIBWidth;           // Print width of the DIB
	WORD        wDIBHeight;          // Print height of the DIB
	
	char        szFileName[MAX_FILENAME];  // DIB's filename
	RECT        rcClip;              // Clipboard cut rectangle.
} DIBINFO, LPDIBINFO;

#define SWAP(x,y)   ((x)^=(y)^=(x)^=(y))
#define MAX(a,b)     ((a) > (b) ? (a) : (b))
#define MIN(a,b)     ((a) < (b) ? (a) : (b))
//注意，R,G,B应该是DWORD类型
#define GRAYLEVEL(R,G,B)  (B*299+G*587+R*114)/1000

typedef struct
{
	HANDLE hDIB;                  // Handle to the DIB.
	char   szFileName [128];      // Its filename.
} DIBCREATEINFO, FAR * LPDIBCREATEINFO;

/* DIB Macros*/

#define IS_WIN30_DIB(lpbi)  ((*(LPDWORD)(lpbi)) == sizeof(BITMAPINFOHEADER))
#define RECTWIDTH(lpRect)     ((lpRect)->right - (lpRect)->left)
#define RECTHEIGHT(lpRect)    ((lpRect)->bottom - (lpRect)->top)
#define DIB_HEADER_MARKER   ((WORD) ('M' << 8) | 'B')

#define WIDTHBYTES(bits)    (((bits) + 31) / 32 * 4)

/* Function prototypes */
BOOL      WINAPI  PaintDIB (HDC, LPRECT, HANDLE, LPRECT, CPalette* pPal);
BOOL      WINAPI  CreateDIBPalette(HANDLE hDIB, CPalette* cPal);
LPSTR     WINAPI  FindDIBBits (LPSTR lpbi);
DWORD     WINAPI  DIBWidth (LPSTR lpDIB);
DWORD     WINAPI  DIBHeight (LPSTR lpDIB);
WORD      WINAPI  PaletteSize (LPSTR lpbi);
BOOL WINAPI DIBSize(const HANDLE m_hDIB,SIZE *size);
int  WINAPI DIBBitsPerPixel(const HANDLE m_hDIB); 
WORD      WINAPI  DIBNumColors (LPSTR lpbi);
HGLOBAL   WINAPI  CopyHandle (HANDLE h);
BOOL      WINAPI  SaveDIB (HANDLE hDib, CFile& file);
HANDLE WINAPI ReadDIBFile(CFile& file);
void WINAPI FreeDIB(HANDLE m_hDIB);
void WINAPI GetDlgItemRect(int nID,CWnd *wndParent,LPRECT Client);
//BOOL WINAPI IsFileExsit(CString& FileName);
HANDLE WINAPI CutDIB(HANDLE hDIB,LPRECT lpRect);
//
void LetsHBMPHasProperty(HANDLE &m_Handle,const int size_x,const int size_y,const int BitsPerPixel);
BOOL InitDIBBuffers(HANDLE &m_hDIBFrame,const WORD m_wCurrMaxWidth,const WORD m_wCurrMaxHeight,const WORD m_wCurrMaxBits);
void SetDIBHeader(const HANDLE &m_hDIBFrame,const WORD m_wCurrMaxWidth,const WORD m_wCurrMaxHeight,const WORD m_wCurrMaxBits);

#endif //!_INC_DIBAPI
