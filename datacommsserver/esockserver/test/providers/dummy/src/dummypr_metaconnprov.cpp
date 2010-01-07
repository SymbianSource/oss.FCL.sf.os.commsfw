// Copyright (c) 2006-2009 Nokia Corporation and/or its subsidiary(-ies).
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
// IPProto MCPR
//
//

/**
 @file
 @internalComponent
*/


#include <comms-infras/ss_log.h>
#include <comms-infras/coremcprstates.h>
#include <comms-infras/coremcpractivities.h>
#include <elements/nm_messages_errorrecovery.h>
#include <comms-infras/mobilitymcpractivities.h>
#include "dummypr_metaconnprov.h"
#include "dummypr_mcprpubsubsubscriber.h"

#ifdef _DEBUG
#define KDummyMCprTag KESockMetaConnectionTag
_LIT8(KDummyMCprSubTag, "dummymcpr");
#endif

using namespace ESock;
using namespace NetStateMachine;
using namespace MCprActivities;
using namespace Messages;
using namespace MeshMachine;



CDummyMetaConnectionProvider* CDummyMetaConnectionProvider::NewL(CMetaConnectionProviderFactoryBase& aFactory,
                                                                     const TProviderInfo& aProviderInfo)
	{
	CDummyMetaConnectionProvider* self = new (ELeave) CDummyMetaConnectionProvider(aFactory,aProviderInfo,MobilityMCprActivities::mobilityMCprActivities::Self());
	CleanupStack::PushL(self);
	self->ConstructL();
	CleanupStack::Pop(self);
	return self;
	}

CDummyMetaConnectionProvider::CDummyMetaConnectionProvider(CMetaConnectionProviderFactoryBase& aFactory,
                                                               const TProviderInfo& aProviderInfo,
                                                               const MeshMachine::TNodeActivityMap& aActivityMap)
:	CMobilityMetaConnectionProvider(aFactory,aProviderInfo,aActivityMap)
	{
	LOG_NODE_CREATE(KDummyMCprTag, CDummyMetaConnectionProvider);
	}

CDummyMetaConnectionProvider::~CDummyMetaConnectionProvider()
	{
	delete iPubSubAvailability;
	delete iPubSubStopTrigger;
	LOG_NODE_DESTROY(KDummyMCprTag, CDummyMetaConnectionProvider);
	}

void CDummyMetaConnectionProvider::ConstructL()
    {
    CMobilityMetaConnectionProvider::ConstructL();
    iPubSubAvailability = CMCPrPubSubAvailability::NewL(*this, ProviderInfo().APId());
    iPubSubStopTrigger  = CMCPrPubSubStopTrigger::NewL(*this, 0);
    }

void CDummyMetaConnectionProvider::ReceivedL(const TRuntimeCtxId& aSender, const TNodeId& aRecipient, TSignatureBase& aMessage)
    {
	__CFLOG_VAR((KDummyMCprTag, KDummyMCprSubTag, _L8("CDummyMetaConnectionProvider %08x:\tReceived() aMessage=%d"),
	   this, aMessage.MessageId().MessageId()));

	TNodeContext<CDummyMetaConnectionProvider> ctx(*this, aMessage, aSender, aRecipient);
    CCoreMetaConnectionProvider::Received(ctx);

    User::LeaveIfError(ctx.iReturn);
	}

void CDummyMetaConnectionProvider::StartAvailabilityMonitoringL(const Messages::TNodeCtxId& aAvailabilityActivity)
    {
    if (!GetFirstClient<TDefaultClientMatchPolicy>(TClientType(TCFClientType::EServProvider)))
        {
        ASSERT(iPubSubAvailability!=NULL);
        RNodeInterface* peer = AddClientL(iPubSubAvailability->Id(), TClientType(TClientType::ERegistrar, TCFClientType::EAvailabilityProvider));
        iPubSubAvailability->StartAvailabilityMonitoringL(aAvailabilityActivity);
        }
    }

void CDummyMetaConnectionProvider::CancelAvailabilityMonitoring()
    {
    if (!GetFirstClient<TDefaultClientMatchPolicy>(TClientType(TCFClientType::EServProvider)))
        {
        ASSERT(iPubSubAvailability!=NULL);
        RemoveClient(iPubSubAvailability->Id());
        iPubSubAvailability->CancelAvailabilityMonitoring();
        }
    }

