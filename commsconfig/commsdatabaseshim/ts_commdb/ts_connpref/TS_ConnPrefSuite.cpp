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
// This defines the TS_ConnPrefSuite class which is the 
// container class for the TS_ConnPrefStep derived test steps
// 
//

/**
 @file TS_ConnPrefSuite.cpp
*/
#include "TS_ConnPrefSuite.h"
#include "TS_ConnPrefStep.h"
#include "TS_ConnPrefHelperSteps.h"
#include "TS_ConnPrefSteps.h"


EXPORT_C CTS_ConnPrefSuite* NewTS_ConnPrefSuite( void ) 
/** Polymorphic interface, exported ordinal 1.  Called by scheduletest
 * and used to instantiate the suite
 * @return a pointer to the created TS_ConnPrefSuite object
 */
{
	CTS_ConnPrefSuite* ts = 0;
	TRAPD(err,ts = new (ELeave) CTS_ConnPrefSuite);
	if (err == KErrNone)
		return ts;
	return 0;
}

CTS_ConnPrefSuite::~CTS_ConnPrefSuite()
/** 
 * the destructor has to clean up any TConnDetails and TSock Details left hanging around
 * 
 */
{
}

void CTS_ConnPrefSuite::AddTestStepL(CTS_ConnPrefStep* ptrTestStep )
/**
 * adds a test step to the test suite object, using the base class method
 * @param ptrTestStep - a pointer to the test step to be added
 */
{
	CTestSuite::AddTestStepL(ptrTestStep);
}

void CTS_ConnPrefSuite::InitialiseL( void )
/**
 * Effective second-phase constructor.  Creates all suite test steps
 * and associates them with the suite.
 */
{
	// Helper test steps	
	AddTestStepL(new(ELeave) CTS_ConnPrefForceCCoverWrite(_L("ForceCCoverWrite")));
	//Add the test steps for the tests which mainly use the dummy nif
	AddTestStepL(new(ELeave) CTS_ConstructAndVersion ());  
	AddTestStepL(new(ELeave) CTS_SetAndGetConnPrefs()); 
	AddTestStepL(new(ELeave) CTS_AssignAndCopyConstruct ()); 
	AddTestStepL(new(ELeave) CTS_ComparePrefs ()); 
	AddTestStepL(new(ELeave) CTS_ExtensionIdAndCast ()); 
	AddTestStepL(new(ELeave) CTS_MultiConnPref ()); 
	AddTestStepL(new(ELeave) CTS_MultiConnPrefVersion ());
	AddTestStepL(new(ELeave) CTS_MultiConnectionAttempts ());
 	
}

TPtrC CTS_ConnPrefSuite::GetVersion( void )
/**
 * Give version information back to Schedultest
 * @return The descriptor of the version
 */
{
	return KTxtVersion();
}
