#ifndef INPUTCOMPONENT_H
#define INPUTCOMPONENT_H

/// <summary>
/// @author Jack Fennell
/// @date 07/02/2020
/// </summary>

#include <Component.h>
#include <InputHandler.h>


class InputComponent : public Component
{
public:
	InputHandler m_input;
	InputComponent(): Component(ComponentType::INPUT){}
	
};
#endif // !INPUTCOMPONENT_H