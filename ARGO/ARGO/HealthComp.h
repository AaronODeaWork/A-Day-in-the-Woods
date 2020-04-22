#ifndef HEALTHCOMP_H
#define HEALTHCOMP_H

#include "Component.h"

class HealthComponent : public Component
{
public:

	HealthComponent() : Component(ComponentType::HEALTH), m_health(100) {}
	HealthComponent(int t_healthNum) : Component(ComponentType::HEALTH), m_health(t_healthNum) {}

	int getHealth() { return m_health; }
	void setHealth(int t_health) { this->m_health = t_health; }

private:
	int m_health;
};

#endif // !HEALTHCOMP_H