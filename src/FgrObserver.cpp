/*
 * FgrObserver.cpp
 *
 *  Created on: 24.10.2009
 *      Author: Avis
 */

#include "FgrObserver.h"
#include <apgtask.h>
#include <apgwgnam.h> //CApaWindowGroupName
#ifdef _DEBUG
#include <e32debug.h>
#endif

CFgrObserver* CFgrObserver::NewL(RWsSession& aWsSession,MFgrCallBack& aCallBack)
	{
	CFgrObserver* self = CFgrObserver::NewLC(aWsSession,aCallBack);
	CleanupStack::Pop(self);
	return self;
	}
 
 
CFgrObserver* CFgrObserver::NewLC(RWsSession& aWsSession,MFgrCallBack& aCallBack)
	{
	CFgrObserver* self = new (ELeave) CFgrObserver(aWsSession,aCallBack);
	CleanupStack::PushL(self);
	self->ConstructL();
	return self;
	}
 
 
CFgrObserver::CFgrObserver(RWsSession& aWsSession,MFgrCallBack& aCallBack)
:CActive(EPriorityHigh),iCallBack(aCallBack), iWsSession(aWsSession), iWg(aWsSession)
{
}
 
CFgrObserver::~CFgrObserver()
{
	Cancel();
	iWg.Close();
}
 
void CFgrObserver::ConstructL()
{
	CActiveScheduler::Add(this);
 
	User::LeaveIfError(iWg.Construct((TUint32)&iWg, EFalse));
	iWg.SetOrdinalPosition(-1);
	iWg.EnableReceiptOfFocus(EFalse);
 
	CApaWindowGroupName* wn=CApaWindowGroupName::NewLC(iWsSession);
	wn->SetHidden(ETrue);
	wn->SetWindowGroupName(iWg);
	CleanupStack::PopAndDestroy();

	//iWg.EnableScreenChangeEvents();
	iWg.EnableFocusChangeEvents();
	iWg.EnableGroupListChangeEvents();
	iHandle=-1;
	iGroupIds=new (ELeave) CArrayFixFlat<TInt>(3);
	iGroupIdsPrev=new (ELeave) CArrayFixFlat<TInt>(3);
	iWsSession.WindowGroupList(iGroupIds);
	iWsSession.WindowGroupList(iGroupIdsPrev);
	Listen();
}
 
void CFgrObserver::RunL()
	{
		iGroupIds->Reset();
		iWsSession.WindowGroupList(iGroupIds);
		TWsEvent wsEvent;
		iWsSession.GetEvent(wsEvent);
		switch (wsEvent.Type())
			{
			//case EEventScreenDeviceChanged:
			//	{
				//iCallBack.ScreenChanged();	
			//	break;
			//	}
			case EEventWindowGroupListChanged:
				{
				if ((iGroupIds->Count()!=iGroupIdsPrev->Count()))
					{iCallBack.GroupListChanged();}
				break;
				}
			case EEventFocusGroupChanged:
			{
			iCallBack.GroupListChanged();
			break;
			}
			default:
				break;
			}	 
		iGroupIdsPrev->Reset();
		iWsSession.WindowGroupList(iGroupIdsPrev);
		if (iStatus != KErrCancel) 
		{
			Listen();
		}
	}
 
void CFgrObserver::DoCancel()
{
	iWsSession.EventReadyCancel();
}
 
void CFgrObserver::Listen()
{
	iWsSession.EventReady(&iStatus);
	SetActive();
}
void CFgrObserver::CaptureKey(TInt aScancode)
	{
	if (iHandle!=-1){iWg.CancelCaptureKeyUpAndDowns(iHandle);}
	iHandle=iWg.CaptureKeyUpAndDowns(aScancode,0,0);
	}
