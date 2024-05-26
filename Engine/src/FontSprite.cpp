//----------------------------------------------------------------------------
// Copyright 2023, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#include "FontSprite.h"
#include "GlyphMan.h"
#include "GraphicsObject_Sprite.h"

namespace Azul
{
	FontSprite::~FontSprite()
	{
		delete[] this->poMessage;
	}

	FontSprite::FontSprite(GraphicsObject *pGraphicsObject)
		: Sprite(pGraphicsObject),
		name(FontSprite::Name::Uninitialized),
		pScreenRect(nullptr),
		poMessage(nullptr),
		glyphName(Glyph::Name::Uninitialized),
		x(0.0f),
		y(0.0f)
	{
	}

	void FontSprite::Set(FontSprite::Name _name,
						 const char *_pMessage,
						 Glyph::Name _glyphName,
						 float xStart,
						 float yStart)
	{
		Color color(1, 1, 1, 1);
		this->Set(_name, _pMessage, _glyphName, xStart, yStart, color);
	}

	void FontSprite::Set(FontSprite::Name _name,
						 const char *_pMessage,
						 Glyph::Name _glyphName,
						 float xStart,
						 float yStart,
						 Color &_color)
	{
		// Deep copy
		assert(_pMessage);
		size_t size = strlen(_pMessage) + 1;
		this->poMessage = new char[size]();
		memset(this->poMessage, 0, size);
		memcpy_s(this->poMessage, size, _pMessage, size - 1);

		this->x = xStart;
		this->y = yStart;

		this->name = _name;
		this->glyphName = _glyphName;

		pGraphicsObjectSprite->color = _color;
	}

	void FontSprite::UpdateMessage(const char *_pMessage)
	{
		delete[] this->poMessage;
		// Deep copy
		assert(_pMessage);
		size_t size = strlen(_pMessage) + 1;
		this->poMessage = new char[size]();
		memset(this->poMessage, 0, size);
		memcpy_s(this->poMessage, size, _pMessage, size - 1);
	}

	void FontSprite::Draw()
	{	
		assert(poMessage);
		size_t len = strlen(poMessage);

		Rect screenRect;

		float xTmp = this->x;
		float yTmp = this->y;

		float xEnd = this->x;

		for(size_t i = 0; i < len; i++)
		{
			int key = (int)poMessage[i];

			Glyph *pGlyph = GlyphMan::Find(this->glyphName, key);
			assert(pGlyph);

			xTmp = xEnd + pGlyph->glyphRect.width / 2;
			screenRect.Set(xTmp, yTmp, pGlyph->glyphRect.width, pGlyph->glyphRect.height);

			pGraphicsObjectSprite->SetTexture(pGlyph->pText);
			pGraphicsObjectSprite->SetImage(pGlyph->glyphRect, pGlyph->pText);
			pGraphicsObjectSprite->SetScreenRect(screenRect);

			this->posX = xTmp;
			this->posY = yTmp;
			Sprite::Update(AnimTime());
			Sprite::Draw();
		

			// move the starting to the next character
			xEnd = pGlyph->glyphRect.width / 2 + xTmp;

		}
	}


	void FontSprite::privUpdate(AnimTime currentTime)
	{
		AZUL_UNUSED_VAR(currentTime);

	}

	void FontSprite::Update(AnimTime currentTime)
	{

		// update the bounding volume based on world matrix
		this->poGraphicsObject->SetWorld(*this->poWorld);
	}

}

//--- End of File ---
