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
// This contains CommDb Unit Test Cases 004.01 - 004.04
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
#include "step_004_xx.h"




//
//	Test step 004.001
//

// constructor
CCommDbTest004_01::CCommDbTest004_01()
	{
	// store the name of this test case
	iTestStepName = _L("step_004_01");
	}

// destructor
CCommDbTest004_01::~CCommDbTest004_01()
	{
	}

TVerdict CCommDbTest004_01::doTestStepPreambleL()
	{	
	openDbAndViewL(TPtrC(DIAL_OUT_ISP));
	return EPass;
	}

TInt CCommDbTest004_01::executeStepL()
	{
	TInt ret = KErrGeneral;

	TBuf<KCommsDbSvrMaxColumnNameLength> tableName;

	// Get the table name and check it matches with the known value
	iTheView->GetTableName( tableName );
	if ( tableName.Compare( TPtrC(DIAL_OUT_ISP)) == 0 )
		ret = KErrNone;

	return ret;
	}

TVerdict CCommDbTest004_01::doTestStepL( )
	{
	Log(_L("Step 004.01 called "));


	if ( executeStep()== KErrNone )
		{
		iTestStepResult = EPass;	
		}
	else
		{
		iTestStepResult = EFail;
		}


	return iTestStepResult;
	}


//
//	Test step 004.002
//

// constructor
CCommDbTest004_02::CCommDbTest004_02()
	{
	// store the name of this test case
	iTestStepName = _L("step_004_02");
	}

// destructor
CCommDbTest004_02::~CCommDbTest004_02( )
	{
	}

TVerdict CCommDbTest004_02::doTestStepPreambleL()
	{	
	openDbAndViewL(TPtrC(DIAL_OUT_ISP));
	return EPass;
	}


#define BUFFER_TOO_SMALL	5	//Must be smaller than the length of the DAIL_OUT_ISP table name

TBool CCommDbTest004_02::executeStepL()
	{
	TBuf<BUFFER_TOO_SMALL> tableName;

	//NB. This should cause a Panic!

	iTheView->GetTableName( tableName );

	if ( tableName.Compare( TPtrC(DIAL_OUT_ISP)) == 0 )
		{
		iTestStepResult = EPass;	
		}
	else
		{
		iTestStepResult = EFail;
		}

	return EFail;
	}


TVerdict CCommDbTest004_02::doTestStepL( )
	{
	if  ( executeStep() )
		iTestStepResult = EPass;
	else
		iTestStepResult = EFail;

		
	return iTestStepResult;
	}


//
//	Test step 004.003
//

// constructor
CCommDbTest004_03::CCommDbTest004_03()
	{
	// store the name of this test case
	iTestStepName = _L("step_004_03");
	}

// destructor
CCommDbTest004_03::~CCommDbTest004_03()
	{
	}

TVerdict CCommDbTest004_03::doTestStepPreambleL()
	{	
	copyTestDatabase( EDatabase_1 );
	openDbAndViewL(TPtrC(DIAL_OUT_ISP));
	return EPass;
	}

//NB. If a zero size buffer is used this will cause an ARM compiler error
#define BUFFER_VERYSMALL	1

TBool CCommDbTest004_03::executeStepL()
	{
	
	TBuf<BUFFER_VERYSMALL> tableName;

	//NB. This should cause a Panic
	
	iTheView->GetTableName( tableName );

	if ( tableName.Compare( TPtrC(DIAL_OUT_ISP)) == 0 )
		{
		iTestStepResult = EPass;	
		}
	else
		{
		iTestStepResult = EFail;
		}

	return EFail;
	}

TVerdict CCommDbTest004_03::doTestStepL( )
	{
	
	if ( executeStep() )
		{
		iTestStepResult = EPass;	
		}
	else
		{
		iTestStepResult = EFail;
		}

	
	return iTestStepResult;
	}



//
//	Test step 004.004
//

// constructor
CCommDbTest004_04::CCommDbTest004_04()
	{
	// store the name of this test case
	iTestStepName = _L("step_004_04");
	}

// destructor
CCommDbTest004_04::~CCommDbTest004_04()
	{
	}


TVerdict CCommDbTest004_04::doTestStepL( )
	{
	Log(_L("Step 004.04 called "));
	
	iTestStepResult = EPass;

	//Heap test for 004.01

	CCommDbTest004_01* step004_01 = new CCommDbTest004_01;
	CleanupStack::PushL(step004_01);
	step004_01->iSuite = iSuite;				
	doTestStepWithHeapFailureL( *step004_01, KErrNone);
	if( step004_01->iTestStepResult == EFail )
		iTestStepResult = EFail;
	CleanupStack::PopAndDestroy(step004_01);
	
	return iTestStepResult;
	}
	
//
//	Test step 004.005
//

// constructor
CCommDbTest004_05::CCommDbTest004_05()
	{
	// store the name of this test case
	iTestStepName = _L("step_004_05");
	}

// destructor
CCommDbTest004_05::~CCommDbTest004_05()
	{
	}


TVerdict CCommDbTest004_05::doTestStepL( )
	{
	
	iTestStepResult = EPass;	
	
	//Heap test for 004.02
//	    a panic is expected
	CCommDbTest004_02* step004_02 = new CCommDbTest004_02;
	CleanupStack::PushL(step004_02);
	step004_02->iSuite = iSuite;				
	doTestStepWithHeapFailureL( *step004_02, KErrNone);
	if( step004_02->iTestStepResult == EFail )
		iTestStepResult = EFail;
	CleanupStack::PopAndDestroy(step004_02);

	return iTestStepResult;
	}

	
//
//	Test step 004.006
//

// constructor
CCommDbTest004_06::CCommDbTest004_06()
	{
	// store the name of this test case
	iTestStepName = _L("step_004_06");
	}

// destructor
CCommDbTest004_06::~CCommDbTest004_06()
	{
	}


TVerdict CCommDbTest004_06::doTestStepL( )
	{
	
	iTestStepResult = EPass;	
	//Heap test for 004.03

	// a panic is expected
	CCommDbTest004_03* step004_03 = new CCommDbTest004_03;
	CleanupStack::PushL(step004_03);
	step004_03->iSuite = iSuite;				
	doTestStepWithHeapFailureL( *step004_03, KErrNone);
	if( step004_03->iTestStepResult == EFail )
		iTestStepResult = EFail;
	CleanupStack::PopAndDestroy(step004_03);

	return iTestStepResult;
	}
