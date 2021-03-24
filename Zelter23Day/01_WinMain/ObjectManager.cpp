#include "pch.h"
#include "ObjectManager.h"
#include "Camera.h"
#include <algorithm>


#include "GameObject.h"
#include "HousingObject.h"
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

	ObjectIter iter1 = mObjectList.find(ObjectLayer::Enemy);
	for (; iter1 != mObjectList.find(ObjectLayer::Bullet); ++iter1)
	{
		//������ �ٿ��� �ʿ��������.
		//if (iter1->first == ObjectLayer::Enemy ||
		//	iter1->first == ObjectLayer::Player ||
		//	iter1->first == ObjectLayer::InteractObject ||
		//	iter1->first == ObjectLayer::NoninteractObject ||
		//{
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
	//������Ʈ �� ���� ���� �־���<-�ʿ��Ѱ�?
	mZorderList.clear();
	mClipingInteractList.clear();
	ObjectIter iter1 = mObjectList.find(ObjectLayer::Enemy);
	for (; iter1 != mObjectList.find(ObjectLayer::Bullet); ++iter1)
	{
		//���� ��� ����
		if (iter1->first != ObjectLayer::HousingObject )
		{
			for (int i = 0; i < iter1->second.size(); ++i)
			{
				mZorderList.push_back(iter1->second[i]);
			}
		}
		if (iter1->first == ObjectLayer::InteractObject)
		{
			//ī�޶� ���� �޾ƿ���
			RECT cameraRect = CameraManager::GetInstance()->GetMainCamera()->GetRect();
			for (int i = 0; i < iter1->second.size(); ++i)
			{
				//ī�޶� ���� ���� �͵�
				if (iter1->second[i]->GetRect().top > cameraRect.bottom || iter1->second[i]->GetRect().bottom < cameraRect.top
					|| iter1->second[i]->GetRect().left > cameraRect.right || iter1->second[i]->GetRect().right < cameraRect.left)
				{
				}
				else
				{
					mClipingInteractList.push_back(iter1->second[i]);
				}
			}
		}
	}

	Zorder(mZorderRenderList);
}

void ObjectManager::Render(HDC hdc)
{
	ObjectIter iterhouse = mObjectList.find(ObjectLayer::HousingObject);
	for (int i = 0; i < iterhouse->second.size(); ++i)
	{
		if (iterhouse->second[i]->GetIsActive() == true)
		{
			if (((HousingObject*)iterhouse->second[i])->GethouseLayer() != HouseLayer::Roof)
			{
				iterhouse->second[i]->Render(hdc);
			}
		}
	}

	//������Ʈ���̾� �տ�ģ������ �ȱ׷��ش�. ����-
	for (int i = 0; i < mZorderRenderList.size(); ++i)
	{
		mZorderRenderList[i]->Render(hdc);
	}

	for (int i = 0; i < iterhouse->second.size(); ++i)
	{
		if (iterhouse->second[i]->GetIsActive() == true)
		{
			if (((HousingObject*)iterhouse->second[i])->GethouseLayer() == HouseLayer::Roof)
			{
				iterhouse->second[i]->Render(hdc);
			}
		}
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

void ObjectManager::Zorder(vector<GameObject*> &zorderRenderList)
{
	zorderRenderList = mZorderList;

	//ī�޶� ���� �޾ƿ���
	RECT cameraRect = CameraManager::GetInstance()->GetMainCamera()->GetRect();


	for (int i = 0; i < zorderRenderList.size(); ++i)
	{
		//��Ͽ��� ī�޶� �ȿ� �ִ� �ֵ鸸 ���ܵΰ� ����
		if (zorderRenderList[i]->GetRect().top > cameraRect.bottom || zorderRenderList[i]->GetRect().bottom < cameraRect.top
			|| zorderRenderList[i]->GetRect().left > cameraRect.right || zorderRenderList[i]->GetRect().right < cameraRect.left)
		{
			//�̵ڷδ� '��Ͽ�����' �� ����� <-����������Ʈ�� ������ �ϸ� ������ ������������ �ȵ�
			zorderRenderList.erase(zorderRenderList.begin() + i);
			--i;
			continue;
		}
	}

	auto func = [](GameObject* a, GameObject* b)
	{
		return a->GetRect().bottom < b->GetRect().bottom;
	};

	sort(zorderRenderList.begin(), zorderRenderList.end(), func);

	return ;
}

