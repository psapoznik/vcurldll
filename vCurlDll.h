// The following ifdef block is the standard way of creating macros which make exporting 
// from a DLL simpler. All files within this DLL are compiled with the VCURLDLL_EXPORTS
// symbol defined on the command line. this symbol should not be defined on any project
// that uses this DLL. This way any other project whose source files include this file see 
// VCURLDLL_API functions as being imported from a DLL, whereas this DLL sees symbols
// defined with this macro as being exported.
#ifdef VCURLDLL_EXPORTS
#define VCURLDLL_API __declspec(dllexport)
#else
#define VCURLDLL_API __declspec(dllimport)
#endif

// This class is exported from the vCurlDll.dll
class VCURLDLL_API CvCurlDll {
public:
	CvCurlDll(void);
	// TODO: add your methods here.
};

extern VCURLDLL_API int nvCurlDll;

VCURLDLL_API int fnvCurlDll(void);
