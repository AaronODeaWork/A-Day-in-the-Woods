#ifndef RENDERSYSTEM_H
#define RENDERSYSTEM_H

#include"Entity.h"
#include"PositionComp.h"


class RenderSystem
{
public:

	void addEntity(Entity* t_e, SDL_Texture* t_tex)
	{
		std::vector<Component*> RenderCheck = t_e->getComponents();

		for (int i = 0; i < RenderCheck.size(); i++)
		{
			if (RenderCheck[i]->getType() == ComponentType::POSITION)
			{
				m_entities.push_back(t_e);
				m_posComp.push_back(static_cast<PositionComponent*>(RenderCheck[i]));
			}
		}
	}

	void removeEntityFromSystem(int t_entityID) {
		for (int i = 0; i < m_entities.size(); i++)
		{
			if (m_entities[i]->getId() == t_entityID)
			{
				m_entities[i]->removeComponent(ComponentType::POSITION);

				m_entities.erase(m_entities.begin() + i);
				m_posComp.erase(m_posComp.begin() + i);
			}
		}
	}

	void update(SDL_Renderer* t_renderer)
	{
		SDL_RenderClear(t_renderer);
		for (int i = 0; i < m_entities.size(); i++)
		{
			SDL_SetRenderDrawColor(t_renderer, 255, 255, 255, 255);
			SDL_RenderDrawRect(t_renderer, &m_posComp[i]->getPos());
			SDL_SetRenderDrawColor(t_renderer, 0, 0, 0, 255);
			SDL_RenderPresent(t_renderer);
		}
	}

	
private:
	std::vector<Entity*> m_entities;
	std::vector<PositionComponent*> m_posComp;
	//std::vector<SDL_Texture*> m_textureList;
};

#endif // !RENDERSYSTEM_H