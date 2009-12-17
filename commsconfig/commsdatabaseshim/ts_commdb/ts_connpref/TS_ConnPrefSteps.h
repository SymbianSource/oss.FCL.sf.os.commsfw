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
* This defines the TS_RConnectionStep class which is the base class for all 
* the RConnection multihoming test step classes
* 
*
*/



/**
 @file TS_RConnectionStep.h
*/
 
#if (!defined __TS_CONNPREFSTEPS_H__)
#define __TS_CONNPREFSTEPS_H__

#include <e32std.h>
#include <cdbstore.h>
#include <es_sock.h>
#include <in_sock.h>
#include <es_enum.h>
#include <commdbconnpref.h>

#include <networking/teststep.h>
#include "TS_ConnPrefSuite.h"
#include "TS_ConnPrefStep.h"

//
class CTS_ConstructAndVersion : public CTS_ConnPrefStep
{
public:
	CTS_ConstructAndVersion();
	virtual ~CTS_ConstructAndVersion();
	virtual enum TVerdict doTestStepL();
};

//
class CTS_SetAndGetConnPrefs : public CTS_ConnPrefStep
{
public:
	CTS_SetAndGetConnPrefs();
	virtual ~CTS_SetAndGetConnPrefs();
	virtual enum TVerdict doTestStepL();
};

//
class CTS_ComparePrefs : public CTS_ConnPrefStep
{
public:
	CTS_ComparePrefs();
	virtual ~CTS_ComparePrefs();
	virtual enum TVerdict doTestStepL();
};

//
class CTS_AssignAndCopyConstruct : public CTS_ConnPrefStep
{
public:
	CTS_AssignAndCopyConstruct();
	virtual ~CTS_AssignAndCopyConstruct();
	virtual enum TVerdict doTestStepL();
};

// 
class CTS_ExtensionIdAndCast : public CTS_ConnPrefStep
{
public:
	CTS_ExtensionIdAndCast();
	virtual ~CTS_ExtensionIdAndCast();
	virtual enum TVerdict doTestStepL();
};

//  
class CTS_MultiConnPref : public CTS_ConnPrefStep
{
public:
	CTS_MultiConnPref();
	virtual ~CTS_MultiConnPref();
	virtual enum TVerdict doTestStepL();
};


///////////////////////////////////////
//	Test step CTS_MultiConnPrefVersion
///////////////////////////////////////

NONSHARABLE_CLASS(CTS_MultiConnPrefVersion) : public CTS_ConnPrefStep
{
public:
	CTS_MultiConnPrefVersion();
	virtual ~CTS_MultiConnPrefVersion();
	virtual enum TVerdict doTestStepL();
	CCommsDbTableView*	iTheView;
	CCommsDatabase*		iTheDb;

};

////////////////////////////////////////////
//	Test step CTS_MultiConnectionAttempts
////////////////////////////////////////////

NONSHARABLE_CLASS(CTS_MultiConnectionAttempts): public CTS_ConnPrefStep
{
public:
	CTS_MultiConnectionAttempts();
	virtual ~CTS_MultiConnectionAttempts();
	virtual enum TVerdict doTestStepL();
};


#endif /* __TS_CONNPREFSTEPS_H__ */















