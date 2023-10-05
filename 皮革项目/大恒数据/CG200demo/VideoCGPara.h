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

	//下面4个参数是视频源参数，本Class没有考虑显示窗口。
	//1,显示窗口的大小<=采集窗口的大小,	(即要求显示窗口不能大于采集窗口)。
	//2,采集窗口的大小==显示窗口的大小	==>剪裁方式
	//3,采集窗口的大小>显示窗口的大小	==>Scale方式
	//显示窗口的左上角的X应该是4的倍数
	int StartY;			//视频源的起点
	int StartX;			//视频源的起点
	int ImageSize_Y;	//视频源的大小
	int ImageSize_X;	//视频源的大小
	int nADSource;	//源路 有效范围： 0~9，0~5:复合输入，6~8:Y/C,9：SVideo
	int nADBri;		//亮度 有效范围：0~255
	int nADCon;		//对比度 有效范围：0~255
	int nADHue;		//色调  有效范围：0~255
	int nADSat;		//色饱和度 有效范围：0~255
	int nVideoStand;	//0,Pal,	1,Ntsc
	int nColorSpace;	//YUV422,0	RGB888,1	RGB565,2	RGB555,3,...
	int nInterlace;		//FIELD	1,FRAME	0
	BOOL bClip;			//TRUE,剪裁		FALSE,比例
	//CG200专有参数
	int nADBandPass;	//钳位电平 有效范围：0~255
	int nADClamp;		//带通 有效范围：0~127
	//CG210专有参数
	//增益
	//	int nAGC;		//0:normal,1:reduce,2:increase
	//	BOOL b75PEDESTAL;//FALSE:disable,TRUE:enable
	int nAGCGN;	//0:正常 68 1:减小 54
	int nAGCRGBH;//0:16 - 235 1:0-255
	int nAGCPED; //0:0%=16 - 100%=235 1:7.5%=16 - 100%=235
	int nGammaCorr;	//0:not,1:Y/C,2:U/B,V/R,3:Y/C,U/B,V/R
	//亮度
	int nLuma_hybwi;//0:normal,1:1MHz higher
	int nLuma_hybwr;//0:Full BW,1:Reduced BW
	BOOL bLuma_ctrap;//FALSE:Disable,TRUE:enable
	int nLuma_mnycmb;//0:auto,1:manual
	int nHYPKCtrl;	//0:less,1:normal,2:more,3:max
	int nHYLPFCtrl;	//0:Full BW,1:4.5MHz BW,2:3.5MHz BW,3:2.5MHz BW,4:1.5MHz BW
	int nYCMBCOCtrl;//0:[1/4,1/2,1/4],1:[3/8,1/2,1/8],2:[1/2,1/2.0],3:[1,0,0],4:[0,1,0],5:[1/2,0,1/2],6:[0,1/2,1/2],7:[1/8,1/2,3/8]	
	//色度
	int nChroma_cbwi;//0:normal,1:increase
	int nChroma_cbwr;//0:3db BW 850KHz, 1:3db BW 550KHz	
	int nChroma_mnccmb;//0:auto,1:manual
	int nCORECtrl;	//0:not,1:range 128+-1=128,2:range 128+-3=128,3:range 128+-7=128

	int nCCMBCOCtrl;//0:[1/2,1/2,0],1:[1/4,1/2,1/4],2:[0,1/2,1/2,0,0],3:[0,1/4,1/2,1/4,0],4:[1,0,0],5:[0,1,0],6:[0,0,1],7:not
	//梳状滤波
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
