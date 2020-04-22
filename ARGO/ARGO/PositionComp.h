#ifndef POSTIONCOMPONENT_H
#define POSTIONCOMPONENT_H

#include "Component.h"

class PositionComponent : public Component
{
public:
	PositionComponent(SDL_Rect t_pos) : Component(ComponentType::POSITION), m_pos(t_pos) { setPosition(t_pos); }

	void setPosition(SDL_Rect t_pos) { this->m_pos = t_pos; }
	SDL_Rect getPos() { return m_pos; }

	void move(SDL_Rect t_movementVec) {
		this->m_pos.x += t_movementVec.x;
		this->m_pos.y += t_movementVec.y;
	}

private:
	SDL_Rect m_pos;
};
#endif // !POSTIONCOMPONENT_H