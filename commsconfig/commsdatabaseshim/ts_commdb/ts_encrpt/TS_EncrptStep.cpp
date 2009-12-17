// Copyright (c) 2002-2009 Nokia Corporation and/or its subsidiary(-ies).
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
// This contains CTS_EncrptStep class which is
// the base class for all the Encrpt test steps
// 
//

/**
 @file TS_EncrptStep.cpp
*/
#include "TS_EncrptStep.h"

CTS_EncrptStep::CTS_EncrptStep()
	{	
	}

CTS_EncrptStep::~CTS_EncrptStep()
	{ 
	}	

void CTS_EncrptStep::ExpLogExtra(const TText8* aFile, TInt aLine, TInt aSeverity,
		TRefByValue<const TDesC> aFmt,...)
	{
	VA_LIST aList;
	VA_START( aList, aFmt );


	// Log to the suite's logger
	iSuite->LogExtra( aFile, aLine, aSeverity, aFmt, aList );

	VA_END( aList ); 

	}

enum TVerdict CTS_EncrptStep::Test(TInt aResult)
	{	
	if (!aResult)
		{								
		iSuite->LogExtra((TText8*)__FILE__, __LINE__, ESevrWarn, KEGeneric);
		return EFail;
		}
	return EPass;
	}


void CTS_EncrptStep::Set(TGlobalDbIds * aGlobals)
	{ Dll::SetTls(aGlobals); }

TGlobalDbIds* CTS_EncrptStep::Get()
	{ TGlobalDbIds * d=(TGlobalDbIds *)Dll::Tls(); return d; }





