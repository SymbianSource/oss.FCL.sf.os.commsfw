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
// // Root Server Test Section 6 - Loading modules in Root Server
// 
//


#if (!defined __ROOTSERVERTEST_6_H__)
#define __ROOTSERVERTEST_6_H__


class CRootServerTest6_1 : public CTestStepRootServer
{
public:
	CRootServerTest6_1();

	virtual TVerdict doTestStepL( void );
};

class CRootServerTest6_2 : public CTestStepRootServer
{
public:
	CRootServerTest6_2();

	virtual TVerdict doTestStepL( void );
};

class CRootServerTest6_BindWithinModule : public CTestStepRootServer
{
protected:
	TVerdict BindWithinModuleL(TThreadPriority aPriority);
};

class CRootServerTest6_3 : public CRootServerTest6_BindWithinModule
{
public:
	CRootServerTest6_3();

	virtual TVerdict doTestStepL( void );
};

class CRootServerTest6_4 : public CRootServerTest6_BindWithinModule
{
public:
	CRootServerTest6_4();

	virtual TVerdict doTestStepL( void );
};

class CRootServerTest6_5 : public CTestStepRootServer
{
public:
	CRootServerTest6_5();

	virtual TVerdict doTestStepL( void );
};

class CRootServerTest6_6 : public CTestStepRootServer
{
public:
	CRootServerTest6_6();

	virtual TVerdict doTestStepL( void );
};

class CRootServerTest6_7 : public CTestStepRootServer
{
public:
	CRootServerTest6_7();

	virtual TVerdict doTestStepL( void );
};

class CRootServerTest6_UnbindWithinModule : public CTestStepRootServer
{
protected:
	TVerdict UnbindWithinModuleL(TThreadPriority aPriority);
};

class CRootServerTest6_8 : public CRootServerTest6_UnbindWithinModule
{
public:
	CRootServerTest6_8();

	virtual TVerdict doTestStepL( void );
};

class CRootServerTest6_9 : public CRootServerTest6_UnbindWithinModule
{
public:
	CRootServerTest6_9();

	virtual TVerdict doTestStepL( void );
};

class CRootServerTest6_10 : public CTestStepRootServer
{
public:
	CRootServerTest6_10();

	virtual TVerdict doTestStepL( void );
};

class CRootServerTest6_11 : public CTestStepRootServer
{
public:
	CRootServerTest6_11();

	virtual TVerdict doTestStepL( void );
};

class CRootServerTest6_12 : public CTestStepRootServer
{
public:
	CRootServerTest6_12();

	virtual TVerdict doTestStepL( void );
};

class CRootServerTest6_13 : public CTestStepRootServer
{
public:
	CRootServerTest6_13();

	virtual TVerdict doTestStepL( void );
};

class CRootServerTest6_14 : public CTestStepRootServer
{
public:
	CRootServerTest6_14();

	virtual TVerdict doTestStepL( void );
};

class CRootServerTest6_15 : public CTestStepRootServer
{
public:
	CRootServerTest6_15();

	virtual TVerdict doTestStepL( void );
};

class CRootServerTest6_16 : public CTestStepRootServer
{
public:
	CRootServerTest6_16();

	virtual TVerdict doTestStepL( void );
};

#endif //(__ROOTSERVERTEST_6_H__)

