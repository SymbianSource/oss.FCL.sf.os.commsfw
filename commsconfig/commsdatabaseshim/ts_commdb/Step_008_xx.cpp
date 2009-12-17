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
// This contains CommDb Unit Test Cases 008.XX
// 
//

// EPOC includes
#include <e32base.h>
#include <commdb.h>


// Test system includes
#include <networking/log.h>
#include <networking/teststep.h>
#include "Teststepcommdb.h"
#include "TestSuiteCommdb.h"
#include "Step_008_xx.h"



//
//	Test step 008.001
//

// constructor
CCommDbTest008_01::CCommDbTest008_01()
	{
	// store the name of this test case
	iTestStepName = _L("step_008_01");

	}

// destructor
CCommDbTest008_01::~CCommDbTest008_01()
	{
	}

TVerdict CCommDbTest008_01::doTestStepPreambleL()
	{	
	openDbAndViewL(TPtrC(DIAL_OUT_ISP));
	return EPass;
	}


TInt CCommDbTest008_01::executeStepL()
	{
	TInt ret=KErrGeneral;
	TUint32 id=0;

	//Try to insert a record
	TRAPD(r, ret = iTheView->InsertRecord( id ) );

	//if we leave, return the leave value
	if ( r!= KErrNone )
		{
		ret = r;
		}
		
	return ret;
	}


TVerdict CCommDbTest008_01::doTestStepL( )
	{
	Log(_L("Step 008.01 called "));

	
	if ( executeStepL() == KErrNone )
		iTestStepResult = EPass;
	else
		iTestStepResult = EFail;


	return iTestStepResult;
	}




//
//	Test step 008.02
//

// constructor
CCommDbTest008_02::CCommDbTest008_02()
	{
	// store the name of this test case
	iTestStepName = _L("step_008_02");
	}

// destructor
CCommDbTest008_02::~CCommDbTest008_02()
	{
	}

TVerdict CCommDbTest008_02::doTestStepL( )
	{
	Log(_L("Step 008.02 called "));

	iTestStepResult = EPass;

	// Heap test for 008.01

	CCommDbTest008_01* step008_01 = new(ELeave) CCommDbTest008_01;
	CleanupStack::PushL(step008_01);
	step008_01->iSuite = iSuite;
	doTestStepWithHeapFailureL( *step008_01, KErrNone);
	if ( step008_01->iTestStepResult == EFail )
		iTestStepResult = EFail;
	CleanupStack::PopAndDestroy(step008_01);

	return iTestStepResult;

	}

//
//	Test step 008.003
//

// constructor
CCommDbTest008_03::CCommDbTest008_03()
	{
	// store the name of this test case
	iTestStepName = _L("step_008_03");

	}

// destructor
CCommDbTest008_03::~CCommDbTest008_03()
	{
	}

TVerdict CCommDbTest008_03::doTestStepPreambleL()
	{	
	openDbAndViewL(TPtrC(DIAL_OUT_ISP));
	return EPass;
	}


TInt CCommDbTest008_03::executeStepL()
	{
	TInt ret=KErrGeneral;
	TUint32 id=0;

	//Position at record to copy
	ret=iTheView->GotoFirstRecord();
	if(ret != KErrNone)
		{return ret;}

	//Try to insert a copy of the first record
	ret = iTheView->InsertCopyRecord(id);

	return ret;
	}

TVerdict CCommDbTest008_03::doTestStepL( )
	{
	Log(_L("Step 008.03 called "));

	
	if ( executeStepL() == KErrNone )
		iTestStepResult = EPass;
	else
		iTestStepResult = EFail;


	return iTestStepResult;
	}

//
//	Test step 008.04
//

// constructor
CCommDbTest008_04::CCommDbTest008_04()
	{
	// store the name of this test case
	iTestStepName = _L("step_008_04");
	}

// destructor
CCommDbTest008_04::~CCommDbTest008_04()
	{
	}

TVerdict CCommDbTest008_04::doTestStepL( )
	{
	Log(_L("Step 008.04 called "));

	iTestStepResult = EPass;

	// Heap test for 008.01

	CCommDbTest008_03* step008_03 = new(ELeave) CCommDbTest008_03;
	CleanupStack::PushL(step008_03);
	step008_03->iSuite = iSuite;
	doTestStepWithHeapFailureL( *step008_03, KErrNone);
	if ( step008_03->iTestStepResult == EFail )
		iTestStepResult = EFail;
	CleanupStack::PopAndDestroy(step008_03);

	return iTestStepResult;

	}
