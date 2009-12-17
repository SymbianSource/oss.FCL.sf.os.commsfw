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

#include "step_052_xx.h"


//
//	Test step 052.01
//


CCommDbTest052_01::CCommDbTest052_01()
{
	// store the name of this test case
	iTestStepName = _L("step_052_01");
}

CCommDbTest052_01::~CCommDbTest052_01()
{
	delete iTheDb;
}

TVerdict CCommDbTest052_01::doTestStepPreambleL()
	{	
	iTheDb = CCommsDatabase::NewL(EDatabaseTypeIAP);
	return EPass;
	}

//Protect normal Record
enum TVerdict CCommDbTest052_01::doTestStepL( void )
	{

	Log(_L("Normal Record : Protection .."));
	iTestStepResult = EPass;

	// Test using dial out isp table as running t_createdb places several records
	// in the table as opposed to just one as in some tables
	CCommsDbProtectTableView* table = (CCommsDbProtectTableView *)iTheDb->OpenTableLC(TPtrC(DIAL_OUT_ISP));
	TESTL(iTheDb->BeginTransaction()==KErrNone);
	
	if(table->GotoFirstRecord()==KErrNone)
		{
		// Protect the first record
		ProtectRecordL(table,KErrNone);
		iTestStepResult = EPass;
		Log(_L("\t\tSUCCESS"));
		}
	else
		{
		iTestStepResult = EFail;
		Log(_L("\t\tFAIL"));
		}

	TESTL(iTheDb->CommitTransaction()==KErrNone);
	CleanupStack::PopAndDestroy(); 
	return iTestStepResult;
	}


//
//	Test step 052.02
//

CCommDbTest052_02::CCommDbTest052_02()
{
	// store the name of this test case
	iTestStepName = _L("step_052_02");
}

CCommDbTest052_02::~CCommDbTest052_02()
{
	delete iTheDb;
}

TVerdict CCommDbTest052_02::doTestStepPreambleL()
	{	
	iTheDb = CCommsDatabase::NewL(EDatabaseTypeIAP);
	return EPass;
	}


//UnProtect normal Record
enum TVerdict CCommDbTest052_02::doTestStepL( void )
	{

	Log(_L("Normal Record : Unprotection .."));
	iTestStepResult = EPass;

	CCommsDbProtectTableView* table = (CCommsDbProtectTableView *)iTheDb->OpenTableLC(TPtrC(DIAL_OUT_ISP));
	TESTL(iTheDb->BeginTransaction()==KErrNone);

	if(table->GotoFirstRecord()==KErrNone)
		{
		// UnProtect the first record
		UnprotectRecordL(table,KErrNone);
		iTestStepResult = EPass;
		Log(_L("\t\tSUCCESS"));
		}
	else
		{
		iTestStepResult = EFail;
		Log(_L("\t\tFAIL"));
		}

	TESTL(iTheDb->CommitTransaction()==KErrNone);
	CleanupStack::PopAndDestroy(); //table
	return iTestStepResult;

	}
