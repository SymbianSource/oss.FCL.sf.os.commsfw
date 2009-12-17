// Copyright (c) 2007-2009 Nokia Corporation and/or its subsidiary(-ies).
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
// Implementation of those test steps for bearermobility covering the AO based API which is not suitable for
// testing under esock test steps
// 
//

/**
 @file te_BearerMobilityTestSuite.cpp
 @file
*/

#include "te_BearerMobilityTestSuite.h"
#include <ecom/ecom.h>


using namespace ESock;

// CBearerMobilityTestStep_761402
//-------------------------------
static const TInt KPreferredAccessPointId = 4;
static const TInt KLessPreferredAccessPointId = 5;

static const TInt KSnapTwoPreferences = 15;

enum TVerdict CBearerMobilityTestStep_761402::doTestStepL(void)
	{
	// Create and install an active scheduler as we are testing an AO api
	CActiveScheduler* scheduler = new(ELeave) CActiveScheduler;
	CleanupStack::PushL(scheduler);
	CActiveScheduler::Install(scheduler);

	// Create and connect the socket server
	TInt err;
	err = iSocketServ.Connect();
	TESTEL(err == KErrNone, err);

	// Create and open the connection
	err = iConnection.Open(iSocketServ);
	TESTEL(err == KErrNone, err);

	// Set the availability of each access point of significance
	SetAvailabilityL(
		KPreferredAccessPointId,
		TAvailabilityStatus(TAvailabilityStatus::EMaxAvailabilityScore));
	SetAvailabilityL(
		KLessPreferredAccessPointId,
		TAvailabilityStatus(TAvailabilityStatus::EMaxAvailabilityScore));
	
	// Start the connection
	TCommSnapPref prefs;
	prefs.SetSnap(KSnapTwoPreferences);
	err = iConnection.Start(prefs);
	TESTEL(err == KErrNone, err);

	// Now create the mobility notification AO
	iMobilityExtension = CActiveCommsMobilityApiExt::NewL(iConnection, *this);

	// Make the preferred become unavailable
	SetAvailabilityL(KPreferredAccessPointId, TAvailabilityStatus(TAvailabilityStatus::EMinAvailabilityScore));

	// Bump the state
	BumpTestStepState();

	// Start the scheduler which will ultimately run the rest of the test
	TRAP_IGNORE(CActiveScheduler::Start())
	
	CleanupStack::PopAndDestroy(scheduler);
	
	iConnection.Close();
	iSocketServ.Close();

	return TestStepResult();
	}

// From MMobilityProtocolResp
void CBearerMobilityTestStep_761402::PreferredCarrierAvailable(TAccessPointInfo aOldAP, TAccessPointInfo aNewAP, TBool aIsUpgrade, TBool aIsSeamless)
	{
	switch(GetTestStepState())
		{
		case 1:
			// Check that we got what we expected
			TEST(aOldAP == KPreferredAccessPointId);
			TEST(aNewAP == KLessPreferredAccessPointId);
			TEST(aIsUpgrade == EFalse);
			TEST(aIsSeamless == EFalse);

			// Arrange for migration
			iMobilityExtension->MigrateToPreferredCarrier();

			BumpTestStepState();
			break;

		default:
			INFO_PRINTF1(KErrTestStepAstray);
			SetTestStepResult(EFail);
			break;
		}
	}

void CBearerMobilityTestStep_761402::NewCarrierActive(TAccessPointInfo aNewAP, TBool aIsSeamless)
	{
	switch(GetTestStepState())
		{
		case 2:
			// Check we got what we expected first
			TEST(aNewAP == KLessPreferredAccessPointId);
			TEST(aIsSeamless == EFalse);

			// Accept the new carrier and we are done so stop the scheduler
			iMobilityExtension->NewCarrierAccepted();
			CActiveScheduler::Stop();

			BumpTestStepState();
			break;

		default:
			INFO_PRINTF1(KErrTestStepAstray);
			SetTestStepResult(EFail);
			break;
		}
	}

void CBearerMobilityTestStep_761402::Error(TInt aError)
	{
	// Most likely a cancel but check for any kind of error
	if(aError == KErrCancel)
		{
		INFO_PRINTF1(_L("Mobility extension cancelled"));
		}
	else
		{
		// Some kind of unexpected error during mobility migration
		INFO_PRINTF2(_L("Unexpected error (ordinarily KErrCancel) from mobility extension. error:%d"), aError);
		SetTestStepError(aError);
		}
	}


// CBearerMobilityTestStep_761403
//-------------------------------

enum TVerdict CBearerMobilityTestStep_761403::doTestStepL(void)
	{
	// Fail by default
	SetTestStepResult(EFail);
	
	// Create and connect the socket server
	TInt err;
	RSocketServ sockServ;
	err = sockServ.Connect();
	TESTEL(err == KErrNone, err);

	// Create and open the connection
	RConnection conn;
	err = conn.Open(sockServ);
	TESTEL(err == KErrNone, err);

	// Set the availability of each access point of significance
	SetAvailabilityL(KPreferredAccessPointId, TAvailabilityStatus(TAvailabilityStatus::EMaxAvailabilityScore));
	SetAvailabilityL(KLessPreferredAccessPointId, TAvailabilityStatus(TAvailabilityStatus::EMaxAvailabilityScore));
	
	// Start the connection
	TCommSnapPref prefs;
	prefs.SetSnap(KSnapTwoPreferences);
	err = conn.Start(prefs);
	TESTEL(err == KErrNone, err);

	// Attach a subconn to the default
	RSubConnection subConn;
	err = subConn.Open(sockServ, RSubConnection::EAttachToDefault, conn);
	TESTEL(err == KErrNone, err);

	// Now create the mobility notification and try to open on the subconnection!
	RCommsMobilityApiExt mobExtension;
	err = mobExtension.Open(subConn);
	if(err == KErrNotSupported)
		{
		INFO_PRINTF1(_L("Received KErrNotSupported as expected"));
		SetTestStepResult(EPass);
		}
	else
		{
		INFO_PRINTF2(_L("Negative test: Expect KErrNotSupported. error:%d"), err);
		SetTestStepError(err);
		}
	
	// Close the resources we opened and out of here
	subConn.Close();
	conn.Close();
	sockServ.Close();

	return TestStepResult();
	}

// CBearerMobilityTestStepBase
//----------------------------
const TUid KAvailabilityTestingPubSubUid = {0x10272F42};

void CBearerMobilityTestStepBase::SetAvailabilityL(TInt aAccessPointId, ESock::TAvailabilityStatus aStatus)
	{
	RProperty a;

	// Set the availability of the access point as prescribed
	TInt error = a.Define(KAvailabilityTestingPubSubUid, aAccessPointId, RProperty::EInt);
	if((error != KErrAlreadyExists) && (error != KErrNone))
		{
		INFO_PRINTF1(_L("Could not define property used for availability simulation"));
		User::Leave(KErrGeneral);
		}
	
	// Successfully created the property so attach to it for use
	error = a.Attach(KAvailabilityTestingPubSubUid, aAccessPointId);
	TESTEL(error == KErrNone, error);

	// Now set the availability as prescribed
	a.Set(aStatus.Score());
	}


// Entry point
//------------

LOCAL_C void MainL()
	{
	CActiveScheduler* sched=NULL;
	sched=new(ELeave) CActiveScheduler;
	CActiveScheduler::Install(sched);
	CBearerMobilitySuiteTestServer* server = NULL;

	// Create the CTestServer derived server
	TRAPD(err, server = CBearerMobilitySuiteTestServer::NewL());
	if(!err)
		{
		// Sync with the client and enter the active scheduler
		RProcess::Rendezvous(KErrNone);
		sched->Start();
		}
	delete server;
	delete sched;
	}



GLDEF_C TInt E32Main()
/**
 * @return - Standard Epoc error code on process exit
 * Secure variant only
 * Process entry point. Called by client using RProcess API
 */
	{
	__UHEAP_MARK;
	CTrapCleanup* cleanup = CTrapCleanup::New();
	if(cleanup == NULL)
		{
		return KErrNoMemory;
		}
	TRAPD(err,MainL());
	delete cleanup;
	REComSession::FinalClose();
	__UHEAP_MARKEND;
	return err;
    }




// Test suite server
//------------------

_LIT(KServerName, "te_BearerMobilityTestSuite");

CBearerMobilitySuiteTestServer* CBearerMobilitySuiteTestServer::NewL()
/**
 * @return - Instance of the test server
 * Same code for Secure and non-secure variants
 * Called inside the MainL() function to create and start the
 * CTestServer derived server.
 */
	{
	CBearerMobilitySuiteTestServer* server = new (ELeave) CBearerMobilitySuiteTestServer();
	CleanupStack::PushL(server);
	server->ConstructL(KServerName);
	CleanupStack::Pop();
	return server;
	}
	
CBearerMobilitySuiteTestServer::~CBearerMobilitySuiteTestServer()
	{
	}
	
CTestStep* CBearerMobilitySuiteTestServer::CreateTestStep(const TDesC& aStepName)
/**
 * @return - A CTestStep derived instance
 * Implementation of CTestServer pure virtual
 */
	{
	CTestStep* testStep = NULL;
	if(aStepName.Compare(_L("NET_BMOBILITY_761402")) == 0)
		testStep = new CBearerMobilityTestStep_761402();
	else if(aStepName.Compare(_L("NET_BMOBILITY_761403")) == 0)
		testStep = new CBearerMobilityTestStep_761403();
	
	return testStep;
	}

