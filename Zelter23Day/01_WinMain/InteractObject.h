#pragma once
#include "GameObject.h"

enum class TypeLayer
{
	철,
	나무,
	헝겁,
	end
};
class Image;
class InteractObject : public GameObject
{
	Image* mImage;
	int mHp;
	int mIndexX;
	int mIndexY;

	bool mIsInteractive;

public:
	InteractObject(const wstring name, float x, float y, int hp);

	void Init()override;
	void Release()override;
	void Update()override;
	void Render(HDC hdc)override;

	void SetHp(int hp) { mHp = hp; }
};

