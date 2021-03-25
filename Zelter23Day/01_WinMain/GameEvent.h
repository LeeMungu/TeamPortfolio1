#pragma once

//interface class : 순수가상함수만을 가지고 있는 클래스
class IEvent
{
public:
	//자동적으로 순수 가상함수가 된다
	virtual void Start() = 0;	//이벤트 시작할 때 호출되는 함수
	//실행하다가 끝나면 return true
	virtual bool Update() = 0;	//이벤트 업데이트 함수
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

//특정 타일에 접근해야 이벤트가 시작된다.
class ITileEvent : public IEvent
{
public:
	//플레이어가 이 위치에 있으면 실행
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

//모든유닛 특정시간 스탑
class IAllUnitStopTime : public IEvent
{
	float mDelayTime;
	float mCurrentTime;
public:
	IAllUnitStopTime(float DelayTime);
	void Start()override;
	bool Update()override;
};

//모든 유닛 정지 1회만 반드시 다시 움직이기와 같이 써주기
class IAllUnitStop : public IEvent
{
public:
	IAllUnitStop();
	void Start()override;
	bool Update()override;
};
//모든 유닛 다시 움직이기
class IAllUnitActive : public IEvent
{
public:
	IAllUnitActive();
	void Start()override;
	bool Update()override;
};

//좀비 생성
class IZombiGeneration : public IEvent
{
	float mX;
	float mY;
	vector<vector<class Tile*>> mTileList;
public:
	IZombiGeneration(float x, float y, vector<vector<class Tile*>> tileList );
	void Start()override;
	bool Update()override;
};