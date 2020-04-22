#ifndef GAME_H
#define GAME_H

#include <SDL.h>
#include <SDL_image.h>

#include <iostream>
#include <fstream>
#include <string>
#include <utility>
#include <map>
#include "Graph.h"

#include "GameStates.h"
#include "MenuScreen.h"
#include "OnlineMode.h"
#include "Gameplay.h"
#include "CreditsScreen.h"
#include "Minigame.h"
#include "SplashScreen.h"

#include "Entity.h"
#include "HealthComp.h"
#include "PositionComp.h"
#include "RenderSystem.h"
#include "InputComponent.h"
#include "InputSystem.h"
#include "Player.h"
#include "NPC.h"
#include "MovementSystem.h"
#include "MovementComponent.h"
#include "AudioManager.h"

#include "Client.h"



class MenuScreen;
class OnlineMode;
class Gameplay;
class CreditScreen;
class MinigameScreen;
class SplashScreen;

typedef GraphArc<pair<std::string, int>, int> Arcs;
typedef GraphNode<pair<std::string, int>, int> Node;

/// <summary>
/// Main Game Class
/// </summary>
class Game
{
public:
	Game();
	~Game();
	void run();
	GameState m_currentState{ GameState::Splash };
	void setGameState(GameState t_newState) { m_currentState = t_newState; };
	void connecToServer();

	void startMinGame();
	void renderNOW();
	void RestGameplay();
private:
	void processEvent();
	void update();
	void render();

	void clean();

	MenuScreen* m_menuscreen;
	OnlineMode* m_onlineMode;
	Gameplay* m_gameplayscreen;
	CreditScreen* m_creditscreen;
	MinigameScreen* m_minigamescreen;
	SplashScreen* m_splashscreen;
	
	SDL_Window* m_window;	// game window
	SDL_Renderer* m_renderer;	// game renderer

	bool m_isRunning;	// is game running?
	
	SDL_Texture* m_TestingTexture;
	SDL_Event event;

	AudioManager * m_audioManager;

	void initNodeFiles();
	map<string, int> nodemap;
	pair<string, int> nodeLabel;

	int posX = 0;
	int posY = 0;
	int type = 0;
	int index = 0;
	ifstream myfile;

	bool GameWon{ false  };

	int winnerIndex;

	string from, to;
	int weight;

	int m_width;
	int m_height;

	std::vector<Tile> m_tile;

	std::vector<Player*> m_player;
	std::vector<NPC*> m_npc;

	//Client
	Client* m_client;


	//---------Entity + Components-----------
	InputSystem m_inputSystem;
	MovementSystem m_movementSystem;
};

#endif // !GAME_H