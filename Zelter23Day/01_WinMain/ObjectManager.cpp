#include "pch.h"
#include "ObjectManager.h"
#include "Camera.h"
#include <algorithm>


#include "GameObject.h"
ObjectManager::ObjectManager()
{
	//ObjectLayer 별로 벡터 하나씩 맵에 집어 넣는다.
	for (int i = 0; i < (int)ObjectLayer::End; ++i)
	{
		vector<GameObject*> emptyVector;
		mObjectList.insert(make_pair((ObjectLayer)i, emptyVector));
	}
}
void ObjectManager::Init()
{
	ObjectIter iter = mObjectList.begin();
	for (; iter != mObjectList.end(); ++iter)
	{
		for (int i = 0; i < iter->second.size(); ++i)
		{	
			iter->second[i]->Init();
		}
	}
}

void ObjectManager::Release()
{
	ObjectIter iter = mObjectList.begin();
	for (; iter != mObjectList.end(); ++iter)
	{
		for (int i = 0; i < iter->second.size(); ++i)
		{
			iter->second[i]->Release();
			SafeDelete(iter->second[i]);

		}

		iter->second.clear();
		iter->second.shrink_to_fit();
	}
}

void ObjectManager::Update()
{
	ObjectIter iter = mObjectList.begin();
	for (; iter != mObjectList.end(); ++iter)
	{
		for (int i = 0; i < iter->second.size(); ++i)
		{
			if (iter->second[i]->GetIsDestroy() == true)
			{
				iter->second[i]->Release();
				SafeDelete(iter->second[i]);
				iter->second.erase(iter->second.begin() + i);
				--i;
				continue;
			}
			//클리핑테스트
			//if (CameraManager::GetInstance()->GetMainCamera()->IsInCameraArea(iter->second[i]->GetRect()))
			//{
			//	iter->second[i]->SetIsActive(true);
			//}
			//else
			//{
			//	iter->second[i]->SetIsActive(false);
			//}
			if (iter->second[i]->GetIsActive() == true)
			{
				iter->second[i]->Update();
			}
		}
	}
	Collision();
}

void ObjectManager::Render(HDC hdc)
{
	ObjectIter iter = mObjectList.begin();
	for (; iter != mObjectList.end(); ++iter)
	{
		for (int i = 0; i < iter->second.size(); ++i)
		{
			if (iter->second[i]->GetIsActive() == true)
			{
				iter->second[i]->Render(hdc);
			}
		}
	}
}

void ObjectManager::AddObject(ObjectLayer layer, GameObject * object)
{
	//map도 배열연산자가 정의되어 있다. 
	//단, 실제 배열처럼 동작하는게 아니라.[]연산자 내부에 find함수를 써서 동작함
	//그래서 결국 find쓰는거랑 비슷한데, 다른점이라고 한다면 해당 키값의 데이터가 
	//없으면 새로 생성해버림. 주의해야함
	mObjectList[layer].push_back(object);
}

//해당 이름의 오브젝트 찾아오기
GameObject * ObjectManager::FindObject(const string & name)
{
	ObjectIter iter = mObjectList.begin();
	for (; iter != mObjectList.end(); ++iter)
	{
		for (int i = 0; i < iter->second.size(); ++i)
		{
			if (iter->second[i]->GetName() == name)
			{
				return iter->second[i];
			}
		}
	}
	return nullptr;
}

//해당 이름의 오브젝트 찾기
GameObject * ObjectManager::FindObject(ObjectLayer layer, const string & name)
{
	ObjectIter iter = mObjectList.find(layer);
	for (int i = 0; i < iter->second.size(); ++i)
	{
		if (iter->second[i]->GetName() == name)
		{
			return iter->second[i];
		}
	}
	return nullptr;
}

vector<class GameObject*> ObjectManager::FindObjects(const string & name)
{
	vector<GameObject*> result;

	ObjectIter iter = mObjectList.begin();
	for (; iter != mObjectList.end(); ++iter)
	{
		for (int i = 0; i < iter->second.size(); ++i)
		{
			if (iter->second[i]->GetName() == name)
			{
				result.push_back(iter->second[i]);
			}
		}
	}

	return result;
}

vector<class GameObject*> ObjectManager::FindObjects(ObjectLayer layer, const string & name)
{
	vector<GameObject*> result;
	ObjectIter iter = mObjectList.find(layer);
	for (int i = 0; i < iter->second.size(); ++i)
	{
		if (iter->second[i]->GetName() == name)
		{
			result.push_back(iter->second[i]); 
		}
	}
	return result;
}

vector<class GameObject*> ObjectManager::GetObjectList(ObjectLayer layer)
{
	return mObjectList[layer];
}

void ObjectManager::Collision()
{
	//RECT temp;
	//RECT mZombieRC;
	//if (ObjectManager::GetInstance()->FindObject(ObjectLayer::Player, "Player") != nullptr)
	//{
	//	RECT mPlayerRC = ObjectManager::GetInstance()->FindObject(ObjectLayer::Player, "Player")->GetRect();
	//	vector<GameObject*> mZombie = ObjectManager::GetInstance()->GetObjectList(ObjectLayer::Enemy);

	//	if (mZombie.size() != NULL)
	//	{
	//		for (int i = 0; i < mZombie.size(); ++i)
	//		{
	//			RECT mZombieRC = mZombie[i]->GetRect();
	//			if (IntersectRect(&temp, &mPlayerRC, &mZombieRC))
	//			{
	//				int a = 1;
	//			}

	//		}
	//	}
	//}
}

vector<GameObject*> ObjectManager::Zorder()
{
	auto tmp = ObjectManager::GetInstance()->GetObjectList(ObjectLayer::NoninteractObject);

	auto NoninteractObject = tmp.begin();
	auto Player = tmp.end();

	auto func = [](GameObject* a, GameObject* b)
	{
		return a->GetY() < b->GetY();
	};

	sort(NoninteractObject, Player, func);
	

	return tmp;
	
	return vector<GameObject*>();
}

