/// <summary>
/// @author Jack Fennell
/// @date 06/02/2020
/// </summary>
#ifndef COMMANDMANGER_H
#define COMMANDMANGER_H

#include <stack>
#include <ConcreteCommands.h>
#include <MovementComponent.h>

class CommandManager
{
public:

	CommandManager();
	void addCmd(Command* t_input, Entity* t_entity, int t_randomNumber);



	void execute();
	Entity* m_entity;
private: 
	std::stack<Command*> m_commands;
	int m_randNumber;
	
};


#endif // !COMMANDMANGER_H