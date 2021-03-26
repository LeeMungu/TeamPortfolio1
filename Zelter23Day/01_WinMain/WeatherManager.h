#pragma once

enum class WeatherMode :int
{
	Sunny=0,			//¸¼À½
	Rain=1,				//¿ìÃµ
	LightningThunder=2,	//ÃµµÕ¹ø°³
	End
};

class WeatherManager
{
	Singleton(WeatherManager);
private:
	WeatherMode mWeather;
	bool mIsChangeWeather;
	vector<class Rain*> mRainList;
	int mRainCount;
public:
	void Init();
	void Release();
	void Update();
	void Render(HDC hdc);

	void SetWeather(WeatherMode weather) 
	{ 
		mWeather = weather;
		mIsChangeWeather = true;
	}
};

