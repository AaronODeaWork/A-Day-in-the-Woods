/// <summary>
/// @author Jack Fennell
/// @date 06/02/2020
/// </summary>
#ifndef INPUTHANDLER_H
#define INPUTHANDLER_H

#include "GameStates.h"
#include <CommandManager.h>
#include <Player.h>
#include <iostream>
#include <Controller.h>
#include <vector>
#include <stack>
#include <SDL.h>



static int noOfControl;

class InputHandler
{
public: 
	InputHandler();
	void ForceAButton(GameState& t_currentState, Player* t_entity);

	void inputHandle(SDL_Event &event, GameState& t_currentState, Player* t_entity);
	
private:
	//Handles the action of the inputs
	CommandManager* m_manager;
    Controller* m_controller;
	
	
	//Controller buttons
	Command* diceRoll = new DiceRoll();
	Command* DirectionUp = new MoveUp();
	Command* DirectionDown = new MoveDown();
	Command* DirectionLeft = new MoveLeft();
	Command* DirectionRight = new MoveRight();

	Command* buttonA = new AButton();
	Command* buttonB = new BOutput();
	Command* buttonX = new XOutput();
	Command* buttonY = new YOutput();
	Command* buttonBack = new BackOutput();
	Command* buttonStart = new StartOutput();
	Command* leftShoulder = new LeftShoulderOutput();
	Command* rightShoulder = new RightShoulderOutput();
	Command* leftStick = new LeftStickOutput();
	Command* rightStick = new RightStickOutput();

	//Controller dpad
	Command* DpadUp = new UpOutput();
	Command* DpadDown = new DownOutput();
	Command* moveRight = new MoveRight();
	Command* moveLeft = new MoveLeft();
	int controlNumber;
	
};


#endif // !INPUTHANDLER_H