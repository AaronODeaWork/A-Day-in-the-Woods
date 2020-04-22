#ifndef COMPONENT_H

#define COMPONENT_H


#include <SDL.h>

enum class ComponentType {
	HEALTH,
	POSITION,
	INPUT,
	MOVEMENT
};

class Component {

public:

	Component(ComponentType t_type) : m_compType(t_type) {};

	ComponentType getType() { return m_compType; }
	void setType(ComponentType t_type) { m_compType = t_type; }

private:
	ComponentType m_compType;
};

#endif // !COMPONENT_H