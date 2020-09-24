#pragma once

#ifndef _GRAPHICS_H
#define _GRAPHICS_H

#include <SDL.h>
#include <SDL_image.h>
#include<SDL_ttf.h>
#include <stdio.h>
#include <string>

class Graphics
{
public:
	static const int SCREEN_WIDTH = 1024;
	static const int SCREEN_HEIGHT = 720;

	const char* WINDOW_TITLE = "CIS 693 Project";

	static Graphics* Instance();
	static void Release(); //Clear any static memory allocation

	static bool Initialized();

	SDL_Texture* LoadTexture(std::string path);
	SDL_Texture* CreateTextTexture(TTF_Font* font, std::string text, SDL_Color color);

	void ClearBackBuffer();

	void DrawTexture(SDL_Texture* texture, SDL_Rect* clippedRect = NULL, SDL_Rect* renderRect = NULL, float angle = 0.0f, SDL_RendererFlip flip = SDL_FLIP_NONE);

	void Render(); //Refresh buffer


private:
	static Graphics* sInstance; //Pointer and is a singleton since we only need 1 instance
	static bool sInitialized; //Determines if graphics initialized correctly

	SDL_Window* mWindow;
	SDL_Surface* mBackBuffer;
	SDL_Renderer* mRenderer;

	Graphics();
	~Graphics();

	bool Init(); //Initalize

};

#endif // !_GRAPHICS_H
