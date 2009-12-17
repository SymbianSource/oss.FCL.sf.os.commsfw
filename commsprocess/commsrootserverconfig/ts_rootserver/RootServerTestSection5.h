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
// This is the header file for ROOTSERVER test section 1
// 
//


#if (!defined __ROOTSERVERTEST_5_H__)
#define __ROOTSERVERTEST_5_H__

class CRootServerTest_GracefulUnload : public CTestStepRootServer
{
protected:
	TVerdict UnloadGracefullyL(TThreadPriority aPriority);
};

class CRootServerTest5_1 : public CRootServerTest_GracefulUnload
{
public:
	CRootServerTest5_1();

	virtual TVerdict doTestStepL( void );
};

class CRootServerTest5_2 : public CRootServerTest_GracefulUnload
{
public:
	CRootServerTest5_2();

	virtual TVerdict doTestStepL( void );
};

class CRootServerTest5_3 : public CTestStepRootServer
{
public:
	CRootServerTest5_3();

	virtual TVerdict doTestStepL( void );
};

class CRootServerTest_UngracefulUnload: public CTestStepRootServer
	{
protected:
	TVerdict UnloadNonGracefullyL(TThreadPriority aPriority);
	};

class CRootServerTest5_4 : public CRootServerTest_UngracefulUnload
{
public:
	CRootServerTest5_4();

	virtual TVerdict doTestStepL( void );
};

class CRootServerTest5_5 : public CRootServerTest_UngracefulUnload
{
public:
	CRootServerTest5_5();

	virtual TVerdict doTestStepL( void );
};

class CRootServerTest5_6 : public CTestStepRootServer
{
public:
	CRootServerTest5_6();

	virtual TVerdict doTestStepL( void );
};

class CRootServerTest5_7 : public CTestStepRootServer
{
public:
	CRootServerTest5_7();

	virtual TVerdict doTestStepL( void );
};

class CRootServerTest5_8 : public CTestStepRootServer
{
public:
	CRootServerTest5_8();

	virtual TVerdict doTestStepL( void );
};


#endif //(__ROOTSERVERTEST_1_H__)

