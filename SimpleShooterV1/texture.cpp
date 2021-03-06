#include "texture.h"


Texture::Texture(std:: string filename)
{
	mGraphics = Graphics::Instance();

	mTexture = AssetManager::Instance()->GetTexture(filename);

	SDL_QueryTexture(mTexture, NULL, NULL, &mWidth, &mHeight);

	mClipped = false;

	mRenderRect.w = mWidth;
	mRenderRect.h = mHeight;
}

Texture::Texture(std::string filename, int x, int y, int w, int h)
{
	mGraphics = Graphics::Instance();

	mTexture = AssetManager::Instance()->GetTexture(filename);

	mClipped = true;
	mWidth = w;
	mHeight = h;

	mRenderRect.w = mWidth;
	mRenderRect.h = mHeight;

	mClippedRect.x = x;
	mClippedRect.y = y;
	mClippedRect.w = mWidth;
	mClippedRect.h = mHeight;
}

Texture::Texture(std::string text, std::string fontPath, int size, SDL_Color color)
{
	mGraphics = Graphics::Instance();

	mTexture = AssetManager::Instance()->GetText(text, fontPath, size, color);

	mClipped = false;

	SDL_QueryTexture(mTexture, NULL, NULL, &mWidth, &mHeight);

	mRenderRect.w = mWidth;
	mRenderRect.h = mHeight;
}

Texture::~Texture()
{
	mTexture = NULL;
	mGraphics = NULL;
}

int Texture::GetTextureWidth()
{
	return mWidth;
}

int Texture::GetTextureHeight()
{
	return mHeight;
}

Vector2 Texture::ScaledDimensions()
{
	Vector2 scaledDimensions = GetScale();

	scaledDimensions.x *= mWidth;
	scaledDimensions.y *= mHeight;
	return scaledDimensions;
}

SDL_Rect Texture::GetRenderRect()
{
	return mRenderRect;
}

SDL_Rect Texture::GetClippedRect()
{
	return mClippedRect;
}

void Texture::SetClipped(int x, int y, int w, int h)
{
	mClipped = true;
	mClippedRect.x = x;
	mClippedRect.y = y;
	mClippedRect.w = w;
	mClippedRect.h = h;
}

void Texture::UpdatePosition(int x, int y)
{
	mRenderRect.x = x;
	mRenderRect.y = y;
}

void Texture::Render()
{
	Vector2 position = GetPosition(SPACE::world);

	Vector2 scale = GetScale(SPACE::world);


	//Center texture on world
	mRenderRect.x = (int)(position.x - mWidth * scale.x*0.5f);
	mRenderRect.y = (int)(position.y - mHeight * scale.y*0.5f);
	
	//Scale width and height
	mRenderRect.w = (int)(mWidth * scale.x);
	mRenderRect.h = (int)(mHeight * scale.y);
	
	mGraphics->DrawTexture(mTexture,(mClipped) ? &mClippedRect : NULL, &mRenderRect, GetRotation(SPACE::world));
}
