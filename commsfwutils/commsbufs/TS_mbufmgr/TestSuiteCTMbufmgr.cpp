// Copyright (c) 2002-2009 Nokia Corporation and/or its subsidiary(-ies).
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
// Contains main DLL entry point for dll and definition of test suite class.
//
//

// Test system includes
#include <es_mbuf.h>
#include "TestStepCTMbufmgr.h"
#include "TestSuiteCTMbufmgr.h"

#ifdef SYMBIAN_OLD_EXPORT_LOCATION
#include "networking/log.h"
#include "networking/teststep.h"
#include "networking/testsuite.h"
#else
#include <networking/log.h>
#include <networking/teststep.h>
#include <networking/testsuite.h>
#endif

#include "Test01CreateDeleteMBufMgr.h"
#include "Test02AllocDealloc.h"
#include "Test03AllocLeave.h"
#include "Test04CopyInOut.h"
#include "Test05CopyInOutOffset.h"
#include "Test06SplitL.h"
#include "Test07TrimStart.h"
#include "Test08TrimEnd.h"
#include "Test09Align.h"
#include "Test10CopyL.h"
#include "Test11AsyncAlloc.h"
#include "Test12General.h"
#include "Test13Performance.h"
#include "Test14HeapFreeCheck.h"
#include "Test15Concurrency.h"
#include "test16memoryfull.h"
#include "test17requestsizelimits.h"
#include "test18exhaustmidsizepools.h"
#include "test19prepend.h"
#include "test20poolceilingfull.h"
#include "test21commsbufs.h"
#include "test22append.h"
#include "test23rmbufq.h"


EXPORT_C CTestSuiteCTMbufmgr* NewTestSuiteCTMbufmgr( void )
	{
	return new (ELeave) CTestSuiteCTMbufmgr;
	}

CTestSuiteCTMbufmgr::~CTestSuiteCTMbufmgr()
	{
	}

// Add a test step into the suite
void CTestSuiteCTMbufmgr::AddTestStepL( CTestStepCTMbufmgr* ptrTestStep )
	{
	// Test steps contain a pointer back to the suite which owns them
	ptrTestStep->iEsockSuite = this;

	// Add the step using the base class method
	CTestSuite::AddTestStepL(ptrTestStep);
	}


// Make a version string available for test system
TPtrC CTestSuiteCTMbufmgr::GetVersion( void )
	{
#ifdef _DEBUG
	_LIT(KTxtVersion,"1.007 (udeb)");
#else
	_LIT(KTxtVersion,"1.007");
#endif

	return KTxtVersion();
	}

// Second phase constructor for MBufMgr test suite
// This creates all the MBufMgr test steps and
// stores them inside CTestSuiteCTMbufmgr
void CTestSuiteCTMbufmgr::InitialiseL( void )
	{

	// Add test steps
	AddTestStepL( new(ELeave) CTest01CreateDeleteMBufMgr );
	AddTestStepL( new(ELeave) CTest02AllocDealloc );
	AddTestStepL( new(ELeave) CTest03AllocLeave );
	AddTestStepL( new(ELeave) CTest04CopyInOut );
	AddTestStepL( new(ELeave) CTest05CopyInOutOffset );
	AddTestStepL( new(ELeave) CTest06Split );
	AddTestStepL( new(ELeave) CTest07TrimStart );
	AddTestStepL( new(ELeave) CTest08TrimEnd );
	AddTestStepL( new(ELeave) CTest09Align );
	AddTestStepL( new(ELeave) CTest10Copy );
	AddTestStepL( new(ELeave) CTest11AsyncAlloc );
	AddTestStepL( new(ELeave) CTest12General );
	AddTestStepL( new(ELeave) CTest13Performance );
	AddTestStepL( new(ELeave) CTest14HeapFreeCheck );
	AddTestStepL( new(ELeave) CTest15Concurrency );
	AddTestStepL( new(ELeave) CTest16MemoryFull );
	AddTestStepL( new(ELeave) CTest17RequestSizeLimits );
	AddTestStepL( new(ELeave) CTest19Prepend );
	AddTestStepL( new(ELeave) CTest20PoolCeilingFull );
    AddTestStepL( new(ELeave) CTest21CommsBufs );
	AddTestStepL( new(ELeave) CTest22Append );
	AddTestStepL( new(ELeave) CTest23RMBufQ );
	return;
	}

