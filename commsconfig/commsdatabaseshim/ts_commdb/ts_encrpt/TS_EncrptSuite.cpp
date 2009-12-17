// Copyright (c) 2002-2009 Nokia Corporation and/or its subsidiary(-ies).
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
// This defines the TS_EncrptSuite class which is the 
// container class for the TS_EncrptStep derived test steps
// 
//

/**
 @file TS_EncrptSuite.cpp
*/
#include "TS_EncrptSuite.h"
#include "TS_EncrptStep.h"
#include "TS_EncrptSteps.h"


EXPORT_C CTS_EncrptSuite* NewTS_ConnPrefSuite( void ) 
/** Polymorphic interface, exported ordinal 1.  Called by scheduletest
 * and used to instantiate the suite
 * @return a pointer to the created TS_ConnPrefSuite object
 */
{
	CTS_EncrptSuite* ts = 0;
	TRAPD(err,ts = new (ELeave) CTS_EncrptSuite);
	if (err == KErrNone)
		return ts;

	return 0;
}

CTS_EncrptSuite::~CTS_EncrptSuite()
/** 
 * the destructor has to clean up any TConnDetails and TSock Details left hanging around
 * 
 */
{
}

void CTS_EncrptSuite::AddTestStepL(CTS_EncrptStep* ptrTestStep )
/**
 * adds a test step to the test suite object, using the base class method
 * @param ptrTestStep - a pointer to the test step to be added
 */
{
	CTestSuite::AddTestStepL(ptrTestStep);
}

void CTS_EncrptSuite::InitialiseL( void )
/**
 * Effective second-phase constructor.  Creates all suite test steps
 * and associates them with the suite.
 */
{
	
	// Add the test steps for the tests which mainly use the dummy nif
	AddTestStepL(new(ELeave) CTS_CreateEntries ());  
	AddTestStepL(new(ELeave) CTS_CheckPasswords ());  
	AddTestStepL(new(ELeave) CTS_DeleteEntries ());  
	
}

TPtrC CTS_EncrptSuite::GetVersion( void )
/**
 * Give version information back to Schedultest
 * @return The descriptor of the version
 */
{
	return KTxtVersion();
}
