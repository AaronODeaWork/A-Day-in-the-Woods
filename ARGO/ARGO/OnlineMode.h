
#ifndef ONLINEMODE_H
#define ONLINEMODE_H

#include <SDL.h>
#include <SDL_image.h>

#include <iostream>
#include "Game.h"
#include <string>
#include <InputSystem.h>
#include "NumFromString.cpp"
#include "Client.h"

class Game;

class OnlineMode
{
public:
	OnlineMode(Game& game, SDL_Renderer* t_renderer, SDL_Event& event, GameState& t_currentState, InputSystem& t_inputSystem, std::vector<Player*> t_entity);
	~OnlineMode();
	void update();
	void render();
	void processEvent();
	void setGameState();
	void ConnectToServer();


private:
	int m_numberPlayers;
	Game& m_game;
	SDL_Texture* m_TestingTexture;
	SDL_Renderer* m_renderer;	// game renderer
	SDL_Event& m_event;

	Client* m_client;
	
	int x = 500;
	int y = 500;

	int m_myX = 10;
	int m_myY = 10;


	GameState& m_currentState;
	InputSystem m_inputSystem;
	std::vector<Player*> m_entity;
};
#endif // OPTIONS
