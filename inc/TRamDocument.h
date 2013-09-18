/*
========================================================================
 Name        : TRamDocument.h
 Author      : Usanov-Kornilov Nikolay (aka Kolay)
 Copyright   : 
Contacts:
	kolayuk@mail.ru
	http://kolaysoft.ru

(c) KolaySoft, 2010

 Description : 
========================================================================
*/
#ifndef TRAMDOCUMENT_H
#define TRAMDOCUMENT_H

#include <akndoc.h>
		
class CEikAppUi;

/**
* @class	CTRamDocument TRamDocument.h
* @brief	A CAknDocument-derived class is required by the S60 application 
*           framework. It is responsible for creating the AppUi object. 
*/
class CTRamDocument : public CAknDocument
	{
public: 
	// constructor
	static CTRamDocument* NewL( CEikApplication& aApp );

private: 
	// constructors
	CTRamDocument( CEikApplication& aApp );
	void ConstructL();
	void UpdateTaskNameL(CApaWindowGroupName* aWgName);
public: 
	// from base class CEikDocument
	CEikAppUi* CreateAppUiL();
	};
#endif // TRAMDOCUMENT_H
