/**
* Copyright (c) 2006-2009 Nokia Corporation and/or its subsidiary(-ies).
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



/**
 @file Connections.TestSteps.h
*/

#if (!defined CONNECTIONS_TESTSTEPS_H)
#define CONNECTIONS_TESTSTEPS_H

#include <test/testexecutestepbase.h>
#include "Te_EsockStepBase.h"

_LIT(KTe_ConnectionName,"ConnName");
_LIT(KTe_AttachToConnectionName,"AttachToConnName");
_LIT(KTe_ConnectionStopTypeName,"ConnStopType");
_LIT(KTe_ConnStopNormal,"EStopNormal");
_LIT(KTe_ConnStopAuthoritative,"EStopAuthoritative");
_LIT(KTe_ConnectionType,"ConnType");

_LIT(KTe_ConnectionAttachTypeName,"ConnAttachType");
_LIT(KTe_ConnAttachTypeNormal,"EAttachTypeNormal");
_LIT(KTe_ConnAttachTypeMonitor,"EAttachTypeMonitor");

_LIT(KTe_CommDbBearerCSD,"KCommDbBearerCSD");
_LIT(KTe_CommDbBearerWcdma,"KCommDbBearerWcdma");
_LIT(KTe_CommDbBearerLAN,"KCommDbBearerLAN");

//mobility api
_LIT(KTe_MobilityAPIName,"MobilityExtName");

//mobility notifications

_LIT(KTe_MobilityNotificationPreferredCarrierAvailable,"PreferredCarrierAvailable");
_LIT(KTe_MobilityNotificationPreferredCarrierAvailable_OldAP,"OldAP");
_LIT(KTe_MobilityNotificationPreferredCarrierAvailable_NewAP,"NewAP");
_LIT(KTe_MobilityNotificationNewCarrierActive,"NewCarrierActive");
_LIT(KTe_MobilityNotificationNewCarrierActive_NewAP,"NewAP");

_LIT(KTe_MobilityNotificationMigrateToPreferredCarrier,"MigrateToPreferredCarrier");
_LIT(KTe_MobilityNotificationIgnorePreferredCarrier,"IgnorePreferredCarrier");
_LIT(KTe_MobilityNotificationNewCarrierAccepted,"NewCarrierAccepted");
_LIT(KTe_MobilityNotificationNewCarrierRejected,"NewCarrierRejected");

// Availability extension api

_LIT(KTe_AvailabilityExpectedValue, "AvailabilityExpectedValue");
_LIT(KTe_AvailabilityAPIExtensionName, "AvailabilityExtensionName");

// Availability notifications
_LIT(KTe_AvailabilityNotification, "RequestNotificationOfAvailabilityChange");

_LIT(KTe_NetworkIndexName,"NET");

// Events in general
//------------------
_LIT(KTimeoutInMilliSeconds, "TimeoutInMilliSeconds");

// Connection Manager
//-------------------

// Connection status and notification extension api
_LIT(KConnStatusResponse, "ConnStatusResponse");
_LIT(KConnStatusChangeNotificationResponse, "ConnStatusChangeNotificationResponse");

//helpers
_LIT(KTe_CreatePublishSubscribeVar, "createpublishsubscribevar");
_LIT(KTe_CreatePublishSubscribeVarUid, "CreatePublishSubscribeVarUid");
_LIT(KTe_CreatePublishSubscribeVarValue, "CreatePublishSubscribeVarValue");

_LIT(KTe_CheckPublishSubscribeVar, "checkpublishsubscribevar");
_LIT(KTe_CheckPublishSubscribeVarUid, "CheckPublishSubscribeVarUid");
_LIT(KTe_CheckPublishSubscribeVarValue, "CheckPublishSubscribeVarValue");

//progress notification events
_LIT(KTe_ConnEventsName,"ConnEventsName");
_LIT(KTe_SelectedProgress,"SelectedProgress");
_LIT(KTe_LinkLayerOpen,"KLinkLayerOpen");
_LIT(KTe_LinkLayerClosed,"KLinkLayerClosed");

// Classes
//--------

/**
Class implementing CreateRConnectionStep

@internalComponent
*/
class CCreateRConnectionStep : public CTe_EsockStepBase
	{
public:
	CCreateRConnectionStep(CCEsockTestBase*& aEsockTest);
	TVerdict doTestStepPreambleL();
	TVerdict doSingleTestStep();
	TInt ConfigureFromIni();

private:
    TRConnectionParams iParams; //current params (.ini)
	};

_LIT(KCreateRConnectionStep,"CreateRConnectionStep");


/**
Class implementing StopRConnectionStep

@internalComponent
*/
class CStopRConnectionStep : public CTe_EsockStepBase
	{
public:
	CStopRConnectionStep(CCEsockTestBase*& aEsockTest);
	TVerdict doSingleTestStep();
	TInt ConfigureFromIni();

private:
    TRConnectionParams iParams; //current params (.ini)
	};

_LIT(KStopRConnectionStep,"StopRConnectionStep");


/**
Class implementing CloseRConnectionStep

@internalComponent
*/
class CCloseRConnectionStep : public CTe_EsockStepBase
	{
public:
	CCloseRConnectionStep(CCEsockTestBase*& aEsockTest);
	TVerdict doSingleTestStep();
	TInt ConfigureFromIni();

private:
    TRConnectionParams iParams; //current params (.ini)
	};

_LIT(KCloseRConnectionStep,"CloseRConnectionStep");


/**
Class implementing StartRConnectionStep

@internalComponent
*/
class CStartRConnectionStep : public CTe_EsockStepBase
	{
public:
	CStartRConnectionStep(CCEsockTestBase*& aEsockTest);
	TVerdict doSingleTestStep();
	TInt ConfigureFromIni();

private:
    TRConnectionParams iParams; //current params (.ini)
	};

_LIT(KStartRConnectionStep,"StartRConnectionStep");


/**
Class implementing openrconnectionStep

@internalComponent
*/
class COpenRConnectionStep : public CTe_EsockStepBase
	{
public:
	COpenRConnectionStep(CCEsockTestBase*& aEsockTest);
	TVerdict doSingleTestStep();
	TInt ConfigureFromIni();

private:
    TRConnectionParams iParams; //current params (.ini)
	};

_LIT(KOpenRConnectionStep,"openrconnectionStep");


/**
Class implementing AcceptIncomingConnectionStep

@internalComponent
*/
class CAcceptIncomingConnectionStep : public CTe_EsockStepBase
	{
public:
	CAcceptIncomingConnectionStep(CCEsockTestBase*& aEsockTest);
	TVerdict doSingleTestStep();
	TInt ConfigureFromIni();

private:
    TRSubConnectionParams iParams;  //current params (.ini)
	};

_LIT(KAcceptIncomingConnectionStep,"AcceptIncomingConnectionStep");


/**
Class implementing RejectIncomingConnectionStep

@internalComponent
*/
class CRejectIncomingConnectionStep : public CTe_EsockStepBase
	{
public:
	CRejectIncomingConnectionStep(CCEsockTestBase*& aEsockTest);
	TVerdict doSingleTestStep();
	TInt ConfigureFromIni();

private:
    TRSubConnectionParams iParams;  //current params (.ini)
	};

_LIT(KRejectIncomingConnectionStep,"RejectIncomingConnectionStep");


/**
Class implementing WaitForIncomingConnectionStep

@internalComponent
*/
class CWaitForIncomingConnectionStep : public CTe_EsockStepBase
	{
public:
	CWaitForIncomingConnectionStep(CCEsockTestBase*& aEsockTest);
	TVerdict doSingleTestStep();
	TInt ConfigureFromIni();

private:
    TPtrC timerSet;
    TPtrC subConnStatus;
    RTimer iTimer;
    TRSubConnectionParams iParams;  //current params (.ini)

	};

_LIT(KWaitForIncomingConnectionStep,"WaitForIncomingConnectionStep");


/**
Class implementing AsyncAcceptIncomingConnectionStep.h

@internalComponent
*/
class CAsyncAcceptIncomingConnectionStep : public CTe_EsockStepBase
	{
public:
	CAsyncAcceptIncomingConnectionStep(CCEsockTestBase*& aEsockTest);
	TVerdict doSingleTestStep();
	TInt ConfigureFromIni();

private:
    TPtrC timerSet;
    TPtrC subConnStatus;
    RTimer iTimer;
    TRSubConnectionParams iParams;  //current params (.ini)
	};

_LIT(KAsyncAcceptIncomingConnectionStep,"AsyncAcceptIncomingConnectionStep");


// Enumerating connections
//------------------------
class TEnumerateConnectionsParams
	{
public:
	TPtrC iConnectionName;
	TUint iExpectedConnCount;
	};

class CEnumerateConnectionsStep : public CTe_EsockStepBase
	{
public:
	CEnumerateConnectionsStep(CCEsockTestBase*& aEsockTest);
	TInt CEnumerateConnectionsStep::ConfigureFromIni();
	TVerdict CEnumerateConnectionsStep::doSingleTestStep();

private:
    TEnumerateConnectionsParams iParams;
	};

_LIT(KEnumerateConnectionsStep,"EnumerateConnectionsStep");

// Attach to connection
//---------------------

class CattachtorconnectionStep : public CTe_EsockStepBase
	{
public:
	CattachtorconnectionStep(CCEsockTestBase*& aEsockTest);
	TVerdict doSingleTestStep();
	TInt ConfigureFromIni();

private:
    TRConnectionParams iParams; //current params (.ini)
	};


_LIT(KattachtorconnectionStep,"attachtorconnectionStep");

// Await connection start complete
//---------------------

class CAwaitRConnectionStartComplete : public CTe_EsockStepBase
	{
public:
	CAwaitRConnectionStartComplete(CCEsockTestBase*& aEsockTest);
	TVerdict doSingleTestStep();
	TInt ConfigureFromIni();

private:
    TRConnectionParams iParams; //current params (.ini)
	};


_LIT(KAwaitRConnectionStartComplete,"AwaitRConnectionStartComplete");

//Set a publish subscribe var

/**
Class implementing CreateRConnectionStep

@internalComponent
*/
class CCreatePublishSubscribeVar : public CTe_EsockStepBase
	{
public:
	CCreatePublishSubscribeVar(CCEsockTestBase*& aEsockTest);
	TVerdict doTestStepPreambleL();
	TVerdict doSingleTestStep();
	TInt ConfigureFromIni();

private:
	TInt iUid;
	TInt iValue;
	};

_LIT(KCreatePublishSubscribeVar,"CreatePublishSubscribeVar");

//Check a publish subscribe var
/**
Class implementing CreateRConnectionStep

@internalComponent
*/
class CCheckPublishSubscribeVar : public CTe_EsockStepBase
	{
public:
	CCheckPublishSubscribeVar(CCEsockTestBase*& aEsockTest);
	TVerdict doTestStepPreambleL();
	TVerdict doSingleTestStep();
	TInt ConfigureFromIni();

private:
	TInt iUid;
	TInt iValue;
	};

_LIT(KCheckPublishSubscribeVar,"CheckPublishSubscribeVar");


/**
Class implementing RegisterProgressNotificationStep

@internalComponent
*/
class CRegisterProgressNotificationStep : public CTe_EsockStepBase
	{
public:
	CRegisterProgressNotificationStep(CCEsockTestBase*& aEsockTest);
	TVerdict doSingleTestStep();
	TInt ConfigureFromIni();

private:
	TEventContainerParams iParams; //current params (.ini)
	};

_LIT(KRegisterProgressNotificationStep,"RegisterProgressNotificationStep");


class CCheckProgressNotificationStep : public CTe_EsockStepBase
	{
public:
	CCheckProgressNotificationStep(CCEsockTestBase*& aEsockTest);
	TVerdict doSingleTestStep();
	TInt ConfigureFromIni();
private:
	TEventContainerParams iParams; //current params (.ini)
	};

_LIT(KCheckProgressNotificationStep,"CheckProgressNotificationStep");

class CCheckNegativeProgressNotificationStep : public CTe_EsockStepBase
	{
public:
	CCheckNegativeProgressNotificationStep(CCEsockTestBase*& aEsockTest);
	TVerdict doSingleTestStep();
	TInt ConfigureFromIni();
private:
	TEventContainerParams iParams; //current params (.ini)
	};

_LIT(KCheckNegativeProgressNotificationStep,"CheckNegativeProgressNotificationStep");


#endif // CONNECTIONS_TESTSTEPS_H


