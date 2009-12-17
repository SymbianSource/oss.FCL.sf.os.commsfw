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
// This contains CTestSuiteRootServer 
// This is the container class for all the RootServer test steps
// 
//

#if (!defined __TESTSUITROOTSERVER_H__)
#define __TESTSUITROOTSERVER_H__

#include <networking/testsuite.h>
#include <c32root.h>

class  CTestSuiteRootServer : public CTestSuite
{
public:
	void InitialiseL( void );
	CTestSuiteRootServer();
	~CTestSuiteRootServer();
	
	void AddTestStepL( CTestStepRootServer * ptrTestStep );
	TPtrC GetVersion( void );

	TInt StartRootServer();
	TBool ShutdownRootServer();

	RRootServ& RootSess()
		{
		return iRootServer;
		}
	TInt NextServerNumber()
		{
		return iNextServerNumber++;
		}

//	RRootServ iRootServer;


private:
	RRootServ iRootServer;
	TInt iNextServerNumber;
};



// CSelfPopScheduler - thin extension of CActiveScheduler to give useful installation & removal cleanup-stack behaviour
class CSelfPopScheduler : public CActiveScheduler
	{
public:
	static CSelfPopScheduler* CreateLC();
	operator TCleanupItem();
private:
	static void Cleanup(TAny* aItem);
	};
#endif /* __TESTSUITROOTSERVER_H__ */

