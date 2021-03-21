#include "pch.h"
#include "MainGame.h"

#include "Image.h"
#include <iostream>
void MainGame::Init()
{
    ImageManager::GetInstance()->LoadFromFile(L"Dog", Resources(L"Dog.jpg"));
    mImage = ImageManager::GetInstance()->FindImage(L"Dog");

    mAngle = 0.f;
    //기존 랜더타겟과 호환되는 별도의 렌더타겟 생성
    D2DRenderer::GetInstance()->GetRenderTarget()->CreateCompatibleRenderTarget(&mFirstBuffer);
    mR = 0;
    mG = 0;
    mB = 1.0f;
    mA = 0.3;
}


void MainGame::Release()
{
    Random::ReleaseInstance();   //싱글톤 인스턴스 삭제
    mFirstBuffer->Release();
}


void MainGame::Update()
{
    mAngle += 360.f * Time::GetInstance()->DeltaTime();
    if(Input::GetInstance()->GetKey('A'))
    { 
        mR += 0.1f*Time::GetInstance()->DeltaTime();
    }
    else if (Input::GetInstance()->GetKey('Z'))
    {
        mR -= 0.1f * Time::GetInstance()->DeltaTime();
    }
    if (Input::GetInstance()->GetKey('S'))
    {
        mG += 0.1f * Time::GetInstance()->DeltaTime();
    }
    else if (Input::GetInstance()->GetKey('X'))
    {
        mG -= 0.1f * Time::GetInstance()->DeltaTime();
    }
    if (Input::GetInstance()->GetKey('D'))
    {
        mB += 0.1f * Time::GetInstance()->DeltaTime();
    }
    else if (Input::GetInstance()->GetKey('C'))
    {
        mB -= 0.1f * Time::GetInstance()->DeltaTime();
    }
    if (Input::GetInstance()->GetKey('F'))
    {
        mA += 0.1f * Time::GetInstance()->DeltaTime();
    }
    else if (Input::GetInstance()->GetKey('V'))
    {
        mA -= 0.1f * Time::GetInstance()->DeltaTime();
    }
    
    //보정
    if (mR > 1.f) mR = 0;
    else if (mR < 0) mR = 1.f;
    if (mG > 1.f) mG = 0;
    else if (mG < 0) mG = 1.f;    
    if (mB > 1.f) mB = 0;
    else if (mB < 0) mB = 1.f;
    if (mA > 1.f) mA = 0;
    else if (mA < 0) mA = 1.f;
}


void MainGame::Render(HDC hdc)
{
    D2DRenderer::GetInstance()->BeginRender(D2D1::ColorF::Black);
    {
        // {{ 인 게임 렌더링 진행 ~
        mFirstBuffer->BeginDraw();
        mFirstBuffer->Clear();
        {
            mImage->SetSize(Vector2(100, 100));
            mImage->SetScale(2.0f);
            //mImage->SetAngle(mAngle);
            mImage->SetAlpha(1.f);
            mImage->Render(mFirstBuffer, Vector2(WINSIZEX / 2, WINSIZEY / 2));

            mImage->SetSize(Vector2(100, 100));
            mImage->Render(mFirstBuffer, Vector2(100, 100));

        }
        mFirstBuffer->EndDraw();
        // }} 

        // {{ 후처리 시작 :: 화면 전체에 마스크로 컬러 멀티플 진행
        ID2D1RenderTarget* renderTarget = D2DRenderer::GetInstance()->GetRenderTarget();
        ID2D1SolidColorBrush* brush;
        renderTarget->CreateSolidColorBrush(D2D1::ColorF(mR, mG, mB, mA), &brush);

        ID2D1Bitmap* bitmap;
        mFirstBuffer->GetBitmap(&bitmap);
        D2D1_RECT_F dxArea = D2D1::RectF(0.f, 0.f, WINSIZEX, WINSIZEY);

        renderTarget->SetTransform(D2D1::Matrix3x2F::Identity());
        renderTarget->DrawBitmap(bitmap, dxArea, 1.0f);
        //그렸던 게임 장면을 Multiply 해서 백버퍼에 렌더링
        renderTarget->FillOpacityMask(bitmap, brush, D2D1_OPACITY_MASK_CONTENT::D2D1_OPACITY_MASK_CONTENT_GRAPHICS, dxArea, dxArea);
        brush->Release();
        // }} 

        D2DRenderer::GetInstance()
            ->RenderText(WINSIZEX / 3, 100, L"A,Z : R+-", 20);
        D2DRenderer::GetInstance()
            ->RenderText(WINSIZEX / 3, 120, L"S,X : G+-", 20);
        D2DRenderer::GetInstance()
            ->RenderText(WINSIZEX / 3, 140, L"D,C : B+-", 20);
        D2DRenderer::GetInstance()
            ->RenderText(WINSIZEX / 3, 160, L"F,V : A+-", 20);

        D2DRenderer::GetInstance()
            ->RenderText(WINSIZEX / 2, WINSIZEY / 2, L"R : "+to_wstring((int)(mR * 100.f)) + L"/100", 20);
        D2DRenderer::GetInstance()
            ->RenderText(WINSIZEX / 2, WINSIZEY / 2 + 20, L"G : " + to_wstring((int)(mG * 100.f)) + L"/100", 20);
        D2DRenderer::GetInstance()
            ->RenderText(WINSIZEX / 2, WINSIZEY / 2 + 40, L"B : " + to_wstring((int)(mB * 100.f)) + L"/100", 20);
        D2DRenderer::GetInstance()
            ->RenderText(WINSIZEX / 2, WINSIZEY / 2 + 60, L"A : " + to_wstring((int)(mA * 100.f)) + L"/100", 20);
    }
    D2DRenderer::GetInstance()->EndRender();
}
