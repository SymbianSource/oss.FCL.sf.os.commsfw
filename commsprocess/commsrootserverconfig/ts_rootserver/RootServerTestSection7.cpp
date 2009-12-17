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
// This contains RootServer Test cases from section 8
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
#include "RootServerTestSection7.h"
#include "RootServerTest.h"

// Test step 7.1 - OOM loop Test1 - Load, Enumerate, GetInfo
CRootServerTest7_1::CRootServerTest7_1()
{
	// store the name of this test case
	iTestStepName = _L("Test7.1");
}

TVerdict CRootServerTest7_1::doTestStepL( void )
	{
	Log(_L("Test Purpose: OOM loop test 1: Load, Enumerate, GetInfo"));
	TVerdict verdict = EPass;
	// Create scheduler/active object framework 
	CSelfPopScheduler* scheduler = CSelfPopScheduler::CreateLC();
    CTestAsynchHandler* asynchHandler = CTestAsynchHandler::NewLC(&iRootServerSuite->RootSess());


	TInt failure = 1000;
	while(verdict == EPass)
		{
		iRootServerSuite->RootSess().__DbgFailNext(failure);
		failure++;

		TRSStartModuleParams startParams;
		TTestModuleIniData iniData;
		DefaultStartParams(startParams, iniData);
		startParams.iParams.iName = KModule1;
		
		asynchHandler->TryLoad(startParams, iniData);
    	CActiveScheduler::Start();

		if (asynchHandler->iStatus != KErrNone)
			{
			Log(_L("TryLoad: %d with FailNext(%d)"), asynchHandler->iStatus.Int(), failure);
if(asynchHandler->iStatus == KErrRSModuleAlreadyExist)
	User::Leave(KErrRSModuleAlreadyExist);
			continue;
			}

		TCFModuleName moduleName;
		TRSIter position;
		TInt ret = iRootServerSuite->RootSess().EnumerateModules(position, moduleName);
		if(ret != KErrNone)
			{
			Log(_L("EnumerateModules: %d with FailNext(%d)"), asynchHandler->iStatus.Int(), failure);
			continue;
			}

		if(moduleName != KModule1)
			{
			Log(_L8("EnumerateModules() returned KErrNone but wrong name: %S"), &moduleName);
			verdict = EFail;
			break;
			}

		TRSModuleInfo info;
		ret = iRootServerSuite->RootSess().GetModuleInfo(KModule1(), info);
		if(ret != KErrNone)
			{
			Log(_L("GetModuleInfo: %d with FailNext(%d)"), asynchHandler->iStatus.Int(), failure);
			continue;
			}

		if(info.iParams.iState != ERunning)
			{
			Log(_L("GetModuleInfo() returned KErrNone but wrong state: %d"), info.iParams.iState);
			verdict = EFail;
			}
		// everything worked;
		Log(_L("OOM loop complete"));
		break;
		}


	Log(_L("Resetting heap"));
	iRootServerSuite->RootSess().__DbgFailNext(-1);
	// uninstall and destroy active scheduler
	CleanupStack::PopAndDestroy(asynchHandler);
	CleanupStack::PopAndDestroy(scheduler);
	return verdict;
	}

// Test step 7.2 - OOM loop Test2 - Unload, GetInfo
CRootServerTest7_2::CRootServerTest7_2()
{
	// store the name of this test case
	iTestStepName = _L("Test7.2");
}

TVerdict CRootServerTest7_2::doTestStepL( void )
	{
	Log(_L("Test Purpose: Heap loop Test2 - Unload, GetInfo"));
	TVerdict verdict = EPass;
	// Create scheduler/active object framework 
	CSelfPopScheduler* scheduler = CSelfPopScheduler::CreateLC();
    CTestAsynchHandler* asynchHandler = CTestAsynchHandler::NewLC(&iRootServerSuite->RootSess());

	Log(_L8("01 Loading cpm: %S"), &KModule1());
	LoadNormalModuleL(asynchHandler, KModule1);

	TInt failure = 1;
	while(verdict == EPass)
		{
		iRootServerSuite->RootSess().__DbgFailNext(failure);
		failure++;

		asynchHandler->TryUnLoad(KModule1(), EUnGraceful);
    	CActiveScheduler::Start();

		if (asynchHandler->iStatus != KErrNone)
			{
			Log(_L("TryUnload: %d with FailNext(%d)"), asynchHandler->iStatus.Int(), failure);
			if(asynchHandler->iStatus != KErrRSModuleNotLoaded)
				{
				continue;
				}
			}

		TRSModuleInfo info;
		TInt ret = iRootServerSuite->RootSess().GetModuleInfo(KModule1(), info);
		if(ret == KErrRSModuleUnknown)
			{
			// everything worked;
			Log(_L("OOM loop complete"));
			break;
			}
		else if(ret == KErrNone)
			{
			Log(_L("GetModuleInfo() returned KErrNone for unloaded module"));
			verdict = EFail;
			}
		else 
			{
			Log(_L("GetModuleInfo: %d with FailNext(%d)"), ret, failure);
			continue;
			}
		}

	Log(_L("Resetting heap"));
	iRootServerSuite->RootSess().__DbgFailNext(-1);
	// uninstall and destroy active scheduler
	CleanupStack::PopAndDestroy(asynchHandler);
	CleanupStack::PopAndDestroy(scheduler);
	return verdict;
	}
	

// Test step 7.3 - OOM loop Test 3 - Bind
CRootServerTest7_3::CRootServerTest7_3()
{
	// store the name of this test case
	iTestStepName = _L("Test7.3");
}

TVerdict CRootServerTest7_3::doTestStepL( void )
	{
	Log(_L("Test Purpose: Heap loop Test3 - Bind, EnumerateBindings"));
	TVerdict verdict = EPass;
	// Create scheduler/active object framework 
	CSelfPopScheduler* scheduler = CSelfPopScheduler::CreateLC();
    CTestAsynchHandler* asynchHandler = CTestAsynchHandler::NewLC(&iRootServerSuite->RootSess());

	Log(_L8("01 Loading cpm: %S"), &KModule1());
	LoadNormalModuleL(asynchHandler, KModule1);

	TCFSubModuleAddress fullName1;
	fullName1.SetModule(KModule1());
	fullName1.SetSubModule(KSubModule1());
	TInt failure = 1;
	while(verdict == EPass)
		{
		Log(_L("Failing after %d Allocs"), failure);
		iRootServerSuite->RootSess().__DbgFailNext(failure);
		failure++;

		TInt ret = TryHierachicalBind(asynchHandler, KModule1, KSubModule1, KModule1, KSubModule2);
		if(ret != KErrNone)
			continue;

		Log(_L("02 Enumerate bindings"));
		TRSBindingInfo bindInfo;
		TRSIter position;
		ret = iRootServerSuite->RootSess().EnumerateBindings(fullName1, position, bindInfo);
		if(ret != KErrNone)
			continue;

		// everything worked;
		Log(_L("OOM loop complete"));
		break;
		}		

	CleanupStack::PopAndDestroy(asynchHandler);
	CleanupStack::PopAndDestroy(scheduler);
	return verdict;
	}

// Test step 7.4 - OOM loop Test 4 - Unbind
CRootServerTest7_4::CRootServerTest7_4()
{
	// store the name of this test case
	iTestStepName = _L("Test7.4");
}

TVerdict CRootServerTest7_4::doTestStepL( void )
	{
	Log(_L("Test Purpose: Heap loop Test4 - Unbind, EnumerateBindings"));
	TVerdict verdict = EPass;
	// Create scheduler/active object framework 
	CSelfPopScheduler* scheduler = CSelfPopScheduler::CreateLC();
    CTestAsynchHandler* asynchHandler = CTestAsynchHandler::NewLC(&iRootServerSuite->RootSess());

	Log(_L8("01 Loading and binding cpm: %S"), &KModule1());
	LoadNormalModuleL(asynchHandler, KModule1);
	TInt ret = TryHierachicalBind(asynchHandler, KModule1, KSubModule1, KModule1, KSubModule2);
	if(ret != KErrNone)
		{
		Log(_L("Binding CPM failed with %d"), ret);
		User::Leave(ret);
		}

	TCFSubModuleAddress fullName1;
	fullName1.SetModule(KModule1());
	fullName1.SetSubModule(KSubModule1());
	TInt failure = 1;
	while(verdict == EPass)
		{
		iRootServerSuite->RootSess().__DbgFailNext(failure);
		failure++;

		TRSUnBindingInfo unbindInfo;
		unbindInfo.iParams.iAddress1.SetModule(KModule1());
		unbindInfo.iParams.iAddress1.SetSubModule(KSubModule1());
		unbindInfo.iParams.iAddress2.SetModule(KModule1());
		unbindInfo.iParams.iAddress2.SetSubModule(KSubModule2());
		asynchHandler->TryUnBind( unbindInfo );
		
		CActiveScheduler::Start();

		if (asynchHandler->iStatus != KErrNone)
			{
			Log(_L("TryUnload: %d with FailNext(%d)"), asynchHandler->iStatus.Int(), failure);
			continue;
			}

		Log(_L("03 Enumerate bindings"));
		TRSBindingInfo bindInfo;
		TRSIter position;
		ret = iRootServerSuite->RootSess().EnumerateBindings(fullName1, position, bindInfo);
		if(ret == KErrEof)
			{
			Log(_L("OOM loop complete"));
			break;
			}
		else if(ret == KErrNone)
			{
			Log(_L("EnumerateBindings returned KErrNone for unbound submodules"));
			verdict = EFail;
			}
		else 
			{
			Log(_L("EnumerateBindings: %d with FailNext(%d)"), ret, failure);
			continue;
			}
		}		

	CleanupStack::PopAndDestroy(asynchHandler);
	CleanupStack::PopAndDestroy(scheduler);
	return verdict;
	}
	
	

