
#ifndef SPLASH_H
#define SPLASH_H
#include <SDL.h>
#include <SDL_image.h>

#include <iostream>
#include "Game.h"
#include <InputSystem.h>
#include "AudioManager.h"

class Game;

class SplashScreen
{
public:
	SplashScreen(Game& game, SDL_Renderer* t_renderer, SDL_Event& event, GameState& t_currentState, InputSystem& t_inputSystem, std::vector<Player*> t_entity, AudioManager& t_audioManager);
	~SplashScreen();
	void update();
	void render();
	void processEvent();
	void setGameState();
private:
	int m_numberPlayers;

	Game& m_game;
	SDL_Texture* m_splashTexture;
	SDL_Renderer* m_renderer;	// game renderer
	SDL_Event& m_event;


	SDL_Texture*  m_buttonSelectorTexture; // button texture
	SDL_Rect m_buttonSelectorRect;
	bool flip{ true };
	SDL_Rect m_titleRect;

	AudioManager& m_audioManager;

	GameState& m_currentState;
	InputSystem m_inputSystem;
	std::vector<Player*> m_entity;
};

#endif // !SPLASH_H
