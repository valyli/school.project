#include <WINDOWS.H>

#ifdef __cplusplus
extern "C" {
#endif

BOOL WINAPI GetBiosId(LPCTSTR lpBiosId);

BOOL WINAPI GetBiosType(LPCTSTR lpBiosType);

BOOL WINAPI GetBiosDate(LPCTSTR lpBiosDate);


#ifdef __cplusplus
}
#endif
