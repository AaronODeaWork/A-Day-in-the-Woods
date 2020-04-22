#ifndef MOVEMENTSYSTEM_H
#define MOVEMENTSYSTEM_H


#include "MovementComponent.h"
#include <vector>
#include "Entity.h"
#include "GameStates.h"


class MovementSystem
{
public:
	MovementSystem(GameState& t_currentState, std::vector<Tile>& t_map, Graph< pair<string, int>, int>& t_g, AudioManager & t_audioManager ) :
		m_gameState(t_currentState),
		m_map(t_map),
		m_graph(t_g),
		m_audioManager(t_audioManager)
	{
	}

	void addEntity(Entity* t_e, SDL_Rect & t_rect,bool & t_IsAi, bool& t_up, bool& t_down, bool& t_left, bool& t_right)
	{
		std::vector<Component*> InputCheck = t_e->getComponents();

		for (int i = 0; i < InputCheck.size(); i++)
		{
			if (InputCheck[i]->getType() == ComponentType::MOVEMENT)
			{
				m_entities.push_back(t_e);
				m_moveComp.push_back(static_cast<MovementComponent*>(InputCheck[i]));
				m_moveComp.back()->setRect(t_rect);
				m_moveComp.back()->setAiCheck(t_IsAi);
				m_moveComp.back()->setChoiceBools(t_up, t_down, t_left, t_right);
			}
		}
	}

	int getPlayerDiceValue(int t_index)
	{
		return m_moveComp[t_index]->getDiceValue();
	}

	void setPlayerDiceValue(int t_index, int num)
	{
		m_moveComp[t_index]->setDiceValue(num);
	}

	bool IsThePlayerMoving(int t_i)
	{
		return m_moveComp[t_i]->getTakeingTurn();
	}

	bool endGame(int t_i)
	{
		return m_moveComp[t_i]->getEndGame();
	}

	void ResetWinner(int t_index)
	{
		if (t_index != -1)
		{
			m_moveComp[t_index]->resetEndGame();
		}
	}
	
	float GetYPos(int t_index)
	{
		return m_moveComp[t_index]->getPosY();
	}

	void leftOrRightChoice(bool t_b, int index)
	{
		m_moveComp[index]->leftOrRightChoice(t_b);
	}
	
	void updateAll() {
		for (int i = 0; i < m_moveComp.size(); i++)
		{
			m_moveComp[i]->update(m_map, m_graph);
		}
	}

	void update(int t_index) {
		

		m_moveComp[t_index]->update(m_map, m_graph);
			
	}

	int getIndex(int t_index)
	{
		return m_moveComp[t_index]->getCurrentIndex();
	}


	void restPlayers()
	{
		for (int i = 0; i < m_entities.size(); i++) {m_moveComp[i]->reSetUp();}
	}
	
private:
	GameState & m_gameState;

	int m_storyPointIndex = 0;

	std::vector<Entity*> m_entities;
	std::vector<MovementComponent*> m_moveComp;

	Graph< pair<string, int>, int>& m_graph;
	std::vector<Tile>& m_map;
	AudioManager& m_audioManager;
};
#endif // !MOVEMENTSYSTEM_H
