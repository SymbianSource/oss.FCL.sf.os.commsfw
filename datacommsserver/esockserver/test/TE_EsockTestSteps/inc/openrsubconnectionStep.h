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
 @file openrsubconnectionStep.h
*/
#if (!defined OPENRSUBCONNECTION_STEP_H)
#define OPENRSUBCONNECTION_STEP_H
#include <testexecutestepbase.h>
#include "Te_EsockStepBase.h"

/**
Class implementing openrsubconnectionStep

@internalComponent
*/
class CopenrsubconnectionStep : public CTe_EsockStepBase
	{
public:
	CopenrsubconnectionStep(CCEsockTestBase*& aEsockTest);
	TVerdict doSingleTestStep();
	TBool DescriptionExists();

private:
	TRSubConnectionParams iParams; //current params (.ini)
	};

_LIT(KopenrsubconnectionStep,"openrsubconnectionStep");

#endif

