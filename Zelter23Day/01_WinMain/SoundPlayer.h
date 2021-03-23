#pragma once
/*
FMOD ���̺��!!!!!
System : FMOD���õ� ��ġ���� �����ϰų�, ���带 ����ϴ� ��, �������� �ý��� ó���� ���� ���
Sound : ���� ����
Channel : ���� ������ִ� �༮
*/

#define MaxChannelBuffer 50	//�ִ� ä�� ��

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
	map<wstring, FMOD::Sound*> mSoundList;
	vector<ChannelInfo> mActiveChannels;		//���� Ȱ��ȭ �Ǿ� �ִ� ä��
	FMOD::System* mSystem;

	float mBGMVolume;
	float mEffectVolume;

private:
	SoundPlayer();
	~SoundPlayer();
public:
	void Update();
	void LoadFromFile(const wstring& keyName, const wstring& fileName, bool isLoop);
	void Play(const wstring& keyName, float volume);
	void Pause(const wstring& keyName);
	void Stop(const wstring& keyName);

	void SetBgmVolume(float vol) { mBGMVolume += vol; }
	float GetBgmVolume() { return mBGMVolume; }
	void SetBgmVolumeUpdate(const wstring& keyName, float volume);

	void SetEffectVolume(float vol) { mEffectVolume += vol; }
	float GetEffectVolume() { return mEffectVolume; }
	void SetEffectVolumeUpdate(const wstring& keyname, float volume);

	//����~ MP3�÷��̾� ��������
	//void SetVolume(const wstring& keyName, float volume);
	//float GetVolume(const wstring& keyName);  
	//void SetPosition(const wstring& keyName, float time);
	//float GetPosition(const wstring& keyName);
};

