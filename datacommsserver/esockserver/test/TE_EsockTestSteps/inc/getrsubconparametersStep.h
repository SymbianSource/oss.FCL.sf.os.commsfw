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
 @file getrsubconparametersStep.h
*/
#if (!defined GETRSUBCONPARAMETERS_STEP_H)
#define GETRSUBCONPARAMETERS_STEP_H
#include <testexecutestepbase.h>
#include "Te_EsockStepBase.h"

/**
Class implementing getrsubconparametersStep

@internalComponent
*/
class CgetrsubconparametersStep : public CTe_EsockStepBase
	{
public:
	CgetrsubconparametersStep(CCEsockTestBase*& aEsockTest);
	TVerdict doSingleTestStep();
	TBool DescriptionExists();

private:
    TRSubConnectionParams iParams; //current params
	};

_LIT(KgetrsubconparametersStep,"getrsubconparametersStep");

#endif //GETRSUBCONPARAMETERS_STEP_H

