#pragma once

/*
## ObjectManager ##
GameObject �����ϴ� Ŭ����
*/

//enum (������) : ������ �ٸ� �̸����� ǥ���ϴ� ��

//*������ ������Ʈ���̾� �ǵ帮�� Save Load�� ���� �������� ��!!!
//Ȥ�� �ؽ�Ʈ ������ �����ؾ��� �� �ִ�
enum class ObjectLayer : int
{
	Background = 0,
	camera = 1,
	Tile = 2,
	Enemy = 3,
	Item = 4,
	Player = 5,
	HousingObject = 6,
	InteractObject = 7,
	NoninteractObject = 8,
	Bullet = 9,
	ToolBook = 10,
	Button = 11,
	ObjectButton = 12,
	Mouse = 13,
	UI = 14,
	InventoryItem = 15,
	End
};

class ObjectManager
{
	Singleton(ObjectManager)
private:
	typedef map<ObjectLayer, vector<class GameObject*>>::iterator ObjectIter;
	map<ObjectLayer, vector<class GameObject*>> mObjectList;

	vector<class GameObject*> mZorderList;
public:
	ObjectManager();

	void Init();
	void Release();
	void Update();
	void Render(HDC hdc);

	void AddObject(ObjectLayer layer, class GameObject* object);
	class GameObject* FindObject(const string& name);
	class GameObject* FindObject(ObjectLayer layer, const string& name);
	vector<class GameObject*> FindObjects(const string& name);
	vector<class GameObject*> FindObjects(ObjectLayer layer, const string& name);
	vector<class GameObject*> GetObjectList(ObjectLayer layer);

	void Collision();

	vector<GameObject*> Zorder();

};

