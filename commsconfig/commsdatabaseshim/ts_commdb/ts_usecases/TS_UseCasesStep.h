/**
* Copyright (c) 2002-2009 Nokia Corporation and/or its subsidiary(-ies).
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
* This defines the CTS_EncrptStep class which is the base class for all 
* the EncrptStep test step classes
* 
*
*/



/**
 @file TS_EncrptStep.cpp.h
*/
 
#if (!defined __TS_USECASESSTEP_H__)
#define __TS_USECASESSTEP_H__

#include <e32std.h>
#include <cdbstore.h>

#include <networking/teststep.h>
#include "TS_UseCasesSuite.h"

// Connection Configuration Lits
_LIT(KNameDefault, "default");

// Test step names
_LIT(KCreatingDatabaseAndView,  "CreatingDatabaseAndView"); 
_LIT(KUsecaseReading,  "UsecaseReading");  
_LIT(KUsecaseWriting,  "UsecaseWriting"); 
_LIT(KUsecaseOverridingATableEntry  ,  "UsecaseOverridingATableEntry"); 
_LIT(KUsecaseOverridingThePreferenceTable  ,  "UsecaseOverridingThePreferenceTable"); 
_LIT(KUsecaseUsingATemplate  ,  "UsecaseUsingATemplate"); 
			
class TGlobalData;
class CTS_UseCasesSuite;

/* CTS_ConnPrefStep class declaration
 * Provides the base class for all ConnPref test steps
 *
 */
class CTS_UseCasesStep : public CTestStep
	{
public:
	CTS_UseCasesStep();
	virtual ~CTS_UseCasesStep();
	enum TVerdict Test(TInt aResult);

	void ExpLogExtra(const TText8* aFile, TInt aLine, TInt aSeverity,
		TRefByValue<const TDesC> aFmt,...);
	
	TGlobalData* Get();
	void Set(TGlobalData * aGlobals);

	CTS_UseCasesSuite* iOwnerSuite;	///< Pointer to suite which owns this test step
	
	};

class TGlobalData
{
public:
	CCommsDbTableView* iView;
	CCommsDatabase* iDb;
};

#endif /* __TS_USECASESSTEP_H__ */
