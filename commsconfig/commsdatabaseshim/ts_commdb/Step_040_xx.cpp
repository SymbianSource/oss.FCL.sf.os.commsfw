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
// This contains CommDb Unit Test Cases 040.XX
// 
//

// EPOC includes
#include <e32base.h>
#include <commdb.h>
#include <d32comm.h>

// Test system includes
#include <networking/log.h>
#include <networking/teststep.h>
#include "Teststepcommdb.h"
#include "TestSuiteCommdb.h"
#include "Step_040_xx.h"


CCommDbTest040_01::CCommDbTest040_01()
	{
	// store the name of this test case
	iTestStepName = _L("step_040_01");
	}

CCommDbTest040_01::~CCommDbTest040_01()
	{}

TVerdict CCommDbTest040_01::doTestStepL( void )
	{
	executeStepL();
	return EPass;	//If we've got this far we've passed
	}

TVerdict CCommDbTest040_01::doTestStepPreambleL()
	{
	return EPass;
	}

TInt CCommDbTest040_01::executeStepL()
	{
	iOverSet=CCommDbOverrideSettings::NewL(CCommDbOverrideSettings::EParamListPartial);
	return KErrNone;
	}
	
TVerdict CCommDbTest040_01::doTestStepPostambleL()
	{
	delete iOverSet;
	return EPass;
	}

//

CCommDbTest040_02::CCommDbTest040_02()
	{
	// store the name of this test case
	iTestStepName = _L("step_040_02");
	}

CCommDbTest040_02::~CCommDbTest040_02()
	{}

TVerdict CCommDbTest040_02::doTestStepL( void )
	{
	executeStepL();
	return EPass;	//If we've got this far we've passed
	}

TVerdict CCommDbTest040_02::doTestStepPreambleL()
	{
	return EPass;
	}

TInt CCommDbTest040_02::executeStepL()
	{
	iOverSet=CCommDbOverrideSettings::NewL(CCommDbOverrideSettings::EParamListFull);
	return KErrNone;
	}
	
TVerdict CCommDbTest040_02::doTestStepPostambleL()
	{
	delete iOverSet;
	return EPass;
	}

//

CCommDbTest040_03::CCommDbTest040_03()
	{
	// store the name of this test case
	iTestStepName = _L("step_040_03");
	}

CCommDbTest040_03::~CCommDbTest040_03()
	{}

TVerdict CCommDbTest040_03::doTestStepL( void )
	{
	Log(_L("Step 040.03 called "));

	iTestStepResult = EPass;

	CCommDbTest040_01* step040_01 = new(ELeave) CCommDbTest040_01;
	CleanupStack::PushL(step040_01);
	step040_01->iSuite = iSuite;
	doTestStepWithHeapFailureL( *step040_01, KErrNone);
	CleanupStack::PopAndDestroy(step040_01);

	CCommDbTest040_02* step040_02 = new(ELeave) CCommDbTest040_02;
	CleanupStack::PushL(step040_02);
	step040_02->iSuite = iSuite;
	doTestStepWithHeapFailureL( *step040_02, KErrNone);
	CleanupStack::PopAndDestroy(step040_02);
	
	return iTestStepResult;
	}
