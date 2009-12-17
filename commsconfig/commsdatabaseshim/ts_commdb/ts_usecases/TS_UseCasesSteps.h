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
* This defines the TS_RConnectionStep class which is the base class for all 
* the RConnection multihoming test step classes
* 
*
*/



/**
 @file TS_RConnectionStep.h
*/
 
#if (!defined __TS_USECASESSTEPS_H__)
#define __TS_USECASESSTEPS_H__

#include <e32std.h>
#include <cdbstore.h>
#include <es_sock.h>
#include <in_sock.h>
#include <es_enum.h>
#include <commdbconnpref.h>

#include <networking/teststep.h>
#include "TS_UseCasesSuite.h"
#include "TS_UseCasesStep.h"


class CTS_CreatingDatabaseAndView : public CTS_UseCasesStep
{
public:
	CTS_CreatingDatabaseAndView();
	virtual ~CTS_CreatingDatabaseAndView();
	virtual enum TVerdict doTestStepL();
};  


class CTS_UsecaseReading: public CTS_UseCasesStep
{
public:
	CTS_UsecaseReading();
	virtual ~CTS_UsecaseReading();
	virtual enum TVerdict doTestStepL();
};  


class CTS_UsecaseWriting: public CTS_UseCasesStep
{
public:
	CTS_UsecaseWriting();
	virtual ~CTS_UsecaseWriting();
	virtual enum TVerdict doTestStepL();
};  


class CTS_UsecaseOverridingATableEntry: public CTS_UseCasesStep
{
public:
	CTS_UsecaseOverridingATableEntry();
	virtual ~CTS_UsecaseOverridingATableEntry();
	virtual enum TVerdict doTestStepL();
};  


class CTS_UsecaseOverridingThePreferenceTable: public CTS_UseCasesStep
{
public:
	CTS_UsecaseOverridingThePreferenceTable();
	virtual ~CTS_UsecaseOverridingThePreferenceTable();
	virtual enum TVerdict doTestStepL();
};   


class CTS_UsecaseUsingATemplate: public CTS_UseCasesStep
{
public:
	CTS_UsecaseUsingATemplate();
	virtual ~CTS_UsecaseUsingATemplate();
	virtual enum TVerdict doTestStepL();
};   


#endif /* __TS_USECASESSTEPS_H__ */
