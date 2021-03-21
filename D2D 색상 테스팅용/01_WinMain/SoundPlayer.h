#pragma once
/*
사운드 재생하는 방법은 많은데 편리하게 하기위해서 FMOD라는 라이브러리를 사용
System : 사운드 파일을 로드하거나, 채널을 생성하거나 등등의 처리를 할 때 사용, 채널관리도 시스템이 함
Sound : 이미지클래스 같은 녀석, 사운드를 관리하는 클래스
Channel : 실제 사운드를 플레이해주고 현재 재생중인 상태를 관리해주는 녀석
*/

#define MaxChannelBuffer 50	//최대 채널 수

class SoundPlayer final
{
	Singleton(SoundPlayer)
private:
	struct ChannelInfo
	{
		wstring SoundName;
		FMOD::Channel* Channel;
	};
	typedef map<wstring, FMOD::Sound*>::iterator SoundIter;
private:
	map<wstring, FMOD::Sound*> mSoundList;		//사운드 파일 관리해주는 녀석
	//현재 활성화 되어 있는 채널, 채널에서 사운드 재생이 끝나면 해당 벡터에서도 빼준다
	vector<ChannelInfo> mActiveChannels;		
	FMOD::System* mSystem;
private:
	SoundPlayer();
	~SoundPlayer();
public:
	void Update();
	void LoadFromFile(const wstring& keyName, const wstring& fileName, bool isLoop);
	void Play(const wstring& keyName, float volume);
	void Pause(const wstring& keyName);
	void Stop(const wstring& keyName);
};

