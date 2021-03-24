#pragma once
class Button final
{
	enum class State : int
	{
		Normal = 0, 
		Push = 1,
		Select = 2,
		End
	};
	enum class Type : int
	{
		OnOffButton = 0,
		SelectButton = 1,
		End
	};
	function<void(void)> mFunc;	//��ư�������� ����� �Լ�
	float mX;
	float mY;
	float mSizeX;
	float mSizeY;
	RECT mRect;
	State mState;
	Type mButtonType;
	wstring mText;
	//�̹����� �ִ°��
	class Image* mImage;
	int mIndexX;
	int mIndexY;
	//������ ��ư - ���� ���ִ��� ���� Ȯ��
	bool mIsSelect;
public:
	Button(wstring text,float x, float y, float sizeX, float sizeY, function<void(void)> func);
	Button(wstring imageKey,int indexY, wstring text, float x, float y, float sizeX, float sizeY, function<void(void)> func);
	Button(wstring imageKey, float x, float y, float multiply, function<void(void)> func);
	void Update();
	void Render(HDC hdc);

	void Move(float x, float y);

	float GetX() const { return mX; }
	float GetY() const { return mY; }
	RECT GetRect() const { return mRect; }

	bool GetIsSelect() const { return mIsSelect; }
	void SetIsSelect(bool isSelect) { mIsSelect = isSelect; }
};