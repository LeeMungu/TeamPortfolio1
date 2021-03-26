#include "pch.h"
#include "GameEvent.h"

#include "Camera.h"
#include "TextBox.h"
#include "Zombie01.h"
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

IAllUnitStopTime::IAllUnitStopTime(float DelayTime)
{
	mDelayTime = DelayTime;
	mCurrentTime = 0;

}

void IAllUnitStopTime::Start()
{
	GameObject* player = ObjectManager::GetInstance()->FindObject(ObjectLayer::Player, "Player");
	vector<GameObject*> monster = ObjectManager::GetInstance()->GetObjectList(ObjectLayer::Enemy);
	if (monster.size() != NULL)
	{
		for (int i = 0; i < monster.size(); ++i)
		{
			monster[i]->SetIsActive(false);
		}
	}
	player->SetIsActive(false);
}

bool IAllUnitStopTime::Update()
{
	if (mDelayTime < mCurrentTime)
	{
		GameObject* player = ObjectManager::GetInstance()->FindObject(ObjectLayer::Player, "Player");
		vector<GameObject*> monster = ObjectManager::GetInstance()->GetObjectList(ObjectLayer::Enemy);
		if (monster.size() != NULL)
		{
			for (int i = 0; i < monster.size(); ++i)
			{
				monster[i]->SetIsActive(true);
			}
		}
		player->SetIsActive(true);
		return true;
	}
	else if (mDelayTime >= mCurrentTime)
	{
		mCurrentTime += Time::GetInstance()->DeltaTime();
		return false;
	}
}

IAllUnitActive::IAllUnitActive()
{
}

void IAllUnitActive::Start()
{
	GameObject* player = ObjectManager::GetInstance()->FindObject(ObjectLayer::Player, "Player");
	vector<GameObject*> monster = ObjectManager::GetInstance()->GetObjectList(ObjectLayer::Enemy);
	if (monster.size() != NULL)
	{
		for (int i = 0; i < monster.size(); ++i)
		{
			monster[i]->SetIsActive(true);
		}
	}
	player->SetIsActive(true);
}

bool IAllUnitActive::Update()
{
	GameObject* player = ObjectManager::GetInstance()->FindObject(ObjectLayer::Player, "Player");
	vector<GameObject*> monster = ObjectManager::GetInstance()->GetObjectList(ObjectLayer::Enemy);
	if (player->GetIsActive() == true)
	{
		if (monster.size() != NULL)
		{
			for (int i = 0; i < monster.size(); ++i)
			{
				if (monster[i]->GetIsActive() == false)
				{
					monster[i]->SetIsActive(true);
					return false;
				}
			}
			//여기까지 왔다면 모두 트루다.
			return true;
		}
	}
	else if (player->GetIsActive() == false)
	{
		player->SetIsActive(true);
		return false;
	}
}

IAllUnitStop::IAllUnitStop()
{
}

void IAllUnitStop::Start()
{
	GameObject* player = ObjectManager::GetInstance()->FindObject(ObjectLayer::Player, "Player");
	vector<GameObject*> monster = ObjectManager::GetInstance()->GetObjectList(ObjectLayer::Enemy);
	if (monster.size() != NULL)
	{
		for (int i = 0; i < monster.size(); ++i)
		{
			monster[i]->SetIsActive(false);
		}
	}
	player->SetIsActive(false);
}

bool IAllUnitStop::Update()
{

	GameObject* player = ObjectManager::GetInstance()->FindObject(ObjectLayer::Player, "Player");
	vector<GameObject*> monster = ObjectManager::GetInstance()->GetObjectList(ObjectLayer::Enemy);
	if (player->GetIsActive() == false)
	{
		if (monster.size() != NULL)
		{
			for (int i = 0; i < monster.size(); ++i)
			{
				if (monster[i]->GetIsActive() == true)
				{
					monster[i]->SetIsActive(false);
					return false;
				}
			}
			//for를 다돌았다면 모두 정지상태
			return true;
		}
	}
	else if (player->GetIsActive() == true)
	{
		player->SetIsActive(false);
		return false;
	}
}

IZombiGeneration::IZombiGeneration(float x, float y, vector<vector<Tile*>>& tileList)
{
	mX = x;
	mY = y;
	mTileList = tileList;
}

void IZombiGeneration::Start()
{
	Zombie01* zombi = new Zombie01(mX, mY);
	zombi->SetTileList(mTileList);
	zombi->Init();
	ObjectManager::GetInstance()->AddObject(ObjectLayer::Enemy, zombi);
}

bool IZombiGeneration::Update()
{
	if (ObjectManager::GetInstance()->GetObjectList(ObjectLayer::Enemy).size() != NULL)
	{
		return true;
	}
	else
	{
		Zombie01* zombi = new Zombie01(mX, mY);
		zombi->SetTileList(mTileList);
		zombi->Init();
		ObjectManager::GetInstance()->AddObject(ObjectLayer::Enemy, zombi);
		return false;
	}
}

IDelayFunEvent::IDelayFunEvent(float delayTime, function<void(void)> func)
{
	mDelayTime = delayTime;
	mCurrentTime = 0.f;
	mFunc = func;
}

void IDelayFunEvent::Start()
{

}

bool IDelayFunEvent::Update()
{
	if (mDelayTime < mCurrentTime)
	{
		mFunc();
		return true;
	}
	else
	{
		mCurrentTime += Time::GetInstance()->DeltaTime();
		return false;
	}
}
//형태도 바꿔야하고 그걸 바꿔서 어떻게 넣어야하는지
IObjectCrushEvent::IObjectCrushEvent(GameObject* object1, GameObject* object2)
{
	mObject1 = object1;
	mObject2 = object2;
	//mObjectRect = object->GetRect();
}

void IObjectCrushEvent::Start()
{
	//mPlayerRect = ObjectManager::GetInstance()->FindObject(ObjectLayer::Player, "Player")->GetRect();
}

bool IObjectCrushEvent::Update()
{
	RECT temp;
	RECT rc1 = mObject1->GetRect();
	RECT rc2 = mObject2->GetRect();
	if (IntersectRect(&temp, &rc1,&rc2))
	{
		return true;
	}
	return false;
}
