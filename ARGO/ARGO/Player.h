#pragma once

#ifndef PLAYER_H
#define PLAYER_H


#include <SDL.h>
#include <SDL_image.h>

#include <vector>
#include "Tile.h"
#include <iostream>
#include <string>
#include "Graph.h"
#include "Entity.h"
#include "MovementSystem.h"
#include <random>

/// <summary>
/// @Authors:
///		@Aaron O'Dea		@C00217820
/// </summary>
/// 
/// 

class Player : public Entity 
{
public:
	Player(int entityIdNum);
	~Player();

	void assignSprite(SDL_Texture* t_PlayerTexture);
	void SetUp();
	void update(MovementSystem & t_move);
	void render(SDL_Renderer* t_renderer,int t_rotation);
	void setPosition(float t_x, float t_y);
	void setPositionOnline(int m_x, int m_y);
	void resetIndex();

	void updateOnline();
	std::string GetPosAsString();

	void setTileType(int t_type, int t_index);
	
	int randomNumber(int t_max, int t_min)
	{
		if (!m_takingTurn)
		{
			std::random_device device;
			std::mt19937 rng(device());
			std::uniform_int_distribution<std::mt19937::result_type> dist(t_min, t_max);
			diceRoll = dist(rng);
		}
		return diceRoll;
	}

	SDL_Rect * getPlayerRectRef();
	
	SDL_Rect getPosition() { return rect; };
	int getDiceRoll() { return diceRoll; };
	int m_lastButtonPressed {NULL};
	void setLastButton(int t_button) { m_lastButtonPressed = t_button; };
	int getLastButtonPressed() { return m_lastButtonPressed; };
	
	std::string GetValueAsString();


	bool IsAI{ false };
	bool m_leftChoiceBool{false};
	bool m_rightChoiceBool{ false };
	bool m_upChoiceBool{ false };
	bool m_downChoiceBool{ false };

private:

	SDL_Rect rect;//temp rect for a player square
	SDL_Rect m_spriteBody;
	SDL_Texture* m_PlayerTexture;
	int diceRoll{-1};




void tileBehaviour();
	


	int m_width;
	int m_height;
	int tileType;
	int currentIndex;
	bool stuck{ false };


	bool m_takingTurn;

};
#endif // !PLAYER_H