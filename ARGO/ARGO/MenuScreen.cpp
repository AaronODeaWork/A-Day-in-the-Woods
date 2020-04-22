#include "MenuScreen.h"

MenuScreen::MenuScreen(Game& game, SDL_Renderer* t_renderer, SDL_Event& event, GameState& t_currentState, InputSystem& t_inputSystem, std::vector<Player*> t_entity, AudioManager& t_audioManager) :
	m_game(game),
	m_event(event),
	m_renderer(t_renderer),
	m_inputSystem(t_inputSystem),
	m_currentState(t_currentState),
	m_entity(t_entity),
	m_audioManager(t_audioManager)
{
	m_numberPlayers = m_entity.size();
	SDL_Surface* m_backgroundSurface = IMG_Load("ASSETS\\IMAGES\\MainMenuBg.png");
	m_backgroundTexture = SDL_CreateTextureFromSurface(m_renderer, m_backgroundSurface);
	
	SDL_Surface* m_titleSurface = IMG_Load("ASSETS\\IMAGES\\Title.png");
	m_titleTexture  = SDL_CreateTextureFromSurface(m_renderer, m_titleSurface);

	SDL_Surface* m_menuButtonSurface;
	m_menuButtonSurface = IMG_Load("ASSETS\\IMAGES\\game.png");
	m_menuButtonTexture.push_back(SDL_CreateTextureFromSurface(m_renderer, m_menuButtonSurface));
	m_menuButtonSurface = IMG_Load("ASSETS\\IMAGES\\options.png");
	m_menuButtonTexture.push_back(SDL_CreateTextureFromSurface(m_renderer, m_menuButtonSurface));
	m_menuButtonSurface = IMG_Load("ASSETS\\IMAGES\\credits.png");
	m_menuButtonTexture.push_back(SDL_CreateTextureFromSurface(m_renderer, m_menuButtonSurface));
	m_menuButtonSurface = IMG_Load("ASSETS\\IMAGES\\quit.png");
	m_menuButtonTexture.push_back(SDL_CreateTextureFromSurface(m_renderer, m_menuButtonSurface));

	SDL_Surface* m_buttonSelectorSurface;
	m_buttonSelectorSurface = IMG_Load("ASSETS/IMAGES/buttons/ABluePawButton.png");
	m_buttonSelectorTexture.push_back(SDL_CreateTextureFromSurface(m_renderer, m_buttonSelectorSurface));
	m_buttonSelectorTextureTwo.push_back(SDL_CreateTextureFromSurface(m_renderer, m_buttonSelectorSurface));
	m_buttonSelectorSurface = IMG_Load("ASSETS/IMAGES/buttons/AGreenPawButton.png");
	m_buttonSelectorTexture.push_back(SDL_CreateTextureFromSurface(m_renderer, m_buttonSelectorSurface));
	m_buttonSelectorTextureTwo.push_back(SDL_CreateTextureFromSurface(m_renderer, m_buttonSelectorSurface));
	m_buttonSelectorSurface = IMG_Load("ASSETS/IMAGES/buttons/APinkPawButton.png");
	m_buttonSelectorTexture.push_back(SDL_CreateTextureFromSurface(m_renderer, m_buttonSelectorSurface));
	m_buttonSelectorTextureTwo.push_back(SDL_CreateTextureFromSurface(m_renderer, m_buttonSelectorSurface));
	m_buttonSelectorSurface = IMG_Load("ASSETS/IMAGES/buttons/APurplePawButton.png");
	m_buttonSelectorTexture.push_back(SDL_CreateTextureFromSurface(m_renderer, m_buttonSelectorSurface));
	m_buttonSelectorTextureTwo.push_back(SDL_CreateTextureFromSurface(m_renderer, m_buttonSelectorSurface));


	for (int i = 0; i < MENU_NUM; i++)
	{
		m_buttonSelectorRect.push_back(SDL_Rect{ 10 ,(i*250),200,200 });
		m_buttonSelectorRectTwo.push_back(SDL_Rect{ 610 ,(i * 250),200,200 });

		m_menuButtonPositionSelected.push_back(SDL_Rect{ 210 ,(i * 250)+50,400,100 });
		m_menuButtonPosition.push_back(SDL_Rect{ 210 ,(i * 250)+50,400,100 });
	}
	
	m_titleRect = { 750 ,10,750, 750 };

	SDL_Surface* m_beeSurface = IMG_Load("ASSETS/IMAGES/bee.png");
	m_beeTexture = SDL_CreateTextureFromSurface(m_renderer, m_beeSurface);

	m_factory = new CharacterFactory;
	m_characters.push_back(m_factory->CreateBee());

	m_characters[0]->SetUp(100, 100, 90, 90, *m_beeTexture);



	audioPlaying = false;

	SDL_FreeSurface(m_backgroundSurface);
	SDL_FreeSurface(m_titleSurface);
	SDL_FreeSurface(m_menuButtonSurface);
	SDL_FreeSurface(m_buttonSelectorSurface);
	SDL_FreeSurface(m_beeSurface);

}

MenuScreen::~MenuScreen()
{
}

void MenuScreen::update()
{
	if (m_audioManager.isMusicPlaying() == 0)
	{
		if (!audioPlaying)
		{
			m_audioManager.PlayMusic("m_menu.wav", 2);
			audioPlaying = true;
		}
	}
	/*if (!audioPlaying)
	{
		SDL_LoadWAV("ASSETS/AUDIO/title.wav", &wavSpec, &wavBuffer, &wavLength);
		deviceId = SDL_OpenAudioDevice(NULL, 0, &wavSpec, NULL, 0);
		int success = SDL_QueueAudio(deviceId, wavBuffer, wavLength); 
		SDL_PauseAudioDevice(deviceId, 0);
		audioPlaying = true;
	}*/

	if (flip)
	{
		m_buttonSelectorRect[m_currentButton].w += 1;
		m_buttonSelectorRect[m_currentButton].h += 1;
		m_buttonSelectorRectTwo[m_currentButton].w += 1;
		m_buttonSelectorRectTwo[m_currentButton].h += 1;
		m_menuButtonPositionSelected[m_currentButton].w += 1;
		m_menuButtonPositionSelected[m_currentButton].h += 1;
		m_titleRect.h += 1;
		m_titleRect.w += 1;
		if (m_buttonSelectorRect[m_currentButton].w >= 450 || m_buttonSelectorRect[m_currentButton].h >= 250) { flip = false; }
	}
	else
	{
		m_buttonSelectorRect[m_currentButton].w -= 1;
		m_buttonSelectorRect[m_currentButton].h -= 1;
		m_buttonSelectorRectTwo[m_currentButton].w -= 1;
		m_buttonSelectorRectTwo[m_currentButton].h -= 1;
		m_menuButtonPositionSelected[m_currentButton].h -= 1;
		m_menuButtonPositionSelected[m_currentButton].w -= 1;
		m_titleRect.h -= 1;
		m_titleRect.w -= 1;
		if (m_buttonSelectorRect[m_currentButton].w >= 400 || m_buttonSelectorRect[m_currentButton].h <= 200) { flip = true; }
	}

		if (m_entity[0]->m_lastButtonPressed == 1)
		{
			m_audioManager.PlaySfx("f_button.wav", 100, 0, 1);
			m_entity[0]->setLastButton(NULL);
			setGameState();
		}

		if (m_entity[0]->IsAI == true)
		{
			m_entity[0]->setLastButton(NULL);
			setGameState();
		}

	
		if (m_entity[0]->m_lastButtonPressed == 3)
		{
			m_audioManager.PlaySfx("f_selector.wav", 20, 0, 1);
			m_entity[0]->setLastButton(NULL);
			m_currentButton++;
			if (m_currentButton >= 4) {m_currentButton = 0;}
		}
		
		if (m_entity[0]->m_lastButtonPressed == 2)
		{
			m_audioManager.PlaySfx("f_selector.wav", 20, 0, 1);
			m_entity[0]->setLastButton(NULL);
			m_currentButton--;
			if (m_currentButton <= -1) {m_currentButton = 3;}
		}
		
		m_characters[0]->Update();
}

void MenuScreen::render()
{
	SDL_RenderCopy(m_renderer, m_backgroundTexture, NULL, NULL);
	SDL_RenderCopyEx(m_renderer, m_titleTexture, NULL, &m_titleRect, 10, NULL, SDL_FLIP_NONE);

	
	for (int i = 0; i < MENU_NUM; i++)
	{
		if (i == m_currentButton)
		{
			SDL_RenderCopy(m_renderer, m_menuButtonTexture[i], NULL, &m_menuButtonPositionSelected[i]);
		}
		else
		{
			SDL_RenderCopy(m_renderer, m_menuButtonTexture[i], NULL, &m_menuButtonPosition[i]);
		}
	}

	SDL_RenderCopyEx(m_renderer, m_buttonSelectorTexture[m_currentButton], NULL, &m_buttonSelectorRect[m_currentButton], 90, NULL, SDL_FLIP_NONE);
	SDL_RenderCopyEx(m_renderer, m_buttonSelectorTextureTwo[m_currentButton], NULL, &m_buttonSelectorRectTwo[m_currentButton], 270, NULL, SDL_FLIP_NONE);


	m_characters[0]->Render(m_renderer);
}

void MenuScreen::processEvent()
{
	for (int i = 0; i < m_numberPlayers ; i++)
	{
		m_inputSystem.update(m_event, m_currentState, m_entity[i]);
	}
}

void MenuScreen::setGameState()
{

	switch (m_currentButton)
	{
	default:
		SDL_Delay(3000); 
		SDL_CloseAudioDevice(deviceId);
		SDL_FreeWAV(wavBuffer); 
		m_game.setGameState(GameState::Gameplay);
		std::cout << "error on Menu select" << std::endl;
		m_entity[0]->setLastButton(NULL);
		break;
	case 0:
		m_game.RestGameplay();
		m_game.setGameState(GameState::Gameplay);
		m_entity[0]->setLastButton(NULL);
		break;
	case 1:
		m_game.connecToServer();
		m_game.setGameState(GameState::Online);
		m_entity[0]->setLastButton(NULL);
		break;
	case 2:
		SDL_Delay(3000);
		SDL_CloseAudioDevice(deviceId);
		SDL_FreeWAV(wavBuffer);
		m_game.setGameState(GameState::Credit);
		m_entity[0]->setLastButton(NULL);
		break;
	case 3:
		SDL_Delay(3000);
		SDL_CloseAudioDevice(deviceId);
		SDL_FreeWAV(wavBuffer);
		m_game.setGameState(GameState::Quit);
		m_entity[0]->setLastButton(NULL);
		break;
	}
}
