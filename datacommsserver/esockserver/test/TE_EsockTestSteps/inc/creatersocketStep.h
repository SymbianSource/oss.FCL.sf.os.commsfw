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
*
*/



/**
 @file creatersocketStep.h
*/
#if (!defined CREATERSOCKET_STEP_H)
#define CREATERSOCKET_STEP_H
#include <testexecutestepbase.h>
#include "Te_EsockStepBase.h"

/**
Class implementing creatersocketStep

@internalComponent
*/
class CcreatersocketStep : public CTe_EsockStepBase
	{
public:
	CcreatersocketStep(CCEsockTestBase*& aEsockTest);
	TVerdict doTestStepPreambleL();
	TVerdict doSingleTestStep();
	TBool DescriptionExists();

private:
    TRSocketParams iParams; //current params (.ini)
	};


_LIT(KcreatersocketStep,"creatersocketStep");

#endif

