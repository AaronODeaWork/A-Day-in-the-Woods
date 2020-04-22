#ifndef MOVEMENTCOMPONENT_H
#define MOVEMENTCOMPONENT_H


#include "Component.h"
#include <vector>
#include "Tile.h"
#include "iostream"
#include "Graph.h"
#include <random>
#include <SDL.h>
#include "AudioManager.h"


class MovementComponent : public Component
{

public:
	AudioManager* m_audioManager;

	SDL_AudioSpec wavSpec;
	Uint32 wavLength;
	Uint8* wavBuffer;
	SDL_AudioDeviceID deviceId;
	int success;

	MovementComponent() : Component(ComponentType::MOVEMENT)
	{


		SDL_DisplayMode DM;
		SDL_GetCurrentDisplayMode(0, &DM);
		auto Width = DM.w;
		auto Height = DM.h;

		m_width = Width;
		m_height = Height;

		setUp();
	}

	~MovementComponent()
	{
		AudioManager::Release();
		m_audioManager = NULL;
	}

	/// <summary>
	/// Set the body that will be moved
	/// </summary>
	/// <param name="t_rect"></param>
	void setRect(SDL_Rect & t_rect) {
		rect = &t_rect;
	}
	void setAiCheck(bool &t_IsAi) {
		m_IsAi = &t_IsAi;
	}
	void setChoiceBools(bool& t_upBool, bool& t_downBool, bool& t_leftBool, bool& t_rightBool) {

		m_upChoiceBool = &t_upBool;
		m_downChoiceBool = &t_downBool;
		m_rightChoiceBool = &t_rightBool;
		m_leftChoiceBool = &t_leftBool;
		
	}


	int randomNumber(int t_max, int t_min)
	{
		std::random_device device;
		std::mt19937 rng(device());
		std::uniform_int_distribution<std::mt19937::result_type> dist(t_min, t_max);
		return dist(rng);
	}

	void setUp(){
		
		m_audioManager = AudioManager::Instance();
		//
		//SDL_PauseAudioDevice(deviceId, 0);
		CurrentGameBoardIndex = 0;
		m_movementSpeed = -1;
		m_takeingTurn = false;
		choiceLoop = true;

	}
	void reSetUp() {
		CurrentGameBoardIndex = 0;
		m_movementSpeed = -1;
		m_takeingTurn = false;
		choiceLoop = true;
		m_newGame = true;
		rect->x = static_cast<int>(m_width / 2.01);
		rect->y = static_cast<int>(m_height / 1.13);
	}
	void update(std::vector<Tile>& t_map, Graph< pair<string, int>, int>& t_g) {
		if (m_newGame == true)
		{
			rect->x = t_map[CurrentGameBoardIndex].getPosition().x - (rect->w / 4.0f);
			rect->y = t_map[CurrentGameBoardIndex].getPosition().y - (rect->h / 4.0f);
			m_newGame = false;
		}


		if (m_takeingTurn)
		{
			nodeNavigation(t_map, t_g);
		}
		else
		{
			rect->x = t_map[CurrentGameBoardIndex].getPosition().x - (rect->w / 4.0f);
			rect->y	= t_map[CurrentGameBoardIndex].getPosition().y - (rect->h / 4.0f);
		}
	}

	void nodeNavigation(std::vector<Tile>& t_map, Graph< pair<string, int>, int>& t_g) {
		if (m_diceRoll > 0)
		{
			*m_downChoiceBool = false;
			*m_upChoiceBool = false;
			*m_rightChoiceBool = false;
			*m_leftChoiceBool = false;

			std::list<GraphArc<std::pair<std::string, int>, int>> p;

			p = t_g.nodeIndex(CurrentGameBoardIndex)->arcList();

			SDL_Event(event);
			SDL_PollEvent(&event);

				if (*m_IsAi == false)
			{
				nodeDirectionCheckIndicator(
					p.front().node()->m_x,
					p.front().node()->m_y,
					t_g.nodeIndex(CurrentGameBoardIndex)->m_x,
					t_g.nodeIndex(CurrentGameBoardIndex)->m_y);
				p.reverse();
				nodeDirectionCheckIndicator(
					p.front().node()->m_x,
					p.front().node()->m_y,
					t_g.nodeIndex(CurrentGameBoardIndex)->m_x,
					t_g.nodeIndex(CurrentGameBoardIndex)->m_y);
			}

			if (p.size() > 1)
			{ // direction choice

				if (*m_IsAi == true && choiceLoop ==true && m_randomDirectionDecided == false)
				{
					m_currentDiceRoll = p.size()-1;
					m_DirectionChoiceNum = randomNumber(6,1);
					choiceLoop = false;
				}
				else if (m_currentDiceRoll != p.size() || m_currentDiceRoll == -1)
				{
					m_randomDirectionDecided = false;
				}
			

				if (!choiceLoop)
				{
	
					//here is where there is a multiple choice 

					if (m_DirectionChoiceNum == nodeDirectionCheck(
						p.front().node()->m_x,
						p.front().node()->m_y,
						t_g.nodeIndex(CurrentGameBoardIndex)->m_x,
						t_g.nodeIndex(CurrentGameBoardIndex)->m_y))
					{
						playerNodeChange(p, t_map, t_g);

						if (*m_IsAi == true)
						{
							m_randomDirectionDecided = true;
						}
					}
					else
					{
						p.reverse();
						if (m_DirectionChoiceNum == nodeDirectionCheck(
							p.front().node()->m_x,
							p.front().node()->m_y,
							t_g.nodeIndex(CurrentGameBoardIndex)->m_x,
							t_g.nodeIndex(CurrentGameBoardIndex)->m_y))
						{
							playerNodeChange(p, t_map, t_g);

							if (*m_IsAi == true)
							{
								m_randomDirectionDecided = true;
							}
						}
					}
					if (!m_randomDirectionDecided)
					{
						if (*m_IsAi == true)
						{
							m_DirectionChoiceNum = randomNumber(6, 1);
						}
					}
			
				}
	
			}
			else
			{ // only one way to go			
				playerNodeChange(p, t_map, t_g);								
				*m_downChoiceBool = false;
				*m_upChoiceBool = false;
				*m_rightChoiceBool = false;
				*m_leftChoiceBool = false;

			}
		}
		else
		{
			if (MoveForward)
			{
				if (!m_audioManager->IsChannelPLaying(1))
				{
					if (IndexPlaceHolder == CurrentGameBoardIndex)
					{
						std::list<GraphArc<std::pair<std::string, int>, int>> p;
						p = t_g.nodeIndex(CurrentGameBoardIndex)->arcList();
						playerNodeChange(p, t_map, t_g);
					}
					else
					{
						m_diceRoll = -1;
						choiceLoop = false;
						m_takeingTurn = false;
						MoveForward = false;
						m_randomDirectionDecided = false;
						m_currentDiceRoll = -1;

						m_moveForwardAudio = false;
					}
				}	
			}

			if (MoveBack)
			{
				if (!m_audioManager->IsChannelPLaying(1))
				{
					if (animateMovingToPoint(t_map[PriorGameBoardIndex].getPosition().x - (rect->w / 4.0f), t_map[PriorGameBoardIndex].getPosition().y - (rect->h / 4.0f)))
					{
						int tempIndex = CurrentGameBoardIndex;
						CurrentGameBoardIndex = PriorGameBoardIndex;
						PriorGameBoardIndex = tempIndex;

						m_diceRoll = -1;
						choiceLoop = false;
						m_takeingTurn = false;

						m_randomDirectionDecided = false;
						m_currentDiceRoll = -1;

						MoveBack = false;

						m_moveBackAudio = false;
						m_moveForwardAudio = false;
					}
				}
				
			}

			if (m_takeingTurn)
			{
				switch (tileBehaviour(t_map))
				{
				case 0: // Basic Tile
					m_takeingTurn = false;
					m_diceRoll = -1;
					choiceLoop = false; 
					m_randomDirectionDecided = false;
					m_currentDiceRoll = -1;
					m_moveForwardAudio = false;
					break;
				case 10://pt1
					
					m_audioManager->PlaySfx("w_pt1.wav", 100, 0, 1);

					m_takeingTurn = false;
					m_diceRoll = -1;
					choiceLoop = false;
					m_randomDirectionDecided = false;
					m_currentDiceRoll = -1;
					m_moveForwardAudio = false;
					break;
				case 11://pt2
					
					m_audioManager->PlaySfx("w_pt2.wav", 100, 0, 1);

					m_takeingTurn = false;
					m_diceRoll = -1;
					choiceLoop = false;
					m_randomDirectionDecided = false;
					m_currentDiceRoll = -1;
					m_moveForwardAudio = false;
					break;
				case 12://pt3

					m_audioManager->PlaySfx("w_pt3.wav", 100, 0, 1);

					m_takeingTurn = false;
					m_diceRoll = -1;
					choiceLoop = false;
					m_randomDirectionDecided = false;
					m_currentDiceRoll = -1;
					m_moveForwardAudio = false;
					break;
				case 13://pt4
					
					m_audioManager->PlaySfx("w_pt4.wav", 100, 0, 1);

					m_takeingTurn = false;
					m_diceRoll = -1;
					m_randomDirectionDecided = false;
					m_currentDiceRoll = -1;
					choiceLoop = false;
					m_moveForwardAudio = false;
					break;
				case 2://bounce - forward 1
					
					if (!m_moveForwardAudio)
					{
						m_audioManager->PlaySfx("t_forward.wav", 100, 0, 1);
						m_moveForwardAudio = true;
					}

					if (!m_audioManager->IsChannelPLaying(1))
					{
						m_diceRoll = 1;
					}
				
					break;
				case 3://dice - add TURN

					m_audioManager->PlaySfx("t_add.wav", 100, 0, 1);

					m_takeingTurn = false;
					m_diceRoll = -2;
					choiceLoop = false;
					m_randomDirectionDecided = false;
					m_currentDiceRoll = -1;
					m_moveForwardAudio = false;
					break;
				case 4://honey - lose turn

					m_audioManager->PlaySfx("t_miss.wav", 100,0,1);

					m_takeingTurn = false;
					m_diceRoll = -3;
					choiceLoop = false;
					m_randomDirectionDecided = false;
					m_currentDiceRoll = -1;
					m_moveForwardAudio = false;
					break;
				case 5:// tumble - back 1
					if (!m_moveBackAudio)
					{
						m_audioManager->PlaySfx("t_back.wav", 100, 0, 1);
						m_moveBackAudio = true;
					}

		

					MoveBack = true;
					//m_takeingTurn = false;
					break;
				}
			}
		}
	}

	void playerNodeChange(std::list<GraphArc<std::pair<std::string, int>, int>>& newPoint, 
							std::vector<Tile>& t_map,
							Graph< pair<string, int>, int>& t_g) {
		for (int i = 0; i < t_map.size(); i++)
		{
			if (CurrentGameBoardIndex == 41)
			{
				std::cout << "Game Won " << std::endl;
				gameWin = true;

				m_audioManager->PlaySfx("s_ending.wav", 75, 0, 1);
			}
			
			if (gameWin)
			{
				break;
			}

			if (newPoint.front().node()->m_x == t_g.nodeIndex(i)->m_x &&
				newPoint.front().node()->m_y == t_g.nodeIndex(i)->m_y)
			{
				// this is then the next tile index to go to

				if (animateMovingToPoint(t_map[i].getPosition().x - (rect->w / 4.0f), t_map[i].getPosition().y - (rect->h / 4.0f)))
				{
					PriorGameBoardIndex = CurrentGameBoardIndex;
					CurrentGameBoardIndex = i;
					m_diceRoll--;
					m_randomDirectionDecided = false;
					choiceLoop = true;
					// direction check here;
				}				
			}			
		}		
	}

	float getPosY()
	{
		return rect->y;
	}


	bool getEndGame()
	{
		return gameWin;
	}

	void resetEndGame()
	{
		gameWin = false;
	}	

	void rollForMove(int t_diceRolled) {

		if (!m_takeingTurn)
		{
			m_diceRoll = t_diceRolled;
			m_takeingTurn = true;
			//m_finishedTurn = false;
		}
	}

	bool animateMovingToPoint(float t_DestX, float t_DestY) {
		float tempX = rect->x - t_DestX;
		float tempY = rect->y - t_DestY;

		if (rect->x == t_DestX && rect->y == t_DestY)
			return true;

		normalize(tempX, tempY);

		rect->x += (tempX * m_movementSpeed);
		rect->y += (tempY * m_movementSpeed);

		return false;
	}

	void normalize(float& t_x, float& t_y) {
		float len = sqrt(t_x * t_x + t_y * t_y);

		t_x /= len;
		t_y /= len;
	}

	void leftOrRightChoice(bool t_choice) {
		LeftOrRight = t_choice;
		choiceLoop = false;
	}

	void directionChoice(int t_choice) {
		m_DirectionChoiceNum = t_choice;
		choiceLoop = false;
	}

	bool getTakeingTurn(){
		return m_takeingTurn;
	}

	int getDiceValue()
	{
		return m_diceRoll;
	}

	void setDiceValue(int i)
	{
		m_diceRoll = i;
	}

	int nodeDirectionCheck(int x1, int y1, int x2, int y2)
	{		
		if (x1 == x2 && y1 > y2)
		{	// p2 Down
			return 1;
		}
		else if (x1 == x2 && y1 < y2)
		{	// p2 Up
			return 6;
		}
		else if (x1 > x2&& y1 == y2)
		{	// p2 Right
			return 4;
		}
		else if (x1 < x2 && y1 == y2)
		{	// p2 Left
			return 5;
		}

		return -1;
	}

	void nodeDirectionCheckIndicator(int x1, int y1, int x2, int y2)
	{
		if (x1 == x2 && y1 > y2){	// p2 Down
		*m_downChoiceBool = true;}
		else if (x1 == x2 && y1 < y2){	// p2 Up
		*m_upChoiceBool = true;	}
		else if (x1 > x2&& y1 == y2){	// p2 Right
		*m_rightChoiceBool = true;}
		else if (x1 < x2 && y1 == y2){	// p2 Left
		*m_leftChoiceBool = true;}
	}

	int getCurrentIndex()
	{
		return CurrentGameBoardIndex;
	}

	int tileBehaviour(std::vector<Tile>& t_map)
	{
		switch (t_map[CurrentGameBoardIndex].getType())
		{
		case 1:
			//SDL_Delay(500);
			std::cout << "good square" << std::endl;
			return 0;
			break;
		case 2:
			switch (CurrentGameBoardIndex)
			{
			case 32:
				//SDL_Delay(500);
				std::cout << "story 1" << std::endl;
				return 10;
				break;
			case 62:
				//SDL_Delay(500);
				std::cout << "story 2" << std::endl;
				return 11;
				break;
			case 104:
				//SDL_Delay(500);
				std::cout << "story 3" << std::endl;
				return 12;
				break;
			case 125:
				//SDL_Delay(500);
				std::cout << "story 4" << std::endl;
				return 13;
				break;
			default:
				break;
			}
			break;
		case 3:
			//SDL_Delay(500);
			std::cout << "bounce square" << std::endl;
			return 2;
			break;
		case 4:
			//SDL_Delay(500);
			std::cout << "dice square" << std::endl;
			return 3;
			break;
		case 5:
			//SDL_Delay(500);
			std::cout << "honey puddle square" << std::endl;
			return 4;
			break;
		case 6:
			//SDL_Delay(500);
			std::cout << "tumble square" << std::endl;
			return 5;
			break;
		default:
			break;
		}
	}

private:
	//Real one
	int CurrentGameBoardIndex;
	int PriorGameBoardIndex;

	bool MoveForward = false;
	bool MoveBack = false;
	int IndexPlaceHolder;

	SDL_Rect * rect;
	bool * m_IsAi;

	bool m_randomDirectionDecided{false};
	bool choiceLoop;

	bool LeftOrRight = false;
	bool useTile = false;
	int m_currentDiceRoll{ -1 };

	bool m_moveBackAudio = false;
	bool m_moveForwardAudio = false;

	bool gameWin = false;
	int playerWon;

	bool m_takeingTurn;
	bool m_newGame{ false };


	bool* m_leftChoiceBool{false};
	bool* m_rightChoiceBool{ false };
	bool* m_upChoiceBool{ false };
	bool* m_downChoiceBool{ false };


	int m_width;
	int m_height;

	float m_movementSpeed;

	int m_diceRoll{-1};

	int m_DirectionChoiceNum = -1;
	//int * m_turnIndex;
};
#endif // !MOVEMENTCOMPONENT_H
	

