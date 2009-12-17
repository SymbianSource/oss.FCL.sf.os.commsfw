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
//
 
// EPOC includes
#include <e32base.h>
#include <commdb.h>
#include <d32comm.h>
#include <cdbstore.h>

// Test system includes
#include <networking/log.h>
#include <networking/teststep.h>
#include "Teststepcommdb.h"
#include "TestSuiteCommdb.h"

#ifdef SYMBIAN_OLD_EXPORT_LOCATION
#include <comms-infras/commdb/protection/protectdb.h>
#include <comms-infras/commdb/protection/protectcpdb.h>
#else
//these headers are user includes in the new env.
#include "protectdb.h"
#include "protectcpdb.h"
#endif

#include <cdbpreftable.h>

#include "step_057_xx.h"

//
//	Test step 057.01
//

//TestProtectRecords
CCommDbTest057_01::CCommDbTest057_01()
{
	// store the name of this test case
	iTestStepName = _L("step_057_01");
}

CCommDbTest057_01::~CCommDbTest057_01()
{
	delete iTheDb;
}

TVerdict CCommDbTest057_01::doTestStepPreambleL()
	{	
	iTheDb = CCommsDatabase::NewL(EDatabaseTypeIAP);
	return EPass;
	}

enum TVerdict CCommDbTest057_01::doTestStepL( void )
	{

	Log(_L("Test Protect Connection Prefs Table "));
	iTestStepResult = EPass;

    CCommsDbConnectionPrefTableView::TCommDbIapConnectionPref  RecordData1, RecordData2;

	// protect the table and do some checking
	// database is modified
	//

	CCommsDbProtectConnectPrefTableView* table = (CCommsDbProtectConnectPrefTableView *)iTheDb->OpenConnectionPrefTableLC();
	CheckTableIsNotProtectedL(table);

	table->ReadConnectionPreferenceL(RecordData1);

	TESTL(table->ProtectTable()==KErrNone);
	
	CheckTableIsProtectedL(table);
	table->ReadConnectionPreferenceL(RecordData2);
	TESTL(RecordData1 == RecordData2);

	iTestStepResult = EPass;
	Log(_L("\t\tSUCCESS"));

	CleanupStack::PopAndDestroy(); 
	return iTestStepResult;
	}



//
//	Test step 057.02
//

//TestUnprotectRecords
CCommDbTest057_02::CCommDbTest057_02()
{
	// store the name of this test case
	iTestStepName = _L("step_057_02");
}

CCommDbTest057_02::~CCommDbTest057_02()
{
	delete iTheDb;
}

TVerdict CCommDbTest057_02::doTestStepPreambleL()
	{	
	iTheDb = CCommsDatabase::NewL(EDatabaseTypeIAP);
	return EPass;
	}

enum TVerdict CCommDbTest057_02::doTestStepL( void )
	{

	Log(_L("Test UnProtect Connection Prefs Table .."));
	iTestStepResult = EPass;

	// unprotect the table and do some checking
	// database is modified
	//
	CCommsDbProtectConnectPrefTableView* table = (CCommsDbProtectConnectPrefTableView *)iTheDb->OpenConnectionPrefTableLC();
	CheckTableIsProtectedL(table);

	TESTL(table->UnprotectTable()==KErrNone);
	
	CheckTableIsNotProtectedL(table);
	
	iTestStepResult = EPass;
	Log(_L("\t\tSUCCESS"));
	CleanupStack::PopAndDestroy(); 
	return iTestStepResult;
	}

