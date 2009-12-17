// Copyright (c) 2001-2009 Nokia Corporation and/or its subsidiary(-ies).
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
// This contains CommDb Unit Test Cases 035.XX
// 
//

// EPOC includes
#include <e32base.h>
#include <commdb.h>
#include <d32comm.h>
#include <cdbtemp.h>

// Test system includes
#include <networking/log.h>
#include <networking/teststep.h>
#include "Teststepcommdb.h"
#include "TestSuiteCommdb.h"
#include "Step_035_xx.h"


CCommDbTest035_01::CCommDbTest035_01()
	{
	// store the name of this test case
	iTestStepName = _L("step_035_01");
	}

CCommDbTest035_01::~CCommDbTest035_01()
	{}

TVerdict CCommDbTest035_01::doTestStepL( void )
	{
	executeStepL();
	return EPass;	//If we've got this far we've passed
	}

TVerdict CCommDbTest035_01::doTestStepPreambleL()
	{
	iTheDb=CCommsDatabase::NewL();

	return EPass;
	}

TInt CCommDbTest035_01::executeStepL()
	{
	CCommsDbTemplateRecord* templateRecord = CCommsDbTemplateRecord::NewL(iTheDb, TPtrC(DIAL_IN_ISP));
	delete templateRecord;
	return KErrNone;
	}
	
TVerdict CCommDbTest035_01::doTestStepPostambleL()
	{
	delete iTheDb;
	iTheDb=NULL;
	return EPass;
	}

//

CCommDbTest035_02::CCommDbTest035_02()
	{
	// store the name of this test case
	iTestStepName = _L("step_035_02");
	}

CCommDbTest035_02::~CCommDbTest035_02()
	{}

TVerdict CCommDbTest035_02::doTestStepL( void )
	{
	if(executeStepL()!=KErrNotSupported)
		return EFail;
	return EPass;
	}

TVerdict CCommDbTest035_02::doTestStepPreambleL()
	{
	iTheDb=CCommsDatabase::NewL();

	return EPass;
	}

TInt CCommDbTest035_02::executeStepL()
	{
	CCommsDbTemplateRecord* templateRecord=NULL;
	//CCommsDbTemplateRecord::NewL should leave with KErrNotSupported, since IAP table doesn't support templates
	TRAPD(err, templateRecord = CCommsDbTemplateRecord::NewL(iTheDb, TPtrC(IAP)));
	delete templateRecord;
	return err;
	}
	
TVerdict CCommDbTest035_02::doTestStepPostambleL()
	{
	delete iTheDb;
	iTheDb=NULL;
	return EPass;
	}

//

CCommDbTest035_03::CCommDbTest035_03()
	{
	// store the name of this test case
	iTestStepName = _L("step_035_03");
	}

CCommDbTest035_03::~CCommDbTest035_03()
	{}

TVerdict CCommDbTest035_03::doTestStepL( void )
	{
	if(executeStepL()!=KErrArgument)
		return EFail;
	return EPass;
	}

TVerdict CCommDbTest035_03::doTestStepPreambleL()
	{
	iTheDb=CCommsDatabase::NewL();

	return EPass;
	}

TInt CCommDbTest035_03::executeStepL()
	{
	CCommsDbTemplateRecord* templateRecord=NULL;
	//CCommsDbTemplateRecord::NewL should leave with KErrArgument for invalid name
	TRAPD(err, templateRecord = CCommsDbTemplateRecord::NewL(iTheDb, _L("Hi there")));
	delete templateRecord;
	return err;
	}
	
TVerdict CCommDbTest035_03::doTestStepPostambleL()
	{
	delete iTheDb;
	iTheDb=NULL;
	return EPass;
	}

//

CCommDbTest035_04::CCommDbTest035_04()
	{
	// store the name of this test case
	iTestStepName = _L("step_035_04");
	}

CCommDbTest035_04::~CCommDbTest035_04()
	{}

TVerdict CCommDbTest035_04::doTestStepL( void )
	{
	Log(_L("Step 035.04 called "));

	iTestStepResult = EPass;

	CCommDbTest035_01* step035_01 = new(ELeave) CCommDbTest035_01;
	CleanupStack::PushL(step035_01);
	step035_01->iSuite = iSuite;
	doTestStepWithHeapFailureL( *step035_01, KErrNone);
	CleanupStack::PopAndDestroy(step035_01);

	CCommDbTest035_02* step035_02 = new(ELeave) CCommDbTest035_02;
	CleanupStack::PushL(step035_02);
	step035_02->iSuite = iSuite;
	doTestStepWithHeapFailureL( *step035_02, KErrNotSupported);
	CleanupStack::PopAndDestroy(step035_02);

	CCommDbTest035_03* step035_03 = new(ELeave) CCommDbTest035_03;
	CleanupStack::PushL(step035_03);
	step035_03->iSuite = iSuite;
	doTestStepWithHeapFailureL( *step035_03, KErrArgument);
	CleanupStack::PopAndDestroy(step035_03);
	
	return iTestStepResult;
	}
