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

	ObjectIter iter1 = mObjectList.find(ObjectLayer::Enemy);
	for (; iter1 != mObjectList.find(ObjectLayer::Item); ++iter1)
	{
		//범위를 줄여서 필요없어졌다.
		//if (iter1->first == ObjectLayer::Enemy ||
		//	iter1->first == ObjectLayer::Player ||
		//	iter1->first == ObjectLayer::InteractObject ||
		//	iter1->first == ObjectLayer::NoninteractObject ||
		//{
		iter1->first == ObjectLayer::HousingObject;
		for (int i = 0; i < iter1->second.size(); ++i)
		{
			mZorderList.push_back(iter1->second[i]);
		}
		//}
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
			if (iter->second[i]->GetIsActive() == true)
			{
				iter->second[i]->Update();
			}
		}
	}
	//업데이트 때 마다 새로 넣어줌<-필요한가?
	mZorderList.clear();
	ObjectIter iter1 = mObjectList.find(ObjectLayer::Enemy);
	for (; iter1 != mObjectList.find(ObjectLayer::Item); ++iter1)
	{
		//범위를 줄여서 필요없어졌다.
		//if (iter1->first == ObjectLayer::Enemy ||
		//	iter1->first == ObjectLayer::Player ||
		//	iter1->first == ObjectLayer::InteractObject ||
		//	iter1->first == ObjectLayer::NoninteractObject ||
		//{
		iter1->first == ObjectLayer::HousingObject;
		for (int i = 0; i < iter1->second.size(); ++i)
		{
			mZorderList.push_back(iter1->second[i]);
		}
		//}
	}
	
	mZorderRenderList = Zorder();
}

void ObjectManager::Render(HDC hdc)
{
	//오브젝트레이어 앞에친구들은 안그려준다. 주의-
	for (int i = 0; i < mZorderRenderList.size(); ++i)
	{
		mZorderRenderList[i]->Render(hdc);
	}
	ObjectIter iter = mObjectList.find(ObjectLayer::Item);
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

vector<GameObject*> ObjectManager::Zorder()
{
	vector<GameObject*> tmp = mZorderList;

	auto func = [](GameObject* a, GameObject* b)
	{
		return a->GetRect().bottom < b->GetRect().bottom;
	};

	sort(tmp.begin(),tmp.end(), func);
	
	//카메라 영역 받아오기
	RECT cameraRect = CameraManager::GetInstance()->GetMainCamera()->GetRect();


	for (int i = 0; i < tmp.size(); ++i)
	{
		//목록에서 카메라 안에 있는 애들만 남겨두고 싶음
		if (tmp[i]->GetRect().top > cameraRect.bottom || tmp[i]->GetRect().bottom < cameraRect.top
			|| tmp[i]->GetRect().left > cameraRect.right || tmp[i]->GetRect().right < cameraRect.left)
		{
			//이뒤로는 '목록에서만' 싹 지우기 <-세이프딜리트나 릴리즈 하면 완전히 지워저벼려서 안됨
			tmp.erase(tmp.begin() + i);
			--i;
			continue;
		}
	}

	return tmp;
}

