// Copyright (c) 2008-2009 Nokia Corporation and/or its subsidiary(-ies).
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
// Test19Prepend.cpp
// Contains MBufMgr Test Step 19 for Prepend() methods
//
//

// EPOC includes
#include <e32base.h>

// Test system includes
#ifdef SYMBIAN_OLD_EXPORT_LOCATION
#include "networking/log.h"
#include "networking/teststep.h"
#else
#include <networking/log.h>
#include <networking/teststep.h>
#endif

#include "TestStepCTMbufmgr.h"
#include "TestSuiteCTMbufmgr.h"

#include "Test19Prepend.h"

// constructor
CTest19Prepend::CTest19Prepend()
	{
	iTestStepName = _L("MBufMgrTest19");// Store the name of this test case
	}

// destructor
CTest19Prepend::~CTest19Prepend()
	{
	}

//
enum TVerdict CTest19Prepend::doTestStepL(void)
	{
	__UHEAP_MARK;

#ifdef __CFLOG_ACTIVE
	__CFLOG_CREATEL;
	__CFLOG_OPEN;
#endif

	//-------------- substep 1 --------------------
	Log(_L("  01 Create CMBufManager and install active scheduler:"));
    CleanupStack::PushL( iActSch = new(ELeave) CActiveScheduler );
	CActiveScheduler::Install(iActSch);

	RArray<TCommsBufPoolCreateInfo> poolInfoArray;
	TCommsBufPoolCreateInfo createInfo;
	createInfo.iBufSize = 128;
	createInfo.iInitialBufs = 128;
	createInfo.iGrowByBufs = 64;
	createInfo.iMinFreeBufs = 40;
	createInfo.iCeiling = (KMBufDefaultHeapSize / 2)/createInfo.iBufSize;
	poolInfoArray.AppendL(createInfo);
	CreateInstanceMBufMgrL(poolInfoArray);
	CleanupClosePushL(iBufPond);
	poolInfoArray.Close ();

	TBool firstFail = EFalse;
	TBool secondFail = EFalse;
	TInt ret;
	RMBufChain chain,chain2;

	//-------------- substep 2 --------------------
	Log(_L("  02 Prepend 20 bytes to an empty chain"));
	ret = chain.Prepend(20);
	if (ret != KErrNone)
		{
		Log(_L("Error: Couldn't prepend:"));
		firstFail = ETrue;
		}
	else
		{
	    if(chain.NumBufs() != 1)
	        {
		    Log(_L("Error: Wrong number of MBufs allocated:"));
			secondFail = ETrue;
		    }
		if(chain.Length() != 20)
			{
		    Log(_L("Error: Wrong number of bytes prepended:"));
			secondFail = ETrue;
			}
		//-------------- substep 3 --------------------
		Log(_L("  03 Deallocating RMBufChain"));
		chain.Free();
		}

	//-------------- substep 4 --------------------
	Log(_L("  04 Prepend 200 bytes to an empty chain"));
    ret = chain.Prepend(200);
	if (ret != KErrNone)
		{
		Log(_L("Error: Couldn't prepend:"));
		firstFail = ETrue;
		}
	else
		{
	    if(chain.NumBufs() != 2)
	        {
		    Log(_L("Error: Wrong number of MBufs allocated:"));
			secondFail = ETrue;
		    }
		if(chain.Length() != 200)
			{
		    Log(_L("Error: Wrong number of bytes prepended:"));
			secondFail = ETrue;
			}
		//-------------- substep 6 --------------------
		Log(_L("  05 Deallocating RMBufChain"));
		chain.Free();
		}
	//-------------- substep 6 --------------------
	Log(_L("  06 Prepend 20 bytes to an existing chain"));
	ret = chain.Alloc(20);
	if (ret != KErrNone)
	    {
        Log(_L("Error: Couldn't allocate initial chain:"));
        firstFail = ETrue;
	    }
    else
        {
		ret = chain.Prepend(20);
		if (ret != KErrNone)
			{
			Log(_L("Error: Couldn't prepend:"));
			firstFail = ETrue;
			}
		else
			{
			if(chain.NumBufs() != 2)
				{
				Log(_L("Error: Wrong number of MBufs allocated:"));
				secondFail = ETrue;
				}
			if(chain.Length() != 40)
				{
				Log(_L("Error: Wrong number of bytes:"));
				secondFail = ETrue;
				}
		    //-------------- substep 7 --------------------
			Log(_L("  07 Deallocating RMBufChain"));
			chain.Free();
			}
		}
	//-------------- substep 8 --------------------
	Log(_L("  08 Prepend 200 bytes to an existing chain"));
	ret = chain.Alloc(20);
	if (ret != KErrNone)
	    {
        Log(_L("Error: Couldn't allocate initial chain:"));
        firstFail = ETrue;
	    }
    else
        {
		ret = chain.Prepend(200);
		if (ret != KErrNone)
			{
			Log(_L("Error: Couldn't prepend:"));
			firstFail = ETrue;
			}
		else
			{
			if(chain.NumBufs() != 3)
				{
				Log(_L("Error: Wrong number of MBufs allocated:"));
				secondFail = ETrue;
				}
			if(chain.Length() != 220)
				{
				Log(_L("Error: Wrong number of bytes:"));
				secondFail = ETrue;
				}
		    //-------------- substep 9 --------------------
			Log(_L("  09 Deallocating RMBufChain"));
			chain.Free();
			}
		}
	//-------------- substep 10 --------------------
	Log(_L("  10 Prepend one chain onto another chain"));
	ret = chain.Alloc(20);
	if (ret != KErrNone)
	    {
        Log(_L("Error: Couldn't allocate initial chain:"));
        firstFail = ETrue;
	    }
    else
        {
		ret = chain2.Alloc(200);
		if (ret != KErrNone)
			{
			Log(_L("Error: Couldn't allocate second chain:"));
			firstFail = ETrue;
			}
		else
			{
			RMBuf* first = chain2.First();
			chain.Prepend(chain2);

			if(chain.NumBufs() != 3)
				{
				Log(_L("Error: Wrong number of MBufs in the chain:"));
				secondFail = ETrue;
				}
			if(chain.Length() != 220)
				{
				Log(_L("Error: Wrong number of bytes:"));
				secondFail = ETrue;
				}
			if(chain.First() != first)
			    {
				Log(_L("Error: chain2 not prepended correctly:"));
				secondFail = ETrue;
				}
		    //-------------- substep 11 --------------------
			Log(_L("  11 Deallocating RMBufChains"));
			chain2.Free();
			}
		chain.Free();
		}
	//-------------- substep 12 --------------------
	Log(_L("  12 Clean up stack:"));
    CleanupStack::PopAndDestroy(); // pond
	CActiveScheduler::Install(NULL);
	CleanupStack::PopAndDestroy(iActSch);

#ifdef __CFLOG_ACTIVE
	__CFLOG_CLOSE;
	__CFLOG_DELETE;
#endif
    __UHEAP_MARKEND;

    if (firstFail || secondFail)
    	{
    	return EFail;
    	}

	return EPass;
	}
