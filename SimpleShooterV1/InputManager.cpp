#include "InputManager.h"

InputManager* InputManager::sInstance = NULL;


InputManager* InputManager::Instance()
{
    if (sInstance == NULL)
    {
        sInstance = new InputManager();
    }

    return sInstance;
}

void InputManager::Release()
{
    delete sInstance;
    sInstance = NULL;
}

bool InputManager::KeyDown(SDL_Scancode scanCode)
{
    return mKeyboardState[scanCode];
}

bool InputManager::KeyPressed(SDL_Scancode scanCode)
{
    
    return !mPreviousKeyboardState[scanCode] && mKeyboardState[scanCode];
}

bool InputManager::KeyReleased(SDL_Scancode scanCode)
{
    return mPreviousKeyboardState[scanCode] && !mKeyboardState[scanCode];
}

bool InputManager::MouseButtonDown(MOUSE_BUTTON button)
{
    Uint32 mask = 0;

    switch (button)
    {
    case left:
        mask = SDL_BUTTON_LMASK;
        break;
    case right:
        mask = SDL_BUTTON_RMASK;
        break;
    case middle:
        mask = SDL_BUTTON_MMASK;
        break;
    case forward:
        mask = SDL_BUTTON_X2MASK;
    case back:
        mask = SDL_BUTTON_X1MASK;
    }
    return (mMouseState & mask);
}

bool InputManager::MouseButtonPressed(MOUSE_BUTTON button)
{
    Uint32 mask = 0;

    switch (button)
    {
    case left:
        mask = SDL_BUTTON_LMASK;
        break;
    case right:
        mask = SDL_BUTTON_RMASK;
        break;
    case middle:
        mask = SDL_BUTTON_MMASK;
        break;
    case forward:
        mask = SDL_BUTTON_X2MASK;
    case back:
        mask = SDL_BUTTON_X1MASK;
    }
    return !(mPreviousMouseState & mask) && (mMouseState & mask);
}

bool InputManager::MouseButtonReleased(MOUSE_BUTTON button)
{
    Uint32 mask = 0;

    switch (button)
    {
    case left:
        mask = SDL_BUTTON_LMASK;
        break;
    case right:
        mask = SDL_BUTTON_RMASK;
        break;
    case middle:
        mask = SDL_BUTTON_MMASK;
        break;
    case forward:
        mask = SDL_BUTTON_X2MASK;
    case back:
        mask = SDL_BUTTON_X1MASK;
    }
    return (mPreviousMouseState & mask) && !(mMouseState & mask);
}

Vector2 InputManager::MousePos()
{
    return Vector2((float)mMouseXPos, (float)mMouseYPos);
}

void InputManager::Update()
{
    //mKeyboardState = SDL_GetKeyboardState(NULL);
    mMouseState = SDL_GetMouseState(&mMouseXPos, &mMouseYPos);
}

void InputManager::UpdatePreviousInput()
{
    memcpy(mPreviousKeyboardState, mKeyboardState, mKeyLength);
    mPreviousMouseState = mMouseState;
}

InputManager::InputManager()
{
    mKeyboardState = SDL_GetKeyboardState(&mKeyLength);
    mPreviousKeyboardState = new Uint8[mKeyLength];
    memcpy(mPreviousKeyboardState, mKeyboardState, mKeyLength);
}

InputManager::~InputManager()
{
    delete[] mPreviousKeyboardState;
    mPreviousKeyboardState = NULL;
}
