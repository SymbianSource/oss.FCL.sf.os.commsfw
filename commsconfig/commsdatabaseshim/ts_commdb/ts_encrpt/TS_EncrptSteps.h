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
 
#if (!defined __TS_ENCRPTSTEPS_H__)
#define __TS_ENCRPTSTEPS_H__

#include <e32std.h>
#include <cdbstore.h>
#include <es_sock.h>
#include <in_sock.h>
#include <es_enum.h>
#include <commdbconnpref.h>

#include <networking/teststep.h>
#include "TS_EncrptSuite.h"
#include "TS_EncrptStep.h"


class CTS_CreateEntries : public CTS_EncrptStep
{
public:
	CTS_CreateEntries();
	virtual ~CTS_CreateEntries();
	virtual enum TVerdict doTestStepL();
};

class CTS_CheckPasswords: public CTS_EncrptStep
{
public:
	CTS_CheckPasswords();
	virtual ~CTS_CheckPasswords();
	virtual enum TVerdict doTestStepL();
};

class CTS_DeleteEntries: public CTS_EncrptStep
{
public:
	CTS_DeleteEntries();
	virtual ~CTS_DeleteEntries();
	virtual enum TVerdict doTestStepL();
};



#endif /* __TS_ENCRPTSTEPS_H__ */
