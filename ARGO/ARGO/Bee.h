#pragma once

#include "Character.h"

class Bee : public Character {
public:

	void SetUp(int t_x, int t_y, int t_w, int t_h, SDL_Texture& t_texture) {
		m_body.x = t_x;
		m_body.y = t_y;

		m_body.w = t_w;
		m_body.h = t_h;

		m_texture = &t_texture;
	}

	void Update() {
		m_body.x += 10.0;
	}

	void Render(SDL_Renderer* t_renderer) {
		SDL_RenderCopy(t_renderer, m_texture, NULL, &m_body);
	}

private:
	SDL_Rect m_body;
	SDL_Texture* m_texture;
};