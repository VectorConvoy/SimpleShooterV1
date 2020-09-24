#include "graphics.h"

Graphics* Graphics::sInstance = NULL;
bool Graphics::sInitialized = false;

Graphics* Graphics::Instance()
{
	if (sInstance == NULL)
	{
		sInstance = new Graphics();
	}
	return sInstance;
}

void Graphics::Release()
{
	delete sInstance;
	sInstance = NULL;

	sInitialized = false;
}

bool Graphics::Initialized()
{
	return sInitialized;
}

SDL_Texture* Graphics::LoadTexture(std::string path)
{
	SDL_Texture* texture = NULL;

	SDL_Surface* surface = IMG_Load(path.c_str());

	if (surface == NULL)
	{
		printf(" Image Load error: Path(%s) - %s\n",path.c_str(), IMG_GetError());		
		return texture;
	}

	texture = SDL_CreateTextureFromSurface(mRenderer, surface);

	SDL_FreeSurface(surface);

	if (texture == NULL)
	{
		printf("Create texture error: %s\n", SDL_GetError());
		return texture;
	}

	return texture;
}

SDL_Texture* Graphics::CreateTextTexture(TTF_Font* font, std::string text, SDL_Color color)
{
	SDL_Surface* surface = TTF_RenderText_Solid(font, text.c_str(), color);
	
	if (surface == NULL)
	{
		printf("Text Render Error: %s\n", TTF_GetError());
		return NULL;
	}

	SDL_Texture* textureOfText = SDL_CreateTextureFromSurface(mRenderer, surface);

	if (textureOfText == NULL)
	{
		printf("Texture Creation from Surface failed: %s\n", SDL_GetError());
		return NULL;
	}

	SDL_FreeSurface(surface);

	return textureOfText;
}

void Graphics::ClearBackBuffer()
{
	SDL_RenderClear(mRenderer);
}

void Graphics::DrawTexture(SDL_Texture* texture, SDL_Rect* clippedRect, SDL_Rect* renderRect, float angle, SDL_RendererFlip flip)
{
	//SDL_RenderCopy(mRenderer, texture, clippedRect, renderRect);
	SDL_RenderCopyEx(mRenderer, texture, clippedRect, renderRect, angle, NULL, flip);
}

void Graphics::Render()
{
	////Refreshes the back buffer of the window
	//SDL_UpdateWindowSurface(mWindow);

	SDL_RenderPresent(mRenderer);
}

Graphics::Graphics()
{
	mBackBuffer = NULL;
	sInitialized = Init();
}

Graphics::~Graphics()
{
	SDL_DestroyWindow(mWindow);
	mWindow = NULL;

	SDL_DestroyRenderer(mRenderer);

	//Close SDL Image
	IMG_Quit();

	//Close SDL TTF
	TTF_Quit();

	//Close SDL
	SDL_Quit();
}

bool Graphics::Init()
{
	bool successful = false;
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0)
	{
		printf("SDL Initialization Error: %s\n", SDL_GetError());
		return successful;
	}

	mWindow = SDL_CreateWindow("CIS 693 Project", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);

	if (mWindow == NULL)
	{
		printf("Window creation Error: %s\n", SDL_GetError());
		return successful;
	}

	mRenderer = SDL_CreateRenderer(mWindow, -1, SDL_RENDERER_ACCELERATED);

	if (mRenderer == NULL)
	{
		printf("Renderer creation error: %s\n", SDL_GetError());
		successful = false;
	}

	SDL_SetRenderDrawColor(mRenderer, 0x00, 0x00, 0x00, 0xFF);

	int flags = IMG_INIT_PNG;
	if (!IMG_Init(flags) & flags)
	{
		printf("Image Initialization error: %s\n", IMG_GetError());
		successful = false;
	}

	if (TTF_Init() == -1)
	{
		printf("TTF Initialization Error: %s\n", TTF_GetError());
		successful = false;
	}

	

	mBackBuffer = SDL_GetWindowSurface(mWindow);


	successful = true;
	return successful;
}
