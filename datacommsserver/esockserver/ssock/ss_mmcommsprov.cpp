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
//

/**
 @file SS_NODE.CPP
*/

#include "ss_mmcommsprov.h"
#include <elements/nm_messages_child.h>


#ifdef _DEBUG
// Panic category for "absolutely impossible!" vanilla ASSERT()-type panics from this module
// (if it could happen through user error then you should give it an explicit, documented, category + code)
_LIT(KSpecAssert_ESockSSocksmcmsp, "ESockSSocksmcmsp");
#endif

using namespace ESock;
using namespace Messages;

CMMCommsProviderBase::CMMCommsProviderBase(CCommsFactoryBase& aFactory,
                                    const MeshMachine::TNodeActivityMap& aActivityMap)
:	ACommsFactoryNodeId(aFactory),
	ACFMMNodeBase(aActivityMap, ANodeId::Id()),
	TIfStaticFetcherNearestInHierarchy(this)
    {
    }

CMMCommsProviderBase::~CMMCommsProviderBase()
    {
#ifdef SYMBIAN_ADAPTIVE_TCP_RECEIVE_WINDOW
	if(!iParameterBundle.IsNull())
		{
		iParameterBundle.Close();
		}
#endif // SYMBIAN_ADAPTIVE_TCP_RECEIVE_WINDOW
    }


EXPORT_C void CMMCommsProviderBase::SetParametersL(const RCFParameterFamilyBundleC& aParameterBundle)
/** Request from a control client to set the parameters of this mm-comms provider

@param aParameterBundle Bundle of parameters to be applied to this mm-comms node
@exception Leaves with System Error Code dependant on the implementation of the mm-comms provider */
	{
	if (! iParameterBundle.IsNull())
		{
		iParameterBundle.Close();
		}
	iParameterBundle.Open(aParameterBundle);
	}

EXPORT_C RCFParameterFamilyBundleC& CMMCommsProviderBase::GetOrCreateParameterBundleL()
	{
	if( ! iParameterBundle.IsNull())
		{
		return iParameterBundle;
		}
	return CreateParameterBundleL();
	}
	
EXPORT_C RCFParameterFamilyBundleC& CMMCommsProviderBase::CreateParameterBundleL()
{
	__ASSERT_DEBUG(iParameterBundle.IsNull(), User::Panic(KSpecAssert_ESockSSocksmcmsp, 1));

	RCFParameterFamilyBundle newBundle;
	newBundle.CreateL();
	iParameterBundle.Open(newBundle);

	return iParameterBundle;
}

/*
void CMMCommsProviderBase::AddCtrlProviderNJoinAsDataClientL( const Messages::TSignatureBase& aCFMessage, TInt aJoinFlags )
    {
   	AddClientL(aCFMessage.iSender, TClientType(TCFClientType::ECtrlProvider));
#ifndef __GCCXML__
	EJoined(Factory().ParentContainer()(),
			aCFMessage.ActivityId(),
	    	(*this)(),
	    	CFNODE_SET_CLIENT_TYPENFLAGS(RNodeInterface::EData, aJoinFlags)
		).PostTo(aCFMessage.iSender);
#endif
    }
*/
EXPORT_C NetInterfaces::TInterfaceControl* CMMCommsProviderBase::FetchNodeInterfaceControlL(TInt aInterfaceId)
	{
	return ACFMMNodeBase::FetchNodeInterfaceControlL(aInterfaceId);
	}

EXPORT_C const RMetaExtensionContainerC& CMMCommsProviderBase::GetAccessPointConfig() const
	{
	return AccessPointConfig();
	}

EXPORT_C void CMMCommsProviderBase::ReturnInterfacePtrL(MAccessPointConfigApi*& aInterface)
	{
	aInterface = this;
	}

void CMMCommsProviderBase::DestroyOrphanedDataClients()
	{
	//Destroy orphaned data clients
	RNodeInterface* dc;
	TClientIter<TDefaultClientMatchPolicy> iter = GetClientIter<TDefaultClientMatchPolicy>(TClientType(TCFClientType::EData));
	while ((dc = iter++) != NULL)
		{
		if (!(dc->Flags()&(TCFClientType::EActive|TCFClientType::EActivating|TCFClientType::ELeaving|TCFClientType::EStarted|TCFClientType::EStarting)))
			{
			//AbortActivitiesOriginatedBy(dc->RecipientId(),aContext);
			dc->PostMessage(Id(), TEChild::TDestroy().CRef());
			dc->SetFlags(TClientType::ELeaving);
			}
		}
	}


