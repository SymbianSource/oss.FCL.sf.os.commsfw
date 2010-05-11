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
// DummyCPR_connProv.h
// TestDummy Connection Provider class definition.
// 
//

/**
 @file
 @internalComponent
*/

#if !defined(__DummyCPR_CONNPROV_H__)
#define __DummyCPR_CONNPROV_H__

#include <comms-infras/mobilitycpr.h>
#include <comms-infras/mobilitycprstates.h>


#ifdef __FLOG_ACTIVE
// CommsDebugUtility logging tags. Use them to enable tracing for DummyCPR
_LIT8(KTestDummyLogTag1,"TestDummyConnProv");
_LIT8(KTestDummyLogTag2,"TestDummyRef");
#endif

class CDummyConnectionProvider : public CMobilityConnectionProvider, public ESock::MLegacyControlApiExt,
                                 public ITFHIERARCHY_LINK_1(CDummyConnectionProvider, CMobilityConnectionProvider, ESock::MLegacyControlApiExt)

/**

@internalComponent
@released since v9.4
 */
    {
public:
	typedef ITFHIERARCHY_LINK_1(CDummyConnectionProvider, CMobilityConnectionProvider, ESock::MLegacyControlApiExt) TIfStaticFetcherNearestInHierarchy;

public:
	virtual ~CDummyConnectionProvider();
	virtual TInt ControlL(TUint aOptionLevel, TUint aOptionName, TDes8& aOption, ESock::MPlatsecApiExt* aPlatsecItf);
    void ReturnInterfacePtrL(ESock::MLegacyControlApiExt*& aInterface);

public:
    enum TConnType
         {
         EConnIncoming = 1,
         EConnNoIncoming = 2,
         };

    static CDummyConnectionProvider* NewL(ESock::CConnectionProviderFactoryBase& aFactory, TConnType aConnStatus);
    static CDummyConnectionProvider* NewVanillaL(ESock::CConnectionProviderFactoryBase& aFactory);
    
    CDummyConnectionProvider(ESock::CConnectionProviderFactoryBase& aFactory, const MeshMachine::TNodeActivityMap& aActivityMap, TConnType aConnStatus);
    
public:
	TConnType iConnStatus;
    };

//-================================================
//
// States and Transitions
//
//-================================================
namespace DummyCPRStates
{
typedef MeshMachine::TNodeContext<CDummyConnectionProvider, CprStates::TContext> TContext;

DECLARE_SMELEMENT_HEADER( TCreateIncomingSCPR, MeshMachine::TStateTransition<TContext>, NetStateMachine::MStateTransition, DummyCPRStates::TContext )
	virtual void DoL();
DECLARE_SMELEMENT_FOOTER( TCreateIncomingSCPR )

DECLARE_SMELEMENT_HEADER( TSetClientAsIncoming, MeshMachine::TStateTransition<TContext>, NetStateMachine::MStateTransition, DummyCPRStates::TContext )
	virtual void DoL();
DECLARE_SMELEMENT_FOOTER( TSetClientAsIncoming )

DECLARE_SMELEMENT_HEADER( TAwaitingStart, MeshMachine::TState<TContext>, NetStateMachine::MState, DummyCPRStates::TContext )
	virtual TBool Accept();
DECLARE_SMELEMENT_FOOTER( TAwaitingStart )


} // namespace DummyCPRStates

#endif // __DummyCPR_CONNPROV_H__

