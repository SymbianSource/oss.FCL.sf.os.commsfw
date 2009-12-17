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
// Contains the implementation of the helper steps (initialisation and waiting
// for esock to die)
// 
//

/**
 @file TS_ConnPrefHelperSteps.cpp
*/

#include "TS_ConnPrefHelperSteps.h"
//

#include <e32base.h>
#include <e32std.h>
//

CTS_ConnPrefForceCCoverWrite::CTS_ConnPrefForceCCoverWrite(TPtrC aName) : CTS_ConnPrefStep()
{
	iTestStepName=aName;
}

CTS_ConnPrefForceCCoverWrite::~CTS_ConnPrefForceCCoverWrite()
{
}

enum TVerdict CTS_ConnPrefForceCCoverWrite::doTestStepL(void)
/*
 * It appears that CCover only writes to its data file every now and again, so force it here 
 * to write its data just before we shutdown and lose anything that has changed
 */
{
	#ifdef CCOVER
		cov_write();
	#endif

	return iTestStepResult;
} // TS_ConnPrefHelperSteps
