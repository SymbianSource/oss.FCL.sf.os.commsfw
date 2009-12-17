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
// This contains CommDb Unit Test Cases 010.XX
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
#include "Step_010_xx.h"



//
//	Test step 010.001
//

// constructor
CCommDbTest010_01::CCommDbTest010_01()
	{
	// store the name of this test case
	iTestStepName = _L("step_010_01");
	}

// destructor
CCommDbTest010_01::~CCommDbTest010_01()
	{
	}

TVerdict CCommDbTest010_01::doTestStepPreambleL()
	{	
	openDbAndViewL(TPtrC(DIAL_OUT_ISP));
	return EPass;
	}


TInt CCommDbTest010_01::executeStepL()
	{
	TInt ret=KErrGeneral;


	//This test must be executed on a populated table
	CDBLEAVE( ret = iTheView->GotoFirstRecord(), KErrNone );


	//Move through the records in the table until the last record is reached
	while( ret == KErrNone )
		{
		TRAPD(r, ret = iTheView->GotoNextRecord() );
		if ( r!= KErrNone )
			User::Leave(r);
		}


	
	return ret;
	}


TVerdict CCommDbTest010_01::doTestStepL( )
	{
	Log(_L("Step 010.01 called "));


	if ( executeStepL() == KErrNotFound )
		iTestStepResult = EPass;
	else
		iTestStepResult = EFail;


	return iTestStepResult;
	}




//
//	Test step 010.02
//

// constructor
CCommDbTest010_02::CCommDbTest010_02()
	{
	// store the name of this test case
	iTestStepName = _L("step_010_02");
	}

// destructor
CCommDbTest010_02::~CCommDbTest010_02()
	{
	}

TVerdict CCommDbTest010_02::doTestStepPreambleL()
	{	
	openDbAndViewL(TPtrC(DIAL_OUT_ISP));
	return EPass;
	}

TInt CCommDbTest010_02::executeStepL()
	{
	TInt ret=KErrGeneral;

	//Move through the records in the table from the last to the first

	CDBLEAVE ( ret = iTheView->GotoFirstRecord(), KErrNone);

	while( ret == KErrNone )
		{
		TRAPD(r, ret = iTheView->GotoNextRecord() );
		if ( r!= KErrNone )
			User::Leave(r);
		}
	//We should be at the end of the records in this table,
	//and ret == KErrNotFound

	CDBLEAVE( ret, KErrNotFound  );

	//Now move back to the first record 
	CDBLEAVE ( ret = iTheView->GotoPreviousRecord(), KErrNone);

	while( ret == KErrNone )
		{
		TRAPD(r, ret = iTheView->GotoPreviousRecord() );
		if ( r!=KErrNone )
			User::Leave(r);
		}


	return ret;
	}


TVerdict CCommDbTest010_02::doTestStepL( )
	{
	Log(_L("Step 010.02 called "));

	
	if ( executeStepL() == KErrNotFound )
		iTestStepResult = EPass;
	else
		iTestStepResult = EFail;


	return iTestStepResult;
	}


//
//	Test step 010.03
//

// constructor
CCommDbTest010_03::CCommDbTest010_03()
	{
	// store the name of this test case
	iTestStepName = _L("step_010_03");
	}

// destructor
CCommDbTest010_03::~CCommDbTest010_03()
	{
	}

TVerdict CCommDbTest010_03::doTestStepPreambleL()
	{	
	openDbAndViewL(TPtrC(DIAL_OUT_ISP));
	return EPass;
	}


TInt CCommDbTest010_03::executeStepL()
	{
	TInt ret=KErrGeneral;

	//The view must contain zero records

	TRAPD(r, ret = iTheView->GotoFirstRecord() );
	if( r!=KErrNone )
		ret =r;

	return ret;
	}


TVerdict CCommDbTest010_03::doTestStepL( )
	{
	Log(_L("Step 010.03 called "));

	
	if ( executeStepL() == KErrNotFound )
		iTestStepResult = EPass;
	else
		iTestStepResult = EFail;


	return iTestStepResult;
	}



//
//	Test step 010.04
//

// constructor
CCommDbTest010_04::CCommDbTest010_04()
	{
	// store the name of this test case
	iTestStepName = _L("step_010_04");
	}

// destructor
CCommDbTest010_04::~CCommDbTest010_04()
	{
	}


TVerdict CCommDbTest010_04::doTestStepPreambleL()
	{	
	openDbAndViewL(TPtrC(DIAL_OUT_ISP));
	return EPass;
	}

TInt CCommDbTest010_04::executeStepL()
	{
	TInt ret=KErrGeneral;

	//The view must contain zero records

	TRAPD( r, ret = iTheView->GotoNextRecord() );

	if ( r!= KErrNone )
		ret = r;


	return ret;
	}


TVerdict CCommDbTest010_04::doTestStepL( )
	{
	Log(_L("Step 010.04 called "));

	
	if ( executeStepL() == KErrNotFound )
		iTestStepResult = EPass;
	else
		iTestStepResult = EFail;


	return iTestStepResult;
	}



//
//	Test step 010.05
//

// constructor
CCommDbTest010_05::CCommDbTest010_05()
	{
	// store the name of this test case
	iTestStepName = _L("step_010_05");
	}

// destructor
CCommDbTest010_05::~CCommDbTest010_05()
	{
	}


TVerdict CCommDbTest010_05::doTestStepL( )
	{
	Log(_L("Step 010.05 called "));

	iTestStepResult = EPass;

	// Heap test for 010.01

	CCommDbTest010_01* step010_01 = new CCommDbTest010_01;
	CleanupStack::PushL(step010_01);
	step010_01->iSuite = iSuite;				
	if ( doTestStepWithHeapFailureL( *step010_01, KErrNotFound) == EFail )
		iTestStepResult = EFail;
	CleanupStack::PopAndDestroy(step010_01);

	//Heap test for 010.02

	CCommDbTest010_02* step010_02 = new CCommDbTest010_02;
	CleanupStack::PushL(step010_02);
	step010_02->iSuite = iSuite;				
	if ( doTestStepWithHeapFailureL( *step010_02, KErrNotFound) == EFail )
		iTestStepResult = EFail;
	CleanupStack::PopAndDestroy(step010_02);

	//Heap test for 010.03

	CCommDbTest010_03* step010_03 = new CCommDbTest010_03;
	CleanupStack::PushL(step010_03);
	step010_03->iSuite = iSuite;				
	if ( doTestStepWithHeapFailureL( *step010_03, KErrNotFound) == EFail )
		iTestStepResult = EFail;
	CleanupStack::PopAndDestroy(step010_03);

	//Heap test for 010.04

	CCommDbTest010_04* step010_04 = new CCommDbTest010_04;
	CleanupStack::PushL(step010_04);
	step010_04->iSuite = iSuite;				
	if ( doTestStepWithHeapFailureL( *step010_04, KErrNotFound) == EFail )
		iTestStepResult = EFail;
	CleanupStack::PopAndDestroy(step010_04);



	return iTestStepResult;	
}
