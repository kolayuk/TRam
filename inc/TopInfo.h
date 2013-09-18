/*
 ============================================================================
 Name		: TopInfo.h
 Author	  : Usanov-Kornilov Nikolay (aka Kolay)
 Version	 : 1.0
 Copyright   : 
 Contacts:
 kolayuk@mail.ru
 http://kolaysoft.ru

 (c) KolaySoft, 2010

 Description : CTopInfo declaration
 ============================================================================
 */

#ifndef TOPINFO_H
#define TOPINFO_H

// INCLUDES
#include <e32std.h>
#include <e32base.h>
#include <w32std.h>


// CLASS DECLARATION
class CTopInfo : public CBase
	{
public:
	~CTopInfo();
	static CTopInfo* NewL(TPoint aPos,TSize aSize);
	static CTopInfo* NewLC(TPoint aPos,TSize aSize);
	void Show();
	void Hide();
	void Update(TDes& aText);
	void SetColor(TRgb aColor);
private:
	CTopInfo();
	void ConstructL(TPoint aPos,TSize aSize);
	RWsSprite* iSprite;
	TSpriteMember iMember;
	CFbsBitmap* iBitmap;
	CFbsBitmap* iMask;
	CFbsBitGc* iBitGc;
	CFbsBitGc* iMaskGc;
	TSize iSize;
	RWindowGroup* iWinGroup;
	TPoint iPos;
	TBool isVisible;
	CFont* iFont;
	HBufC* iText;
	void Draw();
	TRgb iColor;
	TInt iTransparency;
	};

#endif // TOPINFO_H
