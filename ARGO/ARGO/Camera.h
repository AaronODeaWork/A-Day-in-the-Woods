#pragma once



// Basic Camera Class using a SDL_Rect
class Camera {
private:
	SDL_Rect* camera;
	SDL_Rect* lookAt;

	int m_width;
	int m_height;

	int min_x;
	int min_y;
	int max_x;
	int max_y;
	
public:
	Camera()
	{
		camera = new SDL_Rect();
		lookAt = new SDL_Rect();

		SDL_DisplayMode DM;
		SDL_GetCurrentDisplayMode(0, &DM);
		auto Width = DM.w;
		auto Height = DM.h;


		m_width = Width;
		m_height = Height;


		this->camera->x = 0;
		this->camera->y = 0;
		this->camera->w = Width;
		this->camera->h = Height;




	//	static_cast<int>(Width / 6.4), static_cast<int>(Height / 2.7)

	}
	void update(SDL_Rect* focus)
	{
		this->camera->x = ((focus->x + focus->w / 2) - m_width / 2) - m_width;
		this->camera->y = ((focus->y + focus->y / 2) - m_height / 2) - m_height;

		if (this->camera->x < static_cast<int>(m_width / 19.2)) {
			this->camera->x = static_cast<int>(m_width / 19.2);}
		if (this->camera->y < static_cast<int>(m_height / 10.8)) {
			this->camera->y = static_cast<int>(m_height / 10.8);}

		if (this->camera->x > this->camera->w) {this->camera->x = m_width - this->camera->w;}

		if (this->camera->y > this->camera->h) {this->camera->y = m_height - this->camera->h;}

	}

	SDL_Rect* getCamera() { return this->camera; }
	SDL_Rect* getLookAt() { return this->lookAt; }

	// The SDL_Rect enclosing the four players
	SDL_Rect* focus(std::vector<Player*> t_players)
	{
		min_x = t_players[0]->getPosition().x;
		min_y = t_players[0]->getPosition().y;
		max_x = t_players[0]->getPosition().x;
		max_y = t_players[0]->getPosition().y;

		for (int i = 1; i < t_players.size(); i++)
		{

			(min_x > t_players[i]->getPosition().x) ? min_x = t_players[i]->getPosition().x : NULL;
			(max_x < t_players[i]->getPosition().x) ? max_x = t_players[i]->getPosition().x + t_players[i]->getPosition().w : NULL;
			(min_y > t_players[i]->getPosition().y) ? min_y = t_players[i]->getPosition().y : NULL;
			(max_y < t_players[i]->getPosition().y) ? max_y = t_players[i]->getPosition().y + t_players[i]->getPosition().h : NULL;
		}

		lookAt->x = min_x;
		lookAt->y = min_y;
		lookAt->w = (max_x - min_x)+ static_cast<int>(m_width / 9.6);
		lookAt->h = (max_y - min_y)+ static_cast<int>(m_height / 5.4);

		return lookAt;
	}
};
