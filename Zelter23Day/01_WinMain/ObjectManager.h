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
	Player = 4,
	HousingObject = 5,
	InteractObject = 6,
	NoninteractObject = 7,
	Item = 8,
	Bullet = 9,
	Boom = 10,
	Effect = 11,
	ToolBook = 12,
	Button = 13,
	ObjectButton = 14,
	Mouse = 15,
	Weater = 16,
	UI = 17,
	InventoryItem = 18,
	MakingItem = 19,
	Weapon = 20,
	End
};

class ObjectManager
{
	Singleton(ObjectManager)
private:
	typedef map<ObjectLayer, vector<class GameObject*>>::iterator ObjectIter;
	map<ObjectLayer, vector<class GameObject*>> mObjectList;

	vector<class GameObject*> mZorderList;
	vector<class GameObject*> mZorderRenderList;
	vector<class GameObject*> mClipingInteractList;
	vector<RECT> mClipingHousingWallList;
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
	vector<class GameObject*> GetClipingInteraceList() const { return mClipingInteractList; }
	vector<RECT> GetClipingHousingWall() const { return mClipingHousingWallList; }

	void Zorder(vector<GameObject*> &zorderRenderList);

};

