#include "pch.h"
#include "GameEvent.h"

#include "Camera.h"
#include "TextBox.h"
IChangeCameraTargetEvent::IChangeCameraTargetEvent(GameObject * target)
{
	mTarget = target;
}

void IChangeCameraTargetEvent::Start()
{
	CameraManager::GetInstance()->GetMainCamera()->SetTarget(mTarget);
}

bool IChangeCameraTargetEvent::Update()
{
	float x = CameraManager::GetInstance()->GetMainCamera()->GetX();
	float y = CameraManager::GetInstance()->GetMainCamera()->GetY();

	if (Math::GetDistance(x, y, mTarget->GetX(), mTarget->GetY()) <= 5.0f)
	{
		return true;
	}

	return false;
}

IDelayEvent::IDelayEvent(float delayTime)
{
	mDelayTime = delayTime;
	mCurrentTime = 0.f;
}

void IDelayEvent::Start()
{
}

bool IDelayEvent::Update()
{
	mCurrentTime += Time::GetInstance()->DeltaTime();

	if (mCurrentTime >= mDelayTime)
	{
		return true;
	}

	return false;
}

ITextEvent::ITextEvent(float textDelayTime, wstring textContent)
{
	mTextDelayTime = textDelayTime;
	mTextContent = textContent;
	mCurrentTime = 0;
}

void ITextEvent::Start()
{
	mTextBox = new TextBox(mTextContent);
	mTextBox->Init();
	ObjectManager::GetInstance()->AddObject(ObjectLayer::UI, mTextBox);
}

bool ITextEvent::Update()
{
	mCurrentTime += Time::GetInstance()->DeltaTime();

	if (mCurrentTime >= mTextDelayTime)
	{
		mTextBox->SetIsDestroy(true);
		return true;
	}

	return false;
}

ITileEvent::ITileEvent(ITileEvent::Mode mode, float x, float y)
{
	mMode = mode;
	mControlPointX = x;
	mCoutrolPointY = y;
}

void ITileEvent::Start()
{
	GameObject* player = ObjectManager::GetInstance()->FindObject("Player");
	mPlayerX = player->GetX();
	mPlayerY = player->GetY();
}

bool ITileEvent::Update()
{
	GameObject* player = ObjectManager::GetInstance()->FindObject("Player");
	mPlayerX = player->GetX();
	mPlayerY = player->GetY();
	if (mMode == ITileEvent::Mode::UpLeft)
	{
		if (mPlayerX < mControlPointX
			&& mPlayerY < mCoutrolPointY)
		{
			return true;
		}
	}
	else if (mMode == ITileEvent::Mode::UpRight)
	{
		if (mPlayerX > mControlPointX
			&& mPlayerY < mCoutrolPointY)
		{
			return true;
		}
	}
	else if (mMode == ITileEvent::Mode::DownLeft)
	{
		if (mPlayerX < mControlPointX
			&& mPlayerY > mCoutrolPointY)
		{
			return true;
		}
	}
	else if (mMode == ITileEvent::Mode::DownRight)
	{
		if (mPlayerX > mControlPointX
			&& mPlayerY > mCoutrolPointY)
		{
			return true;
		}
	}
	return false;
}
