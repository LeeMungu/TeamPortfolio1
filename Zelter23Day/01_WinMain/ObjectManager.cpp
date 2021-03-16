#include "pch.h"
#include "ObjectManager.h"
#include "Camera.h"
#include <algorithm>


#include "GameObject.h"
ObjectManager::ObjectManager()
{
	//ObjectLayer ���� ���� �ϳ��� �ʿ� ���� �ִ´�.
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

	ObjectIter iter1 = mObjectList.begin();
	for (; iter1 != mObjectList.end(); ++iter1)
	{
		if (iter1->first == ObjectLayer::Enemy ||
			iter1->first == ObjectLayer::Player ||
			iter1->first == ObjectLayer::InteractObject ||
			iter1->first == ObjectLayer::NoninteractObject ||
			iter1->first == ObjectLayer::HousingObject)
		{
			for (int i = 0; i < iter1->second.size(); ++i)
			{
				mZorderList.push_back(iter1->second[i]);
			}
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

			//Ŭ�����׽�Ʈ
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
	
	mZorderList = Zorder();
}

void ObjectManager::Render(HDC hdc)
{
	ObjectIter iter = mObjectList.begin();
	for (; iter != mObjectList.end(); ++iter)
	{
		if (iter->first == ObjectLayer::Enemy || iter->first == ObjectLayer::Player
			|| iter->first == ObjectLayer::NoninteractObject
			|| iter->first == ObjectLayer::InteractObject
			|| iter->first == ObjectLayer::HousingObject)
		{
			for (int i = 0; i < mZorderList.size(); ++i)
			{
				mZorderList[i]->Render(hdc);
			}
			continue;
		}
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
	//map�� �迭�����ڰ� ���ǵǾ� �ִ�. 
	//��, ���� �迭ó�� �����ϴ°� �ƴ϶�.[]������ ���ο� find�Լ��� �Ἥ ������
	//�׷��� �ᱹ find���°Ŷ� ����ѵ�, �ٸ����̶�� �Ѵٸ� �ش� Ű���� �����Ͱ� 
	//������ ���� �����ع���. �����ؾ���
	mObjectList[layer].push_back(object);
}

//�ش� �̸��� ������Ʈ ã�ƿ���
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

//�ش� �̸��� ������Ʈ ã��
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
	vector<GameObject*> tmp = mZorderList;

	auto func = [](GameObject* a, GameObject* b)
	{
		return a->GetRect().bottom < b->GetRect().bottom;
	};

	sort(tmp.begin(),tmp.end(), func);
	
	return tmp;
}

