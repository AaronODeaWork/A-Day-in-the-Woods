#include"AudioManager.h"


AudioManager* AudioManager::sInstance = NULL;



// wants a vector / audio que
// info on if the player is at a turn

AudioManager * AudioManager::Instance()
{
	if (sInstance == NULL)
	{
		sInstance = new AudioManager();
	}
	return sInstance;
}

void AudioManager::Release()
{
	delete sInstance;
	sInstance = NULL;
}

AudioManager::AudioManager() 
{
	m_assetManager = AssetManager::Instance();

	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 4096) < 0) {
		printf("Mixer Init Error: %s\n", Mix_GetError());
	}
}

AudioManager::~AudioManager()
{
	m_assetManager = NULL;
	Mix_Quit();
}


void AudioManager::PlayMusic(std::string t_filename, int t_volume, int t_loops)
{
	Mix_PlayMusic(m_assetManager->GetMusic(t_filename), t_loops);
	Mix_VolumeMusic(t_volume);
}



void AudioManager::PauseMusic()
{
	if (Mix_PlayingMusic() != 0)
	{
		Mix_PausedMusic();
	}
}

void AudioManager::ResumeMusic()
{
	if (Mix_PausedMusic() != 0)
	{
		Mix_ResumeMusic();
	}
}

void AudioManager::PlaySfx(std::string t_filename, int t_volume, int t_loops, int t_channel)
{
	Mix_PlayChannel(t_channel, m_assetManager->GetSfx(t_filename), t_loops);
	Mix_VolumeChunk(m_assetManager->GetSfx(t_filename), t_volume);
}

bool AudioManager::isMusicPlaying()
{
	return Mix_PlayingMusic();
}

int AudioManager::IsChannelPLaying(int t_channel)
{
	return Mix_Playing(t_channel);
}

void AudioManager::StopChannel(int t_channel)
{
	Mix_HaltChannel(t_channel);
}
