#pragma once
//조상님!!!
class GameObject
{
protected:
	string mName;
	Vector2 mPosition;
	Vector2 mSize;
	RECT mRect;
public:
	//순수가상함수 : 반드시 자식에서 해당 함수를 오버라이딩 해야함
	virtual void Init() = 0;
	virtual void Release() = 0;
	virtual void Update() = 0;
	virtual void Render(HDC hdc) = 0;
public:
	inline string GetName()const { return mName; }
	inline void SetName(const string& name) { mName = name; }

};

