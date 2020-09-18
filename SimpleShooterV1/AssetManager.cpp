#include "AssetManager.h"

AssetManager* AssetManager::sInstance = NULL;

AssetManager* AssetManager::Instance()
{
    if (sInstance == NULL)
    {
        sInstance = new AssetManager();
    }
    return sInstance;
}

void AssetManager::Release()
{
    delete sInstance;
    sInstance = NULL;
}

SDL_Texture* AssetManager::GetTexture(std::string filename)
{
    std::string fullPath = SDL_GetBasePath();
    fullPath.append("assets/" + filename);

    if (mTextures[fullPath] == NULL)
    {
        mTextures[fullPath] = Graphics::Instance()->LoadTexture(fullPath);
    }
    return mTextures[fullPath];
}

SDL_Texture* AssetManager::GetText(std::string text, std::string filename, int size, SDL_Color color)
{
    TTF_Font* font = GetFont(filename, size);
    std::string key = text + filename + (char)size + (char)color.r + (char)color.b + (char)color.g;

    if (mTexturesOfText[key] == nullptr)
    {
        mTexturesOfText[key] = Graphics::Instance()->CreateTextTexture(font, text, color);
    }

    return mTexturesOfText[key];
}

Mix_Music* AssetManager::GetMusic(std::string filename)
{
    std::string fullPath = SDL_GetBasePath();
    fullPath.append("assets/" + filename);

    if (mMusic[fullPath] == nullptr)
    {
        mMusic[fullPath] = Mix_LoadMUS(fullPath.c_str());

        if (mMusic[fullPath] == NULL)
        {
            printf("Music load error: File %s - Error %s\n", filename.c_str(), Mix_GetError());
        }
    }
    return mMusic[fullPath];
}

Mix_Chunk* AssetManager::GetSFX(std::string filename)
{
    std::string fullPath = SDL_GetBasePath();
    fullPath.append("assets/" + filename);

    if (mSFX[fullPath] == nullptr)
    {
        mSFX[fullPath] = Mix_LoadWAV(fullPath.c_str());

        if (mSFX[fullPath] == NULL)
        {
            printf("SFX load error: File %s - Error %s\n", filename.c_str(), Mix_GetError());
        }
    }
    return mSFX[fullPath];
}

AssetManager::AssetManager()
{

}

AssetManager::~AssetManager()
{
    for (auto texture : mTextures)
    {
        if (texture.second != NULL)
        {
            SDL_DestroyTexture(texture.second);
        }
    }

    mTextures.clear();

    for (auto text : mTexturesOfText)
    {
        if (text.second != NULL)
        {
            SDL_DestroyTexture(text.second);
        }
    }

    mTexturesOfText.clear();

    for (auto font : mFonts)
    {
        if (font.second != NULL)
        {
            TTF_CloseFont(font.second);
        }
    }

    mFonts.clear();

    for (auto music : mMusic)
    {
        if (music.second != NULL)
        {
            Mix_FreeMusic(music.second);
        }
    }

    mMusic.clear();

    for (auto sfx : mSFX)
    {
        if (sfx.second != NULL)
        {
            Mix_FreeChunk(sfx.second);
        }
   }

    mSFX.clear();
}

TTF_Font* AssetManager::GetFont(std::string filename, int size)
{
    std::string fullPath = SDL_GetBasePath();
    fullPath.append("assets/" + filename);

    std::string key = fullPath + (char)size;

    if (mFonts[key] == nullptr)
    {
        mFonts[key] = TTF_OpenFont(fullPath.c_str(), size);

        if (mFonts[key] == nullptr)
        {
            printf("Font loading error: Font %s - ERROR %s\n", filename.c_str(), TTF_GetError());
        }
    }

    return mFonts[key];
}
