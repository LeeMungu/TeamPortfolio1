#include "pch.h"
#include "WeatherManager.h"
#include "Rain.h"

void WeatherManager::Init()
{
	mIsChangeWeather = false;
	mWeather = WeatherMode::Sunny;
	mRainCount = 0;
}

void WeatherManager::Release()
{
	mRainList.clear();
}

void WeatherManager::Update()
{
	//상시
	if (mIsChangeWeather == false)
	{
		if (mWeather == WeatherMode::Sunny)
		{

		}
		else if (mWeather == WeatherMode::Rain)
		{
			if (mRainList.size() != NULL)
			{
				for (int i = 0; i < mRainList.size(); ++i)
				{
					if (mRainList[i]->GetIsDestroy() == true)
					{
						mRainList[i]->Release();
						SafeDelete(mRainList[i]);
						mRainList.erase(mRainList.begin() + i);
						--i;
						continue;
					}
				}
				for (int i = 0; i < mRainList.size(); ++i)
				{
					mRainList[i]->Update();
				}
			}
			if (mRainList.size() < 80)
			{
				mRainCount++;
				Rain* rain = new Rain(
					-150 + (mRainCount % 10) * Random::GetInstance()->RandomInt(130,160),
					20,
					2, 
					Random::GetInstance()->RandomInt(10,30),			//size
					Random::GetInstance()->RandomInt(20,30),			//angle 
					Random::GetInstance()->RandomInt(5,10),				//speed
					Random::GetInstance()->RandomInt(500,900));			//distance
				rain->Init();
				mRainList.push_back(rain);
			}
		}
		else if (mWeather == WeatherMode::LightningThunder)
		{

		}
	}
	//교체 될때
	else if (mIsChangeWeather == true)
	{
		if (mWeather == WeatherMode::Sunny)
		{

		}
		else if (mWeather == WeatherMode::Rain)
		{
			for (int i = 0; i < 50; ++i)
			{
				Rain* rain = new Rain(
				-100 + (i % 10) * 150,
				20 + (i/10)*150,
				2,
				Random::GetInstance()->RandomInt(20, 50),			//size
				Random::GetInstance()->RandomInt(25, 30),			//angle 
				Random::GetInstance()->RandomInt(10, 15),				//speed
				Random::GetInstance()->RandomInt(500, 900));			//distance
				rain->Init();
				mRainList.push_back(rain);
			}
		}
		else if (mWeather == WeatherMode::LightningThunder)
		{

		}
		mIsChangeWeather = false;
	}
}

void WeatherManager::Render(HDC hdc)
{
	if (mWeather == WeatherMode::Sunny)
	{

	}
	else if (mWeather == WeatherMode::Rain)
	{
		if (mRainList.size() != NULL)
		{
			for (int i = 0; i < mRainList.size(); ++i)
			{
				mRainList[i]->Render(hdc);
			}
		}
	}
	else if (mWeather == WeatherMode::LightningThunder)
	{

	}
}
