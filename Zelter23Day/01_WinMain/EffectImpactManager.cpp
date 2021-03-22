#include "pch.h"
#include "EffectImpactManager.h"
#include "EffectImpact.h"

void EffectImpactManager::Init(int x, int y, int indexX, int indexY)
{
	mEffectImpact = new EffectImpact(x, y, indexX, indexY);

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
