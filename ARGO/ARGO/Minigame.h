
#ifndef MINIGAME
#define MINIGAME

#include <SDL.h>
#include <SDL_image.h>
#include <chrono>
#include <ctime>
#include <iostream>
#include "Game.h"
#include <random>
#include <math.h>
#include "Player.h"
#include "InputSystem.h"

class Game;

class MinigameScreen
{
public:
	MinigameScreen(Game& game, SDL_Renderer* t_renderer, SDL_Event& event, GameState& t_currentState , InputSystem& t_inputSystem, std::vector<Player*> t_entity);
	~MinigameScreen();

	void processEvent();
	void update();
	void render();
	void spriteMove();
	void startMinGame(int t_mineGameID);
	void setGameState();


private:
	int m_numberPlayers;
	GameState& m_currentState; // can remove
	InputSystem m_inputSystem;
	std::vector<Player*> m_entity;



	void GetWinnerPicture();


	SDL_Rect m_direction;
	int m_angle = 0;
	
	SDL_Rect m_velocity;

	float distance = 0;
	int magnitude = 0;

	int randomNumber(int t_max, int t_min);

	std::chrono::time_point<std::chrono::steady_clock> m_startTime;
	std::chrono::duration<float> m_runningTime;
	std::chrono::duration<float> m_randTime;

	//end mini game bools
	bool EndPictureminiGame = false;



	//snapShot 
	int m_randomNumber;
	int m_spawn;
	SDL_Texture* m_reticleTexture; //camera reticle


	//id for mini game 
	int m_miniGameID = 0;

	Game& m_game;
	SDL_Texture* m_TestingTexture;
	SDL_Texture* m_TestingTextureTwo;


	


	std::vector< SDL_Texture*> m_AbuttonTexture;
	std::vector< SDL_Rect> m_buttonRectangle;
	std::vector<float> m_ApressedDistance;
	std::vector<bool> m_playerAns;





	int winnerIndex = 0;
	std::vector <SDL_Texture*> m_WinScreenTexture; // win screen
	SDL_Rect m_Winsscreen;

	SDL_Texture* m_honeyPotTexture; //honey pot
	SDL_Rect reticleRectangle;
	SDL_Rect honeyRectangle;


	SDL_Renderer* m_renderer;	// game renderer
	SDL_Event& m_event;

	
};
#endif // MINIGAME
