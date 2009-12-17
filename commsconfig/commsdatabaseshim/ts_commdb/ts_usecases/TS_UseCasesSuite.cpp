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
// This defines the TS_UseCasesSuite class which is the 
// container class for the CTS_UseCasesStep derived test steps
// 
//

/**
 @file TS_UseCasesSuite.cpp
*/
#include "TS_UseCasesSuite.h"
#include "TS_UseCasesStep.h"
#include "TS_UseCasesSteps.h"


EXPORT_C CTS_UseCasesSuite* NewTS_ConnPrefSuite( void ) 
/** Polymorphic interface, exported ordinal 1.  Called by scheduletest
 * and used to instantiate the suite
 * @return a pointer to the created TS_ConnPrefSuite object
 */
{
	CTS_UseCasesSuite* ts = 0;
	TRAPD(err,ts = new (ELeave) CTS_UseCasesSuite);
	if (err == KErrNone)
		return ts;
	return 0;
}

CTS_UseCasesSuite::~CTS_UseCasesSuite()
/** 
 * the destructor has to clean up any TConnDetails and TSock Details left hanging around
 * 
 */
{
}

void CTS_UseCasesSuite::AddTestStepL(CTS_UseCasesStep* ptrTestStep )
/**
 * adds a test step to the test suite object, using the base class method
 * @param ptrTestStep - a pointer to the test step to be added
 */
{
	CTestSuite::AddTestStepL(ptrTestStep);
}

void CTS_UseCasesSuite::InitialiseL( void )
/**
 * Effective second-phase constructor.  Creates all suite test steps
 * and associates them with the suite.
 */
{

	// Add the test steps for the tests which mainly use the dummy nif
	AddTestStepL(new(ELeave) CTS_CreatingDatabaseAndView ());
	AddTestStepL(new(ELeave) CTS_UsecaseReading ());
	AddTestStepL(new(ELeave) CTS_UsecaseWriting ());
	AddTestStepL(new(ELeave) CTS_UsecaseOverridingATableEntry ());
	AddTestStepL(new(ELeave) CTS_UsecaseOverridingThePreferenceTable ());
	AddTestStepL(new(ELeave) CTS_UsecaseUsingATemplate ()); 
	
	
}

TPtrC CTS_UseCasesSuite::GetVersion( void )
/**
 * Give version information back to Schedultest
 * @return The descriptor of the version
 */
{
	return KTxtVersion();
}
