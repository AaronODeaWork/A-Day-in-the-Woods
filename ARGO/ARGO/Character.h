#pragma once

#include "SDL.h"
#include <SDL_image.h>

class Character {
public:
	Character() {};
	virtual ~Character() {};
	virtual void Render(SDL_Renderer* t_renderer) = 0;
	virtual void Update() = 0;
	virtual void SetUp(int t_x, int t_y, int t_w, int t_h, SDL_Texture& t_texture) = 0;
};