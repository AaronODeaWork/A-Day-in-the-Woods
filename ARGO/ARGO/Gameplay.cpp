#include "Gameplay.h"

Gameplay::Gameplay(Game& game, SDL_Renderer* t_renderer,SDL_Event& event, GameState& t_currentState ,SDL_Window* t_window, InputSystem & t_input, std::vector<Player*> t_entity, AudioManager& t_audioManager):
	m_game(game),
	m_event(event),
	m_renderer(t_renderer),
	m_window(t_window),
	m_inputSystem(t_input),
	m_entity(t_entity),
	m_currentState(t_currentState),
	m_audioManager(t_audioManager)
{
	std::srand(std::time(nullptr));
	m_numberPlayers = m_entity.size();

	SDL_DisplayMode DM;
	SDL_GetCurrentDisplayMode(0, &DM);
	auto Width = DM.w;
	auto Height = DM.h;
	

	SDL_Surface* m_DiceSurface;
	m_DiceSurface = IMG_Load("ASSETS/IMAGES/Dice/DiceOne.png");
	m_DiceTextureSides.push_back(SDL_CreateTextureFromSurface(m_renderer, m_DiceSurface));
	m_DiceSurface = IMG_Load("ASSETS/IMAGES/Dice/DiceTwo.png");
	m_DiceTextureSides.push_back(SDL_CreateTextureFromSurface(m_renderer, m_DiceSurface));
	m_DiceSurface = IMG_Load("ASSETS/IMAGES/Dice/DiceThree.png");
	m_DiceTextureSides.push_back(SDL_CreateTextureFromSurface(m_renderer, m_DiceSurface));
	m_DiceSurface = IMG_Load("ASSETS/IMAGES/Dice/DiceFour.png");
	m_DiceTextureSides.push_back(SDL_CreateTextureFromSurface(m_renderer, m_DiceSurface));
	m_DiceSurface = IMG_Load("ASSETS/IMAGES/Dice/DiceFive.png");
	m_DiceTextureSides.push_back(SDL_CreateTextureFromSurface(m_renderer, m_DiceSurface));
	m_DiceSurface = IMG_Load("ASSETS/IMAGES/Dice/DiceSix.png");
	m_DiceTextureSides.push_back(SDL_CreateTextureFromSurface(m_renderer, m_DiceSurface));

	m_PlayerUIRect.push_back(SDL_Rect{ static_cast<int>(Width/19.2), 0, static_cast<int>(Width / 6.4), static_cast<int>(Height / 2.7) });
	m_PlayerUIRect.push_back(SDL_Rect{ static_cast<int>(Width/1.2), 0, static_cast<int>(Width / 6.4), static_cast<int>(Height / 2.7) });
	m_PlayerUIRect.push_back(SDL_Rect{ static_cast<int>(Width/19.2),static_cast<int>(Height / 1.8), static_cast<int>(Width / 6.4), static_cast<int>(Height / 2.7) });
	m_PlayerUIRect.push_back(SDL_Rect{ static_cast<int>(Width/1.2), static_cast<int>(Height / 1.8), static_cast<int>(Width / 6.4), static_cast<int>(Height / 2.7) });
	SDL_Surface* Indicator;
	Indicator = IMG_Load("ASSETS/IMAGES/Ui/Ypaw.png");
	m_IndicatorTexture.push_back(SDL_CreateTextureFromSurface(m_renderer, Indicator));
	Indicator = IMG_Load("ASSETS/IMAGES/Ui/Apaw.png");
	m_IndicatorTexture.push_back(SDL_CreateTextureFromSurface(m_renderer, Indicator));
	Indicator = IMG_Load("ASSETS/IMAGES/Ui/Xpaw.png");
	m_IndicatorTexture.push_back(SDL_CreateTextureFromSurface(m_renderer, Indicator));
	Indicator = IMG_Load("ASSETS/IMAGES/Ui/Bpaw.png");
	m_IndicatorTexture.push_back(SDL_CreateTextureFromSurface(m_renderer, Indicator));

	m_IndicatorRect.push_back(SDL_Rect{ 0,0,static_cast<int>(Width / 38.4),static_cast<int>(Height / 21.6) });
	m_IndicatorRect.push_back(SDL_Rect{ 0,0,static_cast<int>(Width / 38.4),static_cast<int>(Height / 21.6) });
	m_IndicatorRect.push_back(SDL_Rect{ 0,0,static_cast<int>(Width / 38.4),static_cast<int>(Height / 21.6) });
	m_IndicatorRect.push_back(SDL_Rect{ 0,0,static_cast<int>(Width / 38.4),static_cast<int>(Height / 21.6) });

	m_PlayerShadowUIRect.push_back(SDL_Rect{ static_cast<int>(Width / 17.45),static_cast<int>(Height / 108),static_cast<int>(Width / 6.4), static_cast<int>(Height / 2.7) });
	m_PlayerShadowUIRect.push_back(SDL_Rect{ static_cast<int>(Width / 1.19),static_cast<int>(Height / 108),static_cast<int>(Width / 6.4), static_cast<int>(Height / 2.7) });
	m_PlayerShadowUIRect.push_back(SDL_Rect{ static_cast<int>(Width / 17.45),static_cast<int>(Height / 1.77),static_cast<int>(Width / 6.4), static_cast<int>(Height / 2.7) });
	m_PlayerShadowUIRect.push_back(SDL_Rect{ static_cast<int>(Width / 1.19),static_cast<int>(Height / 1.77),static_cast<int>(Width / 6.4), static_cast<int>(Height / 2.7) });

	m_DiceRect.push_back(SDL_Rect{ static_cast<int>(Width / 9.36),static_cast<int>(Height / 4.9),static_cast<int>(Width / 19.2), static_cast<int>(Height / 10.8) });
	m_DiceRect.push_back(SDL_Rect{ static_cast<int>(Width / 1.12),static_cast<int>(Height / 4.9),static_cast<int>(Width / 19.2), static_cast<int>(Height / 10.8) });
	m_DiceRect.push_back(SDL_Rect{ static_cast<int>(Width / 9.36),static_cast<int>(Height / 1.31),static_cast<int>(Width / 19.2), static_cast<int>(Height / 10.8) });
	m_DiceRect.push_back(SDL_Rect{ static_cast<int>(Width / 1.12),static_cast<int>(Height / 1.31),static_cast<int>(Width / 19.2), static_cast<int>(Height / 10.8) });

	SDL_Surface* WinSurface;
	WinSurface = IMG_Load("ASSETS/IMAGES/buttons/PlayerWin1.png");
	m_WinScreenTexture.push_back(SDL_CreateTextureFromSurface(m_renderer, WinSurface));
	WinSurface = IMG_Load("ASSETS/IMAGES/buttons/PlayerWin2.png");
	m_WinScreenTexture.push_back(SDL_CreateTextureFromSurface(m_renderer, WinSurface));
	WinSurface = IMG_Load("ASSETS/IMAGES/buttons/PlayerWin3.png");
	m_WinScreenTexture.push_back(SDL_CreateTextureFromSurface(m_renderer, WinSurface));
	WinSurface = IMG_Load("ASSETS/IMAGES/buttons/PlayerWin4.png");
	m_WinScreenTexture.push_back(SDL_CreateTextureFromSurface(m_renderer, WinSurface));
	WinSurface = IMG_Load("ASSETS/IMAGES/pic2Glass.png");
	m_WinScreenTexture.push_back(SDL_CreateTextureFromSurface(m_renderer, WinSurface));

	m_Winsscreen.h = Height*1.15;
	m_Winsscreen.w = Width*1.15;
	m_Winsscreen.x = 0;
	m_Winsscreen.y = 0;

	SDL_Surface* m_PlayerShadowUISurface = IMG_Load("ASSETS/IMAGES/Players/bearShadow.png");
	SDL_Surface* m_PlayerUISurface;
	for (int i = 0; i < m_numberPlayers ;i++) 
	{
		switch (i)
		{
		default:
			break;
		case 0:
			m_PlayerUISurface = IMG_Load("ASSETS/IMAGES/Players/bear1.png");
			m_PlayerUITexture.push_back(SDL_CreateTextureFromSurface(m_renderer, m_PlayerUISurface));

			break;
		case 1:
			m_PlayerUISurface = IMG_Load("ASSETS/IMAGES/Players/bear2.png");
			m_PlayerUITexture.push_back(SDL_CreateTextureFromSurface(m_renderer, m_PlayerUISurface));

			break;
		case 2:
			m_PlayerUISurface = IMG_Load("ASSETS/IMAGES/Players/bear3.png");
			m_PlayerUITexture.push_back(SDL_CreateTextureFromSurface(m_renderer, m_PlayerUISurface));

			break;
		case 3:
			m_PlayerUISurface = IMG_Load("ASSETS/IMAGES/Players/bear4.png");
			m_PlayerUITexture.push_back(SDL_CreateTextureFromSurface(m_renderer, m_PlayerUISurface));

			break;
		}
		m_PlayerShadowUITexture.push_back(SDL_CreateTextureFromSurface(m_renderer, m_PlayerShadowUISurface));
		m_DiceTexture.push_back(m_DiceTextureSides[0]);

		m_entity[i]->assignSprite(m_PlayerUITexture[i]);

	}
	


	m_turnOrder = 0;

	m_clouds.reserve(100);

	for (int i = 0; i < 100; i++) {m_clouds.push_back(SDL_Rect{ 
													randomNumber(static_cast<int>(Width / 1.47),static_cast<int>(Width / 3.84)),
													randomNumber(static_cast<int>(Height / 1.2),static_cast<int>(Height / 10.8)),
													static_cast<int>(Width / 12.8),static_cast<int>(Height / 7.2) });} //make 100 clouds

	for (int i = 0; i < 4 ; i++)
	{ 
		m_outLine.push_back(SDL_Rect{ -static_cast<int>(Width / 38.4),(i * static_cast<int>(Height / 5.4))- static_cast<int>(Height / 10.6),
									   static_cast<int>(Width / 9.6),static_cast<int>(Height / 1.35) });

		m_outLine.push_back(SDL_Rect{ Width,(i * static_cast<int>(Height / 5.4))- static_cast<int>(Height /10.8),
												 static_cast<int>(Width / 5.48),static_cast<int>(Height / 1.35) });
	}

	for (int i = 0; i < 4; i++) {m_outLine.push_back(SDL_Rect{ i*550,820 - 100,150,700 });} //make out line of bushes 

	SDL_Surface* m_CloudSurface = IMG_Load("ASSETS/IMAGES/cloud.png");
	m_CloudTexture = SDL_CreateTextureFromSurface(m_renderer, m_CloudSurface);

	SDL_Surface* m_outLineSurface = IMG_Load("ASSETS/IMAGES/UI/hedge.png");
	m_outLineTexture = SDL_CreateTextureFromSurface(m_renderer, m_outLineSurface);
	
	SDL_Surface* m_backgroundSurface = IMG_Load("ASSETS/IMAGES/Board.png");
	m_backgroundTexture = SDL_CreateTextureFromSurface(m_renderer, m_backgroundSurface);
	m_backgroundRect={ static_cast<int>(Width / 25.6),-static_cast<int>(Height / 108) ,Width,Height};

	SDL_Surface* m_taskbarSurface = IMG_Load("ASSETS/IMAGES/Bar.png");
	m_taskbarTexture = SDL_CreateTextureFromSurface(m_renderer, m_taskbarSurface);
	m_taskbarRect = { static_cast<int>(Width / 38.4),Height, Width + static_cast<int>(Width / 19.2) ,static_cast<int>(Height / 7.2)};




	std::srand(std::time(nullptr));
	BehaviourTree behaviourTree;
	BehaviourTree::Selector selector[3];
	BehaviourTree::Sequence sequence[4];
	Action goLeft("Go Left", 80), 
		   goRight("Go Right", 15), 
		   goUp("Go Up", 99), 
		   goDown("Go Down", 25),
		   goBack("Go Back", 10),
		   goForward("Go Forward", 60),
		   stopWalking("Stop Walking", 100);

	behaviourTree.setRootChild(&selector[0]);
	selector[0].addChildren({ &sequence[0],&sequence[2] });
	sequence[0].addChildren({ &goLeft, &selector[1], &goForward, &stopWalking });
	selector[1].addChildren({ &goRight, &sequence[1], &goBack });
	sequence[1].addChildren({ &goUp, &stopWalking });
	sequence[2].addChildren({ &goDown, &selector[2], &goBack, &stopWalking });
	const std::list<BehaviourTree::Node*> nodes = { &goLeft, &sequence[3], &goForward };
	selector[2].addChildren(nodes);
	sequence[3].addChildren({ &goForward, &stopWalking });
	if (behaviourTree.run())
		std::cout << "Behaviour Success" << std::endl;
	else
		std::cout << "Behaviour Failure" << std::endl;

	SDL_FreeSurface(m_DiceSurface);
	SDL_FreeSurface(WinSurface);
	SDL_FreeSurface(m_PlayerShadowUISurface);
	SDL_FreeSurface(m_CloudSurface);
	SDL_FreeSurface(m_outLineSurface);
	SDL_FreeSurface(m_backgroundSurface); 
	SDL_FreeSurface(Indicator);

	m_width = Width;
	m_height = Height;
}

Gameplay::~Gameplay()
{
	SDL_CloseAudioDevice(deviceId);
	SDL_FreeWAV(wavBuffer);

	//AudioManager::Release();
	//m_audioManager = NULL;
}

void Gameplay::update(std::vector<Tile>& t_tile, std::vector<Player*>& t_player, std::vector<NPC*>& t_npc, MovementSystem& t_move)
{


	if (!setUp)
	{
		m_audioManager.PlayMusic("m_gameBoard.wav",5);
		m_audioManager.PlaySfx("s_intro.wav", 128, 0, 1);
		m_storyPointIndex = 0;
		//SDL_PauseAudioDevice(deviceId, 0);
		t_npc[0]->turn = true;
		setUp = true;
	}
	
	for (int i = 0; i < m_numberPlayers ;i++)
	{
		t_move.update(i);
		m_entity[i]->update(t_move);
		//m_entity[i]->setTileType(t_tile[t_move.getIndex(i)].getType(), t_move.getIndex(i));
	}

	if (!m_audioManager.IsChannelPLaying(1))
	{
		for (int i = 0; i < m_numberPlayers; i++)
		{
			switch (m_storyPointIndex)
			{
			case 0:
				if (t_move.GetYPos(i) <= static_cast<int>(m_height / 1.35))
				{
					m_audioManager.PlaySfx("s_pt1.wav", 128, 0, 1);
					m_storyPointIndex++;
				}
				break;
			case 1:
				if (t_move.GetYPos(i) <= static_cast<int>(m_height / 1.66))
				{
					m_audioManager.PlaySfx("s_pt2.wav", 128, 0, 1);
					m_storyPointIndex++;
				}
				break;
			case 2:
				if (t_move.GetYPos(i) <= static_cast<int>(m_height / 2.7))
				{
					m_audioManager.PlaySfx("s_pt3.wav", 128, 0, 1);
					m_storyPointIndex++;
				}
				break;
			case 3:
				if (t_move.GetYPos(i) <= static_cast<int>(m_height / 4.32))
				{
					m_audioManager.PlaySfx("s_pt4.wav", 128, 0, 1);
					m_storyPointIndex++;
				}
				break;
			default:
				break;
			}
		}

	}

	for (int i = 0; i < m_clouds.size(); i++)
	{
		int temp = randomNumber(200, 0);


		if (temp == 0){
		m_clouds[i].x += static_cast<int>(m_width / 190);
		m_clouds[i].h -= static_cast<int>(m_height / 108);
		m_clouds[i].w -= static_cast<int>(m_width / 128);}

		else if (temp == 1){
		m_clouds[i].x -= static_cast<int>(m_width / 190);
		m_clouds[i].h += static_cast<int>(m_height / 108);
		m_clouds[i].w += static_cast<int>(m_width / 128);}

		if (m_clouds[i].x > static_cast<int>(m_width / 1.28) || m_clouds[i].x < static_cast<int>(m_width / 6.4) ||
			m_clouds[i].y > static_cast<int>(m_height / 1.13) || m_clouds[i].y < 0 ||
			m_clouds[i].h > static_cast<int>(m_height / 7.2) || m_clouds[i].h < static_cast<int>(m_height / 21.6))
		{
			m_clouds.erase(m_clouds.begin() + i);
			m_clouds.push_back(SDL_Rect{
										randomNumber(static_cast<int>(m_width / 1.47),static_cast<int>(m_width / 3.84)),
										randomNumber(static_cast<int>(m_height / 1.2),static_cast<int>(m_height / 10.8)),
													static_cast<int>(m_width / 12.8),static_cast<int>(m_height / 7.2) });
		}
	}
	
/*
	if (t_npc[0]->turn)
	{
		t_npc[m_npcCount]->update();
		if (t_npc[m_npcCount]->m_diceNumber == 0)
		{
			if (t_tile[t_npc[m_npcCount]->currentGameBoardIndex].count == 0)
			{
				std::cout << "npc 1 tile" << std::endl;
				t_tile[t_npc[m_npcCount]->currentGameBoardIndex].count++;
				t_tile[t_npc[m_npcCount]->currentGameBoardIndex].update();
				SDL_Delay(200);
			}
			if (!t_npc[m_npcCount]->stuck)
			{
				t_tile[t_npc[m_npcCount]->currentGameBoardIndex].count = 0;
			}
			t_npc[0]->turn = false;
			t_npc[1]->turn = true;
			m_npcCount++;
		}
	}
	else if (t_npc[1]->turn)
	{
		t_npc[m_npcCount]->update();
		if (t_npc[m_npcCount]->end)
		{
			m_npcCount++;
			if (m_npcCount >= t_npc.size())
			{
				m_npcCount = 0;
			}
			t_npc[m_npcCount]->end = false;
			t_npc[m_npcCount]->turn = true;
		}
	}*/
	
	// SDL_Rect to focus on
	focus = camera->focus(m_entity);
	// Update Camera based on new focus
	camera->update(focus);
}

void Gameplay::render(std::vector<Tile>& t_tile, std::vector<Player*>& t_player, std::vector<NPC*>& t_npc, Graph< pair<string, int>, int>& graph)
{
	SDL_RenderClear(m_renderer);
	SDL_RenderSetScale(m_renderer, scale, scale);

	SDL_RenderCopy(m_renderer, m_backgroundTextureTwo, NULL, NULL);
	SDL_RenderCopy(m_renderer, m_backgroundTexture, NULL, &m_backgroundRect);

	offset->x = focus->x - camera->getCamera()->x;
	offset->y = focus->y - camera->getCamera()->y;
	offset->w = focus->w;
	offset->h = focus->h;
	
	for (int i = 0; i < m_clouds.size(); i++)
	{
		if ((m_clouds[i].x > offset->x) + m_clouds[i].w/2){
			if(m_clouds[i].x < (offset->x + offset->w)){
				if (m_clouds[i].y > (offset->y) - m_clouds[i].h / 1.9){
					if (m_clouds[i].y < (offset->y + offset->h)) {m_clouds.erase(m_clouds.begin() + i);}}}}
	}

	SDL_RenderCopy(m_renderer, m_taskbarTexture, NULL, &m_taskbarRect);

	for (int i = 0; i < m_outLine.size()-4; i++) { SDL_RenderCopy(m_renderer, m_outLineTexture, NULL, &m_outLine[i]); }
	for (int i = m_outLine.size() - 4; i < m_outLine.size(); i++) {SDL_RenderCopyEx(m_renderer, m_outLineTexture, NULL, &m_outLine[i],90, NULL, SDL_FLIP_NONE);}






	// Little target Box in middle of Focus
	//offset->w = CHARACTER_WIDTH ;
	//offset->h = CHARACTER_HEIGHT ;
	//offset->x = (((focus->x + focus->w / 2) - offset->w / 2) - camera->getCamera()->x);
	//offset->y = (((focus->y + focus->h / 2) - offset->h / 2) - camera->getCamera()->y);
	//SDL_RenderDrawRect(m_renderer, offset);

	
	if (m_flipUIBear)
	{
		m_rotation -= 1;
		if (m_rotation < -5) { m_flipUIBear = false; }
	}
	else
	{
		m_rotation += 1;
		if (m_rotation > 5) { m_flipUIBear = true; }
	}

	for (int i = 0; i < t_tile.size(); i++)
	{
		t_tile[i].render(m_renderer);
	}

	for (int i = 0; i < m_numberPlayers ;i++)
	{
		if (i == m_turnOrder) {
			if(m_entity[m_turnOrder]->getLastButtonPressed() == 1 && m_diceflip ==3)
			{					
				m_audioManager.PlaySfx("roll.wav", 50, 0, 1);
				m_diceflip = 0;
				m_diceAnimation = true;
				m_entity[i]->setLastButton(998);
			}

			if (m_diceAnimation)
			{
				if (m_diceflip == 0)
				{				

					m_DiceRect[i].h += static_cast<int>(m_height / 1080);
					m_DiceRect[i].w += static_cast<int>(m_width / 960);
					setRandomDiceTexture(i);
					if (m_DiceRect[i].h > static_cast<int>( m_height/7.2)) { m_diceflip = 1; }
				}
				else if(m_diceflip == 1)
				{
					setDiceTexture(i);
					m_DiceRect[i].h -= static_cast<int>(m_height / 1080);
					m_DiceRect[i].w -= static_cast<int>(m_width / 960);
					if (m_DiceRect[i].h < static_cast<int>(m_height / 10.8))
					{
						m_diceAnimation = false;
						m_diceflip = 2;

						m_entity[i]->setLastButton(999);
				
					}
				}
			}
			m_entity[i]->render(m_renderer, m_rotation);
			SDL_RenderCopyEx(m_renderer, m_PlayerShadowUITexture[i], NULL, &m_PlayerShadowUIRect[i], m_rotation, NULL, SDL_FLIP_NONE);
			SDL_RenderCopyEx(m_renderer, m_PlayerUITexture[i], NULL, &m_PlayerUIRect[i], m_rotation, NULL, SDL_FLIP_NONE);
			SDL_RenderCopyEx(m_renderer, m_DiceTexture[i], NULL, &m_DiceRect[i], m_rotation, NULL, SDL_FLIP_NONE);
		}
		else
		{
			m_entity[i]->render(m_renderer, 0);
			SDL_RenderCopyEx(m_renderer, m_PlayerShadowUITexture[i], NULL, &m_PlayerShadowUIRect[i], 0, NULL, SDL_FLIP_NONE);
			SDL_RenderCopyEx(m_renderer, m_PlayerUITexture[i], NULL, &m_PlayerUIRect[i], 0, NULL, SDL_FLIP_NONE);
			SDL_RenderCopyEx(m_renderer, m_DiceTexture[i], NULL, &m_DiceRect[i], 0, NULL, SDL_FLIP_NONE);
		}
	}




	for (int i = 0; i < m_clouds.size(); i++) {SDL_RenderCopyEx(m_renderer, m_CloudTexture, NULL, &m_clouds[i], 0, NULL, SDL_FLIP_NONE);}

	for (int i = 0; i < t_npc.size(); i++) {t_npc[i]->render(m_renderer);}

	if (m_entity[m_turnOrder]->m_upChoiceBool == true) {
		m_IndicatorRect[0].x = (m_entity[m_turnOrder]->getPosition().x - m_entity[0]->getPosition().w/2);
		m_IndicatorRect[0].y = (m_entity[m_turnOrder]->getPosition().y - m_entity[0]->getPosition().h/2)- m_entity[0]->getPosition().h*2.5;

		SDL_RenderCopyEx(m_renderer, m_IndicatorTexture[0], NULL, &m_IndicatorRect[0], 0, NULL, SDL_FLIP_NONE);
	}
	if (m_entity[m_turnOrder]->m_downChoiceBool == true) {
		m_IndicatorRect[1].x = (m_entity[m_turnOrder]->getPosition().x - m_entity[0]->getPosition().w/2);
		m_IndicatorRect[1].y = (m_entity[m_turnOrder]->getPosition().y - m_entity[0]->getPosition().h/2) + m_entity[0]->getPosition().h*1.5;

		SDL_RenderCopyEx(m_renderer, m_IndicatorTexture[1], NULL, &m_IndicatorRect[1], 0, NULL, SDL_FLIP_NONE);
	}
	if (m_entity[m_turnOrder]->m_leftChoiceBool == true) {
		m_IndicatorRect[2].x = (m_entity[m_turnOrder]->getPosition().x - m_entity[0]->getPosition().w/2) - m_entity[0]->getPosition().w*2;
		m_IndicatorRect[2].y = (m_entity[m_turnOrder]->getPosition().y - m_entity[0]->getPosition().h/2);

		SDL_RenderCopyEx(m_renderer, m_IndicatorTexture[2], NULL, &m_IndicatorRect[2], 0, NULL, SDL_FLIP_NONE);
	}
	if (m_entity[m_turnOrder]->m_rightChoiceBool == true) {
		m_IndicatorRect[3].x = (m_entity[m_turnOrder]->getPosition().x - m_entity[0]->getPosition().w/2) + m_entity[0]->getPosition().h*2;
		m_IndicatorRect[3].y = (m_entity[m_turnOrder]->getPosition().y - m_entity[0]->getPosition().h/2);

		SDL_RenderCopyEx(m_renderer, m_IndicatorTexture[3], NULL, &m_IndicatorRect[3], 0, NULL, SDL_FLIP_NONE);
	}



	SDL_RenderPresent(m_renderer);
}

void Gameplay::renderWin(int index)
{

	SDL_RenderClear(m_renderer);

	switch (index)
	{
	case 0:
		SDL_RenderCopy(m_renderer, m_WinScreenTexture[index], NULL, NULL);
		break;
	case 1:
		SDL_RenderCopy(m_renderer, m_WinScreenTexture[index], NULL, NULL);
		break;
	case 2:
		SDL_RenderCopy(m_renderer, m_WinScreenTexture[index], NULL, NULL);
		break;
	case 3:
		SDL_RenderCopy(m_renderer, m_WinScreenTexture[index], NULL, NULL);
		break;
	default:
		break;
	}

	SDL_RenderPresent(m_renderer);
	if (!m_audioManager.IsChannelPLaying(1))
	{
		setGameState();
	}
}

void Gameplay::processEvent(MovementSystem & t_move)
{

	for (int i = 0; i < m_numberPlayers; i++)
	{
		if (m_turnOrder == m_entity[i]->getId()&& m_diceAnimation == false)
		{
			m_entity[i]->m_upChoiceBool = false;
			m_entity[i]->m_downChoiceBool = false;
			m_entity[i]->m_leftChoiceBool = false;
			m_entity[i]->m_rightChoiceBool = false;

			if (!m_audioManager.IsChannelPLaying(1))
			{
		
				if (t_move.getPlayerDiceValue(i) == -2)
				{
					m_inputSystem.update(m_event, m_currentState, m_entity[i], i);
				}
				else if (t_move.getPlayerDiceValue(i) == -3)
				{
					m_turnOrder++;
					if (m_turnOrder == m_entity.size())
						m_turnOrder = 0;
					t_move.setPlayerDiceValue(i, -1);
				}
				else
				{
					if (t_move.getPlayerDiceValue(i) == -1 && !t_move.IsThePlayerMoving(i))
					{
		
						t_move.setPlayerDiceValue(i, 0);
						m_turnOrder++;
						if (m_turnOrder == m_entity.size())
							m_turnOrder = 0;
							m_entity[i]->setLastButton(NULL);

							m_diceflip = 3;
					}
					else
					{

						if ( m_diceflip == 2 && m_entity[i]->getLastButtonPressed() == NULL)
						{m_inputSystem.update(m_event, m_currentState, m_entity[i], i);}

						if(m_entity[i]->IsAI == false && m_diceflip == 2 && m_entity[i]->getLastButtonPressed() == 999 || m_entity[i]->getLastButtonPressed() == NULL)
						{m_inputSystem.update(m_event, m_currentState, m_entity[i], i);}
						
						if (t_move.getPlayerDiceValue(i) >= 0 && m_entity[i]->IsAI == false)
						{m_inputSystem.update(m_event, m_currentState, m_entity[i], i);}
					}
				}
			}
			
		}
	}
}

void Gameplay::setGameState()
{
	//SDL_RenderSetScale(m_renderer, 1, 1);
	//m_game.startMinGame();
	m_game.setGameState(GameState::Menu);
}

void Gameplay::Reset(MovementSystem& t_move)
{

	m_numberPlayers = m_entity.size();
	m_turnOrder = 0;

	for (int i = 0; i < 100; i++) { m_clouds.push_back(SDL_Rect{ randomNumber(static_cast<int>(m_width / 1.47),static_cast<int>(m_width / 3.84)),
																 randomNumber(static_cast<int>(m_height / 1.2),static_cast<int>(m_height / 10.8)),
																			  static_cast<int>(m_width / 12.8),static_cast<int>(m_height / 7.2) });} //make 100 clouds

	for (int i = 0; i < m_entity.size(); i++) {m_entity[i]->SetUp();}
	t_move.restPlayers();
}


float Gameplay::calculateScale(float width, float height, float maxWidth, float maxHeight)
{
	return max(maxWidth / width, maxHeight / height);
}

void Gameplay::setDiceTexture(int m_playerID)
{	
	m_DiceTexture[m_playerID] = m_DiceTextureSides[m_entity[m_playerID]->getDiceRoll()-1] ;
}

void Gameplay::setRandomDiceTexture(int m_playerID)
{
	m_DiceTexture[m_playerID] = m_DiceTextureSides[randomNumber(5,0)];

}

int Gameplay::randomNumber(int t_max, int t_min)
{
	std::random_device device;
	std::mt19937 rng(device());
	std::uniform_int_distribution<std::mt19937::result_type> dist(t_min, t_max);
	return dist(rng);
}