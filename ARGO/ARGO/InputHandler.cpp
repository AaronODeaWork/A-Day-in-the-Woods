#include <InputHandler.h>
InputHandler::InputHandler()
{    
	m_manager = new CommandManager();
	controlNumber = noOfControl++;
	
	m_controller = new Controller(controlNumber);
	
}

void InputHandler::ForceAButton(GameState& t_currentState, Player* t_entity)
{

	switch (t_currentState)
	{
	case GameState::Menu:
		break;
	case GameState::Online:
		break;
	case GameState::Gameplay:
		t_entity->setLastButton(1);
		m_manager->addCmd(diceRoll, t_entity, t_entity->randomNumber(6, 1));

		break;
	case GameState::Credit:
		break;
	case GameState::Minigame:
		break;
	case GameState::Splash:
		t_entity->setLastButton(1);

		break;
	default:
		break;
	}

}

void InputHandler::inputHandle(SDL_Event& event, GameState& t_currentState, Player* t_entity)
{
	if (controlNumber == t_entity->getId())
	{
		m_controller->update();

		if (event.type == SDL_CONTROLLERBUTTONDOWN)
		{
			MovementComponent* movePlay = static_cast<MovementComponent*>(t_entity->getEntity()->getComponent(ComponentType::MOVEMENT));

			if (m_controller->m_currentState.A)
			{
		

				switch (t_currentState)
				{
				case GameState::Menu:
					t_entity->setLastButton(1);
					m_controller->rumbleLow();
					m_manager->addCmd(buttonA, t_entity, NULL);
					break;
				case GameState::Online:
					m_controller->rumbleLow();
					break;
				case GameState::Gameplay:	
						t_entity->setLastButton(1);
						
						if (movePlay->getTakeingTurn())
						{
							m_controller->rumbleLow();
							m_manager->addCmd(DirectionDown, t_entity, NULL);
						}
						else
						{
							m_controller->rumble();
							m_manager->addCmd(diceRoll, t_entity, t_entity->randomNumber(6, 1));
						}
					break;
				case GameState::Credit:
					m_controller->rumbleLow();
					break;
				case GameState::Minigame:					
					t_entity->setLastButton(1);
					m_controller->rumbleLow();
					m_manager->addCmd(buttonA, t_entity, NULL);
					break;
					m_controller->rumbleLow();
				case GameState::Splash:
					m_controller->rumbleLow();
					t_entity->setLastButton(1);
				default:
					break;
				}
			}

			if (m_controller->m_currentState.B)
			{
				m_controller->rumbleLow();

				switch (t_currentState)
				{
				case GameState::Menu:
					break;
				case GameState::Online:
					t_entity->setLastButton(4);
					m_manager->addCmd(buttonB, t_entity, NULL);
					break;
				case GameState::Gameplay:
					t_entity->setLastButton(4);
					m_manager->addCmd(DirectionRight, t_entity, NULL);
					break;
				case GameState::Credit:
					t_entity->setLastButton(4);
					m_manager->addCmd(buttonB, t_entity, NULL);
					break;
				case GameState::Minigame:
					break;
				default:
					break;
				}

				
			}

			if (m_controller->m_currentState.X)
			{
				m_controller->rumbleLow();

				switch (t_currentState)
				{
				case GameState::Menu:
					m_manager->addCmd(buttonA, t_entity, NULL);
					break;
				case GameState::Online:
					break;
				case GameState::Gameplay:
					t_entity->setLastButton(5);
					m_manager->addCmd(DirectionLeft, t_entity, NULL);
					break;
				case GameState::Credit:
					break;
				case GameState::Minigame:
					m_manager->addCmd(buttonA, t_entity, NULL);
					break;
				default:
					break;
				}
			}

			if (m_controller->m_currentState.Y)
			{
				m_controller->rumbleLow();

				switch (t_currentState)
				{
				case GameState::Menu:
					m_manager->addCmd(buttonA, t_entity, NULL);
					break;
				case GameState::Online:
					break;
				case GameState::Gameplay:
					t_entity->setLastButton(6);
					m_manager->addCmd(DirectionUp, t_entity, NULL);
					break;
				case GameState::Credit:
					break;
				case GameState::Minigame:
					m_manager->addCmd(buttonA, t_entity, NULL);
					break;
				default:
					break;
				}
			}

			if (m_controller->m_currentState.Back)
			{
				m_manager->addCmd(buttonBack, t_entity, NULL);
			}

			if (m_controller->m_currentState.Start)
			{
				m_manager->addCmd(buttonStart, t_entity, NULL);
			}

			if (m_controller->m_currentState.LB)
			{
				m_manager->addCmd(leftShoulder, t_entity, NULL);
			}

			if (m_controller->m_currentState.RB)
			{
				m_manager->addCmd(rightShoulder, t_entity, NULL);
			}

			if (m_controller->m_currentState.LeftThumbStickClick)
			{
				m_manager->addCmd(leftStick, t_entity, NULL);
			}

			if (m_controller->m_currentState.RightThumbStickClick)
			{
				m_manager->addCmd(rightStick, t_entity, NULL);
			}

			if (m_controller->m_currentState.DpadUp)
			{
				m_controller->rumbleLow();

				switch (t_currentState)
				{
				case GameState::Menu:
					t_entity->setLastButton(2);
					m_manager->addCmd(DpadUp, t_entity, NULL);
					break;
				case GameState::Online:
					break;
				case GameState::Gameplay:
					break;
				case GameState::Credit:
					break;
				case GameState::Minigame:
					break;
				default:
					break;
				}
			}

			if (m_controller->m_currentState.DpadDown)
			{
				
				m_controller->rumbleLow();

				switch (t_currentState)
				{
				case GameState::Menu:
					t_entity->setLastButton(3);
					m_manager->addCmd(DpadDown, t_entity, NULL);
					break;
				case GameState::Online:
					break;
				case GameState::Gameplay:
					break;
				case GameState::Credit:
					break;
				case GameState::Minigame:
					break;
				default:
					break;
				}
				
			}

			if (m_controller->m_currentState.DpadRight)
			{
				switch (t_currentState)
				{
				case GameState::Menu:
					break;
				case GameState::Online:
					break;
				case GameState::Gameplay:
					break;
				case GameState::Credit:
					break;
				case GameState::Minigame:
					break;
				default:
					break;
				}
				
			}

			if (m_controller->m_currentState.DpadLeft)
			{
				switch (t_currentState)
				{
				case GameState::Menu:
					break;
				case GameState::Online:
					break;
				case GameState::Gameplay:
					break;
				case GameState::Credit:
					break;
				case GameState::Minigame:
					break;
				default:
					break;
				}
			}
		}
	}
}

