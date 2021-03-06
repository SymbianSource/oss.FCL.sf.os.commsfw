/*
* Copyright (c) 2009 Nokia Corporation and/or its subsidiary(-ies).
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
*
*/
// This is the header file for CommDb test 040.XX group of scenarios 

#include<cdbover.h>

#if (!defined __STEP_040_XX_H__)
#define __STEP_040_XX_H__


////////////////////
//	Test step 040.01
////////////////////

NONSHARABLE_CLASS(CCommDbTest040_01) : public CTestStepCommDb
{
public:
	CCommDbTest040_01();
	~CCommDbTest040_01();

	virtual enum TVerdict doTestStepL( void );
	TInt executeStepL();
	TVerdict doTestStepPreambleL();
	TVerdict doTestStepPostambleL();

private:
	CCommDbOverrideSettings* iOverSet;
};

////////////////////
//	Test step 040.02
////////////////////

NONSHARABLE_CLASS(CCommDbTest040_02) : public CTestStepCommDb
{
public:
	CCommDbTest040_02();
	~CCommDbTest040_02();

	virtual enum TVerdict doTestStepL( void );
	TInt executeStepL();
	TVerdict doTestStepPreambleL();
	TVerdict doTestStepPostambleL();

private:
	CCommDbOverrideSettings* iOverSet;
};

////////////////////
//	Test step 040.03
////////////////////

NONSHARABLE_CLASS(CCommDbTest040_03) : public CTestStepCommDb
{
public:
	CCommDbTest040_03();
	~CCommDbTest040_03();

	virtual enum TVerdict doTestStepL( void );
};

#endif //__STEP_040_XX_H__
