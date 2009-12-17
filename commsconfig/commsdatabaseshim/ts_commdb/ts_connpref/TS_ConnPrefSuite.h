/**
* Copyright (c) 2002-2009 Nokia Corporation and/or its subsidiary(-ies).
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
* Header for TS_ConnPrefSuite class. This is the container
* class for all the CommDb ConnPrefSuite test steps
* 
*
*/



/**
 @file TS_ConnPrefSuite.h
*/

#if (!defined __TS_CONNPREFSUITE_H__)
#define __TS_CONNPREFSUITE_H__

#include <e32std.h>
#include <networking/testsuite.h>


#define MAX_NAME_LENGTH		10			///< Maximum length of connection name

_LIT (KTxtVersion,"1.00");				///< Version string for ScheduleTest
//_LIT (KConnLogString, "Name [%S], RConnection[%x], RSocketServ[%x], Clients: %i");


class CTS_ConnPrefStep;

class CTS_ConnPrefSuite : public CTestSuite
{
public:
	virtual		~CTS_ConnPrefSuite();
	void		InitialiseL(void);
	void		AddTestStepL(CTS_ConnPrefStep* ptrTestStep );
	TPtrC		GetVersion(void);	
	
private:
	// nuffin
};

void CommInitL(TBool);

#endif /* __TS_CONNEPREFSUITE_H__ */
