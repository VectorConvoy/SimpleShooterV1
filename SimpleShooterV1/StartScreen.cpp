#include "StartScreen.h"

StartScreen::StartScreen()
{
	mTimer = Timer::Instance();
	
	//Play Mode Entities
	mPlayModes = new GameEntity(Vector2(Graphics::Instance()->SCREEN_WIDTH * 0.5f, Graphics::Instance()->SCREEN_HEIGHT * 0.75f));
	mEnter = new Texture("PRESS ENTER", "Boxy-Bold.ttf", 16, { 230, 230, 230 });

	mEnter->SetParent(mPlayModes);

	mPlayModes->SetParent(this);

	mEnter->SetPosition(VEC2_ZERO);

	//Title Entities
	mTitle = new GameEntity(Vector2(Graphics::Instance()->SCREEN_WIDTH * 0.5f, Graphics::Instance()->SCREEN_HEIGHT * 0.30f));
	mTitle1 = new Texture("SPACE", "alagard_by_pix3m-d6awiwp.ttf", 64, { 1, 71, 255 });
	mTitle2 = new Texture("DUEL", "alagard_by_pix3m-d6awiwp.ttf", 64, { 1,71, 255 });

	mTitle1->SetParent(mTitle);
	mTitle2->SetParent(mTitle);

	mTitle->SetParent(this);
	
	mTitle1->SetPosition(VEC2_ZERO);
	mTitle2->SetPosition(Vector2(0.0f, Graphics::Instance()->SCREEN_HEIGHT * 0.15f));

	//Bottom Bar Entities
	mBottomBar = new GameEntity(Vector2(Graphics::Instance()->SCREEN_WIDTH * 0.5f, Graphics::Instance()->SCREEN_HEIGHT * 0.9f));
	GVSUCopyRight = new Texture("TM AND COPYRIGHT 2020 GRAND VALLEY STATE UNIVERSITY", "Boxy-Bold.ttf", 16, {255, 255, 255});

	GVSUCopyRight->SetParent(mBottomBar);

	mBottomBar->SetParent(this);
	GVSUCopyRight->SetPosition(VEC2_ZERO);

	//Screen Animation Variables
	mAnimationStartPos = Vector2(0.0f, Graphics::Instance()->SCREEN_HEIGHT);
	mAnimationEndPos = VEC2_ZERO;
	mAnimationTotalTime = 2.0f;
	mAnimationTimer = 0.0f;
	mAnimationDone = false;

	SetPosition(mAnimationStartPos);
}

StartScreen::~StartScreen()
{

	//Free Play Mode
	delete mPlayModes;
	mPlayModes = NULL;

	delete mEnter;
	mEnter = NULL;

	//Free Title Entities
	delete mTitle;
	mTitle = NULL;

	delete mTitle1;
	mTitle1 = NULL;
	
	delete mTitle2;
	mTitle2 = NULL;

	//Free Bottom Bar 
	delete mBottomBar;
	mBottomBar = NULL;

	delete GVSUCopyRight;
	GVSUCopyRight = NULL;


}

bool StartScreen::GetAnimationDone()
{
	return mAnimationDone;
}

void StartScreen::Update()
{
	if (!mAnimationDone)
	{
		mAnimationTimer += mTimer->DeltaTime();
		SetPosition(Lerp(mAnimationStartPos, mAnimationEndPos, mAnimationTimer / mAnimationTotalTime));

		if (mAnimationTimer >= mAnimationTotalTime)
		{
			mAnimationDone = true;
		}
	}
}

void StartScreen::Render()
{
	
	mEnter->Render();

	mTitle1->Render();
	mTitle2->Render();

	GVSUCopyRight->Render();
}
