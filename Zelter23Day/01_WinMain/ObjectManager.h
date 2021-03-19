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
	Player = 4,
	HousingObject = 5,
	InteractObject = 6,
	NoninteractObject = 7,
	Bullet = 8,
	ToolBook = 9,
	Button = 10,
	ObjectButton = 11,
	Mouse = 12,
	UI = 13,
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

