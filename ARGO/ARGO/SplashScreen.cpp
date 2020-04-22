#include "SplashScreen.h"

SplashScreen::SplashScreen(Game& game, SDL_Renderer* t_renderer, SDL_Event& event, GameState& t_currentState, InputSystem& t_inputSystem, std::vector<Player*> t_entity, AudioManager& t_audioManager):
	m_game(game),
	m_event(event),
	m_renderer(t_renderer),
	m_inputSystem(t_inputSystem),
	m_currentState(t_currentState),
	m_entity(t_entity),
	m_audioManager(t_audioManager)
{
	m_numberPlayers = m_entity.size();
	SDL_Surface* m_titleSurface = IMG_Load("ASSETS/IMAGES/titleScreen.png");
	m_splashTexture = SDL_CreateTextureFromSurface(m_renderer, m_titleSurface);
	SDL_FreeSurface(m_titleSurface);


	SDL_Surface* m_buttonSelectorSurface;
	m_buttonSelectorSurface = IMG_Load("ASSETS/IMAGES/buttons/ABluePawButton.png");
	m_buttonSelectorTexture = (SDL_CreateTextureFromSurface(m_renderer, m_buttonSelectorSurface));
	SDL_FreeSurface(m_buttonSelectorSurface);

	SDL_DisplayMode DM;
	SDL_GetCurrentDisplayMode(0, &DM);
	int Width = DM.w;
	int Height = DM.h;

	m_buttonSelectorRect= { static_cast<int>(round( Width*0.45f)) , static_cast<int>(round(Height*0.70f)),static_cast<int>(Width/9.6),static_cast<int>(Height/5.4)};
	m_titleRect = { 0,0, Width,Height};

}

SplashScreen::~SplashScreen()
{

}

void SplashScreen::update()
{
	if (m_audioManager.isMusicPlaying() == 0)
	{
		m_audioManager.PlayMusic("m_menu.wav", 2);
		m_audioManager.PlaySfx("s_gameTitle.wav", 100, 0, 1);
	}


	if (flip)
	{
		m_buttonSelectorRect.w += 1;
		m_buttonSelectorRect.h += 1;

		if (m_buttonSelectorRect.w >= 450 || m_buttonSelectorRect.h >= 250) { flip = false; }
	}
	else
	{
		m_buttonSelectorRect.w -= 1;
		m_buttonSelectorRect.h -= 1;
		if (m_buttonSelectorRect.w >= 400 || m_buttonSelectorRect.h <= 200) { flip = true; }
	}



	if (m_entity[0]->m_lastButtonPressed == 1)
	{
		//buton push sound here
		
		m_audioManager.PlaySfx("f_button.wav", 80, 0, 1);

		m_entity[0]->setLastButton(NULL);
		setGameState();
	}

	if (m_entity[0]->IsAI == true)
	{
		m_entity[0]->setLastButton(NULL);
		setGameState();
	}
}

void SplashScreen::render()
{
	SDL_RenderCopy(m_renderer, m_splashTexture, NULL, NULL);
	SDL_RenderCopyEx(m_renderer, m_buttonSelectorTexture, NULL, &m_buttonSelectorRect, 0, NULL, SDL_FLIP_NONE);

}

void SplashScreen::processEvent()
{
	for (int i = 0; i < m_numberPlayers; i++)
	{
		m_inputSystem.update(m_event, m_currentState, m_entity[i]);
	}
}

void SplashScreen::setGameState()
{
	m_game.setGameState(GameState::Menu);
}
