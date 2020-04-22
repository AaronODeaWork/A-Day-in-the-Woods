#include "Minigame.h"

MinigameScreen::MinigameScreen(Game& game, SDL_Renderer* t_renderer, SDL_Event& event, GameState& t_currentState, InputSystem& t_inputSystem, std::vector<Player*> t_entity) :
	m_game(game),
	m_event(event),
	m_renderer(t_renderer),
	m_currentState(t_currentState),
	m_entity(t_entity),
	m_inputSystem(t_inputSystem)
{	
	m_numberPlayers = m_entity.size();
	m_ApressedDistance.push_back(NULL);
	m_ApressedDistance.push_back(NULL);
	m_ApressedDistance.push_back(NULL);
	m_ApressedDistance.push_back(NULL);
	m_playerAns.push_back(false);
	m_playerAns.push_back(false);
	m_playerAns.push_back(false);
	m_playerAns.push_back(false);

	m_buttonRectangle.push_back(SDL_Rect{40,600,400,400, });
	m_buttonRectangle.push_back(SDL_Rect{420,600,400,400 });
	m_buttonRectangle.push_back(SDL_Rect{1000,600,400,400 });
	m_buttonRectangle.push_back(SDL_Rect{1380,600,400,400 });

	SDL_Surface* m_backgroundImage = IMG_Load("ASSETS/IMAGES/BG.png");
	m_TestingTexture = SDL_CreateTextureFromSurface(m_renderer, m_backgroundImage);

	SDL_Surface* tempGlass = IMG_Load("ASSETS/IMAGES/pic2Glass.png");
	m_TestingTextureTwo = SDL_CreateTextureFromSurface(m_renderer, tempGlass);
	SDL_SetTextureBlendMode(m_TestingTextureTwo, SDL_BLENDMODE_BLEND);
	SDL_SetTextureAlphaMod(m_TestingTextureTwo, 150);

	SDL_Surface* reticleSurface = IMG_Load("ASSETS/IMAGES/reticle.png");
	m_reticleTexture = SDL_CreateTextureFromSurface(m_renderer, reticleSurface);

	SDL_Surface* m_buttonSurface;
	m_buttonSurface = IMG_Load("ASSETS/IMAGES/buttons/ABluePawButton.png");
	m_AbuttonTexture.push_back(SDL_CreateTextureFromSurface(m_renderer, m_buttonSurface));
	SDL_SetTextureBlendMode(m_AbuttonTexture[0], SDL_BLENDMODE_BLEND);

	m_buttonSurface = IMG_Load("ASSETS/IMAGES/buttons/AGreenPawButton.png");
	m_AbuttonTexture.push_back(SDL_CreateTextureFromSurface(m_renderer, m_buttonSurface));
	SDL_SetTextureBlendMode(m_AbuttonTexture[1], SDL_BLENDMODE_BLEND);

	m_buttonSurface = IMG_Load("ASSETS/IMAGES/buttons/APinkPawButton.png");
	m_AbuttonTexture.push_back(SDL_CreateTextureFromSurface(m_renderer, m_buttonSurface));
	SDL_SetTextureBlendMode(m_AbuttonTexture[2], SDL_BLENDMODE_BLEND);

	m_buttonSurface = IMG_Load("ASSETS/IMAGES/buttons/APurplePawButton.png");
	m_AbuttonTexture.push_back(SDL_CreateTextureFromSurface(m_renderer, m_buttonSurface));
	SDL_SetTextureBlendMode(m_AbuttonTexture[3], SDL_BLENDMODE_BLEND);

	SDL_Surface* WinSurface;
		WinSurface = IMG_Load("ASSETS/IMAGES/buttons/WinP1.png");
		m_WinScreenTexture.push_back(SDL_CreateTextureFromSurface(m_renderer, WinSurface));
		WinSurface = IMG_Load("ASSETS/IMAGES/buttons/WinP2.png");
		m_WinScreenTexture.push_back(SDL_CreateTextureFromSurface(m_renderer, WinSurface));
		WinSurface = IMG_Load("ASSETS/IMAGES/buttons/WinP3.png");
		m_WinScreenTexture.push_back(SDL_CreateTextureFromSurface(m_renderer, WinSurface));
		WinSurface = IMG_Load("ASSETS/IMAGES/buttons/WinP4.png");
		m_WinScreenTexture.push_back(SDL_CreateTextureFromSurface(m_renderer, WinSurface));
		WinSurface = IMG_Load("ASSETS/IMAGES/pic2Glass.png");
		m_WinScreenTexture.push_back(SDL_CreateTextureFromSurface(m_renderer, WinSurface));

	SDL_Surface* potSurface = IMG_Load("ASSETS/IMAGES/HoneyBig.png");
	m_honeyPotTexture = SDL_CreateTextureFromSurface(m_renderer, potSurface);

	m_Winsscreen.h = 1080;
	m_Winsscreen.w = 1920;
	m_Winsscreen.x = 0;
	m_Winsscreen.y = -400;

	reticleRectangle.h = 200;
	reticleRectangle.w = 200;
	reticleRectangle.x = 800;
	reticleRectangle.y = 350;

	honeyRectangle.h = 150;
	honeyRectangle.w = 150;


	SDL_FreeSurface(m_backgroundImage);
	SDL_FreeSurface(tempGlass);
	SDL_FreeSurface(reticleSurface);
	SDL_FreeSurface(m_buttonSurface);
	SDL_FreeSurface(WinSurface);
	SDL_FreeSurface(potSurface);
}

MinigameScreen::~MinigameScreen()
{
}

void MinigameScreen::processEvent()
{
	for (int i = 0; i < m_numberPlayers ;i++)
	{
		m_inputSystem.update(m_event, m_currentState, m_entity[i]);
	}


	m_direction.x = (honeyRectangle.x - reticleRectangle.x);
	m_direction.y = (honeyRectangle.y - reticleRectangle.y);
	

	if (EndPictureminiGame == true)
	{

		EndPictureminiGame = false;
		setGameState();
	}
}

void MinigameScreen::update()
{
	for (int i = 0; i < m_numberPlayers ;i++)
	{
		if (m_entity[i]->m_lastButtonPressed == 1)
		{
			m_playerAns[i] = true;
			m_ApressedDistance[i] = sqrt((m_direction.x) * (m_direction.x) + (m_direction.y) * (m_direction.y));
			SDL_SetTextureColorMod(m_AbuttonTexture[i], 120, 120, 120);
			m_entity[i]->setLastButton(NULL);
		}
	}

	switch (m_miniGameID)
	{
	default:
		break;

	case 1:
		m_runningTime = std::chrono::high_resolution_clock::now() - m_startTime;

	
		if (m_playerAns[3]== true && m_playerAns[2] == true && m_playerAns[1] == true && m_playerAns[0] == true)
		{
			SDL_Delay(500);
			GetWinnerPicture();
			EndPictureminiGame = true;
		}
		else if (m_runningTime > m_randTime)
		{
			honeyRectangle.x -= m_velocity.x;
			honeyRectangle.y -= m_velocity.y;
		}

		if (m_runningTime >= m_randTime + std::chrono::seconds(2)) 
		{
			SDL_Delay(500);
			GetWinnerPicture();
			EndPictureminiGame = true;
		}
		break;
	case 2:
		break;
	case 3:
		break;
	}



	//std::cout << "Minigame update" << std::endl;

	if (m_event.type == SDL_KEYDOWN)
	{
		if (m_event.key.keysym.sym == SDLK_SPACE || m_event.key.keysym.sym == SDLK_RETURN)
		{
			SDL_Delay(200);
			setGameState();
		}
	}
}



void MinigameScreen::render()
{
	
	if (EndPictureminiGame == true)
	{		
		SDL_RenderCopy(m_renderer, m_WinScreenTexture[winnerIndex], NULL, &m_Winsscreen);
	}

	SDL_RenderCopy(m_renderer, m_TestingTexture, NULL, NULL);



	SDL_RenderCopy(m_renderer, m_TestingTextureTwo, NULL, NULL);
	SDL_RenderCopy(m_renderer, m_honeyPotTexture, NULL, &honeyRectangle);// honey pot thatmoves accross the screen


	SDL_RenderCopy(m_renderer, m_reticleTexture, NULL, &reticleRectangle);

	for (int i = 0; i < m_numberPlayers ;i++)
	{
		SDL_RenderCopy(m_renderer, m_AbuttonTexture[i], NULL, &m_buttonRectangle[i]);
	}



}

void MinigameScreen::spriteMove()
{

	m_direction.x = (honeyRectangle.x  - (reticleRectangle.x+ (reticleRectangle.w/4)) );
	m_direction.y = (honeyRectangle.y - (reticleRectangle.y+ (reticleRectangle.h /4)));

	distance = sqrt((m_direction.x) * (m_direction.x) + (m_direction.y) * (m_direction.y));

	//m_angle = std::atan(m_directionY / m_directionX) * (180 / 3.141592);

	m_velocity.x = m_direction.x / (distance * 0.04);
	m_velocity.y = m_direction.y / (distance * 0.04);

}

void MinigameScreen::startMinGame(int t_mineGameID)
{
	m_startTime = std::chrono::high_resolution_clock::now();
	m_miniGameID = t_mineGameID;


	switch (t_mineGameID)
	{
	default:
		break;

	case 1:
		m_spawn = randomNumber(4, 1);
		m_randomNumber = randomNumber(5, 1);
		m_randTime = std::chrono::seconds(m_randomNumber);

		for (int i = 0; i < m_numberPlayers ;i++)
		{
			SDL_SetTextureColorMod(m_AbuttonTexture[i], 255, 255, 255);
			m_playerAns[i] = false;
		}




		switch (m_spawn)
		{
		case 1:

			
			honeyRectangle.x = -200;
			honeyRectangle.y = randomNumber(1080, 0);
			break;
		case 2:

		
			honeyRectangle.x = 2160;
			honeyRectangle.y = randomNumber(1080, 0);
			break;
		case 3:
			

			honeyRectangle.x = randomNumber(1960, 0);
			honeyRectangle.y = -200;
			break;
		case 4:
			honeyRectangle.x = randomNumber(1960, 0);
			honeyRectangle.y = 1280;
			break;
		default:
			break;
		}
		
		
		spriteMove();
	break;
	case 2:
	break;

	}


	
}

void MinigameScreen::setGameState()
{
	m_game.setGameState(GameState::Gameplay);
}

void MinigameScreen::GetWinnerPicture()
{	


		winnerIndex=4;
		float startNUM = 999999;
		for(int i = 0; i < m_entity.size()-1 ; i++ )
		{
			if (m_playerAns[i] == true)
			{
				if (startNUM > m_ApressedDistance[i]) 
				{
					startNUM = m_ApressedDistance[i];
					winnerIndex = i;
				}
			}		
		}
		std::cout << winnerIndex << std::endl;


}

int MinigameScreen::randomNumber(int t_max, int t_min)
{
	std::random_device device;
	std::mt19937 rng(device());
	std::uniform_int_distribution<std::mt19937::result_type> dist(t_min, t_max);
	return dist(rng);
}
