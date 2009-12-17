// Copyright (c) 2003-2009 Nokia Corporation and/or its subsidiary(-ies).
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
// This contains ESock Test cases from section 4
// 
//

// EPOC includes
#include <e32base.h>
#include <es_mbman.h>

// Test system includes
#include <comms-infras/commsdebugutility.h>
#include <networking/teststep.h>
#include <networking/testsuite.h>

#include "TestStepRootServer.h"
#include "TestSuiteRootServer.h"
#include "TestAsynchHandler.h"

#include "RootServerTest.h"
#include "RootServerTestSection4.h"

// Test step 4.1 - SuddenDeathListener
CRootServerTest4_1::CRootServerTest4_1()
	{
	// store the name of this test case
	iTestStepName = _L("Test4.1");
	}


TVerdict CRootServerTest4_1::doTestStepL( void )
	{
	TVerdict verdict = EPass;

	Log(_L("Test Purpose: SuddenDeathListener"));

	// Create scheduler/active object framework 
	CSelfPopScheduler* scheduler = CSelfPopScheduler::CreateLC();
    CTestAsynchHandler* asynchHandler = CTestAsynchHandler::NewLC(&iRootServerSuite->RootSess());

	TRSStartModuleParams startParams;
	TTestModuleIniData iniData;
	DefaultStartParams(startParams, iniData);
	startParams.iParams.iName = KModule1;
#if defined(SYMBIAN_C32ROOT_API_V3)
	startParams.iParams.iControlFlags = TRSStartModuleParamContainer::KCF_UnstableModule;
#endif
	iniData.iParams.iDeathDelay = isTestServerLifeTime;

	Log(_L8("02 Loading module: %S"), &startParams.iParams.iName);
	asynchHandler->TryLoad(startParams, iniData);

	CActiveScheduler::Start();
    if (asynchHandler->iStatus != KErrNone)
		{
		Log(_L("LoadServer returned error: <%d> "), asynchHandler->iStatus.Int());
		User::Leave(asynchHandler->iStatus.Int());
		}

	// create a new active object for the sudden death handler
	CTestAsynchHandler* suddenDeathHandler = CTestAsynchHandler::NewLC(&iRootServerSuite->RootSess());

	// wait for either sudden death indication or timeout
	Log(_L("03 Waiting for sudden death for up to %1.3f seconds"), isTestServerWaitTime / 1000.0);
	asynchHandler->WaitForTimer(isTestServerWaitTime);
	suddenDeathHandler->TryWaitForDeath();
	CActiveScheduler::Start();

	// uninstall active scheduler
	asynchHandler->Cancel();
	suddenDeathHandler->Cancel();

	// see which events have occurred 
	// if root server worked then timer should not have expired
	// and sudden death handler AO should have returned to idle
	if (CTestAsynchHandler::EWaitingforTimer != asynchHandler->GetiState())
		{
		Log(_L("Timer expired"));
		verdict = EFail;
		}
	
	if (CTestAsynchHandler::EIdle != suddenDeathHandler->GetiState())
		{
		Log(_L("SuddenDeathHandler was not triggered"));
		verdict = EFail;
		}

	// enumerate servers
	Log(_L("04 Enumerating modules"));

	TCFModuleName moduleName;
	TRSIter position;
	TInt ret = iRootServerSuite->RootSess().EnumerateModules(position, moduleName);
	Log(_L("Enumerate returned %d"), ret);
	if (KErrEof != ret)
		{
		Log(_L("Module left alive"));
		verdict = EFail;
		}


	// destroy active objects and scheduler
	CleanupStack::PopAndDestroy(suddenDeathHandler);
	CleanupStack::PopAndDestroy(asynchHandler);
	CleanupStack::PopAndDestroy(scheduler);

	return verdict;
	}


