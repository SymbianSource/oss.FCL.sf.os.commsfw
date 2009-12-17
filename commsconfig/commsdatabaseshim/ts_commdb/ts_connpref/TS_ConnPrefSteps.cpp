// Copyright (c) 2006-2009 Nokia Corporation and/or its subsidiary(-ies).
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

#include <commdbconnpref.h>
#include <e32test.h>

#include "TS_ConnPrefSteps.h"

CTS_ConstructAndVersion::CTS_ConstructAndVersion()
	{
	iTestStepName = KConstructAndVersion;
	}

CTS_ConstructAndVersion::~CTS_ConstructAndVersion()
	{	
	}

enum TVerdict CTS_ConstructAndVersion::doTestStepL()
	{

	TCommDbConnPref connPref;

	Test(connPref.ExtensionId() == TConnPref::EConnPrefCommDb);		
	TVersion ver = connPref.Version();
	Test(ver.iMajor == TCommDbMultiConnPref::KMajorVersionNumber);		
	Test(ver.iMinor == TCommDbMultiConnPref::TCommDbMultiConnPref::KMinorVersionNumber);		
	Test(ver.iBuild == TCommDbMultiConnPref::TCommDbMultiConnPref::KBuildVersionNumber);
	Test(connPref.BearerSet() == KCommDbBearerUnknown);		
	Test(connPref.DialogPreference() == ECommDbDialogPrefUnknown);		
	Test(connPref.Direction() == ECommDbConnectionDirectionUnknown);
	Test(connPref.IapId() == 0);		
	Test(connPref.NetId() == 0);
	
	return EPass;
	}

CTS_SetAndGetConnPrefs::CTS_SetAndGetConnPrefs()
	{
	iTestStepName = KSetAndGetConnPrefs; 
	}

CTS_SetAndGetConnPrefs::~CTS_SetAndGetConnPrefs()
	{	
	}

enum TVerdict CTS_SetAndGetConnPrefs::doTestStepL()
	{

	TCommDbConnPref connPref;

	connPref.SetBearerSet((KCommDbBearerWcdma | KCommDbBearerLAN));
	Test(connPref.BearerSet() == (KCommDbBearerWcdma | KCommDbBearerLAN));

	connPref.SetDialogPreference(ECommDbDialogPrefDoNotPrompt);
	Test(connPref.DialogPreference() == ECommDbDialogPrefDoNotPrompt);

	connPref.SetDirection(ECommDbConnectionDirectionOutgoing);
	Test(connPref.Direction() == ECommDbConnectionDirectionOutgoing);

	connPref.SetIapId(123);
	Test(connPref.IapId() == 123);

	connPref.SetNetId(456);
	Test(connPref.NetId() == 456);

	return EPass;
	}


CTS_ComparePrefs::CTS_ComparePrefs()
	{
	iTestStepName = KComparePrefs; 
	}

CTS_ComparePrefs::~CTS_ComparePrefs()
	{	
	}

enum TVerdict CTS_ComparePrefs::doTestStepL()
	{
	
	TCommDbConnPref connPref1;
	connPref1.SetBearerSet((KCommDbBearerWcdma | KCommDbBearerLAN));
	connPref1.SetDialogPreference(ECommDbDialogPrefDoNotPrompt);
	connPref1.SetDirection(ECommDbConnectionDirectionOutgoing);
	connPref1.SetIapId(123);
	connPref1.SetNetId(456);

	TCommDbConnPref connPref2;
	connPref2.SetBearerSet((KCommDbBearerWcdma | KCommDbBearerLAN));
	connPref2.SetDialogPreference(ECommDbDialogPrefDoNotPrompt);
	connPref2.SetDirection(ECommDbConnectionDirectionOutgoing);
	connPref2.SetIapId(123);
	connPref2.SetNetId(456);

	TCommDbConnPref connPref3;
	connPref3.SetBearerSet(KCommDbBearerCSD);
	connPref3.SetDialogPreference(ECommDbDialogPrefWarn);
	connPref3.SetDirection(ECommDbConnectionDirectionIncoming);
	connPref3.SetIapId(987);
	connPref3.SetNetId(654);

	TCommDbConnPref connPref4;
	connPref4.SetBearerSet(KCommDbBearerCSD);
	connPref4.SetDirection(ECommDbConnectionDirectionIncoming);
	connPref4.SetNetId(654);	

	Test(connPref2.Compare(connPref1) == 0);
	Test(connPref2 == connPref1);

	Test(connPref1.Compare(connPref2) == 0);
	Test(connPref1 == connPref2);

	Test(connPref1.Compare(connPref1) == 0);
	Test(connPref1 == connPref1);

	Test(connPref3.Compare(connPref1) != 0);
	Test(connPref3 != connPref1);

	Test(connPref1.Compare(connPref3) != 0);
	Test(connPref1 != connPref3);

	Test(connPref4 == connPref3);
	Test(connPref3 == connPref4);

	Test(connPref4 != connPref2);
	Test(connPref2 != connPref4);

	return EPass;
	}

CTS_AssignAndCopyConstruct::CTS_AssignAndCopyConstruct()
	{
	iTestStepName = KAssignAndCopyConstruct; 
	}

CTS_AssignAndCopyConstruct::~CTS_AssignAndCopyConstruct()
	{	
	}

enum TVerdict CTS_AssignAndCopyConstruct::doTestStepL()
	{

	TCommDbConnPref connPref1;
	connPref1.SetBearerSet((KCommDbBearerWcdma | KCommDbBearerLAN));
	connPref1.SetDialogPreference(ECommDbDialogPrefDoNotPrompt);
	connPref1.SetDirection(ECommDbConnectionDirectionOutgoing);
	connPref1.SetIapId(123);
	connPref1.SetNetId(456);

	TCommDbConnPref connPref2(connPref1);
	Test(connPref2.Compare(connPref1) == 0);
	Test(connPref1.Compare(connPref2) == 0);

	TCommDbConnPref connPref3 = connPref1;
	Test(connPref3.Compare(connPref1) == 0);
	Test(connPref1.Compare(connPref3) == 0);

	TCommDbConnPref connPref4;
	connPref4 = connPref1;
	Test(connPref4.Compare(connPref1) == 0);
	Test(connPref1.Compare(connPref4) == 0);

	return EPass;
	}

CTS_ExtensionIdAndCast::CTS_ExtensionIdAndCast()
	{
	iTestStepName = KExtensionIdAndCast; 
	}

CTS_ExtensionIdAndCast::~CTS_ExtensionIdAndCast()
	{	
	}

enum TVerdict CTS_ExtensionIdAndCast::doTestStepL()
	{

	TCommDbConnPref commdbPref1;
	commdbPref1.SetBearerSet((KCommDbBearerWcdma | KCommDbBearerLAN));
	commdbPref1.SetDialogPreference(ECommDbDialogPrefDoNotPrompt);
	commdbPref1.SetDirection(ECommDbConnectionDirectionOutgoing);
	commdbPref1.SetIapId(123);
	commdbPref1.SetNetId(456);

	TConnPref basePref(commdbPref1);
	Test(basePref.ExtensionId() == TConnPref::EConnPrefCommDb);

	TCommDbConnPref commdbPref2 = TCommDbConnPref::Cast(basePref);
	Test(commdbPref2 == commdbPref1);
	
	return EPass;
	}


CTS_MultiConnPref::CTS_MultiConnPref()
	{
	iTestStepName = KMultiConnPref; 
	}

CTS_MultiConnPref::~CTS_MultiConnPref()
	{	
	}

enum TVerdict CTS_MultiConnPref::doTestStepL()
	{

	TCommDbConnPref connPref1;
	connPref1.SetBearerSet((KCommDbBearerWcdma | KCommDbBearerLAN));
	connPref1.SetDialogPreference(ECommDbDialogPrefDoNotPrompt);
	connPref1.SetDirection(ECommDbConnectionDirectionOutgoing);
	connPref1.SetIapId(123);
	connPref1.SetNetId(456);

	TCommDbConnPref connPref2;
	connPref2.SetBearerSet(KCommDbBearerCSD);
	connPref2.SetDialogPreference(ECommDbDialogPrefWarn);
	connPref2.SetDirection(ECommDbConnectionDirectionIncoming);
	connPref2.SetIapId(987);
	connPref2.SetNetId(654);

	TCommDbMultiConnPref multiPref;
	TInt err(KErrNone);

	err = multiPref.SetPreference(0, connPref1);
	Test(err == KErrArgument);
	
	err = multiPref.SetPreference(1, connPref1);
	Test(err == KErrNone);

	err = multiPref.SetPreference(2, connPref2);
	Test(err == KErrNone);

	err = multiPref.SetPreference(3, connPref2);
	Test(err == KErrArgument);

	TCommDbConnPref connPref3;

	err = multiPref.GetPreference(0, connPref3);
	Test(err == KErrArgument);

	err = multiPref.GetPreference(1, connPref3);
	Test(err == KErrNone);
	Test(connPref3 == connPref1);

	err = multiPref.GetPreference(2, connPref3);
	Test(err == KErrNone);
	Test(connPref3 == connPref2);

	err = multiPref.GetPreference(3, connPref3);
	Test(err == KErrArgument);

	TConnPref basePref(multiPref);
	Test(basePref.ExtensionId() == TConnPref::EConnPrefCommDbMulti);

	TCommDbMultiConnPref multiPref2;	
	TCommDbConnPref connPref4;
	err = multiPref2.GetPreference(1, connPref4);
	Test(err == KErrNone);
	Test(connPref4 == connPref1);

	TCommDbConnPref connPref5;
	err = multiPref2.GetPreference(2, connPref5);
	Test(err == KErrNone);
	Test(connPref5 == connPref2);

	Test(multiPref.ConnectionAttempts()==TCommDbMultiConnPref::KMaxMultiConnPrefCount);

	multiPref.SetConnectionAttempts(0);
	Test(multiPref.ConnectionAttempts()==TCommDbMultiConnPref::KMaxMultiConnPrefCount);

	multiPref.SetConnectionAttempts(1);
	Test(multiPref.ConnectionAttempts()==1);

	multiPref.SetConnectionAttempts(2);
	Test(multiPref.ConnectionAttempts()==2);

	multiPref.SetConnectionAttempts(TCommDbMultiConnPref::KMaxMultiConnPrefCount+1);
	Test(multiPref.ConnectionAttempts()==TCommDbMultiConnPref::KMaxMultiConnPrefCount);

	return EPass;
	}

//
//	Test step CTS_MultiConnPrefVersion
//

// constructor
CTS_MultiConnPrefVersion::CTS_MultiConnPrefVersion()
	{
	// store the name of this test case
	iTestStepName = KMultiConnPrefVersion;
	}

// destructor
CTS_MultiConnPrefVersion::~CTS_MultiConnPrefVersion()
	{
	}

// do Test step CTS_MultiConnPrefVersion
TVerdict CTS_MultiConnPrefVersion::doTestStepL()
	{
	Log(_L("CTS_MultiConnPrefVersion called "));
	iTestStepResult = EFail;
    TCommDbMultiConnPref pref;	
	TVersion dbVersion = pref.Version();
	Log(_L("TCommDbMultiConnPref::Version -> Major=%d, Minor=%d, Build=%d"), TCommDbMultiConnPref::KMajorVersionNumber, TCommDbMultiConnPref::KMinorVersionNumber, TCommDbMultiConnPref::KBuildVersionNumber);	
	//Test for the expected return value
	if ( dbVersion.iMinor == TCommDbMultiConnPref::KMinorVersionNumber && 
         dbVersion.iMajor == TCommDbMultiConnPref::KMajorVersionNumber && 
         dbVersion.iBuild == TCommDbMultiConnPref::KBuildVersionNumber )
		{
		iTestStepResult = EPass;
		}
    return iTestStepResult;
	}
	

//
//	Test step CTS_MultiConnectionAttempts
//

// constructor
CTS_MultiConnectionAttempts::CTS_MultiConnectionAttempts()
	{
	// store the name of this test case
	iTestStepName = KMultiConnectionAttempts;
	}

// destructor
CTS_MultiConnectionAttempts::~CTS_MultiConnectionAttempts()
	{
	}	
	
// do Test step CTS_MultiConnectionAttempts
TVerdict CTS_MultiConnectionAttempts::doTestStepL( )
	{
	Log(_L("Step CTS_MultiConnectionAttempts called "));
	iTestStepResult = EFail;
	TCommDbMultiConnPref prefPtr;	
	TInt numAttempts = prefPtr.ConnectionAttempts();
	Log(_L("Expected NumAttempts:= %d, Actual NumAttempts:=%d"), TCommDbMultiConnPref::KMaxMultiConnPrefCount,numAttempts);
	if(numAttempts != TCommDbMultiConnPref::KMaxMultiConnPrefCount )
		{
	return iTestStepResult;
		}
	numAttempts	 = 3 ;
	prefPtr.SetConnectionAttempts(numAttempts);
	TInt attempsCheck = prefPtr.ConnectionAttempts();
	Log(_L("Expected NumAttempts:= %d, Actual NumAttempts:=%d"), TCommDbMultiConnPref::KMaxMultiConnPrefCount,attempsCheck);
	Log(_L("This test fails because  no. of attempts is > 2"));
	if(numAttempts == attempsCheck )
		{
		iTestStepResult = EFail;
		}
	return iTestStepResult;
	}
	
	
	
	
