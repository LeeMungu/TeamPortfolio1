#pragma once

//interface class : ���������Լ����� ������ �ִ� Ŭ����
class IEvent
{
public:
	//�ڵ������� ���� �����Լ��� �ȴ�
	virtual void Start() = 0;	//�̺�Ʈ ������ �� ȣ��Ǵ� �Լ�
	//�����ϴٰ� ������ return true
	virtual bool Update() = 0;	//�̺�Ʈ ������Ʈ �Լ�
};

class IChangeCameraTargetEvent : public IEvent
{
	class GameObject* mTarget;
public:
	IChangeCameraTargetEvent(class GameObject* target);

	void Start()override;
	bool Update()override;
};

class IDelayEvent : public IEvent
{
	float mCurrentTime;
	float mDelayTime;
public:
	IDelayEvent(float delayTime);

	void Start()override;
	bool Update()override;
};

class ITextEvent : public IEvent
{
	float mTextDelayTime;
	wstring mTextContent;
	float mCurrentTime;
	class TextBox* mTextBox;
public:
	ITextEvent(float textDelayTime, wstring textContent);

	void Start()override;
	bool Update()override;
};

//Ư�� Ÿ�Ͽ� �����ؾ� �̺�Ʈ�� ���۵ȴ�.
class ITileEvent : public IEvent
{
public:
	//�÷��̾ �� ��ġ�� ������ ����
	enum class Mode
	{
		UpLeft,
		UpRight,
		DownLeft,
		DownRight,
		End
	};
private:
	Mode mMode;
	float mControlPointX;
	float mCoutrolPointY;
	float mPlayerX;
	float mPlayerY;
public:
	ITileEvent(ITileEvent::Mode mode, float x, float y);
	void Start()override;
	bool Update()override;
};