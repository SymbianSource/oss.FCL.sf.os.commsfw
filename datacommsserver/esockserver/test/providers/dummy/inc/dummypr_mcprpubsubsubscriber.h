// Copyright (c) 2007-2009 Nokia Corporation and/or its subsidiary(-ies).
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
//

/**
 @file
 @internalTechnology
 @prototype
*/


#ifndef _DUMMYPR_MCPrPUBSUBSUBSCRIBER_H_
#define _DUMMYPR_MCPrPUBSUBSUBSCRIBER_H_

#include <e32property.h>
#include <e32base.h>
#include <elements/nm_messages_base.h>
#include <comms-infras/ss_nodemessages.h>
#include <comms-infras/ss_mmcommsprov.h>
#include <comms-infras/ss_metaconnprov.h>


NONSHARABLE_CLASS(CMCPrPubSubSubscriber) : public CActive, public Messages::ASimpleNodeIdBase
	{
public:
	static CMCPrPubSubSubscriber* NewL(const ESock::CMetaConnectionProviderBase& aProvBase, TUint aStopCode);
	void StartAvailabilityMonitoringL(const Messages::TNodeCtxId& aAvailabilityActivity);
	void CancelAvailabilityMonitoring();
	virtual ~CMCPrPubSubSubscriber();

    enum
    {
		KStart			= 1, // Causes a TStart message to be issued
		KBlockingStop   = 2, // Causes a TStop to be issued and increments the blocking count to stop the node from being cleaned up.
		KStop	        = 3  // Causes a TStop to be issued;
	};
    
    enum { EAvailabilityTestingPubSubUid = 0x10272F42 };  
    virtual void ReceivedL(const Messages::TRuntimeCtxId& /*aSender*/, const Messages::TNodeId& /*aRecipient*/, Messages::TSignatureBase& aMessage)
        {
        //This object is only a node because its host needs an TCFClientType::EAvailabilityProvider, which
        //can't be the same as the node.
        //Unfortunatelly the CAvailabilityActivity is really persistent when it comes to sending TCancel to
        //availability providers. This can't be avoided here for now.
        if (!aMessage.IsMessage<Messages::TEBase::TCancel>())
            {
            ASSERT(EFalse);
            }
        }


private:
	CMCPrPubSubSubscriber(const ESock::CMetaConnectionProviderBase& aProvBase, TUint aStopCode);
	void StartL();
	void RunL();
	TInt RunError(TInt aError);
	void DoCancel();

private:
    const ESock::CMetaConnectionProviderBase& iNode;
	TInt iStopCode;
	RProperty iProperty;
	TBool iBlocking;
	
	//the availablity activity subscribing for pubsub availablity changes.
	Messages::TNodeCtxId iAvailabilityActivity;
	};

#endif // _DUMMYPR_MCPrPUBSUBSUBSCRIBER_H_
