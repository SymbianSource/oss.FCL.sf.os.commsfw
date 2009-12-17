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

#include "step_055_xx.h"

//
//	Test step 055.01
//

//TestProtectTables
CCommDbTest055_01::CCommDbTest055_01()
{
	// store the name of this test case
	iTestStepName = _L("step_055_01");
}

CCommDbTest055_01::~CCommDbTest055_01()
{
	delete iTheDb;
}

TVerdict CCommDbTest055_01::doTestStepPreambleL()
	{	
	iTheDb = CCommsDatabase::NewL(EDatabaseTypeIAP);
	return EPass;
	}

enum TVerdict CCommDbTest055_01::doTestStepL( void )
	{

	Log(_L("Test Normal Table : Protection .."));
	iTestStepResult = EPass;

	CCommsDbProtectTableView* table = (CCommsDbProtectTableView *)iTheDb->OpenTableLC(TPtrC(DIAL_OUT_ISP));
	CheckTableIsNotProtectedL(table);

	TUint32 recordId;
	table->ReadUintL(TPtrC(COMMDB_ID),recordId);
	
	TESTL(table->ProtectTable()==KErrNone);
	TUint32 postProtectRecordId;
	table->ReadUintL(TPtrC(COMMDB_ID),postProtectRecordId);
	TESTL(postProtectRecordId==recordId);
	
	CheckTableIsProtectedL(table);
	iTestStepResult = EPass;
	Log(_L("\t\tSUCCESS"));

	CleanupStack::PopAndDestroy(); 
	return iTestStepResult;
	}


//
//	Test step 055.02
//


//TestUnprotectTables
CCommDbTest055_02::CCommDbTest055_02()
{
	// store the name of this test case
	iTestStepName = _L("step_055_02");
}

CCommDbTest055_02::~CCommDbTest055_02()
{
	delete iTheDb;
}

TVerdict CCommDbTest055_02::doTestStepPreambleL()
	{	
	iTheDb = CCommsDatabase::NewL(EDatabaseTypeIAP);
	return EPass;
	}

//Protect Connection Preference Record
enum TVerdict CCommDbTest055_02::doTestStepL( void )
	{

	Log(_L("Test Normal Table : unprotection .."));
	iTestStepResult = EPass;

	CCommsDbProtectTableView* table = (CCommsDbProtectTableView *)iTheDb->OpenTableLC(TPtrC(DIAL_OUT_ISP));
	CheckTableIsProtectedL(table);

	TUint32 recordId;
	table->ReadUintL(TPtrC(COMMDB_ID),recordId);
	
	TESTL(table->UnprotectTable()==KErrNone);
	TUint32 postProtectRecordId;
	table->ReadUintL(TPtrC(COMMDB_ID),postProtectRecordId);
	TESTL(postProtectRecordId==recordId);
	
	CheckTableIsNotProtectedL(table);
	
	iTestStepResult = EPass;
	Log(_L("\t\tSUCCESS"));

	CleanupStack::PopAndDestroy(); 
	return iTestStepResult;
	}

