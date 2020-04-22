#include "NPC.h"

NPC::NPC(std::vector<Tile>& t_map, Graph<pair<string, int>, int>& t_g, int t_aiBehaviour) :
	m_map(t_map),
	m_graph(t_g),
	m_aiBehaviour(t_aiBehaviour),
	turn(false),
	end(false),
	stuck(false),
	Entity(2)
{
	srand((unsigned)time(0));

	npc.x = 0;
	npc.y = 0;
	npc.h = 20;
	npc.w = 20;
	items = 5;
}

NPC::~NPC()
{
}

void NPC::update()
{
	SDL_Delay(500);
	rollDice();
	navigateNodes();
	updateTile();
	setPosition(m_map[currentGameBoardIndex].getPosition().x, m_map[currentGameBoardIndex].getPosition().y);
}

void NPC::render(SDL_Renderer* t_renderer)
{
	if (m_aiBehaviour == 1)
	{
		SDL_SetRenderDrawColor(t_renderer, 211, 15, 0, 255);
		SDL_RenderFillRect(t_renderer, &npc);
		SDL_SetRenderDrawColor(t_renderer, 0, 0, 0, 255);
	}
	else if (m_aiBehaviour == 2)
	{
		SDL_SetRenderDrawColor(t_renderer, 245, 207, 54, 255);
		SDL_RenderFillRect(t_renderer, &npc);
		SDL_SetRenderDrawColor(t_renderer, 0, 0, 0, 255);
	}
	else
	{
		SDL_SetRenderDrawColor(t_renderer, 88, 168, 50, 255);
		SDL_RenderFillRect(t_renderer, &npc);
		SDL_SetRenderDrawColor(t_renderer, 0, 0, 0, 255);
	}
}

void NPC::setPosition(float t_x, float t_y)
{
	npc.x = t_x;
	npc.y = t_y;
}

void NPC::navigateNodes()
{
	int temp = 1;
	m_pathDecision = (rand() % 2) + 1;
		
	for (int x = 0; x < 1; x++)
	{

		std::list<GraphArc<std::pair<std::string, int>, int>> p;

		p = m_graph.nodeIndex(currentGameBoardIndex)->arcList();


		if (p.size() > 1)
		{ // direction choice
			bool ChoicMade = false;
			bool choice = false;

			/*while (!ChoicMade)
			{
				SDL_Event(event);
				SDL_PollEvent(&event);

				if (SDLK_a == event.key.keysym.sym)
				{
					choice = false;
					ChoicMade = !ChoicMade;
				}
				if (SDLK_s == event.key.keysym.sym)
				{
					choice = true;
					ChoicMade = !ChoicMade;
				}
			}*/

			if (m_aiBehaviour == 2 || (m_aiBehaviour >= 3 && m_pathDecision == 2))
			{
				//----------------------------Point 1 ------------------------------------------
				if (p.front().node()->m_x == m_graph.nodeIndex(currentGameBoardIndex)->m_x &&
					p.front().node()->m_y > m_graph.nodeIndex(currentGameBoardIndex)->m_y)
				{	// p1 Down
					nodeChange(p);
				}

				if (p.front().node()->m_x == m_graph.nodeIndex(currentGameBoardIndex)->m_x &&
					p.front().node()->m_y < m_graph.nodeIndex(currentGameBoardIndex)->m_y)
				{	// p1 Up
					nodeChange(p);
				}

				if (p.front().node()->m_x > m_graph.nodeIndex(currentGameBoardIndex)->m_x &&
					p.front().node()->m_y == m_graph.nodeIndex(currentGameBoardIndex)->m_y)
				{	//p1 Right
					nodeChange(p);
				}

				if (p.front().node()->m_x < m_graph.nodeIndex(currentGameBoardIndex)->m_x &&
					p.front().node()->m_y == m_graph.nodeIndex(currentGameBoardIndex)->m_y)
				{	//p1 Left
					nodeChange(p);
				}
			}
			else if(m_aiBehaviour == 1 || (m_aiBehaviour >= 3 && m_pathDecision == 1))
			{
				p.reverse();

				//----------------------------Point 2 ------------------------------------------
				if (p.front().node()->m_x == m_graph.nodeIndex(currentGameBoardIndex)->m_x &&
					p.front().node()->m_y > m_graph.nodeIndex(currentGameBoardIndex)->m_y)
				{	// p2 Down
					nodeChange(p);
				}

				if (p.front().node()->m_x == m_graph.nodeIndex(currentGameBoardIndex)->m_x &&
					p.front().node()->m_y < m_graph.nodeIndex(currentGameBoardIndex)->m_y)
				{	// p2 Up
					nodeChange(p);
				}

				if (p.front().node()->m_x > m_graph.nodeIndex(currentGameBoardIndex)->m_x &&
					p.front().node()->m_y == m_graph.nodeIndex(currentGameBoardIndex)->m_y)
				{	//p2 Right
					nodeChange(p);
				}

				if (p.front().node()->m_x < m_graph.nodeIndex(currentGameBoardIndex)->m_x &&
					p.front().node()->m_y == m_graph.nodeIndex(currentGameBoardIndex)->m_y)
				{	//p2 Left
					nodeChange(p);
				}

				if (p.front().node()->m_x > m_graph.nodeIndex(currentGameBoardIndex)->m_x &&
					p.front().node()->m_y > m_graph.nodeIndex(currentGameBoardIndex)->m_y)
				{	//p2 Left
					nodeChange(p);
				}
			}
		}
		else
		{ // only one way to go
			nodeChange(p);
		}
		m_diceNumber -= 1;
	}
}

void NPC::nodeChange(std::list<GraphArc<pair<std::string, int>, int>> newPoint)
{
	for (int i = 0; i < m_map.size(); i++)
	{
		if (newPoint.front().node()->m_x == m_graph.nodeIndex(i)->m_x &&
			newPoint.front().node()->m_y == m_graph.nodeIndex(i)->m_y)
		{
			// this is then the next tile index to go to

			std::cout << "prev: " << previousIndex << std::endl;
			previousIndex = currentGameBoardIndex;
			currentGameBoardIndex = i;
			std::cout << "curr: " << currentGameBoardIndex << std::endl;
			//setPosition(m_map[CurrentGameBoardIndex].getPosition().x - (rect.w / 4.0f), m_map[CurrentGameBoardIndex].getPosition().y - (rect.h / 4.0f));
		}
	}
}

void NPC::rollDice()
{
	if (m_diceNumber <= 0)
	{
		m_diceNumber = (rand() % 6) + 1;
	}
}

void NPC::addItem()
{
	items += 1;
}

void NPC::removeItem()
{
	items -= 1;
}


void NPC::updateTile()
{
	if (!stuck && m_diceNumber == 0)
	{
		if (m_map[currentGameBoardIndex].count == 0)
		{
			std::cout << "npc " << m_aiBehaviour << " tile" << std::endl;
			m_map[currentGameBoardIndex].update();
			tileBehaviour();
			SDL_Delay(500);
		}

		m_map[currentGameBoardIndex].count++;

		if (!stuck)
		{
			m_map[currentGameBoardIndex].count = 0;
		}
				 
		if (end)
		{
			turn = false;
		}
	}
	if (stuck && m_map[currentGameBoardIndex].count == 2)
	{
		stuck = false;
	}
}

void NPC::tileBehaviour()
{
	switch (m_map[currentGameBoardIndex].getType())
	{
	case 1:
		SDL_Delay(500);
		std::cout << "good square" << std::endl;
		end = true;
		break;
	case 2:
		switch (currentGameBoardIndex)
		{
		case 32:
			SDL_Delay(500);
			std::cout << "story 1" << std::endl;
			end = true;
			break;
		case 62:
			SDL_Delay(500);
			std::cout << "story 2" << std::endl;
			end = true;
			break;
		case 104:
			SDL_Delay(500);
			std::cout << "story 3" << std::endl;
			end = true;
			break;
		case 125:
			SDL_Delay(500);
			std::cout << "story 4" << std::endl;
			end = true;
			break;
		default:
			break;
		}
		break;
	case 3:
		SDL_Delay(500);
		std::cout << "bounce square" << std::endl;
		navigateNodes();
		end = true;
		break;
	case 4:
		SDL_Delay(500);
		std::cout << "dice square" << std::endl;
		update();
		break;
	case 5:
		SDL_Delay(500);
		std::cout << "honey puddle square" << std::endl;
		stuck = true;
		end = true;
		break;
	case 6:
		SDL_Delay(500);
		std::cout << "tumble square" << std::endl;
		currentGameBoardIndex = previousIndex;
		std::cout << "tumble curr: " << currentGameBoardIndex << std::endl;
		setPosition(m_map[currentGameBoardIndex].getPosition().x, m_map[currentGameBoardIndex].getPosition().y);
		end = true;
		break;
	default:
		break;
	}
}
