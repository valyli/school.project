//此段代码引自 Eugene Olafsen(美)等著'MFC Programming with Visual C++ 6 Unleashed'
//May.8
//-----------------------------------------------------------------
// Wave Object
// C++ Header - Wave.h
//-----------------------------------------------------------------

#ifndef __WAVE_H__
#define __WAVE_H__

//-----------------------------------------------------------------
// Inclusions
//-----------------------------------------------------------------
#include <MMSystem.h>

//-----------------------------------------------------------------
// CWave Class - Wave Object
//-----------------------------------------------------------------
class CWave : public CObject {
  // Public Constructor(s)/Destructor
public:
          CWave();
          CWave(const CString& sFileName);
          CWave(UINT uiResID, HMODULE hmod =
            AfxGetInstanceHandle());
  virtual ~CWave();

  // Public Methods
public:
  BOOL    Create(const CString& sFileName);
  BOOL    Create(UINT uiResID, HMODULE hmod =
            AfxGetInstanceHandle());
  BOOL    IsValid() const { return (m_pImageData ? TRUE :
            FALSE); };
  BOOL    Play(BOOL bAsync = TRUE, BOOL bLooped = FALSE) const;
  BOOL    GetFormat(WAVEFORMATEX& wfFormat) const;
  DWORD   GetDataLen() const;
  DWORD   GetData(BYTE*& pWaveData, DWORD dwMaxToCopy) const;

  // Protected Methods
protected:
  BOOL    Free();

  // Private Data
private:
  BYTE* m_pImageData;
  DWORD m_dwImageLen;
  BOOL  m_bResource;
};

#endif
