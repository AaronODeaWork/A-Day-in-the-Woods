#ifndef ENTITY_H

#define ENTITY_H


#include <vector>
#include "Component.h"

class Entity
{
public:
	Entity(int t_idNum) : m_id(t_idNum) {};
	void addComponent(Component* t_c) { m_components.push_back(t_c); }
	void removeComponent(ComponentType t_c) { 
		for (int i = 0; i < m_components.size(); i++)
		{
			if (t_c == m_components[i]->getType())
			{
				m_components.erase(m_components.begin() + i);
				break;
			}
		}
	}

	std::vector<Component*> getComponents() { return m_components; }
	Component* getComponent(ComponentType t_type)
	{
		for (int i = 0; i < m_components.size(); i++)
		{
			if (m_components[i]->getType() == t_type)
			{
				return m_components[i];
			}
		}
	}
	int getId() { return m_id; }

	Entity * getEntity(){
		return this;
	}

	void setRoll(int roll) { m_diceValue = roll; }
	int getRoll() { return m_diceValue; };

private:

	std::vector<Component*> m_components;
	int m_id;


	int m_diceValue{ 1 };
};

#endif // !ENTITY_H