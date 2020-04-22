#include "Controller.h"

/// <summary>
/// @author Jack , Aaron
/// @date 12/02/2020
/// </summary>



Controller::Controller(int currentController): joystick_index(currentController)
{
	if (connect())
	{
		controller = SDL_GameControllerOpen(joystick_index);
		m_haptic = SDL_HapticOpenFromJoystick(SDL_GameControllerGetJoystick(controller));
		if (SDL_INIT_HAPTIC)SDL_INIT_HAPTIC;
		if (m_haptic != NULL)
		{
			SDL_HapticRumbleInit(m_haptic);
		}
	}




}

Controller::~Controller()
{
}

void Controller::rumble()
{

	SDL_HapticRumblePlay(m_haptic, .3, 1000);

}

void Controller::rumbleLow()
{
	SDL_HapticRumblePlay(m_haptic, .1, 200);

}



void Controller::update()
{



	if (controller == NULL && connect())
	{
		controller = SDL_GameControllerOpen(joystick_index);
	}
		//Controller Buttons
		m_currentState.A = SDL_GameControllerGetButton(controller, SDL_GameControllerButton::SDL_CONTROLLER_BUTTON_A);
		m_currentState.B = SDL_GameControllerGetButton(controller, SDL_GameControllerButton::SDL_CONTROLLER_BUTTON_B);
		m_currentState.X = SDL_GameControllerGetButton(controller, SDL_GameControllerButton::SDL_CONTROLLER_BUTTON_X);
		m_currentState.Y = SDL_GameControllerGetButton(controller, SDL_GameControllerButton::SDL_CONTROLLER_BUTTON_Y);
		m_currentState.Back = SDL_GameControllerGetButton(controller, SDL_CONTROLLER_BUTTON_BACK);
		m_currentState.Start = SDL_GameControllerGetButton(controller, SDL_CONTROLLER_BUTTON_START);
		m_currentState.LB = SDL_GameControllerGetButton(controller, SDL_CONTROLLER_BUTTON_LEFTSHOULDER);
		m_currentState.RB = SDL_GameControllerGetButton(controller, SDL_CONTROLLER_BUTTON_RIGHTSHOULDER);

		//Thumbstick clicks
		m_currentState.LeftThumbStickClick = SDL_GameControllerGetButton(controller, SDL_CONTROLLER_BUTTON_LEFTSTICK);
		m_currentState.RightThumbStickClick = SDL_GameControllerGetButton(controller, SDL_CONTROLLER_BUTTON_RIGHTSTICK);


		//D-pad Right
		m_currentState.DpadRight = SDL_GameControllerGetButton(controller,SDL_CONTROLLER_BUTTON_DPAD_RIGHT);
		//D-pad Left
		m_currentState.DpadLeft = SDL_GameControllerGetButton(controller, SDL_CONTROLLER_BUTTON_DPAD_LEFT);
		//D-pad Up
		m_currentState.DpadUp = SDL_GameControllerGetButton(controller, SDL_CONTROLLER_BUTTON_DPAD_UP);
		//D-pad Down
		m_currentState.DpadDown = SDL_GameControllerGetButton(controller, SDL_CONTROLLER_BUTTON_DPAD_DOWN);
		//Triggers
		m_currentState.LTrigger = SDL_GameControllerGetAxis(controller, SDL_CONTROLLER_AXIS_TRIGGERLEFT);
		m_currentState.RTrigger = SDL_GameControllerGetAxis(controller, SDL_CONTROLLER_AXIS_TRIGGERRIGHT);
		//Left Thumbstick
		m_currentState.LeftThumbStick.x = SDL_GameControllerGetAxis(controller, SDL_CONTROLLER_AXIS_LEFTX);
		m_currentState.LeftThumbStick.y = SDL_GameControllerGetAxis(controller, SDL_CONTROLLER_AXIS_LEFTY);
		//Right Thumbstick
		m_currentState.RightThumbStick.x = SDL_GameControllerGetAxis(controller, SDL_CONTROLLER_AXIS_RIGHTX);
		m_currentState.RightThumbStick.y = SDL_GameControllerGetAxis(controller, SDL_CONTROLLER_AXIS_RIGHTY);
	

}

bool Controller::connect()
{
	if (SDL_IsGameController(joystick_index))
	{
		return true;
	}
	else
	{
		return false;
	}

}

int Controller::ReturnID()
{
	return joystick_index;
}


