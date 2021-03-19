#pragma once

/*
## ObjectManager ##
GameObject 관리하는 클래스
*/

//enum (열거자) : 정수를 다른 이름으로 표현하는 것

//*앞으로 오브젝트레이어 건드리면 Save Load도 같이 수정해줄 것!!!
//혹은 텍스트 파일을 수정해야할 수 있다
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

