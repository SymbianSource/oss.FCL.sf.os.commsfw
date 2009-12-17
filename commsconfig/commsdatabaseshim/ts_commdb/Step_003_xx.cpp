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
// This contains CommDb Unit Test Cases 003.01 - 003.07
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
#include "Step_003_xx.h"




//
//	Test step 003.001
//

// constructor
CCommDbTest003_01::CCommDbTest003_01()
	{
	// store the name of this test case
	iTestStepName = _L("step_003_01");
	}

// destructor
CCommDbTest003_01::~CCommDbTest003_01()
 	{
	}


TVerdict CCommDbTest003_01::doTestStepPreambleL()
	{	
	openDbL();
	return EPass;
	}

TInt CCommDbTest003_01::myOpenTableL()
	{
	
	// Because OpenTableLC puts an object on the cleanup stack, 
	// we cant use TRAP() on it as this causes a Panic during the 
	// UnTrap cleanup, so we write our own leaving wrapper function.
	iTheView=iTheDb->OpenTableLC(TPtrC(DIAL_OUT_ISP));
	CleanupStack::Pop();

	//if this test does not trap, it can only ever return KErrNone
	return KErrNone;

	}

TInt CCommDbTest003_01::executeStepL()
	{	
	TInt ret=KErrNone;

	TRAPD(r,  ret = myOpenTableL() );
	
	if ( r==KErrNone )
		{
		//if there were no traps, return the value call to the api
		r=ret;
		}

	return r;
	}

	
TVerdict CCommDbTest003_01::doTestStepL( )
	{
	
	Log(_L("Step 003.01 called "));

	if ( executeStepL() == KErrNone  )
		iTestStepResult = EPass;
	else
		iTestStepResult = EFail;
	
	
	return iTestStepResult;
	}



//
//	Test step 003.002
//

// constructor
CCommDbTest003_02::CCommDbTest003_02()
	{
	// store the name of this test case
	iTestStepName = _L("step_003_02");
	}

// destructor
CCommDbTest003_02::~CCommDbTest003_02()
	{
	}


TVerdict CCommDbTest003_02::doTestStepPreambleL()
	{	
	openDbL();
	return EPass;
	}

#define INVALID_TABLE_NAME	_S("Inval")


TInt CCommDbTest003_02::myOpenTableL()
	{
	
	// Because OpenTableLC puts an object on the cleanup stack, 
	// we cant use TRAP() on it as this causes a Panic during the 
	// UnTrap cleanup, so we write our own leaving wrapper function.
	iTheView=iTheDb->OpenTableLC(TPtrC(INVALID_TABLE_NAME));
	CleanupStack::Pop();

	//This test should trap, if it gets here then something has gone wrong 
	return KErrGeneral;

	}


TInt CCommDbTest003_02::executeStepL()
	{	
	TInt ret=KErrNone;

	TRAPD(r,  ret = myOpenTableL() );
	
	if ( r==KErrNone )
		{
		//if there were no traps, return the value call to the api
		r=ret;
		}

	return r;
	}



TVerdict CCommDbTest003_02::doTestStepL( )
	{
	Log(_L("Step 003.02 called "));
	

	//Test for the expected return value
	if ( executeStepL() == KErrNotFound  )
		iTestStepResult = EPass;
	else
		iTestStepResult = EFail;

	
	return iTestStepResult;
	}



//
//	Test step 003.003
//

// constructor
CCommDbTest003_03::CCommDbTest003_03()
	{
	// store the name of this test case
	iTestStepName = _L("step_003_03");
	}

// destructor
CCommDbTest003_03::~CCommDbTest003_03()
	{
	}


TVerdict CCommDbTest003_03::doTestStepPreambleL()
	{	
	openDbL();
	return EPass;
	}

#define ZERO_LENGTH_TABLE_NAME	_S("")

TInt CCommDbTest003_03::myOpenTableL()
	{
	
	// Because OpenTableLC puts an object on the cleanup stack, 
	// we cant use TRAP() on it as this causes a Panic during the 
	// UnTrap cleanup, so we write our own leaving wrapper function.

	iTheView = iTheDb->OpenTableLC(TPtrC(ZERO_LENGTH_TABLE_NAME));
	CleanupStack::Pop();

	//This test should trap, if we get here something has gone wrong
	return KErrGeneral; 
	}


TInt CCommDbTest003_03::executeStepL()
	{
	TInt ret=KErrNone;

	TRAPD(r,  ret = myOpenTableL() );
	
	if ( r==KErrNone )
		{
		//if there were no traps, return the value call to the api
		r=ret;
		}

	return r;
	}


TVerdict CCommDbTest003_03::doTestStepL( )
	{
	Log(_L("Step 003.03 called "));
	

	//Test for the expected return value
	if ( executeStepL() == KErrArgument )
		iTestStepResult = EPass;
	else
		iTestStepResult = EFail;


	return iTestStepResult;
	}

//
//	Test step 003.04
//

// constructor
CCommDbTest003_04::CCommDbTest003_04()
	{
	// store the name of this test case
	iTestStepName = _L("step_003_04");
	}

// destructor
CCommDbTest003_04::~CCommDbTest003_04()
	{
	}

TVerdict CCommDbTest003_04::doTestStepPreambleL()
	{
	openDbL();
	return EPass;
	}

#define LONG_TABLE_NAME	_S("aVeryVeryLongTableNameThatIsLongerThanFiftyCharacters")


TInt CCommDbTest003_04::myOpenTableL()
	{
	
	// Because OpenTableLC puts an object on the cleanup stack, 
	// we cant use TRAP() on it as this causes a Panic during the 
	// UnTrap cleanup, so we write our own leaving wrapper function.
	iTheView=iTheDb->OpenTableLC(TPtrC(LONG_TABLE_NAME));
	CleanupStack::Pop();

	//This test will cause a PANIC, so we will never get here
	return KErrGeneral;
	}


TInt CCommDbTest003_04::executeStepL()
	{
	TInt ret=KErrNone;

	TRAPD(r, myOpenTableL() );
	
	if ( r==KErrNone )
		{
		//if there were no traps, return the value call to the api
		r=ret;
		}

	return r;
}


TVerdict CCommDbTest003_04::doTestStepL( )
	{

	User::SetJustInTime(EFalse);

	if ( executeStepL() == KErrArgument )
		iTestStepResult = EPass;
	else
		iTestStepResult = EFail;
	
	return iTestStepResult;
	}
//
//	Test step 003.05
//

// constructor
CCommDbTest003_05::CCommDbTest003_05()
	{
	// store the name of this test case
	iTestStepName = _L("step_003_05");
	}

// destructor
CCommDbTest003_05::~CCommDbTest003_05()
	{
	}


TVerdict CCommDbTest003_05::doTestStepPreambleL()
	{	
	openDbL();
	return EPass;
	}

//The CONNECTION_PREFERENCES table isn't really a public table,
//but someone still could try to open it.
#define CONNECTION_PREFERENCES		_S("ConnectionPreferences")

TInt CCommDbTest003_05::myOpenTableL()
	{
	
	// Because OpenTableLC puts an object on the cleanup stack, 
	// we cant use TRAP() on it as this causes a Panic during the 
	// UnTrap cleanup, so we write our own leaving wrapper function.
	iTheView=iTheDb->OpenTableLC(TPtrC( CONNECTION_PREFERENCES ));
	CleanupStack::Pop();

	//This test should leave, so we will never reach here
	return KErrGeneral;
	}

TInt CCommDbTest003_05::executeStepL()
{
	TInt ret=KErrNone;

	TRAPD(r,  ret = myOpenTableL() );
	
	if ( r==KErrNone )
		{
		//if there were no traps, return the value call to the api
		r=ret;
		}

	return r;
}
	


TVerdict CCommDbTest003_05::doTestStepL( )
	{
	Log(_L("Step 003.05 called "));
	

	if ( executeStepL() == KErrAccessDenied )
		iTestStepResult = EPass;
	else
		iTestStepResult = EFail;
	
	return iTestStepResult;
	}

//
//	Test step 003.006
//

// constructor
CCommDbTest003_06::CCommDbTest003_06()
	{
	// store the name of this test case
	iTestStepName = _L("step_003_06");
	}

// destructor
CCommDbTest003_06::~CCommDbTest003_06()
	{
	}


TVerdict CCommDbTest003_06::doTestStepPreambleL()
	{	
	openDbL();
	return EPass;
	}

#define GLOBAL_SETTINGS				_S("GlobalSettings")

TInt CCommDbTest003_06::myOpenTableL()
	{
	
	// Because OpenTableLC puts an object on the cleanup stack, 
	// we cant use TRAP() on it as this causes a Panic during the 
	// UnTrap cleanup, so we write our own leaving wrapper function.
	iTheView=iTheDb->OpenTableLC(TPtrC( GLOBAL_SETTINGS ));
	CleanupStack::Pop();

	//This test should leave, so we will never reach here
	return KErrGeneral;
	}

TInt CCommDbTest003_06::executeStepL()
{
	TInt ret=KErrNone;


	TRAPD(r,  ret = myOpenTableL() );
	
	if ( r==KErrNone )
		{
		//if there were no traps, return the value call to the api
		r=ret;
		}

	return r;
}
	

TVerdict CCommDbTest003_06::doTestStepL( )
	{
	Log(_L("Step 003.06 called "));
	

	if ( executeStepL() == KErrNotFound )
		iTestStepResult = EPass;
	else
		iTestStepResult = EFail;
	
	return iTestStepResult;
	}

//
//	Test step 003.07
//

// constructor
CCommDbTest003_07::CCommDbTest003_07()
	{
	// store the name of this test case
	iTestStepName = _L("step_003_07");
	}

// destructor
CCommDbTest003_07::~CCommDbTest003_07()
	{
	}

TVerdict CCommDbTest003_07::doTestStepL( )
	{
	Log(_L("Step 003.07 called "));

	iTestStepResult = EPass;

	//Heap test for 003.01

	CCommDbTest003_01* step003_01 = new CCommDbTest003_01;
	CleanupStack::PushL(step003_01);
	step003_01->iSuite = iSuite;				
	doTestStepWithHeapFailureL( *step003_01, KErrNone);
	if( step003_01->iTestStepResult == EFail )
		iTestStepResult = EFail;
	CleanupStack::PopAndDestroy(step003_01);
		

	//Heap test for 003.02

	CCommDbTest003_02* step003_02 = new CCommDbTest003_02;
	CleanupStack::PushL(step003_02);
	step003_02->iSuite = iSuite;				
	doTestStepWithHeapFailureL( *step003_02, KErrNotFound);
	if( step003_02->iTestStepResult == EFail )
		iTestStepResult = EFail;
	CleanupStack::PopAndDestroy(step003_02);
		

	//Heap test for 003.03

	CCommDbTest003_03* step003_03 = new CCommDbTest003_03;
	CleanupStack::PushL(step003_03);
	step003_03->iSuite = iSuite;			
	doTestStepWithHeapFailureL( *step003_03, KErrArgument);
	if( step003_03->iTestStepResult == EFail )
		iTestStepResult = EFail;
	CleanupStack::PopAndDestroy(step003_03);

	//Heap test for 003.04 - see test step 3.08
	
	//Heap test for 003.05

	CCommDbTest003_05* step003_05 = new CCommDbTest003_05;
	CleanupStack::PushL(step003_05);
	step003_05->iSuite = iSuite;			
	doTestStepWithHeapFailureL( *step003_05, KErrAccessDenied);
	if( step003_05->iTestStepResult == EFail )
		iTestStepResult = EFail;
	CleanupStack::PopAndDestroy(step003_05);
		

	//Heap test for 003.06

	CCommDbTest003_06* step003_06 = new CCommDbTest003_06;
	CleanupStack::PushL(step003_06);
	step003_06->iSuite = iSuite;			
	doTestStepWithHeapFailureL( *step003_06, KErrNotFound);
	if( step003_06->iTestStepResult == EFail )
		iTestStepResult = EFail;
	CleanupStack::PopAndDestroy(step003_06);
		

	return iTestStepResult;
	}
	
//
//	Test step 003.08
//

// constructor
CCommDbTest003_08::CCommDbTest003_08()
	{
	// store the name of this test case
	iTestStepName = _L("step_003_08");
	}

// destructor
CCommDbTest003_08::~CCommDbTest003_08()
	{
	}

TVerdict CCommDbTest003_08::doTestStepL( )
	{

	iTestStepResult = EPass;

	//Heap test for 003.04 - a panic test
	
	CCommDbTest003_04* step003_04 = new CCommDbTest003_04;
	CleanupStack::PushL(step003_04);
	step003_04->iSuite = iSuite;			
	if ( doTestStepWithHeapFailureL( *step003_04, KErrNotFound) == EFail )
		iTestStepResult = EFail;
	CleanupStack::PopAndDestroy(step003_04); 

	return iTestStepResult;
	}
