#ifndef TILE_H
#define TILE_H

/// <summary>
/// @Authors:
///		@Aaron O'Dea		@C00217820
/// </summary>
/// 
/// 
#include <SDL.h>
#include <iostream>

class Tile
{
public:
	Tile(float t_x , float t_y, int t_type);
	~Tile();


	void SetUp();
	void update();
	void render(SDL_Renderer* t_renderer);

	void setPosition();
	SDL_Rect & getPosition();
	int &getType();
	int count;
private:

	SDL_Rect rect;//temp rect for a tile square 
	int m_type;

	int m_width;
	int m_height;

	void green();
	void purple();
	void pink();
	void blue();
	void orange();
	void red();
};

#endif // !TILE_H