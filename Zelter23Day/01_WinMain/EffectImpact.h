#pragma once
#include "GameObject.h"

//enum class TypeLayer
//{
//	stone,
//	wood,
//	glass,
//	fabric,
//	Iron,
//	Leather,
//	plastic,
//	end
//};

class Image;
class Animation;
class InteractObject;
class EffectImpact : public GameObject
{
public:
	Image* mImage;
	Animation* mAnimation;
	Animation* mCurrentAnimation;
	InteractObject* mInteractObject;
	wstring mImageKey;

	//map<wstring, TypeLayer> mObjectLayerList;

	int mIndexX;
	int mIndexY;
	float mAngle;
	float mSpeed;
	float mGravity;


public:
	EffectImpact(wstring imagekey, int x, int y, int indexX);

	void Init()override;
	void Release()override;
	void Update()override;
	void Render(HDC hdc)override;
};

