#include "OnlineMode.h"

OnlineMode::OnlineMode(Game& game, SDL_Renderer* t_renderer, SDL_Event& event, GameState& t_currentState, InputSystem& t_inputSystem, std::vector<Player*> t_entity) :
	m_game(game),
	m_event(event),
	m_renderer(t_renderer),
	m_inputSystem(t_inputSystem),
	m_currentState(t_currentState),
	m_entity(t_entity)
{
	m_numberPlayers = m_entity.size();

	
	SDL_Surface* tempSerface = IMG_Load("ASSETS/IMAGES/pic1.png");
	m_TestingTexture = SDL_CreateTextureFromSurface(m_renderer, tempSerface);
	SDL_FreeSurface(tempSerface);

}

OnlineMode::~OnlineMode()
{
}


void OnlineMode::update()
{
	x = numFromString(m_client->getOtherPos()).at(0);
	y = numFromString(m_client->getOtherPos()).at(1);

	m_myX += 2;
	m_myY += 1;


	m_entity[1]->setPositionOnline(x, y);
	m_entity[0]->setPositionOnline(m_myX, m_myY);


	m_entity[0]->updateOnline();
	m_entity[1]->updateOnline();


	m_client->SendString(m_entity[0]->GetPosAsString());

	if (m_entity[0]->m_lastButtonPressed == 4)
	{
		m_entity[0]->setLastButton(NULL);
		SDL_Delay(200);
		setGameState();
	}
}

void OnlineMode::render()
{
	SDL_RenderClear(m_renderer);
	SDL_RenderCopy(m_renderer, m_TestingTexture, NULL, NULL);

	m_entity[0]->render(m_renderer,0);
	m_entity[1]->render(m_renderer,0);
}

void OnlineMode::processEvent()
{
	for (int i = 0; i < m_numberPlayers ;i++)
	{
		m_inputSystem.update(m_event, m_currentState, m_entity[i]);
	}
	
}

void OnlineMode::setGameState()
{
	m_game.setGameState(GameState::Menu);
}

void OnlineMode::ConnectToServer()
{

	m_client = new Client("149.153.106.157", 1111, m_entity);

	if (!m_client->Connect()) //If client fails to connect...
	{
		std::cout << "Failed to connect to server..." << std::endl;

	}
}
