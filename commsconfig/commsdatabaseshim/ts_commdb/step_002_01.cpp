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
// This contains CommDb Unit Test Case 002.01
// 
//

// EPOC includes
#include <e32base.h>

// Test system includes
#include <networking/log.h>
#include <networking/teststep.h>
#include "Teststepcommdb.h"
#include "TestSuiteCommdb.h"
#include "step_002_01.h"

#include <commdb.h>



// constructor
CCommDbTest002_01::CCommDbTest002_01()
{
	// store the name of this test case
	iTestStepName = _L("step_002_01");
}

// destructor
CCommDbTest002_01::~CCommDbTest002_01()
{
}

// do Test step 002.01
TVerdict CCommDbTest002_01::doTestStepL( )
{

	Log(_L("Step 002.01 called "));

	// delete database file before running this test
/*#ifdef __SECURE_DATA__
	DeleteCurrentDatabaseL();
#else*/
//#endif

	CCommsDatabase* TheDb;
	TheDb=CCommsDatabase::NewL();
	CleanupStack::PushL(TheDb);
	TVersion DbVersion = TheDb->Version();

	CleanupStack::PopAndDestroy();

	Log(_L("Version details: Major %d Minor %d Build %x"), DbVersion.iMajor, DbVersion.iMinor, DbVersion.iBuild);
	if ( DbVersion.iMinor == 1 && DbVersion.iMajor == 1 && DbVersion.iBuild == 0x1 )
	{
		iTestStepResult=EPass;
	}
	else
	{
		iTestStepResult=EFail;
	}

	return iTestStepResult;
}
