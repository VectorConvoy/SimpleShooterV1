#pragma once
#define _TEXTURE_H

#include "GameEntity.h"
#include "AssetManager.h"


class Texture : public GameEntity
{
public:
	Texture(std::string filename);
	Texture(std::string filename, int x, int y, int w, int h);
	Texture(std::string text, std::string fontPath, int size, SDL_Color color);
	~Texture();

	int GetTextureWidth();
	int GetTextureHeight();

	void SetClipped(int x, int y, int w, int h);

	virtual void Render();

protected:
	SDL_Texture* mTexture;
	Graphics* mGraphics;

	int mWidth;
	int mHeight;

	bool mClipped;

	SDL_Rect mRenderRect;
	SDL_Rect mClippedRect;

};

