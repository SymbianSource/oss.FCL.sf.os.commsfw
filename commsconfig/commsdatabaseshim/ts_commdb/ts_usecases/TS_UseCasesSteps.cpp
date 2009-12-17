// Copyright (c) 2001-2009 Nokia Corporation and/or its subsidiary(-ies).
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
// Use cases as in the commdb design overview
// 
//

#include <e32test.h>
#include <f32file.h>
#include <commdb.h>
#include <cdbover.h>
#include <cdbtemp.h>

#include "TS_UseCasesSteps.h"

//
CTS_CreatingDatabaseAndView::CTS_CreatingDatabaseAndView()
	{
	iTestStepName = KCreatingDatabaseAndView;
	}

CTS_CreatingDatabaseAndView::~CTS_CreatingDatabaseAndView()
	{	
	}

enum TVerdict CTS_CreatingDatabaseAndView::doTestStepL()
	{
		
	CCommsDbTableView* view;
	CCommsDatabase* db = CCommsDatabase::NewL();
	const TPtrC kTable1(DIAL_OUT_ISP);
	const TPtrC kColumn1(ISP_TYPE);
	view = db->OpenViewMatchingUintLC(kTable1, kColumn1, EIspTypeInternetOnly);
	CleanupStack::Pop(view);

	// Allocate global storage to be held in tls.
	TGlobalData*  globals=new(ELeave) TGlobalData ;
	globals->iDb = db;
	globals->iView = view;
	CTS_UseCasesStep::Set(globals);

	return EPass;
	}

//
CTS_UsecaseReading::CTS_UsecaseReading()
	{
	iTestStepName = KUsecaseReading;
	}

CTS_UsecaseReading::~CTS_UsecaseReading()
	{	
	}

enum TVerdict CTS_UsecaseReading::doTestStepL()
	{

	TGlobalData* globals = CTS_UseCasesStep::Get();
	CCommsDbTableView* view= globals->iView;  
		
	const TPtrC kColumn(ISP_DESCRIPTION);

	TBuf<KCommsDbSvrMaxFieldLength> description;

	view->GotoFirstRecord();
	view->ReadTextL(kColumn, description);
	
	return EPass;
	}

//
CTS_UsecaseWriting::CTS_UsecaseWriting()
	{
	iTestStepName = KUsecaseWriting;
	}

CTS_UsecaseWriting::~CTS_UsecaseWriting()
	{	
	}

enum TVerdict CTS_UsecaseWriting::doTestStepL()
	{
	
	TGlobalData* globals = CTS_UseCasesStep::Get();
	CCommsDbTableView* view= globals->iView;  
	
	const TPtrC kColumn(ISP_DESCRIPTION);
	const TPtrC kDescription(_L("A new description put in by t_usecases"));

	TInt ret = view->GotoNextRecord();
	if(ret == KErrNone)
		{
		ret = view->UpdateRecord();
		if(ret == KErrNone)
			{
			view->WriteTextL(kColumn, kDescription);
			view->PutRecordChanges();
			}
		}

	return EPass;
	}

//
CTS_UsecaseOverridingATableEntry::CTS_UsecaseOverridingATableEntry()
	{
	iTestStepName = KUsecaseOverridingATableEntry;
	}

CTS_UsecaseOverridingATableEntry::~CTS_UsecaseOverridingATableEntry()
	{	
	}

enum TVerdict CTS_UsecaseOverridingATableEntry::doTestStepL()
	{
	const TPtrC kTable(DIAL_OUT_ISP);
	const TPtrC kColumn(ISP_DESCRIPTION);
	const TPtrC kOverride(_L("An overriden description"));
	TBuf<KCommsDbSvrMaxFieldLength> overridenValue;

	CCommDbOverrideSettings *override;
	override = CCommDbOverrideSettings::NewL(CCommDbOverrideSettings::EParamListPartial);
	CleanupStack::PushL(override);

	override->SetDesOverride(kTable, kColumn, kOverride);

	if (override->GetDesOverride(kTable, kColumn, overridenValue) != KErrNone)
		{
		User::Leave(__LINE__);
		}
	if (overridenValue != kOverride)
		{
		User::Leave(__LINE__);
		}

	CleanupStack::PopAndDestroy(override);

	return EPass;
	}

//
CTS_UsecaseOverridingThePreferenceTable::CTS_UsecaseOverridingThePreferenceTable()
	{
	iTestStepName = KUsecaseOverridingThePreferenceTable;
	}

CTS_UsecaseOverridingThePreferenceTable::~CTS_UsecaseOverridingThePreferenceTable()
	{	
	}

enum TVerdict CTS_UsecaseOverridingThePreferenceTable::doTestStepL()
	{
	CCommsDbConnectionPrefTableView::TCommDbIapConnectionPref overrideSettings;
	CCommsDbConnectionPrefTableView::TCommDbIapConnectionPref overridenValue;

	CCommDbOverrideSettings* override;
	override = CCommDbOverrideSettings::NewL(CCommDbOverrideSettings::EParamListPartial);
	CleanupStack::PushL(override);

	overrideSettings.iDialogPref = ECommDbDialogPrefPrompt;
	overrideSettings.iRanking = 1;
	overrideSettings.iDirection = ECommDbConnectionDirectionOutgoing;
	override->SetConnectionPreferenceOverride(overrideSettings);

	overridenValue.iRanking = 1;
	override->GetConnectionPreferenceOverride(overridenValue);

	if (!(overrideSettings == overridenValue))
		{
		User::Leave(__LINE__);
		}

	CleanupStack::PopAndDestroy(override);

	return EPass;
	}

//
CTS_UsecaseUsingATemplate::CTS_UsecaseUsingATemplate()
	{
	iTestStepName = KUsecaseUsingATemplate;
	}

CTS_UsecaseUsingATemplate::~CTS_UsecaseUsingATemplate()
	{	
	}

enum TVerdict CTS_UsecaseUsingATemplate::doTestStepL()
	{

	TGlobalData* globals = CTS_UseCasesStep::Get();
	CCommsDatabase* db = globals->iDb;
	CCommsDbTableView* view= globals->iView; 
	
	const TPtrC kTable(DIAL_OUT_ISP);
	const TPtrC kColumn(ISP_DESCRIPTION);
	const TPtrC kDescription(_L("A default description put in by t_usecases"));

	CCommsDbTemplateRecord* temp;
	temp = CCommsDbTemplateRecord::NewL(db, kTable);
	CleanupStack::PushL(temp);

	temp->Modify();
	temp->WriteTextL(kColumn, kDescription);
	temp->StoreModifications();
	
	CleanupStack::PopAndDestroy(temp);
	 
	delete view; 
	delete db;		
	delete globals;
	CTS_UseCasesStep::Set(NULL);
	
	return EPass;
	}
