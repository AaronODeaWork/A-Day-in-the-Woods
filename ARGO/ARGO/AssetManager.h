#pragma once

#include<map>
#include<string>
#include<SDL_mixer.h>
#include<SDL.h>
#include<iostream>

//singleton

class AssetManager {
public:
	
	static AssetManager* Instance();
	static void Release();

	Mix_Music* GetMusic(std::string t_filename);
	Mix_Chunk* GetSfx(std::string t_filename);

private:

	AssetManager();
	~AssetManager();

	static AssetManager* sInstance;

	std::map<std::string, Mix_Music*> m_music;
	std::map<std::string, Mix_Chunk*> m_sfx;
};