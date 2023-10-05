// SoundView.cpp : implementation of the CSoundView class
//

#include "stdafx.h"
#include "Sound.h"

#include "SoundDoc.h"
#include "SoundView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSoundView

IMPLEMENT_DYNCREATE(CSoundView, CView)

BEGIN_MESSAGE_MAP(CSoundView, CView)
	//{{AFX_MSG_MAP(CSoundView)
	ON_WM_KEYDOWN()
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSoundView construction/destruction

CSoundView::CSoundView()
{
	m_pDSObject=NULL;
	m_pDSBuffer=NULL;
	m_pDSMix=NULL;
}

CSoundView::~CSoundView()
{
	if (m_pDSMix) m_pDSMix->Release();
	if (m_pDSBuffer) m_pDSBuffer->Release();
	if (m_pDSObject) m_pDSObject->Release();
}

void CSoundView::PlayFreq(double dFreq)
{
	if (!m_pDSObject)
	{
		//Create the Direct Sound Object
		if (DS_OK==DirectSoundCreate(
							NULL,&m_pDSObject,NULL))
		{
			//Set the Co-Operation level
			m_pDSObject->SetCooperativeLevel(m_hWnd,DSSCL_NORMAL);


			//Set the direct sound buffer
			memset(&m_DSBufferDesc,0,sizeof(DSBUFFERDESC));

			//Setup a secondary buffer
			m_DSBufferDesc.dwSize=sizeof(DSBUFFERDESC);
			m_DSBufferDesc.dwFlags=DSBCAPS_CTRLDEFAULT;
			m_DSBufferDesc.dwBufferBytes=4096;

			//Set a wave format for 22.0Khz,1 byte DtoA
			static WAVEFORMATEX sWave={
				WAVE_FORMAT_PCM,1,22000,22000,1,8,0};

			m_DSBufferDesc.lpwfxFormat=&sWave;

			//Create the First Secondary buffer
			m_pDSObject->CreateSoundBuffer(&m_DSBufferDesc,
										&m_pDSBuffer,NULL);

			//Create the Second Secondary buffer
			m_pDSObject->CreateSoundBuffer(&m_DSBufferDesc,
										&m_pDSMix,NULL);
		}
	}

	//if the DirectSound object is valid...
	if (m_pDSObject)
	{
		//Declare buffer pointers
		LPBYTE pBuffer1,pBuffer2;
		LPBYTE pEnv1,pEnv2;
		DWORD dwSize1,dwSize2;

		//Erase the background
		CClientDC dcClient(this);
		CRect rcClient;
		GetClientRect(&rcClient);
		int yOff=(rcClient.Height()-24)/3;
		dcClient.FillSolidRect(
			rcClient,RGB(255,255,255));

		//Lock the sound buffer
		m_pDSBuffer->Lock(0,m_DSBufferDesc.dwBufferBytes,
			(LPVOID*) &pBuffer1,&dwSize1,
			(LPVOID*) &pBuffer2,&dwSize2,0);
		m_pDSMix->Lock(0,m_DSBufferDesc.dwBufferBytes,
			(LPVOID*) &pEnv1,&dwSize1,
			(LPVOID*) &pEnv2,&dwSize2,0);

		//Set the two buffers
		double dRange=128.0/(double)dwSize1;
		double dXRange=(double)rcClient.Width()
						/(double) dwSize1;
		for (int i=0;i<(int) dwSize1;i++)
		{
			double dAmplitude=1.0+dRange*(double)i;
			BYTE b1=(BYTE)(127+(128.0-dAmplitude)
							*sin((double)i/(0.147*dFreq)));
			BYTE b2=(BYTE)(rand()%(int)dAmplitude)>>1;
			*(pBuffer1+i)=b1;
			*(pEnv1+i)=b2;

			BYTE b3=b1+b2;

			//Draw the waveform
			int x=(int)(dXRange*(double)i);
			dcClient.SetPixelV(x,
				(b1>>1),RGB(255,0,0));
			dcClient.SetPixelV(x,yOff+64+
				(b2>>1),RGB(0,255,0));
			dcClient.SetPixelV(x,yOff*2+
				(b3>>1),RGB(0,0,255));
		}

		//Unlock the buffers and play the sound
		m_pDSBuffer->Unlock(pBuffer1,dwSize1,
						pBuffer2,dwSize2);
		m_pDSMix->Unlock(pEnv1,dwSize1,
						pEnv2,dwSize2);
		m_pDSBuffer->Play(0,0,0);
		m_pDSMix->Play(0,0,0);
	}
}

void CSoundView::OnKeyDown(UINT nChar, UINT nRepCnt,
										UINT nFlags) 
{
	CView::OnKeyDown(nChar, nRepCnt, nFlags);

	//Play the note with a freqency of the key value
	if (nRepCnt==1) PlayFreq((double) nChar);
}

BOOL CSoundView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CSoundView drawing

void CSoundView::OnDraw(CDC* pDC)
{
	CSoundDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	// TODO: add draw code for native data here
}

/////////////////////////////////////////////////////////////////////////////
// CSoundView printing

BOOL CSoundView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CSoundView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CSoundView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CSoundView diagnostics

#ifdef _DEBUG
void CSoundView::AssertValid() const
{
	CView::AssertValid();
}

void CSoundView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CSoundDoc* CSoundView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CSoundDoc)));
	return (CSoundDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CSoundView message handlers


