#pragma once

enum class WeatherMode :int
{
	Sunny=0,			//����
	Rain=1,				//��õ
	LightningThunder=2,	//õ�չ���
	End
};

class WeatherManager
{
	Singleton(ObjectManager);
private:
	WeatherMode mWeather;
	bool mIsChangeWeather;
	vector<class Rain*> mRainList;
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
