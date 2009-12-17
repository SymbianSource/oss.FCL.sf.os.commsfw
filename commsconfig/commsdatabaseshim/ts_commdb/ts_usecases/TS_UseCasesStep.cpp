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
// This contains CTS_UseCasesStep class which is
// the base class for all the Encrpt test steps
// 
//

/**
 @file TS_UseCasesStep.cpp
*/
#include "TS_UseCasesStep.h"


CTS_UseCasesStep::CTS_UseCasesStep() 
	{			
	}

CTS_UseCasesStep::~CTS_UseCasesStep()
	{ 
	}	

enum TVerdict CTS_UseCasesStep::Test(TInt aResult)
	{	
	if (!aResult)
		{
		return EFail;		
		}
	return EPass;
	}

void CTS_UseCasesStep::Set(TGlobalData * aGlobals)
	{ Dll::SetTls(aGlobals); }

TGlobalData* CTS_UseCasesStep::Get()
	{ TGlobalData * d=(TGlobalData *)Dll::Tls(); return d; }




