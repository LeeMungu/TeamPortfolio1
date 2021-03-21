#pragma once
//�����!!!
class GameObject
{
protected:
	string mName;
	Vector2 mPosition;
	Vector2 mSize;
	RECT mRect;
public:
	//���������Լ� : �ݵ�� �ڽĿ��� �ش� �Լ��� �������̵� �ؾ���
	virtual void Init() = 0;
	virtual void Release() = 0;
	virtual void Update() = 0;
	virtual void Render(HDC hdc) = 0;
public:
	inline string GetName()const { return mName; }
	inline void SetName(const string& name) { mName = name; }

};

