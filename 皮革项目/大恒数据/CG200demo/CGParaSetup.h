// TrainWheel.h : main header file for the TRAINWHEEL DLL
//
#ifndef __CGPARASETUP_H__
#define __CGPARASETUP_H__
extern "C" BOOL PASCAL EXPORT CGBoardParaSetup(DWORD hCG,int CGoption,CRect& rcDisp,CVideoCGPara& m_CVideoCG210Para);
extern "C" BOOL PASCAL EXPORT CG210AdvaceParaSetup(DWORD hCG,int CGoption,CVideoCGPara& m_CVideoCG210Para);
#endif