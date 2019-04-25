#ifndef ASSCheckHardware_h
#define ASSCheckHardware_h


#include "windows.h"
#include "ASSFaceCodes.h"
#include <string>  

using namespace std;

typedef BOOL(__stdcall * pfnGetSystemTimes)(LPFILETIME lpIdleTime,
	LPFILETIME lpKernelTime, LPFILETIME lpUserTime);

static pfnGetSystemTimes s_pfnGetSystemTimes = NULL;

static HMODULE s_hKernel = NULL;

class ASSCheckHardware
{
public:
	ASSCheckHardware();
	~ASSCheckHardware();
	long CheckMemoryCurrentlyAvailable();
	int CpuUsage(void);
	void GetSystemTimesAddress();

private:


};

#endif
