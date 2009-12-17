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
// This contains ESock Test cases from section 3
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

#include "RootServerTest.h"
#include "RootServerTestSection3.h"


// Note: Test step 3.1 was a RRootServ::Connect() test; this is now obsolete

// Test step 3.2 - SetMBufPoolSize After LoadServer
CRootServerTest3_2::CRootServerTest3_2()
	{
	// store the name of this test case
	iTestStepName = _L("Test3.2");
	}


TVerdict CRootServerTest3_2::doTestStepL( void )
	{
	TVerdict verdict = EPass;

	Log(_L("Test Purpose: SetMBufPoolSize After LoadServer"));

	// Create scheduler/active object framework
	CSelfPopScheduler* scheduler = CSelfPopScheduler::CreateLC();
    CTestAsynchHandler* asynchHandler = CTestAsynchHandler::NewLC(&iRootServerSuite->RootSess());

	Log(_L8("01 Loading test module: %S"), &KModule1());
	LoadNormalModuleL(asynchHandler, KModule1);

	// uninstall and destroy active scheduler
	CleanupStack::PopAndDestroy(asynchHandler);
	CleanupStack::PopAndDestroy(scheduler);

	// now try to set the buffer pool size
	Log(_L("03 Setting MBufPoolSize"));
	TInt ret = iRootServerSuite->RootSess().SetMBufPoolSize(0,KMBufDefaultHeapSize);

	Log(_L("SetMBufPoolSize returned %d"), ret);
	if (KErrInUse != ret)
		{
		verdict = EFail;
		}

	return verdict;
	}


TVerdict CRootServerTest3_DblLoad::LoadSameModuleTwiceL(TThreadPriority aPriority)
	{
	TVerdict verdict = EPass;

	// Create scheduler/active object framework
	CSelfPopScheduler* scheduler = CSelfPopScheduler::CreateLC();
    CTestAsynchHandler* asynchHandler = CTestAsynchHandler::NewLC(&iRootServerSuite->RootSess());

	TRSStartModuleParams startParams;
	TTestModuleIniData iniData;
	DefaultStartParams(startParams, iniData);
	startParams.iParams.iName = KModule1;
	startParams.iParams.iPriority = aPriority;

	Log(_L8("02 Loading module: %S"), &startParams.iParams.iName);
	asynchHandler->TryLoad(startParams, iniData);

	CActiveScheduler::Start();

    if (asynchHandler->iStatus != KErrNone)
		{
		Log(_L("LoadServer returned error: <%d> "), asynchHandler->iStatus.Int());
		User::Leave(asynchHandler->iStatus.Int());
		}

	// try to load same module again
	Log(_L("03 Trying to load same module again"));
	asynchHandler->TryLoad(startParams, iniData);
	CActiveScheduler::Start();

	Log(_L("LoadServer returned %d"), asynchHandler->iStatus.Int());
    if (asynchHandler->iStatus != KErrRSModuleAlreadyExist)
		{
		verdict = EFail;
		}
	// uninstall and destroy active scheduler
	CleanupStack::PopAndDestroy(asynchHandler);
	CleanupStack::PopAndDestroy(scheduler);

	return verdict;
	}

// Test step 3.3 - Load Same Module Twice
CRootServerTest3_3::CRootServerTest3_3()
	{
	// store the name of this test case
	iTestStepName = _L("Test3.3");
	}

TVerdict CRootServerTest3_3::doTestStepL( void )
	{
	Log(_L("Test Purpose: Load Same Module Twice (normal priority)"));
	return LoadSameModuleTwiceL(EPriorityNormal);
	}

// Test step 3.4 - Load Same Module Twice with elevated priority
CRootServerTest3_4::CRootServerTest3_4()
	{
	// store the name of this test case
	iTestStepName = _L("Test3.4");
	}

TVerdict CRootServerTest3_4::doTestStepL( void )
	{
	Log(_L("Test Purpose: Load Same Module Twice (elevated priority)"));
	return LoadSameModuleTwiceL(EPriorityRealTime);
	}


// Test step 3.5 - Retrieve Module Information
CRootServerTest3_5::CRootServerTest3_5()
	{
	// store the name of this test case
	iTestStepName = _L("Test3.5");
	}

TVerdict CRootServerTest3_5::doTestStepL( void )
	{
	TVerdict verdict = EPass;

	Log(_L("Test Purpose: Retrieve Module Information"));

	// Create scheduler/active object framework
	CSelfPopScheduler* scheduler = CSelfPopScheduler::CreateLC();
    CTestAsynchHandler* asynchHandler = CTestAsynchHandler::NewLC(&iRootServerSuite->RootSess());

	TRSStartModuleParams startParams;
	TTestModuleIniData iniData;
	DefaultStartParams(startParams, iniData);
	startParams.iParams.iName = KModule1;

	Log(_L8("02 Loading module: %S"), &startParams.iParams.iName);
	asynchHandler->TryLoad(startParams, iniData);
	CActiveScheduler::Start();

    if (asynchHandler->iStatus != KErrNone)
		{
		Log(_L("LoadServer returned error: <%d> "), asynchHandler->iStatus.Int());
		User::Leave(asynchHandler->iStatus.Int());
		}
	CleanupStack::PopAndDestroy(asynchHandler);
	CleanupStack::PopAndDestroy(scheduler);

	// now try to retrieve information about the module
	Log(_L("03 Getting module information"));
	TRSModuleInfo info;
	TCFModuleName moduleName = KModule1();
	TInt ret = iRootServerSuite->RootSess().GetModuleInfo(moduleName, info);
	Log(_L8("GetModuleInfo for %S returned %d"), &moduleName, ret);

	if(KErrNone != ret)
		{
		return EFail;
		}

	Log(_L("Filename %S, State %d, NumSubmodules %d"),
		&info.iParams.iDll, info.iParams.iState, info.iParams.iNumSubModules);

	if (startParams.iParams.iFilename != info.iParams.iDll ||
		ERunning != info.iParams.iState ||
		3 != info.iParams.iNumSubModules)
		{
		return EFail;
		}

	// now ask for info about a non-existent module
	Log(_L("04 Getting module information for non-existent module"));

	moduleName = KModule2;
	ret = iRootServerSuite->RootSess().GetModuleInfo(moduleName, info);
	Log(_L8("GetModuleInfo for %S returned %d"), &moduleName, ret);

	if(KErrRSModuleUnknown != ret)
		{
		return EFail;
		}

	return verdict;
	}


// Test step 3.6 - CancelLoadModule Before Thread Starts
CRootServerTest3_6::CRootServerTest3_6()
	{
	// store the name of this test case
	iTestStepName = _L("Test3.6");
	}

TVerdict CRootServerTest3_6::doTestStepL( void )
	{
	TVerdict verdict = EPass;

	Log(_L("Test Purpose: CancelLoadModule Before Thread Starts"));

	// Create scheduler/active object framework
	CSelfPopScheduler* scheduler = CSelfPopScheduler::CreateLC();
    CTestAsynchHandler* asynchHandler = CTestAsynchHandler::NewLC(&iRootServerSuite->RootSess());

	TRSStartModuleParams startParams;
	TTestModuleIniData iniData;
	DefaultStartParams(startParams, iniData);
	startParams.iParams.iName = KModule1;
	iniData.iParams.iInitDelay = isRendezvousDelayTime;

	Log(_L8("02 Loading module: %S"), &startParams.iParams.iName);
	asynchHandler->TryLoad(startParams, iniData);

//	User::After(5000000);

	Log(_L8("03 Cancelling Loading module: %S"), &startParams.iParams.iName);
	iRootServerSuite->RootSess().CancelLoadCpm(startParams.iParams.iName);

	CActiveScheduler::Start();

    Log(_L("LoadServer status was: <%d> "), asynchHandler->iStatus.Int());

    if ((KErrCancel != asynchHandler->iStatus.Int()) && (KErrNone != asynchHandler->iStatus.Int()))
		{
		verdict = EFail;
		}
    
    // Unload the CPM anyway in case we were too late to cancel the load.
    TRequestStatus status;
    iRootServerSuite->RootSess().UnloadCpm(status, startParams.iParams.iName, EImmediate);
    User::WaitForRequest(status);

	CleanupStack::PopAndDestroy(asynchHandler);
	CleanupStack::PopAndDestroy(scheduler);
	return verdict;
	}


// Test step 3.7 - CancelLoadServer After Rendezvous
CRootServerTest3_7::CRootServerTest3_7()
	{
	// store the name of this test case
	iTestStepName = _L("Test3.7");
	}

TVerdict CRootServerTest3_7::doTestStepL( void )
	{
	TVerdict verdict = EPass;

	Log(_L("Test Purpose: CancelLoadServer After Rendezvous"));

	// Create scheduler/active object framework
	CSelfPopScheduler* scheduler = CSelfPopScheduler::CreateLC();
    CTestAsynchHandler* asynchHandler = CTestAsynchHandler::NewLC(&iRootServerSuite->RootSess());

	TRSStartModuleParams startParams;
	TTestModuleIniData iniData;
	DefaultStartParams(startParams, iniData);
	startParams.iParams.iName = KModule1;
	Log(_L8("02 Loading module: %S"), &startParams.iParams.iName);
	asynchHandler->TryLoad(startParams, iniData);

	// now wait for testserver to meet rendezvous before cancelling load (give it
	User::After(1000000);
	Log(_L8("03 Cancelling Loading module: %S"), &startParams.iParams.iName);
	iRootServerSuite->RootSess().CancelLoadCpm(startParams.iParams.iName);

	CActiveScheduler::Start();

    Log(_L("LoadServer status was: <%d> "), asynchHandler->iStatus.Int());

    if (KErrNone != asynchHandler->iStatus.Int())
		{
		verdict = EFail;
		}

	CleanupStack::PopAndDestroy(asynchHandler);
	CleanupStack::PopAndDestroy(scheduler);

	return verdict;
	}

// Test step 3.8 - Close Session with Pending LoadServer
CRootServerTest3_8::CRootServerTest3_8()
	{
	// store the name of this test case
	iTestStepName = _L("Test3.8");
	}

TVerdict CRootServerTest3_8::doTestStepL( void )
	{
	TVerdict verdict = EPass;

	Log(_L("Test Purpose: Close Session with Pending LoadServer"));

	// Create scheduler/active object framework
	CSelfPopScheduler* scheduler = CSelfPopScheduler::CreateLC();
    CTestAsynchHandler* asynchHandler = CTestAsynchHandler::NewLC(&iRootServerSuite->RootSess());

	TRSStartModuleParams startParams;
	TTestModuleIniData iniData;
	DefaultStartParams(startParams, iniData);
	startParams.iParams.iName = KModule1;
	iniData.iParams.iInitDelay = isRendezvousDelayTime;

	Log(_L8("02 Loading module: %S"), &startParams.iParams.iName);
	asynchHandler->TryLoad(startParams, iniData);

	Log(_L("03 Closing Session"));
	iRootServerSuite->RootSess().Close();
	Log(_L("RRootServ.Close() completed"));

	CActiveScheduler::Start();

	// note that if the session was closed before the module's thread started,
	// the handler should have been KErrCancelled
    Log(_L("LoadServer status was: <%d> "), asynchHandler->iStatus.Int());
    if ((KErrCancel != asynchHandler->iStatus.Int()) && (KErrNone != asynchHandler->iStatus.Int()))
		{
		verdict = EFail;
		}

	CleanupStack::PopAndDestroy(asynchHandler);
	CleanupStack::PopAndDestroy(scheduler);

	return verdict;
	}


// Test step 3.9 - Module Exits Before Rendezvous
CRootServerTest3_9::CRootServerTest3_9()
	{
	// store the name of this test case
	iTestStepName = _L("Test3.9");
	}

TVerdict CRootServerTest3_9::doTestStepL( void )
	{
	TVerdict verdict = EFail;

	Log(_L("Test Purpose: Module Exits Before Rendezvous"));

	// Create scheduler/active object framework
	CSelfPopScheduler* scheduler = CSelfPopScheduler::CreateLC();
    CTestAsynchHandler* asynchHandler = CTestAsynchHandler::NewLC(&iRootServerSuite->RootSess());

	TRSStartModuleParams startParams;
	TTestModuleIniData iniData;
	DefaultStartParams(startParams, iniData);
	startParams.iParams.iName = KModule1;
	iniData.iParams.iInitDelay = EXIT_BEFORE_RENDEZVOUS;

	Log(_L8("03 Loading module: %S"), &startParams.iParams.iName);
	asynchHandler->TryLoad(startParams, iniData);

	CActiveScheduler::Start();

    Log(_L("LoadServer status was: <%d>"), asynchHandler->iStatus.Int());

    if (KErrNone != asynchHandler->iStatus.Int())
		{
		verdict = EPass;
		}

	CleanupStack::PopAndDestroy(asynchHandler);
	CleanupStack::PopAndDestroy(scheduler);

	return verdict;
	}

// Test step 3.10 - Module Panics Before Meeting Rendezvous
CRootServerTest3_10::CRootServerTest3_10()
	{
	// store the name of this test case
	iTestStepName = _L("Test3.10");
	}

TVerdict CRootServerTest3_10::doTestStepL( void )
	{
	TVerdict verdict = EFail;

	Log(_L("Test Purpose: Module Panics Before Meeting Rendezvous"));

	// Create scheduler/active object framework
	CSelfPopScheduler* scheduler = CSelfPopScheduler::CreateLC();
    CTestAsynchHandler* asynchHandler = CTestAsynchHandler::NewLC(&iRootServerSuite->RootSess());

	TRSStartModuleParams startParams;
	TTestModuleIniData iniData;
	DefaultStartParams(startParams, iniData);
	startParams.iParams.iName = KModule1;
#ifdef SYMBIAN_C32ROOT_API_V3
	startParams.iParams.iControlFlags = TRSStartModuleParamContainer::KCF_UnstableModule;
#endif
	iniData.iParams.iInitDelay = PANIC_BEFORE_RENDEZVOUS;

	// make sure WINS doesn't stop at panic
	TBool jitDbg = User::JustInTime();
	User::SetJustInTime(EFalse);
	Log(_L8("03 Loading module: %S"), &startParams.iParams.iName);
	asynchHandler->TryLoad(startParams, iniData);

	CActiveScheduler::Start();

    Log(_L("LoadServer status was: <%d> "), asynchHandler->iStatus.Int());

    if (KErrNone != asynchHandler->iStatus.Int())
		{
		verdict = EPass;
		}

	// Restore enclosing JIT status
	User::SetJustInTime(jitDbg);

	CleanupStack::PopAndDestroy(asynchHandler);
	CleanupStack::PopAndDestroy(scheduler);

	return verdict;
	}

// Test step 3.11 - Module Panics After Meeting Rendezvous
CRootServerTest3_11::CRootServerTest3_11()
	{
	// store the name of this test case
	iTestStepName = _L("Test3.11");
	}

TVerdict CRootServerTest3_11::doTestStepL( void )
	{
	TVerdict verdict = EFail;

	Log(_L("Test Purpose: Module Panics After Meeting Rendezvous"));

	// Create scheduler/active object framework
	CSelfPopScheduler* scheduler = CSelfPopScheduler::CreateLC();
    CTestAsynchHandler* asynchHandler = CTestAsynchHandler::NewLC(&iRootServerSuite->RootSess());

	TRSStartModuleParams startParams;
	TTestModuleIniData iniData;
	DefaultStartParams(startParams, iniData);
	startParams.iParams.iName = KModule1;
#ifdef SYMBIAN_C32ROOT_API_V3
	startParams.iParams.iControlFlags = TRSStartModuleParamContainer::KCF_UnstableModule;
#endif
	iniData.iParams.iInitDelay = PANIC_AFTER_RENDEZVOUS;

	// make sure WINS doesn't stop at panic
	TBool jitDbg = User::JustInTime();
	User::SetJustInTime(EFalse);
	Log(_L8("03 Loading module: %S"), &startParams.iParams.iName);
	asynchHandler->TryLoad(startParams, iniData);

	CActiveScheduler::Start();

    Log(_L("LoadServer status was: <%d> "), asynchHandler->iStatus.Int());

    if (KErrServerTerminated == asynchHandler->iStatus.Int())
		{
		verdict = EPass;
		}

	// Restore enclosing JIT status
	User::SetJustInTime(jitDbg);

	// destroy active scheduler
	CleanupStack::PopAndDestroy(asynchHandler);
	CleanupStack::PopAndDestroy(scheduler);

	return verdict;
	}


// Test step 3.12 - Load 2 modules sharing the same heap
CRootServerTest3_12::CRootServerTest3_12()
	{
	// store the name of this test case
	iTestStepName = _L("Test3.12");
	}

TVerdict CRootServerTest3_12::doTestStepL( void )
	{
	Log(_L("Test Purpose: Load 2 modules sharing the same heap"));

	TVerdict verdict = EPass;

	// Create scheduler/active object framework
	CSelfPopScheduler* scheduler = CSelfPopScheduler::CreateLC();
    CTestAsynchHandler* asynchHandler = CTestAsynchHandler::NewLC(&iRootServerSuite->RootSess());

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
		verdict = EFail;
		}

	CleanupStack::PopAndDestroy(asynchHandler);
	CleanupStack::PopAndDestroy(scheduler);
	return verdict;
	}

// Test step 3.13 - Load 2 modules with private heaps
CRootServerTest3_13::CRootServerTest3_13()
	{
	// store the name of this test case
	iTestStepName = _L("Test3.13");
	}

TVerdict CRootServerTest3_13::doTestStepL( void )
	{
	Log(_L("Test Purpose: Load 2 modules with private heaps"));

	TVerdict verdict = EPass;

	// Create scheduler/active object framework
	CSelfPopScheduler* scheduler = CSelfPopScheduler::CreateLC();
    CTestAsynchHandler* asynchHandler = CTestAsynchHandler::NewLC(&iRootServerSuite->RootSess());

	TRSStartModuleParams startParams;
	TTestModuleIniData iniData;
	DefaultStartParams(startParams, iniData);
	startParams.iParams.iName = KModule1;
	startParams.iParams.iHeapType = ENewHeap;

	asynchHandler->TryLoad(startParams, iniData);
    CActiveScheduler::Start();
   	if (asynchHandler->iStatus != KErrNone)
		{
		Log(_L("LoadServer returned error: <%d> "), asynchHandler->iStatus.Int());
		User::Leave(asynchHandler->iStatus.Int());
		}

	//*****************step 3************************
	Log(_L("03 Load Test Module"));
	startParams.iParams.iName = KModule2;
	startParams.iParams.iHeapType = ENewHeap;

	asynchHandler->TryLoad(startParams, iniData);
	CActiveScheduler::Start();

	if (asynchHandler->iStatus != KErrNone)
		{
		Log(_L("LoadServer returned error: <%d> "), asynchHandler->iStatus.Int());
		verdict = EFail;
		}

	CleanupStack::PopAndDestroy(asynchHandler);
	CleanupStack::PopAndDestroy(scheduler);
	return verdict;
	}

// Test step 3.14 - Load sluggish module
CRootServerTest3_14::CRootServerTest3_14()
	{
	// store the name of this test case
	iTestStepName = _L("Test3.14");
	}

TVerdict CRootServerTest3_14::doTestStepL( void )
	{
	Log(_L("Test Purpose: Load sluggish module"));
	TVerdict verdict = EPass;

	// Create scheduler/active object framework
	CSelfPopScheduler* scheduler = CSelfPopScheduler::CreateLC();
    CTestAsynchHandler* asynchHandler = CTestAsynchHandler::NewLC(&iRootServerSuite->RootSess());

	TRSStartModuleParams startParams;
	TTestModuleIniData iniData;
	DefaultStartParams(startParams, iniData);
	startParams.iParams.iName = KModule1;
	iniData.iParams.iDiscoveryDelay = 500;
	iniData.iParams.iBindDelay = 1000;
	iniData.iParams.iUnbindDelay = 1000;
	iniData.iParams.iShutdownDelay = 1000;
	asynchHandler->TryLoad(startParams, iniData);

    CActiveScheduler::Start();
   	if (asynchHandler->iStatus != KErrNone)
		{
		Log(_L("LoadServer returned error: <%d> "), asynchHandler->iStatus.Int());
		verdict = EFail;
		}

	CleanupStack::PopAndDestroy(asynchHandler);
	CleanupStack::PopAndDestroy(scheduler);
	return verdict;

	}

// Test step 3.14 - Load dormant module
CRootServerTest3_15::CRootServerTest3_15()
	{
	// store the name of this test case
	iTestStepName = _L("Test3.15");
	}

TVerdict CRootServerTest3_15::doTestStepL( void )
	{
	Log(_L("Test Purpose: Load Dormant module"));
	//*****************step 1*************************//
	TVerdict verdict = EFail;

	// Create scheduler/active object framework
	CSelfPopScheduler* scheduler = CSelfPopScheduler::CreateLC();
    CTestAsynchHandler* asynchHandler = CTestAsynchHandler::NewLC(&iRootServerSuite->RootSess());

	//*****************step 3************************
	Log(_L("03 Load Dormant Module"));

	TRSStartModuleParams startParams;
	TTestModuleIniData iniData;
	DefaultStartParams(startParams, iniData);
	startParams.iParams.iName = KModule1;
	startParams.iParams.iHeapType = ENewHeap;	// when zombie is killed memory will leak
	iniData.iParams.iDiscoveryDelay = 30000;

	asynchHandler->TryLoad(startParams, iniData);
    CActiveScheduler::Start();
   	if (asynchHandler->iStatus != KErrRSZombie)
		{
		Log(_L("LoadServer returned error: <%d> "), asynchHandler->iStatus.Int());
		verdict = EFail;
		}
	else
		{
		//*****************step 4***********************
		Log(_L("04 Unload Dormant Module"));
		asynchHandler->TryUnLoad(startParams.iParams.iName, EUnGraceful);
		CActiveScheduler::Start();

		if (asynchHandler->iStatus != KErrNone)
			{
			Log(_L("Unload returned error: <%d> "), asynchHandler->iStatus.Int());
			verdict = EInconclusive;
			}
		else
			verdict = EPass;
		}

	CleanupStack::PopAndDestroy(asynchHandler);
	CleanupStack::PopAndDestroy(scheduler);
	return verdict;

	}

// Test step 3.16 - Load test module and wait for death
CRootServerTest3_16::CRootServerTest3_16()
	{
	// store the name of this test case
	iTestStepName = _L("Test3.16");
	}

TVerdict CRootServerTest3_16::doTestStepL( void )
	{
	Log(_L("Test Purpose: Load test module, wait for death and check heap"));
	//*****************step 1*************************//
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
#ifdef SYMBIAN_C32ROOT_API_V3
	startParams.iParams.iControlFlags = TRSStartModuleParamContainer::KCF_UnstableModule;
#endif
	iniData.iParams.iDeathDelay = 5000;

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
		Log(_L("04 Waiting for module to die"));

		User::After(6000000);

		TRSModuleInfo info;
		TInt ret = iRootServerSuite->RootSess().GetModuleInfo(KModule1(), info);
		Log(_L8("GetModuleInfo for %S returned %d"), &KModule1(), ret);

		if(KErrRSModuleUnknown == ret)
			{
			verdict = EPass;
			}
		}

	// uninstall and destroy active scheduler
	CleanupStack::PopAndDestroy(asynchHandler);
	CleanupStack::PopAndDestroy(scheduler);
	return verdict;

	}

// Test step 3.17 - Load unknown module and cancel
CRootServerTest3_17::CRootServerTest3_17()
	{
	// store the name of this test case
	iTestStepName = _L("Test3.17");
	}

TVerdict CRootServerTest3_17::doTestStepL( void )
	{
	TVerdict verdict = EPass;

	Log(_L("Test Purpose: Load unknown module and cancel"));

	// Create scheduler/active object framework
	CSelfPopScheduler* scheduler = CSelfPopScheduler::CreateLC();
    CTestAsynchHandler* asynchHandler = CTestAsynchHandler::NewLC(&iRootServerSuite->RootSess());

	TRSStartModuleParams startParams;
	TTestModuleIniData iniData;
	DefaultStartParams(startParams, iniData);
	startParams.iParams.iFilename = _L("unknown_module.cpm");
	startParams.iParams.iName = KModule1;

	Log(_L8("02 Loading module: %S"), &startParams.iParams.iName);
	asynchHandler->TryLoad(startParams, iniData);

	User::After(1000000);
	Log(_L8("03 Cancelling Loading module: %S"), &startParams.iParams.iName);
	iRootServerSuite->RootSess().CancelLoadCpm(startParams.iParams.iName);

	CActiveScheduler::Start();

    Log(_L("LoadServer status was: <%d> "), asynchHandler->iStatus.Int());

    if (KErrNotFound != asynchHandler->iStatus.Int())
		{
		verdict = EFail;
		}

	CleanupStack::PopAndDestroy(asynchHandler);
	CleanupStack::PopAndDestroy(scheduler);
	return verdict;
	}


// Test step 3.18 - UnLoad unknown module and cancel
CRootServerTest3_18::CRootServerTest3_18()
	{
	// store the name of this test case
	iTestStepName = _L("Test3.18");
	}

TVerdict CRootServerTest3_18::doTestStepL( void )
	{
	TVerdict verdict = EPass;

	Log(_L("Test Purpose: UnLoad unknown module and cancel"));

	// Create scheduler/active object framework
	CSelfPopScheduler* scheduler = CSelfPopScheduler::CreateLC();
    CTestAsynchHandler* asynchHandler = CTestAsynchHandler::NewLC(&iRootServerSuite->RootSess());
	_LIT8(KUnknownModule, "unknown_module.cpm");
	Log(_L8("02 UnLoading module: %S"), &KUnknownModule());
	asynchHandler->TryUnLoad(KUnknownModule(), EUnGraceful);

	User::After(1000000);
	Log(_L8("03 Cancelling Unloading module: %S"), &KUnknownModule());
	iRootServerSuite->RootSess().CancelUnloadCpm(KUnknownModule());

	CActiveScheduler::Start();

    Log(_L("UnLoadServer status was: <%d> "), asynchHandler->iStatus.Int());

    if (KErrRSModuleNotLoaded != asynchHandler->iStatus.Int())
		{
		verdict = EFail;
		}

	CleanupStack::PopAndDestroy(asynchHandler);
	CleanupStack::PopAndDestroy(scheduler);
	return verdict;
	}



