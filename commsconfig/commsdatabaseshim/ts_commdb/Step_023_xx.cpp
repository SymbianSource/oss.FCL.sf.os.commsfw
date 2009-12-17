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
// This contains CommDb Unit Test Cases 023.XX
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
#include "Step_023_xx.h"


//
//	Test step 023.01
//

// constructor
CCommDbTest023_01::CCommDbTest023_01()
	{
	// store the name of this test case
	iTestStepName = _L("step_023_01");
	}

// destructor
CCommDbTest023_01::~CCommDbTest023_01()
	{
	}


TVerdict CCommDbTest023_01::doTestStepPreambleL()
	{	
	// Have a temp copy of database
	openDbL();
	return EPass;
	}

TInt CCommDbTest023_01::executeStepL()
	{
	TInt ret=KErrGeneral;

	iTheView = iTheDb->OpenViewOnProxyRecordLC(1, TPtrC(DIAL_OUT_ISP) );
	CleanupStack::Pop();
	TUint32 value;

	//Check the view contains the expected records
	CDBLEAVE( iTheView->GotoFirstRecord(), KErrNone);
	iTheView->ReadUintL(TPtrC(PROXY_ISP), value);

	CDBLEAVE( iTheView->GotoNextRecord(), KErrNotFound );

	ret = KErrNone;
	
	return ret;
	}


TVerdict CCommDbTest023_01::doTestStepL( )
	{
	Log(_L("Step 023.01 called "));


	if ( executeStepL() == KErrNone )
		iTestStepResult = EPass;
	else
		iTestStepResult = EFail;

	return iTestStepResult;
	}



//
//	Test step 023.02
//

// constructor
CCommDbTest023_02::CCommDbTest023_02()
	{
	// store the name of this test case
	iTestStepName = _L("step_023_02");
	}

// destructor
CCommDbTest023_02::~CCommDbTest023_02()
	{
	}


TVerdict CCommDbTest023_02::doTestStepPreambleL()
	{	
	openDbL();
	return EPass;
	}

TInt CCommDbTest023_02::executeStepL()
	{
	TInt ret=KErrGeneral;

	iTheView = iTheDb->OpenViewOnProxyRecordLC(99, TPtrC(DIAL_OUT_ISP) );
	CleanupStack::Pop();

	//The view should be empty
	CDBLEAVE( iTheView->GotoFirstRecord(), KErrNotFound);

	ret = KErrNone;
	
	return ret;
	}


TVerdict CCommDbTest023_02::doTestStepL( )
	{
	Log(_L("Step 023.02 called "));


	if ( executeStepL() == KErrNone )
		iTestStepResult = EPass;
	else
		iTestStepResult = EFail;

	return iTestStepResult;
	}


//
//	Test step 023.03
//

// constructor
CCommDbTest023_03::CCommDbTest023_03()
	{
	// store the name of this test case
	iTestStepName = _L("step_023_03");
	}

// destructor
CCommDbTest023_03::~CCommDbTest023_03()
	{
	}


TVerdict CCommDbTest023_03::doTestStepPreambleL()
	{	
	openDbL();
	return EPass;
	}


#define INVALID_TABLE	_L("Invalid")

TInt CCommDbTest023_03::executeStepL()
	{
	TInt ret=KErrGeneral;


	iTheView = iTheDb->OpenViewOnProxyRecordLC(1, TPtrC(INVALID_TABLE) );
	CleanupStack::Pop();
	
	//It should be an empty view
	CDBLEAVE( iTheView->GotoFirstRecord(), KErrNotFound );

	ret = KErrNone;

	return ret;
	}


TVerdict CCommDbTest023_03::doTestStepL( )
	{
	Log(_L("Step 023.03 called "));


	if ( executeStepL() == KErrNone )
		iTestStepResult = EPass;
	else
		iTestStepResult = EFail;

	return iTestStepResult;
	}



//
//	Test step 023.04
//

// constructor
CCommDbTest023_04::CCommDbTest023_04()
	{
	// store the name of this test case
	iTestStepName = _L("step_023_04");
	}

// destructor
CCommDbTest023_04::~CCommDbTest023_04()
	{
	}

TVerdict CCommDbTest023_04::doTestStepL( )
	{
	Log(_L("Step 023.04 called "));

	iTestStepResult = EPass;

		// Heap test for 023.01

	CCommDbTest023_01* step023_01 = new(ELeave) CCommDbTest023_01;
	CleanupStack::PushL(step023_01);
	step023_01->iSuite = iSuite;
	if ( doTestStepWithHeapFailureL( *step023_01, KErrNone) == EFail )
		iTestStepResult = EFail;
	CleanupStack::PopAndDestroy(step023_01);


	return iTestStepResult;	

}


//
//	Test step 023.05
//

// constructor
CCommDbTest023_05::CCommDbTest023_05()
	{
	// store the name of this test case
	iTestStepName = _L("step_023_05");
	}

// destructor
CCommDbTest023_05::~CCommDbTest023_05()
	{
	}

TVerdict CCommDbTest023_05::doTestStepL( )
	{
	Log(_L("Step 023.05 called "));

	iTestStepResult = EPass;
	
			// Heap test for 023.02

	CCommDbTest023_02* step023_02 = new CCommDbTest023_02;
	CleanupStack::PushL(step023_02);
	step023_02->iSuite = iSuite;
	if ( doTestStepWithHeapFailureL( *step023_02, KErrNone) == EFail ) 
		iTestStepResult = EFail;
	CleanupStack::PopAndDestroy(step023_02);
	
	return iTestStepResult;
	}
	
//
//	Test step 023.06
//

// constructor
CCommDbTest023_06::CCommDbTest023_06()
	{
	// store the name of this test case
	iTestStepName = _L("step_023_06");
	}

// destructor
CCommDbTest023_06::~CCommDbTest023_06()
	{
	}

TVerdict CCommDbTest023_06::doTestStepL( )
	{
	Log(_L("Step 023.06 called "));

	iTestStepResult = EPass;
	
		// Heap test for 023.03

	CCommDbTest023_03* step023_03 = new CCommDbTest023_03;
	CleanupStack::PushL(step023_03);
	step023_03->iSuite = iSuite;
	if ( doTestStepWithHeapFailureL( *step023_03, KErrNone) == EFail )
		iTestStepResult = EFail;
	CleanupStack::PopAndDestroy(step023_03);
	
	return iTestStepResult;
	}

//EOF
