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
// This contains RootServer Test cases from section 6
// 
//

// EPOC includes
#include <e32base.h>
#include <es_mbman.h>

// Test system includes
#include <networking/log.h>
#include <networking/teststep.h>
#include <networking/testsuite.h>

#include "TestStepRootServer.h"
#include "TestSuiteRootServer.h"
#include "TestAsynchHandler.h"
#include "RootServerTestSection5.h"
#include "RootServerTest.h"


TVerdict CRootServerTest_GracefulUnload::UnloadGracefullyL(TThreadPriority aPriority)
	{
	TVerdict verdict = EFail;

	// Create scheduler/active object framework 
	CSelfPopScheduler* scheduler = CSelfPopScheduler::CreateLC();
    CTestAsynchHandler* asynchHandler = CTestAsynchHandler::NewLC(&iRootServerSuite->RootSess());

    //*****************step 2************************
	Log(_L("02 Load test module"));

	TRSStartModuleParams startParams;
	TTestModuleIniData iniData;
	DefaultStartParams(startParams, iniData);
	startParams.iParams.iName = KModule1;
	startParams.iParams.iPriority = aPriority;

	asynchHandler->TryLoad(startParams, iniData);
    CActiveScheduler::Start();
   	if (asynchHandler->iStatus != KErrNone)
		{
		Log(_L("LoadServer returned error: <%d> "), asynchHandler->iStatus.Int());
		verdict = EInconclusive;
		}
	else
		{
		//*****************step 4***********************
		Log(_L("04 Unload Test Module"));

		asynchHandler->TryUnLoad(startParams.iParams.iName, EGraceful);
		
		CActiveScheduler::Start();

   		if (asynchHandler->iStatus != KErrNone)
			{
			Log(_L("Unload returned error: <%d> "), asynchHandler->iStatus.Int());
			verdict = EInconclusive;
			}
		else
			{
			verdict = EPass;			
			}
		}

	// uninstall and destroy active scheduler
	CleanupStack::PopAndDestroy(asynchHandler);
	CleanupStack::PopAndDestroy(scheduler);
	return verdict;
	}


// Test step 5.1 - UnLoad Gracefully (normal priority)
CRootServerTest5_1::CRootServerTest5_1()
{
	// store the name of this test case
	iTestStepName = _L("Test5.1");
}

TVerdict CRootServerTest5_1::doTestStepL( void )
	{
	Log(_L("Test Purpose: UnLoad Comms Provider Module gracefully (normal priority)"));
	return UnloadGracefullyL(EPriorityNormal);
	}


// Test step 5.2 - UnLoad Gracefully (elevated priority)
CRootServerTest5_2::CRootServerTest5_2()
{
	// store the name of this test case
	iTestStepName = _L("Test5.2");
}

TVerdict CRootServerTest5_2::doTestStepL( void )
	{
	Log(_L("Test Purpose: UnLoad Comms Provider Module gracefully (elevated priority)"));
	return UnloadGracefullyL(EPriorityRealTime);
	}


// Test step 5.3 -  Cancel UnLoad Gracefully
CRootServerTest5_3::CRootServerTest5_3()
{
	// store the name of this test case
	iTestStepName = _L("Test5.3");
}

TVerdict CRootServerTest5_3::doTestStepL( void )
	{
	Log(_L("Test Purpose: Cancel UnLoad Comms Provider Module gracefully"));
	TVerdict verdict = EPass;

	// Create scheduler/active object framework 
	CSelfPopScheduler* scheduler = CSelfPopScheduler::CreateLC();
    CTestAsynchHandler* asynchHandler = CTestAsynchHandler::NewLC(&iRootServerSuite->RootSess());

	//*****************step 2************************
	Log(_L("02 Load Test Module"));
	TRSStartModuleParams startParams;
	TTestModuleIniData iniData;
	DefaultStartParams(startParams, iniData);
	startParams.iParams.iName = KModule1;

	asynchHandler->TryLoad(startParams, iniData);
    CActiveScheduler::Start();
   	if (asynchHandler->iStatus != KErrNone)
		{
		Log(_L("LoadServer returned error: <%d> "), asynchHandler->iStatus.Int());
		verdict = EInconclusive;
		}
	else
		{
		//*****************step 3***********************
		Log(_L("03 Unload Test Module"));
		asynchHandler->TryUnLoad(startParams.iParams.iName, EGraceful);
		
		//*****************step 4***********************
		Log(_L8("04 Cancelling UnLoad: %S"), &startParams.iParams.iName);
		iRootServerSuite->RootSess().CancelUnloadCpm(startParams.iParams.iName);
		
		CActiveScheduler::Start();

   		if ((asynchHandler->iStatus != KErrNone) && (asynchHandler->iStatus != KErrCancel))
			{
			Log(_L("Unload returned error: <%d> "), asynchHandler->iStatus.Int());
			verdict = EFail;
			}

		}

	// uninstall and destroy active scheduler
	CleanupStack::PopAndDestroy(asynchHandler);
	CleanupStack::PopAndDestroy(scheduler);
	return verdict;
	}


TVerdict CRootServerTest_UngracefulUnload::UnloadNonGracefullyL(TThreadPriority aPriority)
	{
	TVerdict verdict = EFail;

	// Create scheduler/active object framework 
	CSelfPopScheduler* scheduler = CSelfPopScheduler::CreateLC();
    CTestAsynchHandler* asynchHandler = CTestAsynchHandler::NewLC(&iRootServerSuite->RootSess());

	//*****************step 3************************
	Log(_L("03 Load Test Module"));
	TRSStartModuleParams startParams;
	TTestModuleIniData iniData;
	DefaultStartParams(startParams, iniData);
	startParams.iParams.iName = KModule1;
	startParams.iParams.iPriority = aPriority;

	asynchHandler->TryLoad(startParams, iniData);
    CActiveScheduler::Start();
   	if (asynchHandler->iStatus != KErrNone)
		{
		Log(_L("LoadServer returned error: <%d> "), asynchHandler->iStatus.Int());
		verdict = EInconclusive;
		}
	else
		{
		//*****************step 4***********************
		Log(_L("04 Unload Test Module"));
		asynchHandler->TryUnLoad(startParams.iParams.iName, EUnGraceful);
		
		CActiveScheduler::Start();

   		if (asynchHandler->iStatus != KErrNone)
			{
			Log(_L("Unload returned error: <%d> "), asynchHandler->iStatus.Int());
			verdict = EInconclusive;
			}
		else
			{
			verdict = EPass;			
			}
		}

	// uninstall and destroy active scheduler
	CleanupStack::PopAndDestroy(asynchHandler);
	CleanupStack::PopAndDestroy(scheduler);
	return verdict;
	}
	

// Test step 5.4 - UnLoad Ungracefully - normal priority
CRootServerTest5_4::CRootServerTest5_4()
{
	// store the name of this test case
	iTestStepName = _L("Test5.4");
}

TVerdict CRootServerTest5_4::doTestStepL( void )
	{
	Log(_L("Test Purpose: UnLoad Comms Provider Module Ungracefully (normal priority)"));
	return UnloadNonGracefullyL(EPriorityNormal);
	}

// Test step 5.5 - UnLoad Ungracefully - elevated priority
CRootServerTest5_5::CRootServerTest5_5()
{
	// store the name of this test case
	iTestStepName = _L("Test5.5");
}

TVerdict CRootServerTest5_5::doTestStepL( void )
	{
	Log(_L("Test Purpose: UnLoad Comms Provider Module Ungracefully (elevated priority)"));
	return UnloadNonGracefullyL(EPriorityRealTime);
	}


// Test step 5.6 - Cancel UnLoad Ungracefully
CRootServerTest5_6::CRootServerTest5_6()
{
	// store the name of this test case
	iTestStepName = _L("Test5.6");
}

TVerdict CRootServerTest5_6::doTestStepL( void )
	{
	Log(_L("Test Purpose: Cancel UnLoad Comms Provider Module Ungracefully"));
	TVerdict verdict = EPass;

	// Create scheduler/active object framework 
	CSelfPopScheduler* scheduler = CSelfPopScheduler::CreateLC();
    CTestAsynchHandler* asynchHandler = CTestAsynchHandler::NewLC(&iRootServerSuite->RootSess());

	//*****************step 2************************
	Log(_L("02 Load Test Module"));
	TRSStartModuleParams startParams;
	TTestModuleIniData iniData;
	DefaultStartParams(startParams, iniData);
	startParams.iParams.iName = KModule1;

	asynchHandler->TryLoad(startParams, iniData);
    CActiveScheduler::Start();
   	if (asynchHandler->iStatus != KErrNone)
		{
		Log(_L("Load returned error: <%d> "), asynchHandler->iStatus.Int());
		verdict = EInconclusive;
		}
	else
		{
		//*****************step 3***********************
		Log(_L("03 Unload Test Module"));
		asynchHandler->TryUnLoad(startParams.iParams.iName, EUnGraceful);
		
		//*****************step 4***********************
		Log(_L8("04 Cancelling UnLoad: %S"), &startParams.iParams.iName);
		iRootServerSuite->RootSess().CancelUnloadCpm(startParams.iParams.iName);
		
		CActiveScheduler::Start();
    
	    // Unload the CPM anyway in case we were too late to cancel the load.
	    TRequestStatus status;
	    iRootServerSuite->RootSess().UnloadCpm(status, startParams.iParams.iName, EImmediate);
	    User::WaitForRequest(status);

   		if (asynchHandler->iStatus != KErrNone)
			{
			Log(_L("Unload returned error: <%d> "), asynchHandler->iStatus.Int());
			verdict = EFail;
			}

		}

	// uninstall and destroy active scheduler
	CleanupStack::PopAndDestroy(asynchHandler);
	CleanupStack::PopAndDestroy(scheduler);
	return verdict;
	}
	
	
// Test step 5.7 - UnLoad 2 modules sharing the same heap
CRootServerTest5_7::CRootServerTest5_7()
{
	// store the name of this test case
	iTestStepName = _L("Test5.7");
}

TVerdict CRootServerTest5_7::doTestStepL( void )
	{
	Log(_L("Test Purpose: UnLoad 2 modules sharing the same heap"));
	TVerdict verdict = EFail;

	// Create scheduler/active object framework 
	CSelfPopScheduler* scheduler = CSelfPopScheduler::CreateLC();
    CTestAsynchHandler* asynchHandler = CTestAsynchHandler::NewLC(&iRootServerSuite->RootSess());
    
	//*****************step 3************************
	Log(_L("03 Load Test Module_Share1"));
	TRSStartModuleParams startParams;
	TTestModuleIniData iniData;
	DefaultStartParams(startParams, iniData);
	_LIT8(KShareModule1, "Test ModuleShare1");
	_LIT8(KShareModule2, "Test ModuleShare2");
	startParams.iParams.iName = KShareModule1;

	asynchHandler->TryLoad(startParams, iniData);
    CActiveScheduler::Start();
   	if (asynchHandler->iStatus != KErrNone)
		{
		Log(_L("LoadServer returned error: <%d> "), asynchHandler->iStatus.Int());
		User::Leave(asynchHandler->iStatus.Int());
		}

	//*****************step 3************************
	Log(_L("03 Load Test Module"));
	startParams.iParams.iName = KShareModule2;
	startParams.iParams.iHeapType = EShareHeap;
	startParams.iParams.iShareHeapWith = KShareModule1;

	asynchHandler->TryLoad(startParams, iniData);
	CActiveScheduler::Start();

	if (asynchHandler->iStatus != KErrNone)
		{
		Log(_L("LoadServer returned error: <%d> "), asynchHandler->iStatus.Int());
		User::Leave(asynchHandler->iStatus.Int());
		}

    //*****************step 5***********************
	Log(_L("05 Unload Test Module_Share1"));
	startParams.iParams.iName = KShareModule1;
	asynchHandler->TryUnLoad(startParams.iParams.iName, EGraceful);
	CActiveScheduler::Start();

	if (asynchHandler->iStatus != KErrNone)
		{
		Log(_L("Unload returned error: <%d> "), asynchHandler->iStatus.Int());
		User::Leave(asynchHandler->iStatus.Int());
		}

	//*****************step 6***********************
	Log(_L("06 Unload Test Module_Share2"));
	startParams.iParams.iName = KShareModule2;
	asynchHandler->TryUnLoad(startParams.iParams.iName, EGraceful);
	
	CActiveScheduler::Start();

	if (asynchHandler->iStatus != KErrNone)
		{
		Log(_L("Unload returned error: <%d> "), asynchHandler->iStatus.Int());
		verdict = EInconclusive;
		}
	else
		{
		verdict = EPass;			
		}

	// uninstall and destroy active scheduler
	CleanupStack::PopAndDestroy(asynchHandler);
	CleanupStack::PopAndDestroy(scheduler);
	return verdict;
	}
    
    
// Test step 5.8 - Unload Sluggish CPM Gracefully with intervening Close of Session
CRootServerTest5_8::CRootServerTest5_8()
{
	// store the name of this test case
	iTestStepName = _L("Test5.8");
}

TVerdict CRootServerTest5_8::doTestStepL( void )
	{
	Log(_L("Test Purpose: Unload Sluggish CPM Gracefully with intervening Close of Session"));
	TVerdict verdict = EPass;

	// Create scheduler/active object framework 
	CSelfPopScheduler* scheduler = CSelfPopScheduler::CreateLC();
    CTestAsynchHandler* asynchHandler = CTestAsynchHandler::NewLC(&iRootServerSuite->RootSess());
    
	TRSStartModuleParams startParams;
	TTestModuleIniData iniData;
	DefaultStartParams(startParams, iniData);
	startParams.iParams.iName = KModule1;
	iniData.iParams.iShutdownDelay = isTestServerLifeTime;
	Log(_L8("01 Loading sluggish module: %S"), &startParams.iParams.iName);
	asynchHandler->TryLoad(startParams, iniData);

	CActiveScheduler::Start();
    if (asynchHandler->iStatus != KErrNone)
		{
		Log(_L("LoadServer returned error: <%d> "), asynchHandler->iStatus.Int());
		User::Leave(asynchHandler->iStatus.Int());
		}

	Log(_L("02 Unload sluggish Module"));
	asynchHandler->TryUnLoad(startParams.iParams.iName, EGraceful);

	// Brief wait to give unload chance to start
	User::After(250 * 1000);

	// Close the session
	Log(_L("03 Closing RRootServ"));
	iRootServerSuite->RootSess().Close();
	// Brief wait for any fireworks
	User::After(250 * 1000);
	
	// Let the request complete
	CActiveScheduler::Start();

	// Reconnect the session
	Log(_L("04 Reconnecting RRootServ"));
	TInt ret = iRootServerSuite->RootSess().Connect();
	if (ret != KErrNone)
		{
		Log(_L("Reconnect of RRootServ failed with error: <%d> "), ret);
		User::Leave(ret);
		}
	// Brief wait for any fireworks
	User::After(250 * 1000);

	// now try to retrieve information about the module; should be ERunning after session close
	// causes unload handler to be canceled
	Log(_L("05 Getting module information"));
	TRSModuleInfo info;
	TCFModuleName moduleName = startParams.iParams.iName;
	ret = iRootServerSuite->RootSess().GetModuleInfo(moduleName, info);
	Log(_L8("GetModuleInfo for %S returned %d, state %c= ERunning"), &moduleName, ret, info.iParams.iState == ERunning ? '=': '!');
	
	if(KErrNone != ret || info.iParams.iState != ERunning)
		{
		CleanupStack::PopAndDestroy(asynchHandler);
		CleanupStack::PopAndDestroy(scheduler);
		return EFail;
		}

	// Wait for it to finish stopping when its thread terminates, query again
	Log(_L("06 Getting module information after waiting for stop"));
	User::After((iniData.iParams.iShutdownDelay + 500) * 1000);
	moduleName = startParams.iParams.iName;
	ret = iRootServerSuite->RootSess().GetModuleInfo(moduleName, info);
	Log(_L8("GetModuleInfo for %S returned %d"), &moduleName, ret);
	
	if(KErrRSModuleUnknown != ret)
		{
		CleanupStack::PopAndDestroy(asynchHandler);
		CleanupStack::PopAndDestroy(scheduler);
		return EFail;
		}

	CleanupStack::PopAndDestroy(asynchHandler);
	CleanupStack::PopAndDestroy(scheduler);
	return verdict;
	}
    
    

