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

#include "step_053_xx.h"

//
//	Test step 053.01
//

CCommDbTest053_01::CCommDbTest053_01()
{
	// store the name of this test case
	iTestStepName = _L("step_053_01");
}

CCommDbTest053_01::~CCommDbTest053_01()
{
	delete iTheDb;
}

TVerdict CCommDbTest053_01::doTestStepPreambleL()
	{	
	iTheDb = CCommsDatabase::NewL(EDatabaseTypeIAP);
	return EPass;
	}

//Protect Connection Preference Table
enum TVerdict CCommDbTest053_01::doTestStepL( void )
	{

	Log(_L("Connection Preference Table : Protection .."));
	iTestStepResult = EPass;

	CCommsDbProtectConnectPrefTableView* table = (CCommsDbProtectConnectPrefTableView *)iTheDb->OpenConnectionPrefTableLC();

	if(table->GotoFirstRecord()==KErrNone)
		{
		TESTL(table->ProtectTable()==0);
		iTestStepResult = EPass;
		Log(_L("\t\tSUCCESS"));
		}
	else
		{
		iTestStepResult = EFail;
		Log(_L("\t\tFAIL"));
		}
	CleanupStack::PopAndDestroy(); 
	return iTestStepResult;
	}


//
//	Test step 053.02
//

CCommDbTest053_02::CCommDbTest053_02()
{
	// store the name of this test case
	iTestStepName = _L("step_053_02");
}

CCommDbTest053_02::~CCommDbTest053_02()
{
	delete iTheDb;
}

TVerdict CCommDbTest053_02::doTestStepPreambleL()
	{	
	iTheDb = CCommsDatabase::NewL(EDatabaseTypeIAP);
	return EPass;
	}

//UnProtect Connection pref Record
enum TVerdict CCommDbTest053_02::doTestStepL( void )
	{

	Log(_L("Connection Preference Table : Unprotection .."));
	iTestStepResult = EPass;

	CCommsDbProtectConnectPrefTableView* table = (CCommsDbProtectConnectPrefTableView *)iTheDb->OpenConnectionPrefTableLC();

	if(table->GotoFirstRecord()==KErrNone)
		{
		TESTL(table->UnprotectTable()==KErrNone);
		iTestStepResult = EPass;
		Log(_L("\t\tSUCCESS"));
		}
	else
		{
		iTestStepResult = EFail;
		Log(_L("\t\tFAIL"));
		}
	CleanupStack::PopAndDestroy(); 
	return iTestStepResult;
	}

