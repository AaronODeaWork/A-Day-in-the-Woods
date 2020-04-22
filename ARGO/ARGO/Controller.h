/// <summary>
///	@author Jack Fennell
/// @date 12/02/2020
/// </summary>

#ifndef CONTROLLER
#define CONTROLLER
#include <SDL.h>

struct GamePadState
{
	bool A;
	bool B;
	bool X;
	bool Y;
	bool LB;
	bool RB;
	bool LeftThumbStickClick;
	bool RightThumbStickClick;
	bool DpadUp;
	bool DpadDown;
	bool DpadLeft;
	bool DpadRight;
	bool Start;
	bool Back;
	float RTrigger;
	float LTrigger;
	SDL_Point RightThumbStick;
	SDL_Point LeftThumbStick;
	

};

class Controller {
private:
	
	const int joystick_index;
	SDL_GameController* controller;
public:
	const int DPAD_THRESHOLD = 8000;
	SDL_Haptic* m_haptic;

	
	GamePadState m_currentState;
	
	Controller(int currentController);
	~Controller();
	
	void rumble();
	void rumbleLow();

	void update();
	bool connect();
	int ReturnID();

};

#endif // !CONTROLLER


