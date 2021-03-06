// Copyright (c) 2004-2009 Nokia Corporation and/or its subsidiary(-ies).
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
// SocketTestSection15.h
// This is the header file for ESOCK basic socket test section 16
// 
//


#if (!defined __SOCKETTEST_16_H__)
#define __SOCKETTEST_16_H__
#include "TestStepSocket.h"

class CSocketTest16_1 : public CSocketTestStep_OOMCapable
	{
	public:
		static const TDesC& GetTestName();
		virtual enum TVerdict InternalDoTestStepL( void );
	};


#endif //(__SOCKETTEST_16_H__)

