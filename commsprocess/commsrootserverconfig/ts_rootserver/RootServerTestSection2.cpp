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
// This contains ESock Test cases from section 2
// 
//

// EPOC includes
#include <e32base.h>

// RootServer includes
#include <es_mbman.h>

// Test system includes
#include <networking/log.h>
#include <networking/teststep.h>
#include <networking/testsuite.h>

#include "TestStepRootServer.h"
#include "TestSuiteRootServer.h"
#include "TestAsynchHandler.h"

#include "RootServerTestSection2.h"
#include "RootServerTest.h"

// Test step 2.1 - Enumerate with No Servers
CRootServerTest2_1::CRootServerTest2_1()
{
	// store the name of this test case
	iTestStepName = _L("Test2.1");
}

TVerdict CRootServerTest2_1::doTestStepL( void )
	{
	TVerdict verdict = EPass;

	Log(_L("Test Purpose: Enumerate with No Servers"));

	// enumerate servers
	Log(_L("02 Enumerating servers"));

	TCFModuleName moduleName;
	TRSIter position;
	TInt ret = iRootServerSuite->RootSess().EnumerateModules(position, moduleName);
	Log(_L("Enumerate returned %d"), ret);

	if (KErrEof != ret)
		{
		verdict = EFail;
		}

	return verdict;
	}


// Test step 2.2 - Enumerate
CRootServerTest2_2::CRootServerTest2_2()
	{
	// store the name of this test case
	iTestStepName = _L("Test2.2");
	}

TVerdict CRootServerTest2_2::doTestStepL( void )
	{	
	TVerdict verdict = EPass;

	Log(_L("Test Purpose: EnumerateModules"));

	// Create scheduler/active object framework 
	CSelfPopScheduler* scheduler = CSelfPopScheduler::CreateLC();
    CTestAsynchHandler* asynchHandler = CTestAsynchHandler::NewLC(&iRootServerSuite->RootSess());

	Log(_L8("01 Loading first cpm: %S"), &KModule1());
	LoadNormalModuleL(asynchHandler, KModule1);

	Log(_L8("02 Loading second cpm: %S"), &KModule2());
	LoadNormalModuleL(asynchHandler, KModule2);

	// uninstall active scheduler
	CleanupStack::PopAndDestroy(asynchHandler);
	CleanupStack::PopAndDestroy(scheduler);

	// now enumerate
	Log(_L("03 Enumerating once to get first servername"));

	TCFModuleName moduleName;
	TPtrC8 expectedModule2;
	TRSIter position;
	TInt ret = iRootServerSuite->RootSess().EnumerateModules(position, moduleName);

	Log(_L("Enumerate returned %d"), ret);

	if (KErrNone != ret)
		{
		verdict = EFail;
		}
	else
		{
		if (moduleName == KModule1)
			{
			expectedModule2.Set(KModule2);
			}
		else if(moduleName == KModule2)
			{
			expectedModule2.Set(KModule1);
			}
		else
			{
			Log(_L8("%S not found in serverlist"), &moduleName);
			verdict = EFail;
			}
		if(expectedModule2.Length())
			{
			Log(_L("Found first so enumerating again to get second servername"));
			ret = iRootServerSuite->RootSess().EnumerateModules(position, moduleName);

			Log(_L("Enumerate returned %d"), ret);

			if (KErrNone != ret)
				{
				verdict = EFail;
				}
			else if (moduleName != expectedModule2)
				{
				Log(_L8("%S not found in serverlist"), &moduleName);
				verdict = EFail;
				}
			else
				{
				Log(_L("Found second so enumerating again to get EOF"));
				ret = iRootServerSuite->RootSess().EnumerateModules(position, moduleName);
				Log(_L("Enumerate returned %d"), ret);
				if(ret != KErrEof)
					{
					verdict = EFail;
					}
				else
					{
					Log(_L("Found end of enumeration; enumerating again to check stability"));
					ret = iRootServerSuite->RootSess().EnumerateModules(position, moduleName);
					Log(_L("Enumerate returned %d"), ret);
					if(ret != KErrEof)
						{
						verdict = EFail;
						}
					}
				}
			}
			
		}

	return verdict;
	}

// Test step 2.3 - Enumerate submodules
CRootServerTest2_3::CRootServerTest2_3()
	{
	// store the name of this test case
	iTestStepName = _L("Test2.3");
	}

TVerdict CRootServerTest2_3::doTestStepL( void )
	{	
	TVerdict verdict = EPass;

	Log(_L("Test Purpose: EnumerateSubModules"));

	// Create scheduler/active object framework 
	CSelfPopScheduler* scheduler = CSelfPopScheduler::CreateLC();
    CTestAsynchHandler* asynchHandler = CTestAsynchHandler::NewLC(&iRootServerSuite->RootSess());

	Log(_L8("01 Loading test module: %S"), &KModule1());
	LoadNormalModuleL(asynchHandler, KModule1);

	// uninstall and destroy active scheduler
	CleanupStack::PopAndDestroy(asynchHandler);
	CleanupStack::PopAndDestroy(scheduler);
	
	TCFSubModuleName subModule;
	TCFModuleName module(KModule1());
	TBuf<0x40> str;
	TCFSubModuleName expected1(_L8("Test Protocol1"));
	TCFSubModuleName expected2(_L8("Test Protocol2"));
	TCFSubModuleName expected3(_L8("Test Protocol3"));
	TCFSubModuleName* expected[] = { &expected1, &expected2, &expected3 };
	const TInt cntExpected = sizeof(expected) / sizeof(expected[0]);
	TInt idx;
	TRSIter position;
	TInt ret;
	while((ret = iRootServerSuite->RootSess().EnumerateSubModules(module, position, subModule)) == KErrNone)
		{
		str.Copy(subModule);

		Log(_L("Got %S"), &str);
		for(idx = 0; idx < cntExpected; ++idx)
			{
			if ((expected[idx] && subModule == *expected[idx]))
				{
				expected[idx] = NULL;
				break;
				}
			}
		if(idx == cntExpected)
			{
			Log(_L("not an expected sub-module"));
			verdict = EFail;
			}
		}
	if(EPass == verdict && KErrEof != ret)
		{
		Log(_L("Enumeration didn't end with expected KErrEof"));
		verdict = EFail;
		}
	else if((ret = iRootServerSuite->RootSess().EnumerateSubModules(module, position, subModule)) != KErrEof)
		{
		Log(_L("Further enumeration didn't return expected KErrEof"));
		verdict = EFail;
		}

	for(idx = 0; idx < cntExpected; ++idx)
		{
		if (expected[idx])
			{
			Log(_L8("Expected sub-module %S wasn't enumerated"), expected[idx]);
			verdict = EFail;
			break;
			}
		}

	return verdict;
	}

