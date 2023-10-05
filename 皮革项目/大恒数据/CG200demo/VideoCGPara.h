// VideoCG210Para.h: interface for the CVideoCG210Para class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_VIDEOCG210PARA_H__690BFE3A_F277_11D3_91DA_444553540001__INCLUDED_)
#define AFX_VIDEOCG210PARA_H__690BFE3A_F277_11D3_91DA_444553540001__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "cg210-32.h"
#include "cg200-32.h"
#include "DHCardID.h"

class CVideoCGPara  
{
public:
	CVideoCGPara();
	virtual ~CVideoCGPara();
public:

	int m_CGoption;		//0:	cg200,	1:	cg210
	void SetColorSpace(int nBitsPerPixel);
	void VideoParaTakeEffect(DWORD& hcg);
	void DefaultVideoPara(CString &strIniFileName);
	void SaveVideoPara(CString& strIniFileName,BOOL bDefault);
	void GetVideoPara(CString& strIniFilName,int nDefault);
	void WritePrivateProfileInt(CString strKey, CString strSection, int mValue, CString strIniFileName);

	//����4����������ƵԴ��������Classû�п�����ʾ���ڡ�
	//1,��ʾ���ڵĴ�С<=�ɼ����ڵĴ�С,	(��Ҫ����ʾ���ڲ��ܴ��ڲɼ�����)��
	//2,�ɼ����ڵĴ�С==��ʾ���ڵĴ�С	==>���÷�ʽ
	//3,�ɼ����ڵĴ�С>��ʾ���ڵĴ�С	==>Scale��ʽ
	//��ʾ���ڵ����Ͻǵ�XӦ����4�ı���
	int StartY;			//��ƵԴ�����
	int StartX;			//��ƵԴ�����
	int ImageSize_Y;	//��ƵԴ�Ĵ�С
	int ImageSize_X;	//��ƵԴ�Ĵ�С
	int nADSource;	//Դ· ��Ч��Χ�� 0~9��0~5:�������룬6~8:Y/C,9��SVideo
	int nADBri;		//���� ��Ч��Χ��0~255
	int nADCon;		//�Աȶ� ��Ч��Χ��0~255
	int nADHue;		//ɫ��  ��Ч��Χ��0~255
	int nADSat;		//ɫ���Ͷ� ��Ч��Χ��0~255
	int nVideoStand;	//0,Pal,	1,Ntsc
	int nColorSpace;	//YUV422,0	RGB888,1	RGB565,2	RGB555,3,...
	int nInterlace;		//FIELD	1,FRAME	0
	BOOL bClip;			//TRUE,����		FALSE,����
	//CG200ר�в���
	int nADBandPass;	//ǯλ��ƽ ��Ч��Χ��0~255
	int nADClamp;		//��ͨ ��Ч��Χ��0~127
	//CG210ר�в���
	//����
	//	int nAGC;		//0:normal,1:reduce,2:increase
	//	BOOL b75PEDESTAL;//FALSE:disable,TRUE:enable
	int nAGCGN;	//0:���� 68 1:��С 54
	int nAGCRGBH;//0:16 - 235 1:0-255
	int nAGCPED; //0:0%=16 - 100%=235 1:7.5%=16 - 100%=235
	int nGammaCorr;	//0:not,1:Y/C,2:U/B,V/R,3:Y/C,U/B,V/R
	//����
	int nLuma_hybwi;//0:normal,1:1MHz higher
	int nLuma_hybwr;//0:Full BW,1:Reduced BW
	BOOL bLuma_ctrap;//FALSE:Disable,TRUE:enable
	int nLuma_mnycmb;//0:auto,1:manual
	int nHYPKCtrl;	//0:less,1:normal,2:more,3:max
	int nHYLPFCtrl;	//0:Full BW,1:4.5MHz BW,2:3.5MHz BW,3:2.5MHz BW,4:1.5MHz BW
	int nYCMBCOCtrl;//0:[1/4,1/2,1/4],1:[3/8,1/2,1/8],2:[1/2,1/2.0],3:[1,0,0],4:[0,1,0],5:[1/2,0,1/2],6:[0,1/2,1/2],7:[1/8,1/2,3/8]	
	//ɫ��
	int nChroma_cbwi;//0:normal,1:increase
	int nChroma_cbwr;//0:3db BW 850KHz, 1:3db BW 550KHz	
	int nChroma_mnccmb;//0:auto,1:manual
	int nCORECtrl;	//0:not,1:range 128+-1=128,2:range 128+-3=128,3:range 128+-7=128

	int nCCMBCOCtrl;//0:[1/2,1/2,0],1:[1/4,1/2,1/4],2:[0,1/2,1/2,0,0],3:[0,1/4,1/2,1/4,0],4:[1,0,0],5:[0,1,0],6:[0,0,1],7:not
	//��״�˲�
	int nComb_acmbre;//0:high,1:low
	int nComb_acmbco;//0:100%,1:75%
	BOOL bComb_acmben;//FALSE:disable,TRUE,enable
	int nVCTRLCtrl;	//0:Scaler uses LPF, Comb uses HPF
					//1:Scaler uses full BW, Comb is disabled
					//2:Scaler is disabled, Comb uses full BW
					//3:Scaler uses LPF, Comb is disabled
					//4:Scaler is disabled, Comb uses HPF
	//Scale
	int nVerscl_vrt2x;//0:3 tap,1:5 tap
	BOOL bHorscl_hydec;//FALSE:enable,TRUE,disable
	int nVsclenctrl;//0:Enable,
					//1:Disable
					//2:Disable. Video is 1 line delayed
					//3:Disable. Video is 2 line delayed
};

#endif // !defined(AFX_VIDEOCG210PARA_H__690BFE3A_F277_11D3_91DA_444553540001__INCLUDED_)
