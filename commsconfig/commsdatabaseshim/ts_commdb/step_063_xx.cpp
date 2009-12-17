// Copyright (c) 2006-2009 Nokia Corporation and/or its subsidiary(-ies).
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
// This contains CommDb Unit Test Cases 063.XX
// 
//

// EPOC includes
#include <commdb.h>
#include <d32dbms.h>
#include <badesca.h>
#include <cdbstore.h>

#ifdef SYMBIAN_OLD_EXPORT_LOCATION
#include <comms-infras/commdb/protection/protectdb.h>
#include <comms-infras/commdb/protection/protectcpdb.h>
#else
//these headers are user includes in the new env.
#include "protectdb.h"
#include "protectcpdb.h"
#endif

// Test system includes
#include <networking/log.h>
#include <networking/teststep.h>
#include "Teststepcommdb.h"
#include "TestSuiteCommdb.h"
#include "step_063_xx.h"

//
//	Test step 063.01
//

// constructor
CCommDbTest063_01::CCommDbTest063_01()
	{
	// store the name of this test case
	iTestStepName = _L("step_063_01");
	}

// destructor
CCommDbTest063_01::~CCommDbTest063_01()
	{}
	
enum TVerdict CCommDbTest063_01::doTestStepL( void )
	{
	iTestStepResult = EPass;

	iTheProtectedDb = CCommsDatabaseProtect::NewL();

	if(iTheProtectedDb->ProtectTable(TPtrC(DIAL_OUT_ISP))!=KErrNone)
		{iTestStepResult = EFail;}

	RDbRowSet::TAccess rowSet = RDbRowSet::EUpdatable;
	TRAPD(ret, rowSet = iTheProtectedDb->GetTableAccessL(TPtrC(DIAL_OUT_ISP)));

	if (ret != KErrNone || rowSet != RDbRowSet::EReadOnly)
		{
		iTestStepResult = EFail;
		}

	delete iTheProtectedDb;
	iTheProtectedDb=NULL;

	return iTestStepResult;
	}

//
//	Test step 063.02
//

// constructor
CCommDbTest063_02::CCommDbTest063_02()
	{
	// store the name of this test case
	iTestStepName = _L("step_063_02");
	}

// destructor
CCommDbTest063_02::~CCommDbTest063_02()
	{}
	
enum TVerdict CCommDbTest063_02::doTestStepL( void )
	{
	iTestStepResult = EPass;

	iTheProtectedDb = CCommsDatabaseProtect::NewL();

	if(iTheProtectedDb->UnProtectTable(TPtrC(DIAL_OUT_ISP))!=KErrNone)
		{
		iTestStepResult = EFail;
		}

	RDbRowSet::TAccess rowSet = RDbRowSet::EReadOnly;
	TRAPD(ret, rowSet = iTheProtectedDb->GetTableAccessL(TPtrC(DIAL_OUT_ISP)));

	if (ret != KErrNone || rowSet != RDbRowSet::EUpdatable)
		{
		iTestStepResult = EFail;
		}

	delete iTheProtectedDb;
	iTheProtectedDb=NULL;

	return iTestStepResult;
	}

//
//	Test step 063.03
//

// constructor
CCommDbTest063_03::CCommDbTest063_03()
	{
	// store the name of this test case
	iTestStepName = _L("step_063_03");
	}

// destructor
CCommDbTest063_03::~CCommDbTest063_03()
	{}
	
enum TVerdict CCommDbTest063_03::doTestStepL( void )
	{
	iTestStepResult = EPass;

	iTheProtectedDb = CCommsDatabaseProtect::NewL();

	//Construct table list
	CPtrCArray* tableArray;
	tableArray = new (ELeave) CPtrCArray(2);
	CleanupStack::PushL(tableArray);

	TRAPD(ret, tableArray->InsertL(0,DIAL_OUT_ISP));
	if (ret != KErrNone)
		{
		iTestStepResult = EFail;
		CleanupStack::PopAndDestroy(tableArray);
		delete iTheProtectedDb;
		iTheProtectedDb=NULL;
		return iTestStepResult;
		}

	TRAP(ret, tableArray->InsertL(1,DIAL_IN_ISP));
	if (ret != KErrNone)
		{
		iTestStepResult = EFail;
		CleanupStack::PopAndDestroy(tableArray);
		delete iTheProtectedDb;
		iTheProtectedDb=NULL;
		return iTestStepResult;
		}
	
	if(iTheProtectedDb->ProtectTables(*tableArray) != KErrNone)
		{
		iTestStepResult = EFail;
		CleanupStack::PopAndDestroy(tableArray);
		delete iTheProtectedDb;
		iTheProtectedDb=NULL;
		return iTestStepResult;
		}

	RDbRowSet::TAccess rowSet = RDbRowSet::EUpdatable;
	TRAP(ret, rowSet = iTheProtectedDb->GetTableAccessL(TPtrC(DIAL_IN_ISP)));

	if (ret != KErrNone || rowSet != RDbRowSet::EReadOnly)
		{
		iTestStepResult = EFail;
		}

	CleanupStack::PopAndDestroy(tableArray);

	delete iTheProtectedDb;
	iTheProtectedDb=NULL;

	return iTestStepResult;
	}

//
//	Test step 063.04
//

// constructor
CCommDbTest063_04::CCommDbTest063_04()
	{
	// store the name of this test case
	iTestStepName = _L("step_063_04");
	}

// destructor
CCommDbTest063_04::~CCommDbTest063_04()
	{}
	
enum TVerdict CCommDbTest063_04::doTestStepL( void )
	{
	iTestStepResult = EPass;

	iTheProtectedDb = CCommsDatabaseProtect::NewL();

	//Construct table list
	CPtrCArray* tableArray;
	tableArray = new (ELeave) CPtrCArray(2);
	CleanupStack::PushL(tableArray);

	TRAPD(ret, tableArray->InsertL(0,DIAL_OUT_ISP));
	if (ret != KErrNone)
		{
		iTestStepResult = EFail;
		CleanupStack::PopAndDestroy(tableArray);
		delete iTheProtectedDb;
		iTheProtectedDb=NULL;
		return iTestStepResult;
		}

	TRAP(ret, tableArray->InsertL(1,DIAL_IN_ISP));
	if (ret != KErrNone)
		{
		iTestStepResult = EFail;
		CleanupStack::PopAndDestroy(tableArray);
		delete iTheProtectedDb;
		iTheProtectedDb=NULL;
		return iTestStepResult;
		}

	if(iTheProtectedDb->UnprotectTables(*tableArray) != KErrNone)
		{
		iTestStepResult = EFail;
		CleanupStack::PopAndDestroy(tableArray);
		delete iTheProtectedDb;
		iTheProtectedDb=NULL;
		return iTestStepResult;
		}

	RDbRowSet::TAccess rowSet = RDbRowSet::EReadOnly;
	TRAP(ret, rowSet = iTheProtectedDb->GetTableAccessL(TPtrC(DIAL_IN_ISP)));

	if (ret != KErrNone || rowSet != RDbRowSet::EUpdatable)
		{
		iTestStepResult = EFail;
		}

	CleanupStack::PopAndDestroy(tableArray);

	delete iTheProtectedDb;
	iTheProtectedDb=NULL;

	return iTestStepResult;
	}

//
//	Test step 063.05
//

// constructor
CCommDbTest063_05::CCommDbTest063_05()
	{
	// store the name of this test case
	iTestStepName = _L("step_063_05");
	}

// destructor
CCommDbTest063_05::~CCommDbTest063_05()
	{
	}
	
enum TVerdict CCommDbTest063_05::doTestStepL( void )
	{	
	iTestStepResult = EPass;
	TBool val=0;
	iTheProtectedDb = CCommsDatabaseProtect::NewL(val);
	if(iTheProtectedDb->ProtectTable(TPtrC(DIAL_OUT_ISP)) != KErrNone)
		{
		iTestStepResult = EFail;
		}
	RDbRowSet::TAccess rowSet = RDbRowSet::EUpdatable;
	TRAPD(ret, rowSet = iTheProtectedDb->GetTableAccessL(TPtrC(DIAL_OUT_ISP)));
	if (ret != KErrNone || rowSet != RDbRowSet::EReadOnly)
		{
		iTestStepResult = EFail;
		}
	delete iTheProtectedDb;
	iTheProtectedDb=NULL;
    return iTestStepResult;
	}
		
	//
//	Test step 063.06
//

// constructor
CCommDbTest063_06::CCommDbTest063_06()
	{
	// store the name of this test case
	iTestStepName = _L("step_063_06");
	}

// destructor
CCommDbTest063_06::~CCommDbTest063_06()
	{
	}
	
enum TVerdict CCommDbTest063_06::doTestStepL( void )
	{
	iTestStepResult = EPass;
    TBool val=0;
	iTheProtectedDb = CCommsDatabaseProtect::NewL(val);
	if(iTheProtectedDb->UnProtectTable(TPtrC(DIAL_OUT_ISP)) != KErrNone)
		{
		iTestStepResult = EFail;
		}
	RDbRowSet::TAccess rowSet = RDbRowSet::EReadOnly;
	TRAPD(ret, rowSet = iTheProtectedDb->GetTableAccessL(TPtrC(DIAL_OUT_ISP)));
	if (ret != KErrNone || rowSet != RDbRowSet::EUpdatable)
		{
		iTestStepResult = EFail;
		}
	delete iTheProtectedDb;
	iTheProtectedDb=NULL;
	return iTestStepResult;
	}

//
//	Test step 063.07
//

// constructor
CCommDbTest063_07::CCommDbTest063_07()
	{
	// store the name of this test case
	iTestStepName = _L("step_063_07");
	}

// destructor
CCommDbTest063_07::~CCommDbTest063_07()
	{
	}
	
enum TVerdict CCommDbTest063_07::doTestStepL( void )
	{
	iTestStepResult = EPass;
	TBool val=0;
	iTheProtectedDb = CCommsDatabaseProtect::NewL(val);
	//Construct table list
	CPtrCArray* tableArray = new (ELeave) CPtrCArray(2);
	CleanupStack::PushL(tableArray);
	TRAPD(ret, tableArray->InsertL(0,DIAL_OUT_ISP));
	if (ret != KErrNone)
		{
		iTestStepResult = EFail;
		CleanupStack::PopAndDestroy(tableArray);
		delete iTheProtectedDb;
		iTheProtectedDb=NULL;
		return iTestStepResult;
		}
	TRAP(ret, tableArray->InsertL(1,DIAL_IN_ISP));
	if (ret != KErrNone)
		{
		iTestStepResult = EFail;
		CleanupStack::PopAndDestroy(tableArray);
		delete iTheProtectedDb;
		iTheProtectedDb=NULL;
		return iTestStepResult;
		}	
	if(iTheProtectedDb->ProtectTables(*tableArray) != KErrNone)
		{
		iTestStepResult = EFail;
		CleanupStack::PopAndDestroy(tableArray);
		delete iTheProtectedDb;
		iTheProtectedDb=NULL;
		return iTestStepResult;
		}
	RDbRowSet::TAccess rowSet = RDbRowSet::EUpdatable;
	TRAP(ret, rowSet = iTheProtectedDb->GetTableAccessL(TPtrC(DIAL_IN_ISP)));
	if (ret != KErrNone || rowSet != RDbRowSet::EReadOnly)
		{
		iTestStepResult = EFail;
		}
	CleanupStack::PopAndDestroy(tableArray);
	delete iTheProtectedDb;
	iTheProtectedDb=NULL;
	return iTestStepResult;
	}

//
//	Test step 063.08
//

// constructor
CCommDbTest063_08::CCommDbTest063_08()
	{
	// store the name of this test case
	iTestStepName = _L("step_063_08");
	}

// destructor
CCommDbTest063_08::~CCommDbTest063_08()
	{
	}
	
enum TVerdict CCommDbTest063_08::doTestStepL( void )
	{
	iTestStepResult = EPass;
	TBool val=0;
	iTheProtectedDb = CCommsDatabaseProtect::NewL(val);
	//Construct table list
	CPtrCArray* tableArray = new (ELeave) CPtrCArray(2);
	CleanupStack::PushL(tableArray);
	TRAPD(ret, tableArray->InsertL(0,DIAL_OUT_ISP));
	if (ret != KErrNone)
		{
		iTestStepResult = EFail;
		CleanupStack::PopAndDestroy(tableArray);
		delete iTheProtectedDb;
		iTheProtectedDb=NULL;
		return iTestStepResult;
		}
	TRAP(ret, tableArray->InsertL(1,DIAL_IN_ISP));
	if (ret != KErrNone)
		{
		iTestStepResult = EFail;
		CleanupStack::PopAndDestroy(tableArray);
		delete iTheProtectedDb;
		iTheProtectedDb=NULL;
		return iTestStepResult;
		}
	if(iTheProtectedDb->UnprotectTables(*tableArray) != KErrNone)
		{
		iTestStepResult = EFail;
		CleanupStack::PopAndDestroy(tableArray);
		delete iTheProtectedDb;
		iTheProtectedDb=NULL;
		return iTestStepResult;
		}
	RDbRowSet::TAccess rowSet = RDbRowSet::EReadOnly;
	TRAP(ret, rowSet = iTheProtectedDb->GetTableAccessL(TPtrC(DIAL_IN_ISP)));
	if (ret != KErrNone || rowSet != RDbRowSet::EUpdatable)
		{
		iTestStepResult = EFail;
		}
	CleanupStack::PopAndDestroy(tableArray);
	delete iTheProtectedDb;
	iTheProtectedDb=NULL;
	return iTestStepResult;
	}
	



	
	
	
	
	
	


