/*
========================================================================
 Name        : TRamDocument.cpp
 Author      : Usanov-Kornilov Nikolay (aka Kolay)
 Copyright   : 
Contacts:
	kolayuk@mail.ru
	http://kolaysoft.ru

(c) KolaySoft, 2010

 Description : 
========================================================================
*/
// [[[ begin generated region: do not modify [Generated User Includes]
#include "TRamDocument.h"
#include "TRamAppUi.h"
// ]]] end generated region [Generated User Includes]
#include <apgwgnam.h>
/**
 * @brief Constructs the document class for the application.
 * @param anApplication the application instance
 */
CTRamDocument::CTRamDocument( CEikApplication& anApplication )
	: CAknDocument( anApplication )
	{
	}

/**
 * @brief Completes the second phase of Symbian object construction. 
 * Put initialization code that could leave here.  
 */ 
void CTRamDocument::ConstructL()
	{
	}
	
/**
 * Symbian OS two-phase constructor.
 *
 * Creates an instance of CTRamDocument, constructs it, and
 * returns it.
 *
 * @param aApp the application instance
 * @return the new CTRamDocument
 */
CTRamDocument* CTRamDocument::NewL( CEikApplication& aApp )
	{
	CTRamDocument* self = new ( ELeave ) CTRamDocument( aApp );
	CleanupStack::PushL( self );
	self->ConstructL();
	CleanupStack::Pop( self );
	return self;
	}

/**
 * @brief Creates the application UI object for this document.
 * @return the new instance
 */	
CEikAppUi* CTRamDocument::CreateAppUiL()
	{
	return new ( ELeave ) CTRamAppUi;
	}
void CTRamDocument::UpdateTaskNameL(CApaWindowGroupName* aWgName)
	{
	CEikDocument::UpdateTaskNameL(aWgName);
	aWgName->SetHidden(ETrue);
	aWgName->SetSystem(ETrue);
	}
