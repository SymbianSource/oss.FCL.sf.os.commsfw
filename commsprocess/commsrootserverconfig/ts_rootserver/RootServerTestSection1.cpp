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
// This contains ESock Test cases from section 1
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
#include "RootServerTestSection1.h"


// Test step 1.1 - Set MBufPoolSize
CRootServerTest1_1::CRootServerTest1_1()
{
	// store the name of this test case
	iTestStepName = _L("Test1.1");
}

TVerdict CRootServerTest1_1::doTestStepL( void )
{
	Log(_L("Test Purpose: Set MBufPoolSize"));
	Log(_L("Depreciated by PREQ1248."));
	return EPass;

	}

// Test step 1.2 - Test that StartC32() doesnt leak handles.
CRootServerTest1_2::CRootServerTest1_2()
    {
	// store the name of this test case
	iTestStepName = _L("Test1.2");
    }

TVerdict CRootServerTest1_2::doTestStepL( void )
    {
	Log(_L("Test Purpose: Test that StartC32() doesnt leak handles"));

    TAutoClose<RThread> thisThread;

	//*****************step 1*************************
	// Open handle on current thread
	Log(_L("01 Open handle on current thread"));
    TInt result=thisThread.iObj.Open(RThread().Id());
	if (KErrNone != result)
		{
		return EFail;
		}

	//*****************step 2*************************
	// Get handlecount of thread
	Log(_L("02 Get handlecount of thread"));
    TInt threadhandlecount, processhandlecount;
    thisThread.iObj.HandleCount(processhandlecount, threadhandlecount);

	//*****************step 3*************************
	// Start comms process
	Log(_L("03 Start comms process"));
 	_LIT(KPhbkSyncCMI, "phbsync.cmi, c32.cmi, etel.cmi, esock.cmi, esock_main.cmi, esock_codealer1.cmi, esock_codealer2.cmi, esock_ip.cmi, esock_mip.cmi, esock_dip.cmi, esock_tr.cmi, esock_ir.cmi, esock_bt.cmi, esock_smswap.cmi, esock_pdummy1.cmi, esock_pdummy2.cmi, esock_ipc.cmi, esock_sip.cmi");
    result = StartC32WithCMISuppressions(KPhbkSyncCMI);
	if (KErrNone != result)
		{
		return EFail;
		}

	//*****************step 4*************************
	// Get handlecount of thread
	Log(_L("04 Get handlecount of thread"));
    TInt threadhandlecount2, processhandlecount2;
    thisThread.iObj.HandleCount(processhandlecount2, threadhandlecount2);

	if (threadhandlecount2!=threadhandlecount)
		{
		return EFail;
		}

	return EPass;
	}


