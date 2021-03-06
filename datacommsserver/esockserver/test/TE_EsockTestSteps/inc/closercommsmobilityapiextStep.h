/**
* Copyright (c) 2005-2009 Nokia Corporation and/or its subsidiary(-ies).
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
 @file closercommsmobilityapiextStep.h
*/
#if (!defined CLOSERCOMMSMOBILITYAPIEXT_STEP_H)
#define CLOSERCOMMSMOBILITYAPIEXT_STEP_H
#include <testexecutestepbase.h>
#include "Te_EsockStepBase.h"

/**
Class implementing closercommsmobilityapiextStep

@internalComponent
*/
class CclosercommsmobilityapiextStep : public CTe_EsockStepBase
	{
public:
	CclosercommsmobilityapiextStep(CCEsockTestBase*& aEsockTest);
	TVerdict doSingleTestStep();
	TBool DescriptionExists();

private:
    TPtrC iMobilityExtName;
    TPtrC iConnectionName;
	};

_LIT(KclosercommsmobilityapiextStep,"closercommsmobilityapiextStep");

#endif //CLOSERCOMMSMOBILITYAPIEXT_STEP_H

