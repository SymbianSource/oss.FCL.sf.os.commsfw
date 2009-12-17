// Copyright (c) 1997-2009 Nokia Corporation and/or its subsidiary(-ies).
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
// TS_ENCRPT.CPP
// Test code for encryption in Database
// 
//

#include <e32test.h>
#include <f32file.h>
#include <d32comm.h>
#include <cdbcols.h>
#include <commdb.h>
#include <cdblen.h>

#include "TS_EncrptSteps.h"


//#define KSvDbFileName	_L("\\SYSTEM\\DATA\\CDBV2.DAT")		// test database

#define pass1			_L("PASS")
#define pass2			_L("1234567890")
#define pass3			_L("abcdefghijklmnopqrstuvwxyz")
#define pass4			_L("!\xa3$%^&*()_+-=?><,.@~:;'#|")


CTS_CreateEntries::CTS_CreateEntries()
	{
	iTestStepName = KCreateEntries;
	}

CTS_CreateEntries::~CTS_CreateEntries()
	{	
	}

enum TVerdict CTS_CreateEntries::doTestStepL()
	{
	
	TUint32 id1 = 0;  
	TUint32 id2 = 0; 
		
	Log(_L("Testing encryption"));

    CCommsDatabase* db=CCommsDatabase::NewL(EDatabaseTypeIAP);
		CleanupStack::PushL(db);
	User::LeaveIfError(db->BeginTransaction());
	
	CCommsDbTableView* table=db->OpenTableLC(TPtrC(DIAL_OUT_ISP));
	Test(table->InsertRecord(id1)==KErrNone);
	table->WriteTextL(TPtrC(COMMDB_NAME),_L("Test 1"));
	table->WriteBoolL(TPtrC(ISP_DIAL_RESOLUTION),ETrue);
	table->WriteBoolL(TPtrC(ISP_USE_LOGIN_SCRIPT),EFalse);
	table->WriteBoolL(TPtrC(ISP_PROMPT_FOR_LOGIN),EFalse);
	table->WriteTextL(TPtrC(ISP_LOGIN_NAME),_L("AnnW"));
	table->WriteTextL(TPtrC(ISP_LOGIN_PASS),pass1);
	table->WriteBoolL(TPtrC(ISP_IF_PROMPT_FOR_AUTH),ETrue);
	table->WriteTextL(TPtrC(ISP_IF_AUTH_NAME),_L("RasUser"));
	table->WriteTextL(TPtrC(ISP_IF_AUTH_PASS),pass2);
	table->WriteBoolL(TPtrC(ISP_IP_ADDR_FROM_SERVER),ETrue);
	table->WriteBoolL(TPtrC(ISP_IP_DNS_ADDR_FROM_SERVER),ETrue);
	table->WriteBoolL(TPtrC(ISP_IP6_DNS_ADDR_FROM_SERVER),ETrue);
	Test(table->PutRecordChanges()==KErrNone);

	Test(table->InsertRecord(id2)==KErrNone);
	table->WriteTextL(TPtrC(COMMDB_NAME),_L("Test 2"));
	table->WriteBoolL(TPtrC(ISP_DIAL_RESOLUTION),ETrue);
	table->WriteBoolL(TPtrC(ISP_USE_LOGIN_SCRIPT),EFalse);
	table->WriteBoolL(TPtrC(ISP_PROMPT_FOR_LOGIN),EFalse);
	table->WriteTextL(TPtrC(ISP_LOGIN_NAME),_L("AnnW"));
	table->WriteTextL(TPtrC(ISP_LOGIN_PASS),pass3);
	table->WriteBoolL(TPtrC(ISP_IF_PROMPT_FOR_AUTH),ETrue);
	table->WriteTextL(TPtrC(ISP_IF_AUTH_NAME),_L("RasUser"));
	table->WriteTextL(TPtrC(ISP_IF_AUTH_PASS),pass4);
	table->WriteBoolL(TPtrC(ISP_IP_ADDR_FROM_SERVER),ETrue);
	table->WriteBoolL(TPtrC(ISP_IP_DNS_ADDR_FROM_SERVER),ETrue);
	table->WriteBoolL(TPtrC(ISP_IP6_DNS_ADDR_FROM_SERVER),ETrue);
	Test(table->PutRecordChanges()==KErrNone);

	Test(db->CommitTransaction()==KErrNone);
	CleanupStack::PopAndDestroy(2);
	
	// Allocate global storage to be held in tls.
	TGlobalDbIds  *globals=new(ELeave) TGlobalDbIds ;
	globals->id1 = id1;
	globals->id2 = id2;
	CTS_EncrptStep::Set(globals);

	Log(_L("IAP Entries Added Successfully"));

	return EPass;
	}


CTS_CheckPasswords::CTS_CheckPasswords()
	{
	iTestStepName = KCheckPasswords;
	}

CTS_CheckPasswords::~CTS_CheckPasswords()
	{	
	}

enum TVerdict CTS_CheckPasswords::doTestStepL()
	{

	Log(_L("Checking passwords"));

	TGlobalDbIds* globals = CTS_EncrptStep::Get();

	TUint32 id1 = globals->id1;  
	TUint32 id2 = globals->id2;

	CCommsDatabase* db=CCommsDatabase::NewL(EDatabaseTypeIAP);
		CleanupStack::PushL(db);
	
	CCommsDbTableView* table=db->OpenViewMatchingUintLC(TPtrC(DIAL_OUT_ISP), TPtrC(COMMDB_ID), id1);

	TBuf<KCommsDbSvrMaxFieldLength> password;
	Test(table->GotoFirstRecord()==KErrNone);
	table->ReadTextL(TPtrC(ISP_LOGIN_PASS),password);
	Test(password==pass1);
	table->ReadTextL(TPtrC(ISP_IF_AUTH_PASS),password);
	Test(password==pass2);

	CleanupStack::PopAndDestroy(table);
	table = NULL;
	table = db->OpenViewMatchingUintLC(TPtrC(DIAL_OUT_ISP), TPtrC(COMMDB_ID), id2);

	Test(table->GotoFirstRecord()== KErrNone);
	table->ReadTextL(TPtrC(ISP_LOGIN_PASS),password);
	Test(password==pass3);
	table->ReadTextL(TPtrC(ISP_IF_AUTH_PASS),password);
	Test(password==pass4);
	
	CleanupStack::PopAndDestroy(2);

	return EPass;
	}


CTS_DeleteEntries::CTS_DeleteEntries()
	{
	iTestStepName = KDeleteEntries;
	}

CTS_DeleteEntries::~CTS_DeleteEntries()
	{	
	}

enum TVerdict CTS_DeleteEntries::doTestStepL()
	{

	Log(_L("Delete the IAP entries."));

	TGlobalDbIds* globals = CTS_EncrptStep::Get();
	TUint32 id1 = globals->id1;  
	TUint32 id2 = globals->id2;

    CCommsDatabase* db = CCommsDatabase::NewL(EDatabaseTypeIAP);
		CleanupStack::PushL(db);
	
	CCommsDbTableView* table = db->OpenViewMatchingUintLC(TPtrC(DIAL_OUT_ISP), TPtrC(COMMDB_ID), id1);

	if (table->GotoFirstRecord() == KErrNone)
		table->DeleteRecord();

	CleanupStack::PopAndDestroy(table);
	table = NULL;
	table = db->OpenViewMatchingUintLC(TPtrC(DIAL_OUT_ISP), TPtrC(COMMDB_ID), id2);

	if (table->GotoFirstRecord() == KErrNone)
		table->DeleteRecord();

	CleanupStack::PopAndDestroy(2);

	Log(_L("IAP Entries Deleted Successfully"));

	delete globals;
	CTS_EncrptStep::Set(NULL);
	
	return EPass;
	}








