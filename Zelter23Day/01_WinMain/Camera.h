#pragma once
#include "GameObject.h"

class Camera : public GameObject
{
public:
	enum class Mode : int
	{
		Follow, Free
	};
protected:
	Mode mMode;
	GameObject* mTarget;		//쫓아가야할 타겟

	float mMoveSpeed;

public:
	bool mIsShake;

	void Init()override; 
	void Release()override; 
	void Update()override; 
	void Render(HDC hdc)override;

	void SetTarget(GameObject* target) { mTarget = target; }
	void ChangeMode(Mode mode) { mMode = mode; }
public:
	void RenderText(float x, float y, wstring textContext, float fontSize);
	void Render(HDC hdc, class Image* image, int x, int y);
	void Render(HDC hdc, class Image* image, int x, int y, int tempX, int tempY, int tempWidth, int tempHeight);
	void FrameRender(HDC hdc, class Image* image, int x, int y, int frameX, int frameY);
	void AlphaRender(HDC hdc, class Image* image, int x, int y, float alpha);
	void AlphaFrameRender(HDC hdc, class Image* image, int x, int y, int frameX, int frameY, float alpha);
	void ScaleRender(HDC hdc, class Image* image, int x, int y, int width, int height);
	void ScaleFrameRender(HDC hdc,class Image* image, int x, int y, int frameX, int frameY, int width, int height);
	void AlphaScaleRender(HDC hdc,class Image* image, int x, int y, int width, int height, float alpha);
	void AlphaScaleFrameRender(HDC hdc, class Image* image, int x, int y, int frameX, int frameY, int width, int height, float alpha);
	//엑티브
	void ActivitScaleRender(HDC hdc, class Image* image, int x, int y, int width, int height, float angleX, float angleY);
	//그림자
	void ShadowRender(HDC hdc,class Image* image, int x, int y, int frameX, int frameY, int width, int height, float alpha, float time, int tileCountY = 0);
	//문여닫기
	void DoorScaleFrameRender(HDC hdc,class Image* image, int x, int y, int frameX, int frameY, int width, int height, float time);
	//아이템테두리 그리기
	void ItemRender(HDC hdc, class Image* image, int x, int y, int frameX, int frameY, int width, int height, float time);
	//카메라 흔들기
	void ShakingCamera();

	void RenderRect(HDC hdc, RECT rc);
	void RenderRect(HDC hdc, RECT rc, Gizmo::Color color);
	void RenderEllipse(HDC hdc, float x, float y, float radius);

	bool IsInCameraArea(float x, float y, float width, float height);
	bool IsInCameraArea(RECT rc);

	inline float GetMoveSpeed()const { return mMoveSpeed; }
	inline void SetMoveSpeed(float speed) { mMoveSpeed = speed; }

	POINT GetPoint(long x, long y)const { return { x - mRect.left, y - mRect.top }; }
};

