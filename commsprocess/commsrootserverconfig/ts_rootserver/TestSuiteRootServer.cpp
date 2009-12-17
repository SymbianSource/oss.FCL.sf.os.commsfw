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
// This main DLL entry point for the TS_RootServer.dll
// 
//


// EPOC includes
#include <e32base.h>

// RootServer includes
#include <rsshared.h>

// Test system includes
#include <comms-infras/commsdebugutility.h>
#include <networking/teststep.h>
#include "TestStepRootServer.h"
#include "TestSuiteRootServer.h"
#include "TestAsynchHandler.h"
#include "RootServerTestSection1.h"
#include "RootServerTestSection2.h"
#include "RootServerTestSection3.h"
#include "RootServerTestSection4.h"
#include "RootServerTestSection5.h"
#include "RootServerTestSection6.h"
#include "RootServerTestSection7.h"
#include "RootServerTestSection8.h"

_LIT(KRootServerExe, "c32exe.exe");
_LIT(KRootServerProcessPattern, "c32exe*");

EXPORT_C CTestSuiteRootServer* NewTestSuiteRootServer( void ) 
    {
	return new (ELeave) CTestSuiteRootServer;
    }

CTestSuiteRootServer::CTestSuiteRootServer()
	{
	}

// destructor
CTestSuiteRootServer::~CTestSuiteRootServer()
	{
	}


// Add a test step into the suite
void CTestSuiteRootServer::AddTestStepL( CTestStepRootServer * ptrTestStep )
{
	// test steps contain a pointer back to the suite which owns them
	ptrTestStep->iRootServerSuite = this; 

	// add the step using the base class method
	CTestSuite::AddTestStepL(ptrTestStep);
}

// make a version string available for test system 
TPtrC CTestSuiteRootServer::GetVersion( void )
	{

#ifdef _DEBUG
	_LIT(KTxtVersion,"1.00 (udeb)");
#else
	_LIT(KTxtVersion,"1.00");
#endif

	return KTxtVersion();
	}


// second phase constructor for RootServer test suite
// this creates all the ESOCK test steps and
// stores them inside CTestSuiteRootServer
void CTestSuiteRootServer::InitialiseL( void )
	{
	// add test steps
	AddTestStepL( new(ELeave) CRootServerTest1_1 );
	AddTestStepL( new(ELeave) CRootServerTest1_2 );
	AddTestStepL( new(ELeave) CRootServerTest2_1 );
	AddTestStepL( new(ELeave) CRootServerTest2_2 );
	AddTestStepL( new(ELeave) CRootServerTest2_3 );	
//	AddTestStepL( new(ELeave) CRootServerTest3_1 );
	AddTestStepL( new(ELeave) CRootServerTest3_2 );
	AddTestStepL( new(ELeave) CRootServerTest3_3 );
	AddTestStepL( new(ELeave) CRootServerTest3_4 );
	AddTestStepL( new(ELeave) CRootServerTest3_5 );
	AddTestStepL( new(ELeave) CRootServerTest3_6 );
	AddTestStepL( new(ELeave) CRootServerTest3_7 );
	AddTestStepL( new(ELeave) CRootServerTest3_8 );
	AddTestStepL( new(ELeave) CRootServerTest3_9 );
	AddTestStepL( new(ELeave) CRootServerTest3_10 );
	AddTestStepL( new(ELeave) CRootServerTest3_11 );
	AddTestStepL( new(ELeave) CRootServerTest3_12 );
	AddTestStepL( new(ELeave) CRootServerTest3_13 );
	AddTestStepL( new(ELeave) CRootServerTest3_14 );
	AddTestStepL( new(ELeave) CRootServerTest3_15 );
	AddTestStepL( new(ELeave) CRootServerTest3_16 );
	AddTestStepL( new(ELeave) CRootServerTest3_17 );
	AddTestStepL( new(ELeave) CRootServerTest3_18 );
	AddTestStepL( new(ELeave) CRootServerTest4_1 );
	AddTestStepL( new(ELeave) CRootServerTest5_1 );
	AddTestStepL( new(ELeave) CRootServerTest5_2 );
	AddTestStepL( new(ELeave) CRootServerTest5_3 );
	AddTestStepL( new(ELeave) CRootServerTest5_4 );
	AddTestStepL( new(ELeave) CRootServerTest5_5 );
	AddTestStepL( new(ELeave) CRootServerTest5_6 );
	AddTestStepL( new(ELeave) CRootServerTest5_7 );
	AddTestStepL( new(ELeave) CRootServerTest5_8 );
	AddTestStepL( new(ELeave) CRootServerTest6_1 );
	AddTestStepL( new(ELeave) CRootServerTest6_2 );
	AddTestStepL( new(ELeave) CRootServerTest6_3 );
	AddTestStepL( new(ELeave) CRootServerTest6_4 );
	AddTestStepL( new(ELeave) CRootServerTest6_5 );
	AddTestStepL( new(ELeave) CRootServerTest6_6 );
	AddTestStepL( new(ELeave) CRootServerTest6_7 );
	AddTestStepL( new(ELeave) CRootServerTest6_8 );
	AddTestStepL( new(ELeave) CRootServerTest6_9 );
	AddTestStepL( new(ELeave) CRootServerTest6_10 );
	AddTestStepL( new(ELeave) CRootServerTest6_11 );
	AddTestStepL( new(ELeave) CRootServerTest6_12 );
	AddTestStepL( new(ELeave) CRootServerTest6_13 );
	AddTestStepL( new(ELeave) CRootServerTest6_14 );
	AddTestStepL( new(ELeave) CRootServerTest6_15 );
	AddTestStepL( new(ELeave) CRootServerTest6_16 );
	AddTestStepL( new(ELeave) CRootServerTest7_1 );
	AddTestStepL( new(ELeave) CRootServerTest7_2 );
	AddTestStepL( new(ELeave) CRootServerTest7_3 );
	AddTestStepL( new(ELeave) CRootServerTest7_4 );
	AddTestStepL( new(ELeave) CRootServerTest8_1 );

	iNextServerNumber = 0;
	}

TInt CTestSuiteRootServer::StartRootServer()
/**
 * Start the Root Server and connect the standard session to it
 *
 * @return TInt - An error code
 */
    {    
    TInt err = KErrNone;
    TFindServer findCS(KRootServerName);
    TFullName name;
    RProcess rootServer;

    if (findCS.Next(name) == KErrNone)
		{
		Log(_L("Shutting down existing RootServer"));

		// Try to shutdown any existing instance of the rootserver so we can
		// safely change the MBuf pool size before any modules are loaded.
		// A sticky module such as ETel may prevent complete shutdown so we
		// kill the process if necessary.
		if(!ShutdownRootServer())
			{
			Log(_L("Killing existing RootServer"));

			// Kill the rootserver process if normal shutdown fails.
			TFindProcess findPS(KRootServerProcessPattern);
			err = findPS.Next(name);
			if(err == KErrNone)
				{
	 			err = rootServer.Open(findPS);
	 			if(err == KErrNone)
	 				{
		 			TRequestStatus status;
					rootServer.Logon(status);
					rootServer.Kill(KErrNone);
					User::WaitForRequest(status);
					
					// Create a timer in case some other entity holds an open handle on the
					// configurator which prevents the kernel from destroying it.  We timeout
					// after one second.
					TAutoClose<RTimer> timer;
					if(timer.iObj.CreateLocal() == KErrNone)
						{
						// Request destruction notification so we know when it is safe to start
						// the process again.
						TRequestStatus destructionStatus;
						rootServer.NotifyDestruction(destructionStatus);
						rootServer.Close();
					
						enum{ KProcessDestructionTimeout = 1000000 };
				  					
						TRequestStatus timerStatus;
						timer.iObj.After(timerStatus, KProcessDestructionTimeout);
						
						// Wait for the process to be destroyed or for the timeout.
						User::WaitForRequest(destructionStatus, timerStatus);
						if(timerStatus.Int() == KRequestPending)
							{
							timer.iObj.Cancel();
							User::WaitForRequest(timerStatus);
							}
						else
							{
							User::CancelMiscNotifier(destructionStatus);
							User::WaitForRequest(destructionStatus);
							
							Log(_L("CTestSuiteRootServer::StartRootServer - existing RootServer process has still not been destroyed after %f.0s"), KProcessDestructionTimeout / 1000000.0);
							}
						}
	 				}
				}
			}
		}
	else
		{
	    err = rootServer.Create(KRootServerExe, KNullDesC);
		TRequestStatus status;
	    if (err == KErrNone)
			{
			rootServer.Rendezvous(status);
			rootServer.Resume();
			User::WaitForRequest(status);
			rootServer.Close();
			err = status.Int();
			}
		if(err == KErrNone)
			{
			err = RootSess().Connect();
			}
		}

    return err;
    }


TBool CTestSuiteRootServer::ShutdownRootServer()
/**
 * Tell the Root Server to shutdown via its standard session, and validate that it did so.
 *
 * @return TBool - True if shutdown was successful
 */
    {
	TInt err;
	// Some tests close the session
	if(RootSess().Handle() == 0)
		{
		err = RootSess().Connect();
		if(err != KErrNone)
			{
			Log(_L("Failed to reconnect session (err %d) - maybe dead already?"), err);
			return EFalse;
			}
		}

	TRSIter position;
	while((err = RootSess().Shutdown()) == KErrRSModulesStillRunning)
		{
		TCFModuleName moduleName;
		err = RootSess().EnumerateModules(position, moduleName);
		if(err == KErrEof)
			{
			Log(_L("RRootServ::Shutdown could not be completed, probably due to the presence of sticky modules"));
			return EFalse;
			}
		TRSModuleInfo moduleInfo;
		err = RootSess().GetModuleInfo(moduleName, moduleInfo);
		if(err == KErrRSModuleUnknown)
			continue;	// an unload probably just completed
		else if(err != KErrNone)
			{
			Log(_L("RRootServ::GetModuleInfo failed during shutdown"));
			return EFalse;
			}
		TBuf<KCFMaxModuleName> wideModuleName;
		wideModuleName.Copy(moduleName);
		Log(_L("RRootServ::Shutdown in progress; need to unload %S (state %d)"), &wideModuleName, moduleInfo().iState);
		TRequestStatus status;
		switch(moduleInfo().iState)
			{
			case EStarting:		// treat a starting module as a zombie coz we're in a hurry, and who knows how long that rendezvous could take?
			case EZombie:
				{
				RootSess().UnloadCpm(status, moduleName, EUnGraceful);
				User::WaitForRequest(status);
				if(status != KErrNone && status != KErrRSSuddenDeath && status != KErrRSModuleUnknown)
					{
					Log(_L("RRootServ::Shutdown failed, zombie could not be killed"));
					return EFalse;
					}
				break;
				}
			case ERunning:
				{
				RootSess().UnloadCpm(status, moduleName, EGraceful);
				User::WaitForRequest(status);
				if(status.Int() == KErrLocked)
					{
					Log(_L("Module is sticky and cannot be unloaded"));
					
					// Move to the next module.
					continue;
					}
				else
					{
					Log(_L("UnloadCPM returned %d"), status.Int());
					}
				break;	// either it worked or it should have become a zombie
				}
			case EStopping:
				{
				// transition states; snooze and try again
				User::After(1000000);
				break;
				}
			default:
				{
				Log(_L("RRootServ::Shutdown failed, module in improper states"));
				return EFalse;
				}
			}
			
			// Try to unload this module again.
			position.Reset();
		}
	RootSess().Close();
	RRootServ probeSess;
	TBool res = (probeSess.Connect() != KErrNone);
	if(!res)
		{
		probeSess.Close();
		}

    return res;
    }



CSelfPopScheduler* CSelfPopScheduler::CreateLC()
	{
	CSelfPopScheduler* self = new(ELeave)CSelfPopScheduler;
	CleanupStack::PushL(self);
	CActiveScheduler::Install(self);
	return self;
	}

CSelfPopScheduler::operator TCleanupItem()
	{
	return TCleanupItem(Cleanup, this);
	}

void CSelfPopScheduler::Cleanup(TAny* aItem)
	{
	CActiveScheduler::Install(NULL);
	delete reinterpret_cast<CSelfPopScheduler*>(aItem);
	}


