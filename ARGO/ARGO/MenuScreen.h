#ifndef MENU
#define MENU

#include <SDL.h>
#include <SDL_image.h>

#include <iostream>
#include <Game.h>
#include <Player.h>
#include <InputSystem.h>

#include "CharacterFactory.h"

#include"AudioManager.h"

class Game;

class MenuScreen
{
public:
	MenuScreen(Game& game, SDL_Renderer* t_renderer, SDL_Event &event, GameState& t_currentState, InputSystem& t_inputSystem, std::vector<Player*> t_entity, AudioManager & t_audioManager );
	~MenuScreen();
	void update();
	void render();
	void processEvent();
	void setGameState();

	Factory* m_factory;
	std::vector<Character*> m_characters;

private:
	int m_numberPlayers;
	Game& m_game;
	SDL_Renderer* m_renderer;	// game renderer
	SDL_Event& m_event;

	GameState& m_currentState;
	InputSystem m_inputSystem;
	std::vector<Player*> m_entity;

	const int MENU_NUM = 4;
	int m_currentButton = 0;

	//Background
	SDL_Texture* m_backgroundTexture;
	//Background
	SDL_Texture* m_titleTexture;
	SDL_Rect m_titleRect;

	//Selector for Buttons 
	std::vector <SDL_Texture*> m_buttonSelectorTexture; // button texture
	std::vector <SDL_Texture*> m_buttonSelectorTextureTwo; // button texture
	std::vector<SDL_Rect> m_buttonSelectorRect;
	std::vector<SDL_Rect> m_buttonSelectorRectTwo;

	bool flip{true};
	
	//Buttons
	std::vector <SDL_Texture*> m_menuButtonTexture;
	std::vector<SDL_Rect> m_menuButtonPosition;
	std::vector<SDL_Rect> m_menuButtonPositionSelected;

	SDL_AudioSpec wavSpec;
	Uint32 wavLength;
	Uint8* wavBuffer;
	SDL_AudioDeviceID deviceId;
	bool audioPlaying = false;
	//bee
	SDL_Texture* m_beeTexture;

	AudioManager & m_audioManager;
};
#endif // MENU