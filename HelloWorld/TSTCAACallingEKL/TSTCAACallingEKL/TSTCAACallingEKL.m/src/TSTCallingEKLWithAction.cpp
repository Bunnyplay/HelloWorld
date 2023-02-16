#include "TSTCallingEKLWithAction.h"
// CATPLMComponentInterfaces
#include "CATPLMSessionServices.h"

//CATPLMComponentInterfaces, for PLMReference/PLMRepReference
#include "CATIPLMNavReference.h"
#include "CATIPLMNavRepReference.h"
#include "CATIPLMNavEntity.h"

// PLMSetupDataInterfaces
#include "PLMSetupDataGlobalFunctions.h" // To access PLMISetupDataFinder
#include "PLMISetupDataFinder.h"         // To access set up data

#include "CATICkeFunction.h"
#include "CATCkeGlobalFunctions.h"

//System
#include "CATString.h" 
#include "CATSysBoolean.h"
#include "CATUnicodeString.h"
#include "CATListOfCATUnicodeString.h"
#include "CATStdIO.h" 

// KnowledgeInterfaces
#include "CATICkeSheet.h"
#include "CATICkeObject.h"

#include "CATIAdpPLMIdentificator.h"
#include "CATIPLMComponent.h"

// Library framework
/*
#include "PLMICLGLibrary.h" 
#include "PLMICLGClass.h" 
#include "PLMCLGPublicLibraryNavServices.h"
*/
// XMLParserItf , for XML parsing
#include "CATIXMLDOMDocumentBuilder.h"
#include "CATIDOMDocument.h"
#include "CATIDOMElement.h"

//others
#include "iostream.h"

// ===========================================================================================================
TSTCallingEKLWithAction::TSTCallingEKLWithAction(){}

TSTCallingEKLWithAction::~TSTCallingEKLWithAction(){}

HRESULT TSTCallingEKLWithAction::Test()
{
    HRESULT hr = E_FAIL;

    // ===========================================================================================================
    // 1- Retrieves  SetupData Finder
    // ===========================================================================================================
    CATUnicodeString SetupDataFinderID = "MyFinder";
    PLMISetupDataFinder_var setupDataFinder = PLMSetupDataGlobalFunctions::GetPLMSetupDataFinder(SetupDataFinderID);
    if ( NULL_var == setupDataFinder ) return hr;
    cout <<"   The setup data finded is retrieved " << endl;

    // ===========================================================================================================
    // 2- Retrieves the Resource
    // ===========================================================================================================
    CATUnicodeString ResourceId = "KnowledgeResources|RoutingIndexation" ;
    cout <<"   The ID of the Resource is " << ResourceId.ConvertToChar() << endl;
    CATBaseUnknown_var spRcsAsCBU = NULL_var; 
    hr = setupDataFinder->FindPointedResource(ResourceId,NULL_var,spRcsAsCBU);
    if (NULL_var !=spRcsAsCBU) 
    {
        CATICkeFunction_var spEKLAction;
        spEKLAction = spRcsAsCBU;
        if (NULL_var == spEKLAction) return hr;

        CATICkeParm_var spInputCkeParm;
        CATICkeParmFactory_var spVolFactory = CATCkeGlobalFunctions::GetVolatileFactory();
        if (!!spVolFactory)
        {
            // 3- Prepare input arguements for Action
            CATCkeListOfParm plspParameters = new CATListValCATBaseUnknown_var();
            CATIPLMNavReference_var spPLMNavRef = NULL_var; // TODO, need to get from somewhere
            spInputCkeParm = spVolFactory->CreateObjectReference(spPLMNavRef);
            plspParameters->Append(spInputCkeParm);
            //spInputCkeParm = spVolFactory->CreateString("Parameter1","val1");
            //plspParameters->Append(spInputCkeParm);
            //spInputCkeParm = spVolFactory->CreateInteger("Parameter2",2);
            //plspParameters->Append(spInputCkeParm);

            // 4- Run the action
            CATICkeParm_var spReturnedParameter;
            spEKLAction->Run(plspParameters, spReturnedParameter);
            delete plspParameters;
        }
    }
    // ===========================================================================================================
    // 5- Removes the SetupData Finder
    // ===========================================================================================================
    hr = PLMSetupDataGlobalFunctions::RemovePLMSetupDataFinder(SetupDataFinderID);
    if (E_FAIL == hr ) return hr;
    cout <<"   The setup data finded is released " << endl;
    return hr ;
}

