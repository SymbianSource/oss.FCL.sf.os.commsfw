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
// This contains CTestSuiteCommDb 
// This is the container class for all the CommDb test steps
// 
//

#if (!defined __TESTSUITCOMMDB_H__)
#define __TESTSUITCOMMDB_H__

#include <networking/testsuite.h>


NONSHARABLE_CLASS(CTestSuiteCommDb) : public CTestSuite
{
public:
	void InitialiseL( void );
	~CTestSuiteCommDb();
	TPtrC GetVersion( void );
	void AddTestStepL( CTestStepCommDb * ptrTestStep );


private:

};

// these values have been copied from Testenv.h
const TInt KSmallBufSize = 256;
const TInt KLargeBufSize = 2048;
const TInt KHugeBufSize = 16384;

// CommDb test macros copied from Testenv.h
typedef TBuf8<KLargeBufSize> TLargeBuf;
#define IPADDR(a,b,c,d) (TUint32)(((a)<<24)|((b)<<16)|((c)<<8)|(d))

//Test suite parameters
const TInt KHeapFailure	= 500;

#endif /* __TESTSUITCOMMDB_H__ */
