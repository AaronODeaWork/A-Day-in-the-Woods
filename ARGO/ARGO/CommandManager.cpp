#include <CommandManager.h>


CommandManager::CommandManager()
{}

void CommandManager::addCmd(Command* t_input, Entity* t_entity, int t_randomNumber)
{
	m_randNumber = t_randomNumber;
	m_entity = t_entity;
	//push onto stack then execute
	m_commands.push(t_input);
	execute();
}


void CommandManager::execute()
{
	m_entity->setRoll(m_randNumber);
	m_commands.top()->execute(*m_entity);
}