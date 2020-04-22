/// <summary>
/// @author Jack Fennell
/// @date 06/02/2020
/// </summary>


#pragma warning(push)
#pragma warning( disable:4703 )
#ifndef CONCRETECOMMANDS_H
#define CONCRETECOMMANDS_H


#include "CommandInterface.h"
#include <MovementComponent.h>
#include <iostream>

//Command list for inputs

class UpOutput : public Command
{
public:
	//placeholder for actual function prints out to command window
	virtual void execute(Entity& t_entity) {
		
		std::cout << "Up Dpad " << std::endl; 
	}
};

class DownOutput : public Command
{
public:
	//placeholder for actual function prints out to command window
	virtual void execute(Entity& t_entity) { std::cout << "Down Dpad " << std::endl; }
};



class MoveLeft : public Command
{
public:
	//placeholder for actual function prints out to command window


	virtual void execute(Entity& t_entity) {	
	MovementComponent* movePlay = static_cast<MovementComponent*>(t_entity.getComponent(ComponentType::MOVEMENT)); 
	movePlay->directionChoice(5);
	 }
};

class MoveRight : public Command
{
public:
	//placeholder for actual function prints out to command window

	virtual void execute(Entity& t_entity) { 
	MovementComponent* movePlay = static_cast<MovementComponent*>(t_entity.getComponent(ComponentType::MOVEMENT)); 
	movePlay->directionChoice(4);
	 }
};


class MoveUp : public Command
{
public:
	//placeholder for actual function prints out to command window


	virtual void execute(Entity& t_entity) {
		MovementComponent* movePlay = static_cast<MovementComponent*>(t_entity.getComponent(ComponentType::MOVEMENT));
		movePlay->directionChoice(6);
	}
};


class MoveDown : public Command
{
public:
	//placeholder for actual function prints out to command window


	virtual void execute(Entity& t_entity) {
		MovementComponent* movePlay = static_cast<MovementComponent*>(t_entity.getComponent(ComponentType::MOVEMENT));
		movePlay->directionChoice(1);
	}
};


//Controller Commands
class DiceRoll : public Command
{
public:
	//placeholder for actual function prints out to command window
	virtual void execute(Entity& t_entity) {
	MovementComponent* movePlay = static_cast<MovementComponent*>(t_entity.getComponent(ComponentType::MOVEMENT));
		movePlay->rollForMove(t_entity.getRoll());
	}
};
class AButton : public Command
{
public:
	//placeholder for actual function prints out to command window
	virtual void execute(Entity& t_entity) { 
	
	std::cout << "A Controller " << std::endl; 
	}
};
class BOutput : public Command
{
public:
	//placeholder for actual function prints out to command window
	virtual void execute(Entity& t_entity) { std::cout << "B Controller " << std::endl; }
};

class XOutput : public Command
{
public:
	//placeholder for actual function prints out to command window
	virtual void execute(Entity& t_entity) { std::cout << "X Controller " << std::endl; }
};

class YOutput : public Command
{
public:
	//placeholder for actual function prints out to command window
	virtual void execute(Entity& t_entity) { std::cout << "Y Controller " << std::endl; }
};

class BackOutput : public Command
{
public:
	//placeholder for actual function prints out to command window
	virtual void execute(Entity& t_entity) { std::cout << "Back Button Controller " << std::endl; }
};

class StartOutput : public Command
{
public:
	//placeholder for actual function prints out to command window
	virtual void execute(Entity& t_entity) { std::cout << "Start Button Controller " << std::endl; }
};

class LeftShoulderOutput : public Command
{
public:
	//placeholder for actual function prints out to command window
	virtual void execute(Entity& t_entity) { std::cout << "Left Shoulder Controller " << std::endl; }
};

class RightShoulderOutput : public Command
{
public:
	//placeholder for actual function prints out to command window
	virtual void execute(Entity& t_entity) { std::cout << "Right Shoulder Controller " << std::endl; }
};

class LeftStickOutput : public Command
{
public:
	//placeholder for actual function prints out to command window
	virtual void execute(Entity& t_entity) { std::cout << "Left Stick Controller " << std::endl; }
};

class RightStickOutput : public Command
{
public:
	//placeholder for actual function prints out to command window
	virtual void execute(Entity& t_entity) { std::cout << "Right Stick Controller " << std::endl; }
};



#endif // !CONCRETECOMMANDS_H
#pragma warning( pop )