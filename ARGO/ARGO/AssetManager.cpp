#include"AssetManager.h"


AssetManager* AssetManager::sInstance = NULL;


AssetManager* AssetManager::Instance()
{
	if (sInstance == NULL)
	{
		sInstance = new AssetManager();
	}
	return sInstance;
}

void AssetManager::Release()
{
	delete sInstance;
	sInstance = NULL;
}

AssetManager::AssetManager() {

}

AssetManager::~AssetManager() {

}

Mix_Music* AssetManager::GetMusic(std::string t_filename)
{
	std::string fullPath;
	fullPath.append("ASSETS\\AUDIO\\" + t_filename);

	if (m_music[fullPath] == nullptr)
	{
		m_music[fullPath] = Mix_LoadMUS(fullPath.c_str());
		
		if (m_music[fullPath] == NULL)
		{
			printf("Music Loading Error: File-%s Error-%s", t_filename.c_str(), Mix_GetError());
		}
	}

	return m_music[fullPath];
}

Mix_Chunk* AssetManager::GetSfx(std::string t_filename)
{
	std::string fullPath;
	fullPath.append("ASSETS\\AUDIO\\" + t_filename);

	if (m_sfx[fullPath] == nullptr)
	{
		m_sfx[fullPath] = Mix_LoadWAV(fullPath.c_str());

		if (m_sfx[fullPath] == NULL) 
		{
			printf("SFX Loading Error: File-%s Error-%s", t_filename.c_str(), Mix_GetError());
		}
	}

	return m_sfx[fullPath];
}
