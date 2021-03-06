//
// Copyright (c) 2009 Nokia Corporation and/or its subsidiary(-ies).
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
//
//

/**
 * @file TE_EncrptServer.h
 *
 * Header for TE_EncrptSuite class. This is the container
 * class for all the CommDb ConnPrefSuite test steps
 *
 */
#if (!defined __TE_EncrptSUITE_H__)
#define __TE_EncrptSUITE_H__

#include <test/TestExecuteServerBase.h>
#include <e32std.h>

#define MAX_NAME_LENGTH		10			///< Maximum length of connection name

class CTE_EncrptStep;

class CTE_EncrptServer : public CTestServer
	{
public:
	static CTE_EncrptServer* NewL();
	virtual CTestStep* CreateTestStep(const TDesC& aStepName);
	
	
	// this should be a pure virtual so every test ddl
	// has to provide a version but for now defaults to ?.?
	virtual TPtrC GetVersion( void );
		
	};

void CommInitL(TBool);
	
#endif
