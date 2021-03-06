// Copyright (c) 2003-2009 Nokia Corporation and/or its subsidiary(-ies).
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

/**
 @file TestLoginDialog.cpp
*/
//Symbian OS Headers
#include <c32comm.h>
#include <agentdialog.h>

//Test Framework Header
#include <test/testexecutelog.h>

//Test Step Header
#include "TestLoginDialog.h"


CTestLoginDialog::~CTestLoginDialog()
/**
 * Destructor
 */
	{
	}

CTestLoginDialog::CTestLoginDialog()
/**
 * Constructor
 */
	{
	SetTestStepName(KTestLoginDialog);
	}


TVerdict CTestLoginDialog::doTestStepL()
	{


 	// When bootstrapping C32 we have to avoid the PhBkSyncServer being started, since
 	// it needs a different CommDB
 	_LIT(KPhbkSyncCMI, "phbsync.cmi");
    TInt ret = StartC32WithCMISuppressions(KPhbkSyncCMI);
	if ((ret != KErrNone) && (ret != KErrAlreadyExists))
		INFO_PRINTF2(_L("error is : %d \n"), ret);
	else	
		INFO_PRINTF1(_L("Started C32\n"));

	RGenConAgentDialogServer dlgSv;
	TRAP_IGNORE(dlgSv.Connect());
	INFO_PRINTF1(_L("Connected Dialog Server\n"));

	TRequestStatus status;

	INFO_PRINTF1(_L("\nTesting the Login Dialog\n")); 
	TBuf<KCommsDbSvrMaxFieldLength> username=_L("LnUser");
	TBuf<KCommsDbSvrMaxFieldLength> password=_L("LnPass");
	dlgSv.Login(username,password,EFalse,status);
	User::WaitForRequest(status);
	ret=status.Int();
	INFO_PRINTF2(_L("Login completed with code=%d\n"),ret);
	checkError(dlgSv,ret);
	INFO_PRINTF3(_L("Username=%S Password=%S\n"),&username,&password);

	return TestStepResult();
	}


void CTestLoginDialog::checkError(RGenConAgentDialogServer& aDlgSvr, TInt aError)
	{
	if (aError!=KErrNone && aError!=KErrCancel)
		aDlgSvr.Close();

	if ((aError!=KErrNone) && (aError!=KErrCancel))
		INFO_PRINTF2(_L("Error is : %d \n"), aError);
	}

void CTestLoginDialog::checkPctError(RGenConAgentDialogServer& aDlgSvr, TInt aError)
	{
	if (aError!=KErrNone)
		{
		aDlgSvr.ClosePct();
		TRequestStatus destroyStatus;
		User::WaitForRequest(destroyStatus);
		aDlgSvr.Close();
		}

	TEST(aError==KErrNone);
	}	


