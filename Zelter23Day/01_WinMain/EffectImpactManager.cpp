#include "pch.h"
#include "EffectImpactManager.h"
#include "EffectImpact.h"

void EffectImpactManager::Init(wstring imagekey, int x, int y, int indexX)
{
	mEffectImpact = new EffectImpact(imagekey, x, y, indexX);

	mEffectImpact->Init();

}

void EffectImpactManager::Release()
{
}

void EffectImpactManager::Update()
{
	mEffectImpact->Update();
}

void EffectImpactManager::Render(HDC hdc)
{
	mEffectImpact->Render(hdc);
}
