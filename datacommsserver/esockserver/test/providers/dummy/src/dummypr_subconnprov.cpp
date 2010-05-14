// Copyright (c) 2005-2009 Nokia Corporation and/or its subsidiary(-ies).
// All rights reserved.
// This component and the accompanying materials are made available
// under the terms of "Eclipse Public License v1.0"
// which accompanies this distribution, and is available
// at the URL "http://www.eclipse.org/legal/epl-v10.html".
//
// Initial Contributors:
// Nokia Corporation - initial contribution.
//
// Contributors:
//
// Description:
// Dummy implementation file for a SubConnection Provider
// 
//

/**
 @file
 @internalComponent
*/

#include <comms-infras/ss_log.h>
#include <comms-infras/corescpractivities.h>
#include <cs_subconparams.h>
#include <cs_subconevents.h>

#include "dummypr_subconnprov.h"
#include "dummypr_metaconnprov.h"
#include "activityTest.h"

#include <elements/sd_mintercept.h>

#ifdef __CFLOG_ACTIVE
	#define KDummySCPRTag KESockConnectionTag
#endif

using namespace ESock;
using namespace MeshMachine;

//We reserve space for two preallocated activities that may start concurrently on the SCPR
//node: destroy and data client stop.
static const TUint KDefaultMaxPreallocatedActivityCount = 2;
static const TUint KMaxPreallocatedActivitySize = sizeof(MeshMachine::CNodeRetryParallelActivity) + sizeof(MeshMachine::APreallocatedOriginators<4>);
static const TUint KDummySCPRPreallocatedActivityBufferSize = KDefaultMaxPreallocatedActivityCount * KMaxPreallocatedActivitySize;

namespace DummySCPRStates
{
DEFINE_SMELEMENT(TRaiseGranted, NetStateMachine::MStateTransition, DummySCPRStates::TContext)
void TRaiseGranted::DoL()
	{
	if (iContext.Node().incomingStatus == TRUE)
		{
		//generate paramsgranted.
		CSubConGenEventParamsGranted* grantedevent = CSubConGenEventParamsGranted::NewL();
	    grantedevent->SetFamily(KSubConQoSFamily);
	    iContext.Node().NotifyClientsL(*grantedevent);
	    iContext.Node().incomingStatus = FALSE;
		}
	}

DEFINE_SMELEMENT(TAwaitingReBindTo, NetStateMachine::MState, DummySCPRStates::TContext)
TBool TAwaitingReBindTo::Accept()
	{
	const TLayerSelectionInfo* selectionInfo = static_cast<const TLayerSelectionInfo*>(
		iContext.Node().AccessPointConfig().FindExtension(TLayerSelectionInfo::TypeId()));
	ASSERT(selectionInfo); // should always be there
	
	TCFDataClient::TBindTo* bindToMsg = Messages::message_cast<TCFDataClient::TBindTo>(&iContext.iMessage);
	if (bindToMsg && iContext.Node().ServiceProvider() && bindToMsg->iNodeId != iContext.Node().ServiceProvider()->RecipientId())
	    {
	    if (TCprConfigModifier::Is(selectionInfo->CprConfig(), TCprConfigModifier::ESCPRHangOnRebind))
	        {
	        return ETrue;
	        }
	    else if (TCprConfigModifier::Is(selectionInfo->CprConfig(), TCprConfigModifier::ESCPRFailOnRebind))
	        {
	        iContext.iMessage.ClearMessageId();
	        Messages::RClientInterface::OpenPostMessageClose(iContext.NodeId(), iContext.iSender, 
                Messages::TEBase::TError(KErrAbort).CRef());
	        }
	    }
	return EFalse;
	}

DEFINE_SMELEMENT(TAwaitingBrokenStart, NetStateMachine::MState, DummySCPRStates::TContext)
TBool TAwaitingBrokenStart::Accept()
	{
	const TLayerSelectionInfo* selectionInfo = static_cast<const TLayerSelectionInfo*>(
		iContext.Node().AccessPointConfig().FindExtension(TLayerSelectionInfo::TypeId()));
	ASSERT(selectionInfo); // should always be there

	return (iContext.iMessage.IsMessage<TCFDataClient::TStart>() && 
			TCprConfigModifier::Is(selectionInfo->CprConfig(), TCprConfigModifier::ESCPRHangOnStart));
	}
}

namespace DummySCprParamsRequest
{
#ifdef SYMBIAN_ADAPTIVE_TCP_RECEIVE_WINDOW
DECLARE_DEFINE_NODEACTIVITY(ECFActivityParamRequest, dummySCprParamRequest, TCFScpr::TSetParamsRequest)
	NODEACTIVITY_ENTRY(KNoTag, PRStates::TRespondWithCurrentParams, PRStates::TAwaitingParamRequest,  MeshMachine::TNoTag)
#else
DECLARE_DEFINE_NODEACTIVITY(ECFActivityParamRequest, dummySCprParamRequest, TCFScpr::TParamsRequest)
	NODEACTIVITY_ENTRY(KNoTag, SCprStates::TRespondWithCurrentParams, SCprStates::TAwaitingParamRequest,  MeshMachine::TNoTag)
#endif // SYMBIAN_ADAPTIVE_TCP_RECEIVE_WINDOW
NODEACTIVITY_END()
}

namespace DummyBindToActivity
{
DECLARE_DEFINE_NODEACTIVITY(ECFActivityBindTo, dummyBindTo, TCFDataClient::TBindTo)
	FIRST_NODEACTIVITY_ENTRY(DummySCPRStates::TAwaitingReBindTo, MeshMachine::TNoTag)
	NODEACTIVITY_ENTRY(KNoTag, MeshMachine::TDoNothing, CoreStates::TNeverAccept,  MeshMachine::TNoTag)
	LAST_NODEACTIVITY_ENTRY(KNoTag, MeshMachine::TDoNothing)
NODEACTIVITY_END()
}

namespace DummyBreakStartActivity
{
DECLARE_DEFINE_CUSTOM_NODEACTIVITY(ECFActivityStart, dummyBreakSCPrStart, TCFDataClient::TStart, PRActivities::CStartActivity::NewL)
    FIRST_NODEACTIVITY_ENTRY(DummySCPRStates::TAwaitingBrokenStart, MeshMachine::TNoTag)
	NODEACTIVITY_ENTRY(KNoTag, MeshMachine::TDoNothing, CoreStates::TNeverAccept,  MeshMachine::TNoTag)
	LAST_NODEACTIVITY_ENTRY(KNoTag, MeshMachine::TDoNothing)
NODEACTIVITY_END()
}

namespace DummyStartActivity
{
DECLARE_DEFINE_CUSTOM_NODEACTIVITY(ECFActivityStart, dummySCPrStart, TCFServiceProvider::TStart, PRActivities::CStartActivity::NewL)
    FIRST_NODEACTIVITY_ENTRY(CoreNetStates::TAwaitingStart, MeshMachine::TNoTag)
 	THROUGH_NODEACTIVITY_ENTRY(KNoTag, CoreNetStates::TSendStarted, MeshMachine::TNoTag)
 	LAST_NODEACTIVITY_ENTRY(KNoTag, DummySCPRStates::TRaiseGranted)
NODEACTIVITY_END()
}

// Activity Map For test-code ridden scpr
namespace DummySCPRStates
{
DEFINE_ACTIVITY_MAP(stateMap)
   ACTIVITY_MAP_ENTRY(DummySCprParamsRequest, dummySCprParamRequest)
   ACTIVITY_MAP_ENTRY(DummyBindToActivity, dummyBindTo)
   ACTIVITY_MAP_ENTRY(DummyBreakStartActivity, dummyBreakSCPrStart)   
   ACTIVITY_MAP_ENTRY(DummyStartActivity, dummySCPrStart)   
ACTIVITY_MAP_END_BASE(SCprActivities, coreSCprActivities)
}

// Activity Map For vanilla cpr
namespace VanillaDummySCPRStates
{
DECLARE_DEFINE_ACTIVITY_MAP(stateMap)
        ACTIVITY_MAP_ENTRY(CancelTestBindToActivity, CancelBindTo)   
ACTIVITY_MAP_END_BASE(SCprActivities, coreSCprActivities)
}

CDummySubConnectionProvider* CDummySubConnectionProvider::NewL(ESock::CSubConnectionProviderFactoryBase& aFactory)
    {
    CDummySubConnectionProvider* self = new (ELeave) CDummySubConnectionProvider(aFactory, DummySCPRStates::stateMap::Self());
    CleanupStack::PushL(self);
    self->ConstructL(KDummySCPRPreallocatedActivityBufferSize);
    CleanupStack::Pop(self);
    return self;
    }

CDummySubConnectionProvider* CDummySubConnectionProvider::NewVanillaL(ESock::CSubConnectionProviderFactoryBase& aFactory)
    {
    CDummySubConnectionProvider* self = new (ELeave) CDummySubConnectionProvider(aFactory, VanillaDummySCPRStates::stateMap::Self());
    CleanupStack::PushL(self);
    self->ConstructL(KDummySCPRPreallocatedActivityBufferSize);
    CleanupStack::Pop(self);
    return self;
    }


CDummySubConnectionProvider::CDummySubConnectionProvider(CSubConnectionProviderFactoryBase& aFactory, const MeshMachine::TNodeActivityMap& aActivityMap)
:CCoreSubConnectionProvider(aFactory, aActivityMap)
	{
	LOG_NODE_CREATE(KDummySCPRTag, CDummySubConnectionProvider);
	}

CDummySubConnectionProvider::~CDummySubConnectionProvider()
	{
	LOG_NODE_DESTROY(KDummySCPRTag, CDummySubConnectionProvider);
	}


void CDummySubConnectionProvider::SetToIncomingL()
	{
 	_LIT(KName,"Test1");
 	TBuf<5> paramName(KName);

 	const int qosParams = 128;

	//RCFParameterFamilyBundle& pfb = CreateParameterBundleL();
	//RParameterFamily family = pfb.CreateFamilyL(KSubConQoSFamily); //PJLEFT
	RCFParameterFamilyBundle newBundle;
	newBundle.CreateL();
	iParameterBundle.Open(newBundle);
	RParameterFamily family = newBundle.CreateFamilyL(KSubConQoSFamily);

	// Create the generic set
	CSubConQosGenericParamSet* isubConQosGenParSet = CSubConQosGenericParamSet::NewL(family, RParameterFamily::EGranted);

    isubConQosGenParSet->SetHeaderMode(0);
    isubConQosGenParSet->SetName(paramName);
    isubConQosGenParSet->SetDownlinkBandwidth(qosParams);
    isubConQosGenParSet->SetDownLinkMaximumBurstSize(qosParams);
    isubConQosGenParSet->SetDownLinkAveragePacketSize(qosParams);
    isubConQosGenParSet->SetDownLinkDelay(qosParams);
    isubConQosGenParSet->SetDownLinkDelayVariation(qosParams);
   	isubConQosGenParSet->SetDownLinkMaximumBurstSize(qosParams);
   	isubConQosGenParSet->SetDownLinkPriority(qosParams);
   	isubConQosGenParSet->SetDownLinkMaximumPacketSize(qosParams);

   	isubConQosGenParSet->SetUpLinkAveragePacketSize(qosParams);
   	isubConQosGenParSet->SetUpLinkDelay(qosParams);
   	isubConQosGenParSet->SetUplinkBandwidth(qosParams);
   	isubConQosGenParSet->SetUpLinkDelayVariation(qosParams);
   	isubConQosGenParSet->SetUpLinkMaximumBurstSize(qosParams);
   	isubConQosGenParSet->SetUpLinkMaximumPacketSize(qosParams);
   	isubConQosGenParSet->SetUpLinkPriority(qosParams);

 	incomingStatus = ETrue;
	}






