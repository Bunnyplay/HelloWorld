#include "TSTCallingEKLWithBR.h"

// PLMSetupDataInterfaces
#include "PLMSetupDataGlobalFunctions.h"			 // To access PLMIBusinessRuleExecutionManager
#include "PLMIBusinessRuleExecutionManager.h"        // To access set up data

//System
#include "CATString.h" 
#include "CATSysBoolean.h"
#include "CATUnicodeString.h"
#include "CATListOfCATUnicodeString.h"
#include "CATStdIO.h" 

// KnowledgeInterfaces
#include "CATICkeObject.h"
#include "CATCkeGlobalFunctions.h"
#include "CATICkeParmFactory.h"
#include "CATIList.h"
#include "CATCkeObjectAttrReadServices.h"

#include "CATIAdpPLMIdentificator.h"
#include "CATIPLMComponent.h"


//others
#include "iostream.h"

// ===========================================================================================================

TSTCallingEKLWithBR::TSTCallingEKLWithBR (){}

TSTCallingEKLWithBR::~TSTCallingEKLWithBR (){}


HRESULT TSTCallingEKLWithBR::Test()
{
	HRESULT hr = E_FAIL;

	// ===========================================================================================================
	// 1- Retrieves  PLMIBusinessRuleExecutionManager
	// ===========================================================================================================
	PLMIBusinessRuleExecutionManager_var businessRuleManager = PLMSetupDataGlobalFunctions::GetBusinessRuleExecutionManager();
	if ( NULL_var == businessRuleManager ) return hr;
    cout <<"   The business rule manager is retrieved " << endl;

	// 2- Creation of a fake object to invoke the business rules on it
	CATICkeObject_var iFakeObject;
	if (FAILED(businessRuleManager->CreateVolatileInstance (iFakeObject))) return hr;
	if (NULL_var==iFakeObject) return hr;

	// 3- Creation of the context for the first opening ID
	CATUnicodeString businessRuleOpeningId1 ("TestBR"); 
	CATLISTV(CATICkeParm_var) iListAttributeValuesForContext;
	// Retrieving volatile factory 
	CATICkeParmFactory_var volatileFactory = CATCkeGlobalFunctions::GetVolatileFactory();
	if (NULL_var==volatileFactory) return hr;
	// Creating Parameter1, Parameter2 and OutputList
	iListAttributeValuesForContext.Append(volatileFactory->CreateString("Parameter1","val1"));
	iListAttributeValuesForContext.Append(volatileFactory->CreateInteger("Parameter2",2));
	iListAttributeValuesForContext.Append(volatileFactory->CreateList("OutputList"));
	// Need to add the parameters defined in TestBR
	CATICkeObject_var iContextForID1;
	if (FAILED(businessRuleManager->ProduceBusinessRuleContext (businessRuleOpeningId1,iListAttributeValuesForContext,iContextForID1))) return hr;
	if (NULL_var == iContextForID1) return hr;

	// Calling business rule on fake object
	CATBoolean oValidationResult = TRUE;
	CATUnicodeString oMessage;
    int oSeverity=0;
    cout <<"   Executing a validation business rule " << endl;
	if (FAILED(businessRuleManager->PerformValidation (businessRuleOpeningId1,iFakeObject,iContextForID1,oValidationResult,oMessage,oSeverity))) return hr;

	return S_OK ;
}
