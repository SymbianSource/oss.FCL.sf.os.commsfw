// Copyright (c) 2006-2009 Nokia Corporation and/or its subsidiary(-ies).
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
// SS_COMMSPROV.CPP
// 
//

/**
 @file @internalTechnology
*/


#include "ss_common.h"
#include <comms-infras/ss_log.h>
#include <es_panic.h>
#include <ss_std.h>
using namespace ESock;

#ifdef _DEBUG
/** Because we strive to maintain a single owner for a message and to pass by reference when ownership
it's generally an error for the handle to be set upon destruction.
*/
RSafeMessage::~RSafeMessage()
	{
	if(Handle() != KNullHandle)
		{
		LOG(ESockLog::Printf(KESockServerTag, _L8("RSafeMessage(%08x) - WARNING! handle still set in destructor, may be a leak, session %08x"), Handle(), Session()) );
		}
	}
#endif

/** Complete the message with the given reason code, with detailed logging
*/
void RSafeMessage::Complete(TInt aReason) const
	{
	LOG(ESockLog::Printf(KESockServerTag, _L8("RSafeMessage(%08x)::Complete(%d) - session %08x"), Handle(), aReason, Session()) );
	RMessage2::Complete(aReason);
	}

/** Panic the client with the given category & reason code, with detailed logging
*/
void RSafeMessage::Panic(const TDesC& aCategory, TInt aReason) const
	{
	LOG(ESockLog::Printf(KESockServerTag, _L("RSafeMessage(%08x)::Panic(\"%S\", %d) - session %08x"), Handle(), &aCategory, aReason, Session()) );
	RMessage2::Panic(aCategory, aReason);
	}

/** Take over a message. Beyond being a simple copy this resets the source's handle so that double-ownership is avoided
*/
void RSafeMessage::Adopt(RSafeMessage& aSrc)
	{
	*this = aSrc;
	aSrc.ResetHandle();
	}

/** Duplicate a message, including aliasing the handle & so raising the risk of a double-complete
*/
void RSafeMessage::Duplicate(const RSafeMessage& aSrc)
	{
	*this = aSrc;
	}

/** Null the handle, so this safe message no longer references a client request. This is normally done automatically
by completing or panicking the client or transferring message ownership, so this will seldom need to be called
explicitly
*/
void RSafeMessage::ResetHandle()
	{
	iHandle = KNullHandle;
	}

RSafeMessage& RSafeMessage::operator=(const RSafeMessage& aSrc)
	{
	RMessage2::operator=(aSrc);
	return *this;
	}

void RSafeMessage::PanicClient(TInt aReason) const
	{
	RThread t;
	RMessage2::Client(t);
	TUint tid = t.Id();
	TExitType exittype=t.ExitType();
	t.Close();
	if(exittype == EExitPending) // is client alive?
		{
		LOG(
			TBuf8<sizeof(KESockClientPanic) / sizeof(TUint16)> clientPanic8;
			clientPanic8.Copy(KESockClientPanic);
			TBuf8<64> messBuf;
			ESockLog::IPCMessName((TSockMess) RMessage2::Function(), messBuf);
			ESockLog::Printf(KESockErrorTag, _L8("RSafeMessage:\tPanicClient, Category %S, Reason %d, Tid %d, RMessage2 %08x [%S], Args %08x %08x %08x %08x, ClientStatus %08x"),
							 &clientPanic8, aReason, tid, RMessage2::Handle(), &messBuf, RMessage2::Int0(), RMessage2::Int1(), RMessage2::Int2(), RMessage2::Int3(), RMessage2::ClientStatus())
		);
		Panic(KESockClientPanic, aReason);
		}		
	}

TInt RSafeMessage::Read(TInt aSrcParamIndex,TDes8 &aDes,TInt anOffset) const
	{
	TInt res= RMessage2::Read(aSrcParamIndex,aDes,anOffset);
	__ASSERT_DEBUG(res!=KErrArgument,Fault(EBadState));
	if (res!=KErrNone)
		{
		PanicClient(EBadDescriptorRead);
		res = KErrBadDescriptor;
		}
	return res;
	}

void RSafeMessage::ReadL(TInt aSrcParamIndex,TDes8& aDes,TInt anOffset) const
	{
	User::LeaveIfError(Read(aSrcParamIndex, aDes, anOffset));		
	}

TInt RSafeMessage::Write(TInt aDstParamIndex,const TDesC8& aDes,TInt anOffset) const
	{
	TInt res = RMessage2::Write(aDstParamIndex,aDes,anOffset);
	__ASSERT_DEBUG(res!=KErrArgument,Fault(EBadState));
	if (res!=KErrNone)
		{
		PanicClient(EBadDescriptorWrite);
		res = KErrBadDescriptor;
		}
	return res;		
	}

void RSafeMessage::WriteL(TInt aDstParamIndex,const TDesC8& aDes,TInt anOffset) const
	{
	User::LeaveIfError(Write(aDstParamIndex, aDes, anOffset));
	}

TInt RSafeMessage::Read(TInt aSrcParamIndex,TDes16 &aDes,TInt anOffset) const
	{
	TInt res= RMessage2::Read(aSrcParamIndex,aDes,anOffset);
	__ASSERT_DEBUG(res!=KErrArgument,Fault(EBadState));
	if (res!=KErrNone)
		{
		PanicClient(EBadDescriptorRead);
		res = KErrBadDescriptor;
		}
	return res;		
	}

void RSafeMessage::ReadL(TInt aSrcParamIndex,TDes16& aDes,TInt anOffset) const
	{
	User::LeaveIfError(Read(aSrcParamIndex, aDes, anOffset));	
	}

TInt RSafeMessage::Write(TInt aDstParamIndex,const TDesC16 &aDes,TInt anOffset) const
	{
	TInt res = RMessage2::Write(aDstParamIndex,aDes,anOffset);
	__ASSERT_DEBUG(res!=KErrArgument,Fault(EBadState));
	if (res!=KErrNone)
		{
		PanicClient(EBadDescriptorWrite);
		res = KErrBadDescriptor;
		}
	return res;		
	}

void RSafeMessage::WriteL(TInt aDstParamIndex,const TDesC16& aDes,TInt anOffset) const
	{
	User::LeaveIfError(Write(aDstParamIndex,aDes,anOffset));
	}

TInt RSafeMessage::Write(TInt aDstParamIndex,const TPckg<TUint32>& aDes,TInt anOffset) const
	{
	TInt res = RMessage2::Write(aDstParamIndex,aDes,anOffset);
	__ASSERT_DEBUG(res!=KErrArgument,Fault(EBadState));
	if (res!=KErrNone)
		{
		PanicClient(EBadDescriptorWrite);
		res = KErrBadDescriptor;
		}
	return res;		
	}

void RSafeMessage::WriteL(TInt aDstParamIndex,const TPckg<TUint32>& aDes,TInt anOffset) const
	{
	User::LeaveIfError(Write(aDstParamIndex, aDes, anOffset));		
	}

TInt RSafeMessage::GetDesLengthL(TInt aParam) const
	{
	TInt res = RMessage2::GetDesLength(aParam);
	__ASSERT_DEBUG(res!=KErrArgument,Fault(EBadState));
	if (res<0)
		{
		PanicClient(EBadDescriptorLength);
		User::Leave(KErrBadDescriptor);
		}
	return res;		
	}


TInt RSafeMessage::GetDesMaxLengthL(TInt aParam) const
	{
	TInt res = RMessage2::GetDesMaxLength(aParam);
	__ASSERT_DEBUG(res!=KErrArgument, Fault(EBadState));
	if (res < 0)
		{
		PanicClient(EBadDescriptorLength);
		User::Leave(KErrBadDescriptor);
		}
	return res;		
	}

