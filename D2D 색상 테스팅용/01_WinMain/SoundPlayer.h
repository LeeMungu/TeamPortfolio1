#pragma once
/*
���� ����ϴ� ����� ������ ���ϰ� �ϱ����ؼ� FMOD��� ���̺귯���� ���
System : ���� ������ �ε��ϰų�, ä���� �����ϰų� ����� ó���� �� �� ���, ä�ΰ����� �ý����� ��
Sound : �̹���Ŭ���� ���� �༮, ���带 �����ϴ� Ŭ����
Channel : ���� ���带 �÷������ְ� ���� ������� ���¸� �������ִ� �༮
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
	map<wstring, FMOD::Sound*> mSoundList;		//���� ���� �������ִ� �༮
	//���� Ȱ��ȭ �Ǿ� �ִ� ä��, ä�ο��� ���� ����� ������ �ش� ���Ϳ����� ���ش�
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

