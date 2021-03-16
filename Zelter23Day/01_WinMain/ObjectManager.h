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
	NoninteractObject = 3,
	InteractObject = 4,
	HousingObject = 5,
	Enemy = 6,
	Player = 7,
	ToolBook = 8,
	Button = 9,
	ObjectButton = 10,
	Mouse = 11,
	UI = 12,
	End
	//Background = 0,
	//camera = 1,
	//Tile = 2,
	//Enemy = 3,
	//Player = 4,
	//HousingObject = 5,
	//InteractObject = 6,
	//NoninteractObject = 7,
	//ToolBook = 8,
	//Button = 9,
	//ObjectButton = 10,
	//Mouse = 11,
	//UI = 12,
	//End
};

class ObjectManager
{
	Singleton(ObjectManager)
private:
	typedef map<ObjectLayer, vector<class GameObject*>>::iterator ObjectIter;
	map<ObjectLayer, vector<class GameObject*>> mObjectList;
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
};

