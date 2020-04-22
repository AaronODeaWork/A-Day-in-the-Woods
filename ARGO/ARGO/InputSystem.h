#ifndef INPUTSYSTEM_H
#define INPUTSYSTEM_H

#include <iostream>
#include <vector>
#include "SDL.h"
#include "Game.h"
#include "Entity.h"
#include "Player.h"
#include "InputComponent.h"



class InputSystem {
public:
	InputSystem()
	{}

	void addEntity(Entity* t_e)
	{
		
		std::vector<Component*> InputCheck = t_e->getComponents();

		for (int i = 0; i < InputCheck.size(); i++)
		{
			if (InputCheck[i]->getType() == ComponentType::INPUT)
			{
				m_entities.push_back(t_e);
				m_inputComp.push_back(static_cast<InputComponent*>(InputCheck[i]));
			}
		}
	}
	
	void update(SDL_Event &event, GameState &t_currentState, Player* t_entity)
	{

		if (t_entity->IsAI == true)
		{
			m_inputComp[t_entity->getId()]->m_input.ForceAButton(t_currentState,t_entity);
		}
		else{m_inputComp[t_entity->getId()]->m_input.inputHandle(event, t_currentState, t_entity);}
		
	}


	void update(SDL_Event& event, GameState& t_currentState, Player* t_entity, int t_index)
	{
		if (t_entity->IsAI == true)
		{
			m_inputComp[t_entity->getId()]->m_input.ForceAButton(t_currentState, t_entity);
		}
		else {m_inputComp[t_index]->m_input.inputHandle(event, t_currentState, t_entity);}
	}

private:

	//Game& game;
	std::vector<Entity*> m_entities;
	std::vector<InputComponent*> m_inputComp;
};

#endif // !INPUTSYSTEM_H
