#pragma once
#include "GameObject.h"

#define InteractObjectSize 2

class Image;
class InteractObject : public GameObject
{
	Image* mImage;
	int mHp;
	int mIndexX;
	int mIndexY;
	int mImpactY;
	//차지하는 타일 갯수
	int mTileCountX, mTileCountY;
	//시작 타일 배열값
	int mTileIndexX, mTileIndexY;
	//입력해주는 값
	int mInputX, mInputY;
	//피격 시 무적 시간 (bool값 변경을 위한)
	float mInvincibleCount;
	//피격시 무적 판정 및 이펙트연출을 위한 변수
	bool mIsInvincible;

	//무슨변수인가? 필요한 변수인가?
	bool mIsInteractive;

	wstring mImageKey;
	//인터렉트 렉트
	RECT mInteractRect;

	//문짝 true = 열림.
	bool mIsDoorOpen;
	bool mChangeDoor;
	float mDoorTime;
	
	GameObject* mPlayer;
public:
	InteractObject(const wstring imageKey, float x, float y, int hp, int tileCountX, int tileCountY);

	void Init()override;
	void Release()override;
	void Update()override;
	void Render(HDC hdc)override;

	int GetHp()const { return mHp; }
	void SetHp(int hp) { mHp = hp; }
	wstring GetImageKey()const { return mImageKey; }
	
	int GetInputX()const { return mInputX; }
	int GetInputY()const { return mInputY; }
	int GetTileIndexX()const { return mTileIndexX; }
	int GetTileIndexY()const { return mTileIndexY; }
	int GetTileCountX()const { return mTileCountX; }
	int GetTileCountY()const { return mTileCountY; }

	RECT GetInteractRect()const { return mInteractRect; }

	bool GetIsDoorOpen() { return mIsDoorOpen; }
	bool GetIsInvincible() { return mIsInvincible; }
	void SetIsInvincible(bool isInvincible) { mIsInvincible = isInvincible; }

};

