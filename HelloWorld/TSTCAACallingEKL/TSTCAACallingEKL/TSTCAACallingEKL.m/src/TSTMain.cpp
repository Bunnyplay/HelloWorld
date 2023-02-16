//============================================================================================
//Return code      :
//				     0 successful execution
//				     1 execution failed
//============================================================================================      
#include "TSTCallingEKLWithAction.h"
#include "TSTCallingEKLWithBR.h"


// CATPLMComponentInterfaces
#include "CATPLMSessionServices.h"

//System
#include "CATString.h" 
#include "CATSysBoolean.h"
#include "CATUnicodeString.h"
#include "CATListOfCATUnicodeString.h"
#include "CATStdIO.h" 

//others
#include "iostream.h"

// ===========================================================================================================
HRESULT  InitSession (CATUnicodeString repository,
		CATUnicodeString server,
		CATUnicodeString user,
		CATUnicodeString password,
		CATUnicodeString role);
// ===========================================================================================================

int main(int iArgc, char *iArgv[])
{
	HRESULT hr = E_FAIL;
	cout << "TSTMain starts" << endl;

	// ===========================================================================================================
	// 1- Creates Session and connect to the input repository
	// ===========================================================================================================
	 
	hr = InitSession(iArgv[1], iArgv[2], iArgv[3], iArgv[4], iArgv[5]) ;
	if ( FAILED(hr) ) return 1;
	cout <<"   The session is created" << endl;

    cout << "   Test TSTCallingEKLWithAction" <<endl ;
    TSTCallingEKLWithAction toto;
    hr = toto.Test();

    cout << "   Test TSTCallingEKLWithBR" <<endl ;
    TSTCallingEKLWithBR titi;
    hr = titi.Test();

	// ===========================================================================================================
	// 4- Closes Session  
	// ===========================================================================================================
	hr = CATPLMSessionServices::ClosePLMSession();
	if ( FAILED(hr)) return 1;
	cout <<"   The session is closed" << endl;

	cout << "TSTMain ends ..." << endl;
	return 0 ;
}

// ===========================================================================================================
// 2- Creates Session and connect to the input repository
// ===========================================================================================================
	 
HRESULT  InitSession (CATUnicodeString repository,
		CATUnicodeString server,
		CATUnicodeString user,
		CATUnicodeString password,
		CATUnicodeString role)
{
	HRESULT hr = CATPLMSessionServices::SetPLMSessionParameter("Repository", repository);
	if (SUCCEEDED(hr) && server.GetLengthInChar() > 0 && server!="null")
		hr = CATPLMSessionServices::SetPLMSessionParameter("Server", server);

	if (SUCCEEDED(hr) && user.GetLengthInChar() > 0)
		hr = CATPLMSessionServices::SetPLMSessionParameter("UserID", user);

	if (SUCCEEDED(hr) && password.GetLengthInChar() > 0)
		hr = CATPLMSessionServices::SetPLMSessionParameter("UserPasswd", password);

	if (SUCCEEDED(hr) && role.GetLengthInChar() > 0)
		hr = CATPLMSessionServices::SetPLMSessionParameter("SecurityCtx", role);

	if (SUCCEEDED(hr))
		hr = CATPLMSessionServices::InitPLMSession();

	return hr ;
};

