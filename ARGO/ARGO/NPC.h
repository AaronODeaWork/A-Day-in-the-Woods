#ifndef NPC_H
#define NPC_H


#include "SDL.h"

#include <cstdlib>
#include <ctime>
#include <vector>
#include "Tile.h"
#include "iostream"
#include "Graph.h"
#include "Entity.h"

class Tile;
typedef GraphArc<pair<std::string, int>, int> Arcs;
typedef GraphNode<pair<std::string, int>, int> Node;

class NPC : public Entity
{
public:
	NPC(std::vector<Tile>& t_map, Graph< pair<string, int>, int>& t_g, int t_aiBehaviour);
	~NPC();
	void update();
	void render(SDL_Renderer* t_renderer);
	void setPosition(float t_x, float t_y);
	void navigateNodes();
	void nodeChange(std::list<GraphArc<pair<std::string, int>, int>> newPoint);
	void rollDice();

	void addItem();
	void removeItem();

	int currentGameBoardIndex;
	int previousIndex;
	int m_diceNumber;
	int items;
	bool turn;
	bool stuck;
	bool end;
private:
	void updateTile();
	void tileBehaviour();
	std::vector<Tile>& m_map;
	Graph< pair<string, int>, int>& m_graph;
	int m_aiBehaviour;
	SDL_Rect npc;
	int m_pathDecision;
};

#endif // !NPC_H