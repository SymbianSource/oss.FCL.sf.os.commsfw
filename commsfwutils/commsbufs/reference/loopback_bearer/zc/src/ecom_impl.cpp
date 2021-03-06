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

#include <ecom/implementationproxy.h>
#include <ecom/ecom.h>

#include "flow.h"
#include "mcpr_factory.h"
#include "tier_manager_factory.h"
#include "params.h"

const TImplementationProxy ImplementationTable[] =
	{   
	IMPLEMENTATION_PROXY_ENTRY(KZeroCopyLoopbackFlowImplementationUid, CZeroCopyLoopbackSubConnectionFlowFactory::NewL),
	IMPLEMENTATION_PROXY_ENTRY(CZeroCopyLoopbackMetaConnectionProviderFactory::iUid, CZeroCopyLoopbackMetaConnectionProviderFactory::NewL),
	IMPLEMENTATION_PROXY_ENTRY(CZeroCopyLoopBackTierManagerFactory::iUid, CZeroCopyLoopBackTierManagerFactory::NewL),
	IMPLEMENTATION_PROXY_ENTRY(TZeroCopyLoopbackPref::EUid, CZeroCopyLoopbackParamaterFactory::NewL)
   	};


EXPORT_C const TImplementationProxy* ImplementationGroupProxy(TInt& aTableCount)
   {
   aTableCount = sizeof(ImplementationTable) / sizeof(TImplementationProxy);
   return ImplementationTable;
   }
