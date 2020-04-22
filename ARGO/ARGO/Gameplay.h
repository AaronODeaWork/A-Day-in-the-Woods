
#ifndef GAMEPLAY
#define GAMEPLAY
#include <SDL.h>
#include <SDL_image.h>

#include <iostream>
#include "Game.h"
#include "Tile.h"
#include <map>
#include "Graph.h"
#include "Player.h"
#include "NPC.h"
#include <InputSystem.h>
#include "Entity.h"
#include "MovementSystem.h"
#include "MovementComponent.h"
#include "Camera.h"

#include "AudioManager.h"
#include "BehaviourTree.h"

class Game;

class Gameplay
{
public:
	Gameplay(Game& game, SDL_Renderer* t_renderer, SDL_Event& event, GameState& t_currentState , SDL_Window* t_window, InputSystem& t_input, std::vector<Player*> t_entity, AudioManager& t_audioManager );
	~Gameplay();
	void update(std::vector<Tile>& t_tile, std::vector<Player*>& t_player, std::vector<NPC*>& t_npc, MovementSystem & t_move);
	void render(std::vector<Tile>& t_tile, std::vector<Player*>& t_player, std::vector<NPC*>& t_npc, Graph< pair<string, int>, int>& graph);
	void renderWin(int index);
	
	void processEvent(MovementSystem& t_move);
	void setGameState();
	void Reset(MovementSystem& t_move);
	int randomNumber(int t_max, int t_min);
	
	int m_npcCount = 0;
	int m_turnOrder{ 0 };

	//AudioManager* m_audioManager;

private:
	int m_numberPlayers;
	
	float calculateScale(float width, float height, float maxWidth, float maxHeight);
	SDL_Window* m_window;

	void setDiceTexture(int m_playerID);
	void setRandomDiceTexture(int m_playerID);

	int m_rotation = 0;

	AudioManager& m_audioManager;
	
	//------------ Camera -------------
	float scale = .9f;
	Camera * camera = new Camera();	//camera
	SDL_Rect* focus = new SDL_Rect();
	SDL_Rect* offset = new SDL_Rect();

	//background
	SDL_Texture* m_backgroundTexture;
	SDL_Rect m_backgroundRect;

	SDL_Texture* m_backgroundTextureTwo;

	//Dice
	std::vector <SDL_Texture*> m_DiceTexture; // Dice texture
	std::vector <SDL_Texture*> m_DiceTextureSides; // Dice texture

	std::vector<SDL_Rect> m_DiceRect;

	//player UI
	std::vector<SDL_Texture*>m_PlayerUITexture; // Player UI texture
	std::vector<SDL_Rect> m_PlayerUIRect;
	
	std::vector<SDL_Texture*>m_PlayerShadowUITexture; // Player Shadow UI texture
	std::vector<SDL_Rect> m_PlayerShadowUIRect;

	//Clouds
	std::vector<SDL_Rect> m_clouds;
	SDL_Texture* m_CloudTexture; // Clouds texture

	//Outline
	std::vector<SDL_Rect> m_outLine;
	SDL_Texture* m_outLineTexture; // outline texture	
	//Table 
	SDL_Texture* m_taskbarTexture;
	SDL_Rect m_taskbarRect;

	//Winner Screen
	std::vector <SDL_Texture*> m_WinScreenTexture; // win screen
	SDL_Rect m_Winsscreen;
	//Direction Indicators 
	std::vector<SDL_Texture*> m_IndicatorTexture; // Indicator texture	
	std::vector<SDL_Rect> m_IndicatorRect;




	// ------ A* stuff ----------
	//void aStar();

	SDL_AudioSpec wavSpec;
	Uint32 wavLength;
	Uint8* wavBuffer;
	SDL_AudioDeviceID deviceId;
	
	bool setUp{ false };
	bool startAstar{ false };
	//------! A* stuff ------------

	bool m_flipUIBear{ false };
	bool m_diceAnimation{ false };
	int m_diceflip = 2;


	int m_width;
	int m_height;

	Game& m_game;
	SDL_Renderer* m_renderer;	// game renderer
	SDL_Event& m_event;

	std::vector<Player*> m_entity;

	GameState& m_currentState;
	InputSystem& m_inputSystem;

	int m_storyPointIndex = 0;
};

#endif // !GAMEPLAY