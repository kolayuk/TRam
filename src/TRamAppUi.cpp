/*
========================================================================
 Name        : TRamAppUi.cpp
 Author      : Usanov-Kornilov Nikolay (aka Kolay)
 Copyright   : 
Contacts:
	kolayuk@mail.ru
	http://kolaysoft.ru

(c) KolaySoft, 2010

 Description : 
========================================================================
*/
// [[[ begin generated region: do not modify [Generated System Includes]
#include <eikmenub.h>
#include <akncontext.h>
#include <akntitle.h>
#include <TRam.rsg>
// ]]] end generated region [Generated System Includes]

// [[[ begin generated region: do not modify [Generated User Includes]
#include "TRamAppUi.h"
#include "TRam.hrh"
#include "TRamContainerView.h"
// ]]] end generated region [Generated User Includes]

// [[[ begin generated region: do not modify [Generated Constants]
// ]]] end generated region [Generated Constants]
#include <const.h>
#include <bautils.h>
#include <TopInfo.h>
#include <hal.h>
#include <e32math.h>

/**
 * Construct the CTRamAppUi instance
 */ 
CTRamAppUi::CTRamAppUi()
	{
	// [[[ begin generated region: do not modify [Generated Contents]
	// ]]] end generated region [Generated Contents]
	
	}

/** 
 * The appui's destructor removes the container from the control
 * stack and destroys it.
 */
CTRamAppUi::~CTRamAppUi()
	{
	// [[[ begin generated region: do not modify [Generated Contents]
	// ]]] end generated region [Generated Contents]
	delete iTimer;
	delete iInfo;
	}

// [[[ begin generated function: do not modify
void CTRamAppUi::InitializeContainersL()
	{
	iTRamContainerView = CTRamContainerView::NewL();
	AddViewL( iTRamContainerView );
	SetDefaultViewL( *iTRamContainerView );
	}
// ]]] end generated function

/**
 * Handle a command for this appui (override)
 * @param aCommand command id to be handled
 */
void CTRamAppUi::HandleCommandL( TInt aCommand )
	{
	// [[[ begin generated region: do not modify [Generated Code]
	TBool commandHandled = EFalse;
	switch ( aCommand )
		{ // code to dispatch to the AppUi's menu and CBA commands is generated here
		default:
			break;
		}
	
		
	if ( !commandHandled ) 
		{
		if ( aCommand == EAknSoftkeyExit || aCommand == EEikCmdExit )
			{
			Exit();
			}
		}
	// ]]] end generated region [Generated Code]
	
	}

/** 
 * Override of the HandleResourceChangeL virtual function
 */
void CTRamAppUi::HandleResourceChangeL( TInt aType )
	{
	CAknViewAppUi::HandleResourceChangeL( aType );
	// [[[ begin generated region: do not modify [Generated Code]
	// ]]] end generated region [Generated Code]
	
	}
				
/** 
 * Override of the HandleKeyEventL virtual function
 * @return EKeyWasConsumed if event was handled, EKeyWasNotConsumed if not
 * @param aKeyEvent 
 * @param aType 
 */
TKeyResponse CTRamAppUi::HandleKeyEventL(
		const TKeyEvent& aKeyEvent,
		TEventCode aType )
	{
	// The inherited HandleKeyEventL is private and cannot be called
	// [[[ begin generated region: do not modify [Generated Contents]
	// ]]] end generated region [Generated Contents]
	
	return EKeyWasNotConsumed;
	}

/** 
 * Override of the HandleViewDeactivation virtual function
 *
 * @param aViewIdToBeDeactivated 
 * @param aNewlyActivatedViewId 
 */
void CTRamAppUi::HandleViewDeactivation( 
		const TVwsViewId& aViewIdToBeDeactivated, 
		const TVwsViewId& aNewlyActivatedViewId )
	{
	CAknViewAppUi::HandleViewDeactivation( 
			aViewIdToBeDeactivated, 
			aNewlyActivatedViewId );
	// [[[ begin generated region: do not modify [Generated Contents]
	// ]]] end generated region [Generated Contents]
	
	}

/**
 * @brief Completes the second phase of Symbian object construction. 
 * Put initialization code that could leave here. 
 */ 
void CTRamAppUi::ConstructL()
	{
	// [[[ begin generated region: do not modify [Generated Contents]
	
	BaseConstructL( EAknEnableSkin ); 
	InitializeContainersL();
	// ]]] end generated region [Generated Contents]
	ReadSettings();
	iInfo=CTopInfo::NewL(TPoint(iSettings[0],iSettings[1]),TSize(iSettings[2],iSettings[3]));
	iInfo->SetColor(TRgb(iSettings[4],iSettings[5],iSettings[6],iSettings[7]));
	iInfo->Show();
	iTimer=CPeriodic::NewL(CActive::EPriorityHigh);
	iTimer->Start(1000000,1000000,TCallBack(Tick,this));
	HideApplicationFromFSW(ETrue);
	CEikonEnv::Static()->RootWin().SetOrdinalPosition(-4);
	}

void CTRamAppUi::ReadSettings()
	{
	TInt err=KErrNone;
	iSettings.Reset();
	if (BaflUtils::FileExists(CEikonEnv::Static()->FsSession(),KSettingPath)) //!!!!!!!!!!!!!!!!!!!!!!!!!!!
		{
		TBuf<255> val;
		RFile filesave;
		TBuf<10> t;
		TFileText ft;
		TInt IntVal;
		filesave.Open(CEikonEnv::Static()->FsSession(), KSettingPath, EFileRead);
		ft.Set(filesave);
		while (ft.Read(val)==KErrNone)
			{
			TLex conv(val);
			conv.Val(IntVal);
			iSettings.Append(IntVal);
			}
		filesave.Close();
		}
	else
		{
		TParse parse;
		CEikonEnv::Static()->FsSession().Parse(KSettingPath,parse);
		if (!BaflUtils::FolderExists(CEikonEnv::Static()->FsSession(),parse.DriveAndPath()))
			{
			CEikonEnv::Static()->FsSession().MkDirAll(parse.DriveAndPath());
			}
		iSettings.Append(KPosX);
		iSettings.Append(KPosY);
		iSettings.Append(KWidth);
		iSettings.Append(KHeight);
		iSettings.Append(KRed);
		iSettings.Append(KGreen);
		iSettings.Append(KBlue);
		iSettings.Append(KAlpha);
		WriteSettings();
		}
	}
void CTRamAppUi::WriteSettings()
	{
		RFs iFS=CEikonEnv::Static()->FsSession();
		RFile filesave;
		TInt err1=filesave.Replace(iFS, KSettingPath, EFileWrite);
		TFileText ft;
		ft.Set(filesave);
		TInt i;
		TBuf<255> temp;
		for (i=0;i<iSettings.Count();i++)
			{
			temp.Num(iSettings[i]);
			ft.Write(temp);
			}
		filesave.Close();
	}
TInt CTRamAppUi::Tick(TAny* aObj)
	{
	TRealFormat rf;
	TBuf <255> txt;
	TInt val;
	HAL::Get(HAL::EMemoryRAMFree,val);
	TReal real=val/(1024.0*1024.0);
	TReal round;
	Math::Round(round,real,2);
	txt.Num(round,rf);
	((CTRamAppUi*)aObj)->iInfo->Update(txt);
	}
