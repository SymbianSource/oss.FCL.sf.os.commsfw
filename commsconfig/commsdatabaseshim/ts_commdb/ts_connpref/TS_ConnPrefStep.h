/**
* Copyright (c) 2006-2009 Nokia Corporation and/or its subsidiary(-ies).
* All rights reserved.
* This component and the accompanying materials are made available
* under the terms of "Eclipse Public License v1.0"
* which accompanies this distribution, and is available
* at the URL "http://www.eclipse.org/legal/epl-v10.html".
*
* Initial Contributors:
* Nokia Corporation - initial contribution.
*
* Contributors:
*
* Description:
* This defines the CTS_ConnPrefStep class which is the base class for all 
* the ConnPrefStep test step classes
* 
*
*/



/**
 @file TS_ConnPrefStep.cpp.h
*/
 
#if (!defined __TS_CONNPREFSTEP_H__)
#define __TS_CONNPREFSTEP_H__

#include <e32std.h>
#include <cdbstore.h>

#include <networking/teststep.h>
#include "TS_ConnPrefSuite.h"

// Connection Configuration Lits
_LIT(KNameDefault, "default");

// Test step names
_LIT(KConstructAndVersion,  "ConstructAndVersion"); 
_LIT(KSetAndGetConnPrefs,  "SetAndGetConnPrefs"); 
_LIT(KComparePrefs,  "ComparePrefs");  
_LIT(KAssignAndCopyConstruct ,  "AssignAndCopyConstruct"); 
_LIT(KExtensionIdAndCast ,  "ExtensionIdAndCast"); 
_LIT(KMultiConnPref ,  "MultiConnPref");
_LIT(KMultiConnPrefVersion,  "MultiConnPrefVersion");
_LIT(KMultiConnectionAttempts,  "MultiConnectionAttempts");

//Error string.
_LIT(KEGeneric, "Test left!"); 
			

class CTS_ConnPrefSuite;

/* CTS_ConnPrefStep class declaration
 * Provides the base class for all ConnPref test steps
 *
 */
class CTS_ConnPrefStep : public CTestStep
	{
public:
	CTS_ConnPrefStep();
	virtual ~CTS_ConnPrefStep();
	enum TVerdict Test(TInt aResult);

	void ExpLogExtra(const TText8* aFile, TInt aLine, TInt aSeverity,
		TRefByValue<const TDesC> aFmt,...);
	
	
	CTS_ConnPrefSuite* iOwnerSuite;	///< Pointer to suite which owns this test step
	
	};

#endif /* __TS_CONNPREFSTEP_H__ */
