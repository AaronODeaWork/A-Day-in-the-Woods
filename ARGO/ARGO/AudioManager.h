#pragma once

#include"AssetManager.h"

//singleton

class AudioManager {
public:

	static AudioManager* Instance();
	static void Release();

	void PlayMusic(std::string t_filename, int t_volume = 100, int t_loops = -1);
	void PauseMusic();
	void ResumeMusic();
	void PlaySfx(std::string t_filename, int t_volume = 100, int t_loops = 0, int t_channel = 0);

	bool isMusicPlaying();
	int IsChannelPLaying(int t_channel);
	void StopChannel(int t_channel);



private:
	AudioManager();
	~AudioManager();

	static AudioManager* sInstance;
	AssetManager* m_assetManager;

};