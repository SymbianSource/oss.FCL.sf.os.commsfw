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
#include "RootServerTestSection6.h"
#include <cfshared.h>
#include "RootServerTest.h"


// Test step 6.1 - Bind without loading
CRootServerTest6_1::CRootServerTest6_1()
{
	// store the name of this test case
	iTestStepName = _L("Test6.1");
}

TVerdict CRootServerTest6_1::doTestStepL( void )
	{
	Log(_L("Test Purpose: Bind without loading"));
	TVerdict verdict = EPass;

	// Create scheduler/active object framework 
	CSelfPopScheduler* scheduler = CSelfPopScheduler::CreateLC();
    CTestAsynchHandler* asynchHandler = CTestAsynchHandler::NewLC(&iRootServerSuite->RootSess());

	//*****************step 2************************
	Log(_L("02 Attempting bind"));
	TInt ret = TryHierachicalBind(asynchHandler, KModule1, KSubModule1, KModule1, KSubModule2);
	if (ret != KErrRSModuleNotLoaded)
		{
		Log(_L("LoadProvider returned error: <%d> "), asynchHandler->iStatus.Int());
		verdict = EFail;
		}

	// uninstall and destroy active scheduler
	CleanupStack::PopAndDestroy(asynchHandler);
	CleanupStack::PopAndDestroy(scheduler);
	return verdict;

	}
	
	// Test step 6.2 - Bind loaded to unloaded
CRootServerTest6_2::CRootServerTest6_2()
{
	// store the name of this test case
	iTestStepName = _L("Test6.2");
}

TVerdict CRootServerTest6_2::doTestStepL( void )
	{
	Log(_L("Test Purpose: Bind loaded to unloaded"));
	TVerdict verdict = EPass;

	// Create scheduler/active object framework 
	CSelfPopScheduler* scheduler = CSelfPopScheduler::CreateLC();
    CTestAsynchHandler* asynchHandler = CTestAsynchHandler::NewLC(&iRootServerSuite->RootSess());

	//*****************step 02*************************//
	Log(_L("02 Load Test Module"));
	LoadNormalModuleL(asynchHandler, KModule1);

	//*****************step 3************************
	Log(_L("03 Attempting bind"));
	TInt ret = TryHierachicalBind(asynchHandler, KModule1, KSubModule1, KModule2, KSubModule1);
	if (ret != KErrRSModuleNotLoaded)
		{
		Log(_L("Bind returned error: <%d> "), ret);
		verdict = EFail;
		}

	// uninstall and destroy active scheduler
	CleanupStack::PopAndDestroy(asynchHandler);
	CleanupStack::PopAndDestroy(scheduler);
	return verdict;

	}


TVerdict CRootServerTest6_BindWithinModule::BindWithinModuleL(TThreadPriority aPriority)
	{
	TVerdict verdict = EPass;

	// Create scheduler/active object framework 
	CSelfPopScheduler* scheduler = CSelfPopScheduler::CreateLC();
    CTestAsynchHandler* asynchHandler = CTestAsynchHandler::NewLC(&iRootServerSuite->RootSess());

	//*****************step 01*************************//
	Log(_L("01 Load Test Module"));
	LoadNormalModuleL(asynchHandler, KModule1, aPriority);

	//*****************step 2***********************
	Log(_L("02 Attempting Bind"));
	TInt ret = TryHierachicalBind(asynchHandler, KModule1, KSubModule1, KModule1, KSubModule2);
	if (ret != KErrNone)
		{
		Log(_L("Bind returned error: <%d> "), ret);
		verdict = EFail;
		}

	// uninstall and destroy active scheduler
	CleanupStack::PopAndDestroy(asynchHandler);
	CleanupStack::PopAndDestroy(scheduler);
	return verdict;
	}

// Test step 6.3 - Bind within a module (normal priority)
CRootServerTest6_3::CRootServerTest6_3()
{
	// store the name of this test case
	iTestStepName = _L("Test6.3");
}

TVerdict CRootServerTest6_3::doTestStepL( void )
	{
	Log(_L("Test Purpose: Bind within module (normal priority)"));
	return BindWithinModuleL(EPriorityNormal);
	}
	
// Test step 6.4 - Bind within a module (elevated priority)
CRootServerTest6_4::CRootServerTest6_4()
{
	// store the name of this test case
	iTestStepName = _L("Test6.4");
}

TVerdict CRootServerTest6_4::doTestStepL( void )
	{
	Log(_L("Test Purpose: Bind within module (elevated priority)"));
	return BindWithinModuleL(EPriorityRealTime);
	}

// Test step 6.5 - Bind submodule to itself
CRootServerTest6_5::CRootServerTest6_5()
{
	// store the name of this test case
	iTestStepName = _L("Test6.5");
}

TVerdict CRootServerTest6_5::doTestStepL( void )
	{
	Log(_L("Test Purpose: Bind submodule to itself"));
	TVerdict verdict = EPass;

	// Create scheduler/active object framework 
	CSelfPopScheduler* scheduler = CSelfPopScheduler::CreateLC();
    CTestAsynchHandler* asynchHandler = CTestAsynchHandler::NewLC(&iRootServerSuite->RootSess());

	//*****************step 01*************************//
	Log(_L("01 Load Test Module"));
	LoadNormalModuleL(asynchHandler, KModule1);

	//*****************step 2***********************
	Log(_L("02 Attempting Bind"));
	TInt ret = TryHierachicalBind(asynchHandler, KModule1, KSubModule1, KModule1, KSubModule1);
	if (ret != KErrNone)
		{
		Log(_L("Bind returned error: <%d> "), ret);
		verdict = EFail;
		}

	// uninstall and destroy active scheduler
	CleanupStack::PopAndDestroy(asynchHandler);
	CleanupStack::PopAndDestroy(scheduler);
	return verdict;
	}

// Test step 6.6 - Bind already bound
CRootServerTest6_6::CRootServerTest6_6()
{
	// store the name of this test case
	iTestStepName = _L("Test6.6");
}

TVerdict CRootServerTest6_6::doTestStepL( void )
	{
	Log(_L("Test Purpose: Bind again"));
	TVerdict verdict = EPass;

	// Create scheduler/active object framework 
	CSelfPopScheduler* scheduler = CSelfPopScheduler::CreateLC();
    CTestAsynchHandler* asynchHandler = CTestAsynchHandler::NewLC(&iRootServerSuite->RootSess());

	//*****************step 01*************************//
	Log(_L("01 Load Test Module"));
	LoadNormalModuleL(asynchHandler, KModule1);

	//*****************step 2************************
	Log(_L("02 Bind internally"));
	TInt ret = TryHierachicalBind(asynchHandler, KModule1, KSubModule1, KModule1, KSubModule2);
	if (ret != KErrNone)
		{
		Log(_L("Bind returned error: <%d> "), ret);
		User::Leave(ret);
		}

	//*****************step 3************************
	Log(_L("03 Bind Again"));
	ret = TryHierachicalBind(asynchHandler, KModule1, KSubModule1, KModule1, KSubModule2);
	if (ret != KErrRSAlreadyBound)
		{
		Log(_L("Bind returned error: <%d> "), ret);
		User::Leave(KErrGeneral);
		}

	// uninstall and destroy active scheduler
	CleanupStack::PopAndDestroy(asynchHandler);
	CleanupStack::PopAndDestroy(scheduler);
	return verdict;

	}
	
// Test step 6.7 - Enumerate BindInfo
CRootServerTest6_7::CRootServerTest6_7()
{
	// store the name of this test case
	iTestStepName = _L("Test6.7");
}

TVerdict CRootServerTest6_7::doTestStepL( void )
	{
	TCFSubModuleAddress fullName1;
	fullName1.SetModule(KModule1());
	fullName1.SetSubModule(KSubModule1());
	TCFSubModuleAddress fullName2;
	fullName2.SetModule(KModule1());
	fullName2.SetSubModule(KSubModule2());	
	
	Log(_L("Test Purpose: Enumerate BindInfo"));
	TVerdict verdict = EPass;

	// Create scheduler/active object framework 
	CSelfPopScheduler* scheduler = CSelfPopScheduler::CreateLC();
    CTestAsynchHandler* asynchHandler = CTestAsynchHandler::NewLC(&iRootServerSuite->RootSess());
	//*****************step 01*************************//
	Log(_L("01 Load Test Module"));
	LoadNormalModuleL(asynchHandler, KModule1);

	//*****************step 2************************
	Log(_L("02 Bind internally"));
	TInt ret = TryHierachicalBind(asynchHandler, KModule1, KSubModule1, KModule1, KSubModule2);
	if (ret != KErrNone)
		{
		Log(_L("Bind returned error: <%d> "), ret);
		User::Leave(ret);
		}

	TRSBindingInfo bindInfo;
	TRSIter position;
	
	//*****************step 2************************
	Log(_L("02 Enumerate bindings"));
	ret = iRootServerSuite->RootSess().EnumerateBindings(fullName1, position, bindInfo);

	Log(_L("Enumerate returned %d"), ret);

	if (KErrNone != ret)
		{
		verdict = EFail;
		}
	else
		{		
		if ( (bindInfo.iParams.iAddress1 == fullName1) && (bindInfo.iParams.iAddress2 == fullName2) )
			{
			Log(_L("Binding Found") );
			}
		else if ( (bindInfo.iParams.iAddress1 == fullName2) && (bindInfo.iParams.iAddress2 == fullName1) )
			{
			Log(_L("Binding Found") );
			}
		else
			{
			Log(_L("Binding not found"));
			verdict = EFail;
			}
		ret = iRootServerSuite->RootSess().EnumerateBindings(fullName1, position, bindInfo);
		Log(_L("Follow-up Enumerate returned %d"), ret);
		if(KErrEof != ret)
			{
			Log(_L("(should have returned KErrEof"));
			verdict = EFail;
			}
		ret = iRootServerSuite->RootSess().EnumerateBindings(fullName1, position, bindInfo);
		Log(_L("Further Enumerate returned %d"), ret);
		if(KErrEof != ret)
			{
			Log(_L("(should have returned KErrEof"));
			verdict = EFail;
			}
		}
	
	// uninstall and destroy active scheduler
	CleanupStack::PopAndDestroy(asynchHandler);
	CleanupStack::PopAndDestroy(scheduler);

	return verdict;
	}


TVerdict CRootServerTest6_UnbindWithinModule::UnbindWithinModuleL(TThreadPriority aPriority)
	{
	TVerdict verdict = EPass;

	// Create scheduler/active object framework 
	CSelfPopScheduler* scheduler = CSelfPopScheduler::CreateLC();
    CTestAsynchHandler* asynchHandler = CTestAsynchHandler::NewLC(&iRootServerSuite->RootSess());

	//*****************step 01*************************//
	Log(_L("01 Load Test Module"));
	LoadNormalModuleL(asynchHandler, KModule1, aPriority);

	//*****************step 2************************
	Log(_L("02 Bind internally"));
	TInt ret = TryHierachicalBind(asynchHandler, KModule1, KSubModule1, KModule1, KSubModule2);
	if (ret != KErrNone)
		{
		Log(_L("Bind returned error: <%d> "), ret);
		User::Leave(ret);
		}
	//*****************step 3************************
	Log(_L("03 Unbind"));
	TRSUnBindingInfo unbindInfo;
	unbindInfo.iParams.iAddress1.SetModule(KModule1());
	unbindInfo.iParams.iAddress1.SetSubModule(KSubModule1());
	unbindInfo.iParams.iAddress2.SetModule(KModule1());
	unbindInfo.iParams.iAddress2.SetSubModule(KSubModule2());

    asynchHandler->TryUnBind( unbindInfo );
	
	CActiveScheduler::Start();
	if (asynchHandler->iStatus != KErrNone)
		{
		Log(_L("Unbind returned error: <%d> "), asynchHandler->iStatus.Int());
		verdict = EFail;
		}
	
	Log(_L("04 Duplicate Unbind"));
    asynchHandler->TryUnBind( unbindInfo );
	
	CActiveScheduler::Start();
	if (asynchHandler->iStatus != KErrRSBindingUnknown)
		{
		Log(_L("Duplicate Unbind returned error: <%d> "), asynchHandler->iStatus.Int());
		verdict = EFail;
		}
	
	// uninstall and destroy active scheduler
	CleanupStack::PopAndDestroy(asynchHandler);
	CleanupStack::PopAndDestroy(scheduler);
	return verdict;
	}

// Test step 6.8 - Unbind within Module (normal priority)
CRootServerTest6_8::CRootServerTest6_8()
{
	// store the name of this test case
	iTestStepName = _L("Test6.8");
}

TVerdict CRootServerTest6_8::doTestStepL( void )
	{
	Log(_L("Test Purpose: UnBind within Module (elevated priority)"));
	return UnbindWithinModuleL(EPriorityNormal);
	}
	
// Test step 6.9 - Unbind within Module (normal priority)
CRootServerTest6_9::CRootServerTest6_9()
{
	// store the name of this test case
	iTestStepName = _L("Test6.9");
}

TVerdict CRootServerTest6_9::doTestStepL( void )
	{
	Log(_L("Test Purpose: UnBind within Module (elevated priority)"));
	return UnbindWithinModuleL(EPriorityRealTime);
	}
	

	
// Test step 6.10 - Cancel Bind
CRootServerTest6_10::CRootServerTest6_10()
{
	// store the name of this test case
	iTestStepName = _L("Test6.10");
}

TVerdict CRootServerTest6_10::doTestStepL( void )
	{
	Log(_L("Test Purpose: Cancel bind"));
	TVerdict verdict = EPass;

	// Create scheduler/active object framework 
	CSelfPopScheduler* scheduler = CSelfPopScheduler::CreateLC();
    CTestAsynchHandler* asynchHandler = CTestAsynchHandler::NewLC(&iRootServerSuite->RootSess());

	//*****************step 01*************************//
	Log(_L("01 Load Test Module"));
	LoadNormalModuleL(asynchHandler, KModule1);

	//*****************step 2************************
	Log(_L("02 Attempting bind"));
	TRSBindingInfo bindInfo;
	bindInfo.iParams.iType = EHierarchical;
	bindInfo.iParams.iAddress1.SetModule(KModule1());
	bindInfo.iParams.iAddress1.SetSubModule(KSubModule1());
	bindInfo.iParams.iAddress2.SetModule(KModule1());
	bindInfo.iParams.iAddress2.SetSubModule(KSubModule2());
	bindInfo.iParams.iState1 = KErrNone;
	bindInfo.iParams.iState2 = KErrNone;
	bindInfo.iParams.iForwardQLength = TRSBindingInfo::EMinQueueLength;	
	bindInfo.iParams.iReverseQLength = TRSBindingInfo::EMinQueueLength;	
	
	TRSSubModuleAddress name1(bindInfo.iParams.iAddress1);
	TRSSubModuleAddress name2(bindInfo.iParams.iAddress2);
		
	asynchHandler->TryBind( bindInfo );
	
	//*****************step 3************************
	Log(_L("04 Wait for bind to be completed"));
	User::After(1000000);
	//*****************step 4************************
	Log(_L("04 Cancelling Bind"));
	iRootServerSuite->RootSess().CancelBind(name1, name2);
	
	CActiveScheduler::Start();

	if (asynchHandler->iStatus != KErrNone)
		{
		Log(_L("Bind returned error: <%d> "), asynchHandler->iStatus.Int());
		verdict = EFail;
		}

	// uninstall and destroy active scheduler
	CleanupStack::PopAndDestroy(asynchHandler);
	CleanupStack::PopAndDestroy(scheduler);
	return verdict;

	}
	
// Test step 6.11 - Cancel UnBind
CRootServerTest6_11::CRootServerTest6_11()
{
	// store the name of this test case
	iTestStepName = _L("Test6.11");
}

TVerdict CRootServerTest6_11::doTestStepL( void )
	{
	Log(_L("Test Purpose: Cancel Unbind"));
	TVerdict verdict = EPass;

	// Create scheduler/active object framework 
	CSelfPopScheduler* scheduler = CSelfPopScheduler::CreateLC();
    CTestAsynchHandler* asynchHandler = CTestAsynchHandler::NewLC(&iRootServerSuite->RootSess());

	//*****************step 01*************************//
	Log(_L("01 Load Test Module"));
	LoadNormalModuleL(asynchHandler, KModule1);

	//*****************step 2************************
	Log(_L("02 Bind internally"));
	TInt ret = TryHierachicalBind(asynchHandler, KModule1, KSubModule1, KModule1, KSubModule2);
	if (ret != KErrNone)
		{
		Log(_L("Bind returned error: <%d> "), ret);
		User::Leave(ret);
		}

	//*****************step 3************************
	Log(_L("03 Unbind"));
	TRSUnBindingInfo unbindInfo;
	unbindInfo.iParams.iAddress1.SetModule(KModule1());
	unbindInfo.iParams.iAddress1.SetSubModule(KSubModule1());
	unbindInfo.iParams.iAddress2.SetModule(KModule1());
	unbindInfo.iParams.iAddress2.SetSubModule(KSubModule2());
	
	TRSSubModuleAddress name1(unbindInfo.iParams.iAddress1);
	TRSSubModuleAddress name2(unbindInfo.iParams.iAddress2);

    asynchHandler->TryUnBind( unbindInfo );
    
    //*****************step 4************************
	Log(_L("04 Wait for unbind to be completed"));
 	User::After(1000000);
	//*****************step 5************************
   Log(_L("05 Cancelling UnBind"));
	iRootServerSuite->RootSess().CancelUnbind(name1, name2);
	
	CActiveScheduler::Start();

	if (asynchHandler->iStatus != KErrNone)
		{
		Log(_L("Unbind returned error: <%d> "), asynchHandler->iStatus.Int());
		verdict = EFail;
		}

	// uninstall and destroy active scheduler
	CleanupStack::PopAndDestroy(asynchHandler);
	CleanupStack::PopAndDestroy(scheduler);
	return verdict;

	}
	
// Test step 6.12 - Bind sluggish cpm
CRootServerTest6_12::CRootServerTest6_12()
{
	// store the name of this test case
	iTestStepName = _L("Test6.12");
}

TVerdict CRootServerTest6_12::doTestStepL( void )
	{
	Log(_L("Test Purpose: Bind sluggish cpm"));
	TVerdict verdict = EPass;

	// Create scheduler/active object framework 
	CSelfPopScheduler* scheduler = CSelfPopScheduler::CreateLC();
    CTestAsynchHandler* asynchHandler = CTestAsynchHandler::NewLC(&iRootServerSuite->RootSess());
    
	TRSStartModuleParams startParams;
	TTestModuleIniData iniData;
	DefaultStartParams(startParams, iniData);
	startParams.iParams.iName = KModule1;
	iniData.iParams.iDiscoveryDelay = 500;
	iniData.iParams.iBindDelay = 500;
	iniData.iParams.iUnbindDelay = 500;
	iniData.iParams.iShutdownDelay = 500;
	asynchHandler->TryLoad(startParams, iniData);

    CActiveScheduler::Start();
   	if (asynchHandler->iStatus != KErrNone)
		{
		Log(_L("LoadServer returned error: <%d> "), asynchHandler->iStatus.Int());
		User::Leave(asynchHandler->iStatus.Int());
		}
    //*****************step 02*************************//
	Log(_L("02 Attempting bind"));
	TInt ret = TryHierachicalBind(asynchHandler, KModule1, KSubModule1, KModule1, KSubModule2);
	if (ret != KErrNone)
		{
		Log(_L("Bind returned error: <%d> "), ret);
		verdict = EFail;
		}

	// uninstall and destroy active scheduler
	CleanupStack::PopAndDestroy(asynchHandler);
	CleanupStack::PopAndDestroy(scheduler);
	return verdict;

	}
	
// Test step 6.13 - Bind dormant cpm
CRootServerTest6_13::CRootServerTest6_13()
{
	// store the name of this test case
	iTestStepName = _L("Test6.13");
}

TVerdict CRootServerTest6_13::doTestStepL( void )
	{
	Log(_L("Test Purpose: Bind dormant cpm"));
	TVerdict verdict = EPass;

	// Create scheduler/active object framework 
	CSelfPopScheduler* scheduler = CSelfPopScheduler::CreateLC();
    CTestAsynchHandler* asynchHandler = CTestAsynchHandler::NewLC(&iRootServerSuite->RootSess());
    
       //*****************step 02*************************//
	Log(_L("02 Load Dormant Test CPM"));
	TRSStartModuleParams startParams;
	TTestModuleIniData iniData;
	DefaultStartParams(startParams, iniData);
	startParams.iParams.iName = KModule1;
	iniData.iParams.iDiscoveryDelay = 500;
	iniData.iParams.iBindDelay = 30000;
	iniData.iParams.iUnbindDelay = 30000;
	iniData.iParams.iShutdownDelay = 1000;
	asynchHandler->TryLoad(startParams, iniData);

    CActiveScheduler::Start();
   	if (asynchHandler->iStatus != KErrNone)
		{
		Log(_L("LoadServer returned error: <%d> "), asynchHandler->iStatus.Int());
		User::Leave(asynchHandler->iStatus.Int());
		}
    //*****************step 02*************************//
	Log(_L("02 Attempting bind"));
	TInt ret = TryHierachicalBind(asynchHandler, KModule1, KSubModule1, KModule1, KSubModule2);
	if (ret != KErrRSRequestTimedOut)
		{
		Log(_L("Bind returned error: <%d> "), ret);
		verdict = EFail;
		}

	// uninstall and destroy active scheduler
	CleanupStack::PopAndDestroy(asynchHandler);
	CleanupStack::PopAndDestroy(scheduler);
	return verdict;

	}
	
// Test step 6.14 - UnBind sluggish test cpm
CRootServerTest6_14::CRootServerTest6_14()
{
	// store the name of this test case
	iTestStepName = _L("Test6.14");
}

TVerdict CRootServerTest6_14::doTestStepL( void )
	{
	Log(_L("Test Purpose: Unbind sluggish test cpm"));
	TVerdict verdict = EPass;

	// Create scheduler/active object framework 
	CSelfPopScheduler* scheduler = CSelfPopScheduler::CreateLC();
    CTestAsynchHandler* asynchHandler = CTestAsynchHandler::NewLC(&iRootServerSuite->RootSess());

	TRSStartModuleParams startParams;
	TTestModuleIniData iniData;
	DefaultStartParams(startParams, iniData);
	startParams.iParams.iName = KModule1;
	iniData.iParams.iDiscoveryDelay = 500;
	iniData.iParams.iBindDelay = 500;
	iniData.iParams.iUnbindDelay = 500;
	iniData.iParams.iShutdownDelay = 500;
	asynchHandler->TryLoad(startParams, iniData);

    CActiveScheduler::Start();
   	if (asynchHandler->iStatus != KErrNone)
		{
		Log(_L("LoadServer returned error: <%d> "), asynchHandler->iStatus.Int());
		User::Leave(asynchHandler->iStatus.Int());
		}
    //*****************step 02*************************//
	Log(_L("02 Attempting bind"));
	TInt ret = TryHierachicalBind(asynchHandler, KModule1, KSubModule1, KModule1, KSubModule2);
	if (ret != KErrNone)
		{
		Log(_L("Bind returned error: <%d> "), ret);
		User::Leave(asynchHandler->iStatus.Int());
		}

	Log(_L("03 Unbind"));
	TRSUnBindingInfo unbindInfo;
	unbindInfo.iParams.iAddress1.SetModule(KModule1());
	unbindInfo.iParams.iAddress1.SetSubModule(KSubModule1());
	unbindInfo.iParams.iAddress2.SetModule(KModule1());
	unbindInfo.iParams.iAddress2.SetSubModule(KSubModule2());

    asynchHandler->TryUnBind( unbindInfo );
	
	CActiveScheduler::Start();
	if (asynchHandler->iStatus != KErrNone)
		{
		Log(_L("Unbind returned error: <%d> "), asynchHandler->iStatus.Int());
		verdict = EFail;
		}

	// uninstall and destroy active scheduler
	CleanupStack::PopAndDestroy(asynchHandler);
	CleanupStack::PopAndDestroy(scheduler);
	return verdict;

	}
	
	
// Test step 6.15 - UnBind dormant test cpm
CRootServerTest6_15::CRootServerTest6_15()
{
	// store the name of this test case
	iTestStepName = _L("Test6.15");
}

TVerdict CRootServerTest6_15::doTestStepL( void )
	{
	Log(_L("Test Purpose: Unbind dormant test cpm"));
	TVerdict verdict = EPass;

	// Create scheduler/active object framework 
	CSelfPopScheduler* scheduler = CSelfPopScheduler::CreateLC();
    CTestAsynchHandler* asynchHandler = CTestAsynchHandler::NewLC(&iRootServerSuite->RootSess());

	TRSStartModuleParams startParams;
	TTestModuleIniData iniData;
	DefaultStartParams(startParams, iniData);
	startParams.iParams.iName = KModule1;
	iniData.iParams.iDiscoveryDelay = 500;
	iniData.iParams.iBindDelay = 500;
	iniData.iParams.iUnbindDelay = 30000;
	iniData.iParams.iShutdownDelay = 500;
	asynchHandler->TryLoad(startParams, iniData);

    CActiveScheduler::Start();
   	if (asynchHandler->iStatus != KErrNone)
		{
		Log(_L("LoadServer returned error: <%d> "), asynchHandler->iStatus.Int());
		User::Leave(asynchHandler->iStatus.Int());
		}
    //*****************step 02*************************//
	Log(_L("02 Attempting bind"));
	TInt ret = TryHierachicalBind(asynchHandler, KModule1, KSubModule1, KModule1, KSubModule2);
	if (ret != KErrNone)
		{
		Log(_L("Bind returned error: <%d> "), ret);
		User::Leave(asynchHandler->iStatus.Int());
		}

	Log(_L("03 Unbind"));
	TRSUnBindingInfo unbindInfo;
	unbindInfo.iParams.iAddress1.SetModule(KModule1());
	unbindInfo.iParams.iAddress1.SetSubModule(KSubModule1());
	unbindInfo.iParams.iAddress2.SetModule(KModule1());
	unbindInfo.iParams.iAddress2.SetSubModule(KSubModule2());

    asynchHandler->TryUnBind( unbindInfo );
	CActiveScheduler::Start();

	if (asynchHandler->iStatus != KErrRSRequestTimedOut)
		{
		Log(_L("Unbind returned error: <%d> "), asynchHandler->iStatus.Int());
		verdict = EFail;
		}
	// uninstall and destroy active scheduler
	CleanupStack::PopAndDestroy(asynchHandler);
	CleanupStack::PopAndDestroy(scheduler);
	return verdict;
	}


// Test step 6.16 - Bind between a server and a module
CRootServerTest6_16::CRootServerTest6_16()
{
	// store the name of this test case
	iTestStepName = _L("Test6.16");
}

TVerdict CRootServerTest6_16::doTestStepL( void )
	{
	Log(_L("Test Purpose: Bind between a server and a module"));
	TVerdict verdict = EPass;

	// Create scheduler/active object framework 
	CSelfPopScheduler* scheduler = CSelfPopScheduler::CreateLC();
    CTestAsynchHandler* asynchHandler = CTestAsynchHandler::NewLC(&iRootServerSuite->RootSess());

	_LIT8(KPlainModule, "PlainCPM");
	_LIT8(KServerModule, "ServerCPM");

	//*****************step 01*************************//
	Log(_L("01 Load Plain Module"));
	LoadNormalModuleL(asynchHandler, KPlainModule);

	//*****************step 02*************************//
	Log(_L("02 Load Server Module"));
	TRSStartModuleParams startParams;
	TTestModuleIniData iniData;
	DefaultStartParams(startParams, iniData);
	startParams.iParams.iName = KServerModule;
	startParams.iParams.iIsServer = ETrue;
	asynchHandler->TryLoad(startParams, iniData);

    CActiveScheduler::Start();
   	if (asynchHandler->iStatus != KErrNone)
		{
		Log(_L("LoadServer returned error: <%d> "), asynchHandler->iStatus.Int());
		User::Leave(asynchHandler->iStatus.Int());
		}

    //*****************step 03*************************//
	Log(_L("03 Attempting bind of plain above server"));
	TInt ret = TryHierachicalBind(asynchHandler, KPlainModule, KSubModule1, KServerModule, KSubModule1);
	if (ret != KErrRSInvalidBinding)
		{
		Log(_L("Bind returned error: <%d> "), ret);
		User::Leave(ret);
		}

	//*****************step 04***********************
	Log(_L("04 Attempting bind of server above plain"));
	ret = TryHierachicalBind(asynchHandler, KServerModule, KSubModule1, KPlainModule, KSubModule1);
	if (ret != KErrNone)
		{
		Log(_L("Bind returned error: <%d> "), ret);
		User::Leave(ret);
		}

	// uninstall and destroy active scheduler
	CleanupStack::PopAndDestroy(asynchHandler);
	CleanupStack::PopAndDestroy(scheduler);
	return verdict;

	}

