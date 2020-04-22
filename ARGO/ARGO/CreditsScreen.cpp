#include "CreditsScreen.h"

CreditScreen::CreditScreen(Game& game, SDL_Renderer* t_renderer, SDL_Event& event, GameState& t_currentState, InputSystem& t_inputSystem, std::vector<Player*> t_entity) :
	m_game(game),
	m_event(event),
	m_renderer(t_renderer),
	m_inputSystem(t_inputSystem),
	m_currentState(t_currentState),
	m_entity(t_entity)
{
	m_numberPlayers = m_entity.size();

	SDL_Surface* tempSerface = IMG_Load("ASSETS/IMAGES/pic3.png");
	m_TestingTexture = SDL_CreateTextureFromSurface(m_renderer, tempSerface);
	SDL_FreeSurface(tempSerface);

	
}

CreditScreen::~CreditScreen()
{
}

void CreditScreen::update()
{
	
	if (m_entity[0]->m_lastButtonPressed == 4)
	{
		m_entity[0]->setLastButton(NULL);
		SDL_Delay(200);
		setGameState();
	}
}

void CreditScreen::render()
{	
	//SDL_RenderClear(m_renderer);
	SDL_RenderCopy(m_renderer, m_TestingTexture, NULL, NULL);
}

void CreditScreen::processEvent()
{
	for (int i = 0; i < m_numberPlayers ;i++)
	{
		m_inputSystem.update(m_event, m_currentState, m_entity[i]);
	}
}

void CreditScreen::setGameState()
{
	m_game.setGameState(GameState::Menu);
}
