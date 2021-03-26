#include "pch.h"
#include "WeatherManager.h"
#include "Rain.h"

void WeatherManager::Init()
{
	mIsChangeWeather = false;
	mWeather = WeatherMode::Sunny;
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
					mRainList[i]->Update();
				}
			}
			//if (iter->second[i]->GetIsDestroy() == true)
			//{
			//	iter->second[i]->Release();
			//	SafeDelete(iter->second[i]);
			//	iter->second.erase(iter->second.begin() + i);
			//	--i;
			//	continue;
			//}
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
