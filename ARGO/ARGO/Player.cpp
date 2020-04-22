#include "Player.h"

Player::Player(int entityIdNum) :
	Entity(entityIdNum)
{


	SDL_DisplayMode DM;
	SDL_GetCurrentDisplayMode(0, &DM);
	auto Width = DM.w;
	auto Height = DM.h;

	m_width = Width;
	m_height = Height;

	SetUp();
}

Player::~Player()
{
}

void Player::assignSprite(SDL_Texture* t_PlayerTexture)
{
	m_PlayerTexture = t_PlayerTexture;
}

void Player::SetUp()
{
	rect.x = static_cast<int>(m_width / 2.01);
	rect.y = static_cast<int>(m_height / 1.13);
	rect.w = static_cast<int>(m_width / 96);
	rect.h = static_cast<int>(m_height / 54);

	m_spriteBody.x = 0;
	m_spriteBody.y = 0;
	m_spriteBody.w = static_cast<int>(m_width / 48);
	m_spriteBody.h = static_cast<int>(m_height / 21.6);
}

void Player::update(MovementSystem & t_move)
{
	m_spriteBody.x = rect.x - static_cast<int>(m_width / 384);
	m_spriteBody.y = rect.y - static_cast<int>(m_height / 54);

	m_takingTurn = t_move.IsThePlayerMoving(this->getEntity()->getId());
	/*if (m_takingTurn)
	{
		tileBehaviour();
	}*/
}

void Player::render(SDL_Renderer* t_renderer, int t_rotation)
{

	SDL_SetRenderDrawColor(t_renderer, 0, 155, 255, 255);
	SDL_RenderCopyEx(t_renderer, m_PlayerTexture, NULL, &m_spriteBody, t_rotation, NULL, SDL_FLIP_NONE);
	SDL_SetRenderDrawColor(t_renderer, 0, 0, 0, 255);
}

void Player::setPosition(float t_x, float t_y)
{
	rect.x = t_x;
	rect.y = t_y;
}

void Player::setPositionOnline(int m_x, int m_y)
{

	rect.x = m_x;
	rect.y = m_y;

}

void Player::resetIndex()
{
	currentIndex = 0;
}

void Player::updateOnline()
{
	m_spriteBody.x = rect.x - static_cast<int>(m_width / 384);
	m_spriteBody.y = rect.y - static_cast<int>(m_height / 54);
}

std::string Player::GetPosAsString()
{
	return std::string("X: " + std::to_string(rect.x) + ", " + "Y: " + std::to_string(rect.y));
}
void Player::setTileType(int t_type, int t_index)
{
	tileType = t_type;
	currentIndex = t_index;
}

SDL_Rect * Player::getPlayerRectRef()
{
	return & rect;
}

std::string Player::GetValueAsString()
{
	return std::string(std::to_string(diceRoll));
}
void Player::tileBehaviour()
{
	switch (tileType)
	{
	case 1:
		SDL_Delay(500);
		std::cout << "good square" << std::endl;
		break;
	case 2:
		switch (currentIndex)
		{
		case 32:
			SDL_Delay(500);
			std::cout << "story 1" << std::endl;
			break;
		case 62:
			SDL_Delay(500);
			std::cout << "story 2" << std::endl;
			break;
		case 104:
			SDL_Delay(500);
			std::cout << "story 3" << std::endl;
			break;
		case 125:
			SDL_Delay(500);
			std::cout << "story 4" << std::endl;
			break;
		default:
			break;
		}
		break;
	case 3:
		SDL_Delay(500);
		std::cout << "bounce square" << std::endl;
		break;
	case 4:
		SDL_Delay(500);
		std::cout << "dice square" << std::endl;
		break;
	case 5:
		SDL_Delay(500);
		std::cout << "honey puddle square" << std::endl;
		stuck = true;
		break;
	case 6:
		SDL_Delay(500);
		std::cout << "tumble square" << std::endl;
		break;
	default:
		break;
	}
}
