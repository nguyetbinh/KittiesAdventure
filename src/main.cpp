#include "CommonFunction.h"
#include "BaseObj.h"
#include <iostream>
#include "gamemap.h"
#include "Player.h"
#include "ImpTimer.h"
#include "Text.h"
#include "Menu.h"
#include "OtherObj.h"
#include "MapFiles.h"
#include "GameOver.h"
#include "Save_game.h"

#include <iostream>
#include <string>

using namespace std;

BaseObj background1;
BaseObj background2;

TTF_Font *mainfont;
Save_game HKgame;

bool init() {
	bool success = true;
	int ret = SDL_Init(SDL_INIT_VIDEO);
	if (ret < 0) {
		return false;
	}
	SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1");
	gwindow = SDL_CreateWindow("Hungry Kitties", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
	if (gwindow == NULL) {
		success = false;
	}
	else {
		gscreen = SDL_CreateRenderer(gwindow, -1, SDL_RENDERER_ACCELERATED);
        SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");
        SDL_RenderSetLogicalSize(gscreen,SCREEN_WIDTH, SCREEN_HEIGHT );
		if (gscreen == NULL) {
			success = false;
		}
		else {
			SDL_SetRenderDrawColor(gscreen, 255, 255, 255, 255);
			int imgflags = IMG_INIT_PNG;
			if (!(IMG_Init(imgflags) && imgflags))
				success = false;
		}
		if (TTF_Init() == -1) {
			success = false;
		}
		mainfont = TTF_OpenFont("./fonts/m6x11.ttf", 50);
		if (mainfont == NULL) {
			success = false;
		}
	}
	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) <0) {
		success = false;
	}
	background_music = Mix_LoadMUS("./sounds/mainbackground.wav");
	menu_music = Mix_LoadMUS("./sounds/menu.wav");
	gameover_music = Mix_LoadMUS("./sounds/gameover.wav");
	winner_music = Mix_LoadMUS("./sounds/win.wav");

	sound[0] = Mix_LoadWAV("./sounds/jump.wav");
    sound[1] = Mix_LoadWAV("./sounds/fish.wav");
	if (background_music==NULL||sound[0] == NULL|| sound[0] == NULL || menu_music == NULL || gameover_music == NULL||winner_music == NULL ) {
		cerr << "Sound Error!\n" << Mix_GetError();
		success = false;
	}

	return success;
}
bool LoadBackGround1() {
	bool ret = background1.LoadImg("./assets/lv1.png",gscreen);
	return ret;
}
bool LoadBackGround2()
{
	bool ret = background2.LoadImg("./assets/lv2.png",gscreen);
	return ret;
}

void close() {
	background1.Free();
	background2.Free();
	SDL_DestroyRenderer(gscreen);
	gscreen = NULL;

	TTF_CloseFont(mainfont);
	mainfont = NULL;
	SDL_DestroyWindow(gwindow);
	gwindow = NULL;
	Mix_FreeMusic(background_music);
	background_music = NULL;
	Mix_FreeMusic(menu_music);
	menu_music = NULL;
	Mix_FreeMusic(gameover_music);
	gameover_music = NULL;
	Mix_FreeMusic(winner_music);
	winner_music = NULL;
	Mix_FreeChunk(sound[0]);
	sound[0] = NULL;
	Mix_FreeChunk(sound[1]);
	sound[1] = NULL;
	Mix_CloseAudio();

	TTF_Quit();

	IMG_Quit();
	SDL_Quit();
}


//main program
int main(int arcs, char* argv[]) {
	const int FPS = 60;
	const int frameDelay = 1000 / FPS;
	Uint32 framestart;
	int frametime;

	ImpTimer fps_timer;

	if (!init()) {
		return -1;
	}
	if (LoadBackGround1() == false||LoadBackGround2() == false) {
		return -1;
	}
	Map_LinkedList* mllist = new Map_LinkedList();

	mllist->insertAtTail("./map/map1.txt");
	mllist->insertAtTail("./map/map2.txt");

	MapFiles* tmp = mllist->getHead();

	GameMap game_map;
	string s = mllist->getHead()->mapfile;
	const char* c = s.c_str();
	game_map.LoadMap(c);
	game_map.LoadTiles(gscreen);

	Player player1;
	player1.LoadImg("./assets/player1.png", gscreen);
	player1.setclip();

	Player player2;
	player2.LoadImg("./assets/player2.png", gscreen);
	player2.setclip();

	player1.setPos(332, 662);
	player2.setPos(500, 662);

	OtherObj cutemus;
	cutemus.setPos(230,480);
    cutemus.LoadImg("./assets/mushroom.png", gscreen, 48);
	cutemus.getNum(4);
	cutemus.setclip();

	OtherObj gate;
	gate.setPos(1440,225);
	gate.LoadImg("./assets/gate.png",gscreen, 32);
	gate.getNum(14);
	gate.setclip();

	Text score_text_1;
	score_text_1.SetColor(Text::BLACK);
	int score_value_1 = 0;

	Text score_text_2;
	score_text_2.SetColor(Text::BLACK);
	int score_value_2 = 0;

    score_text_1.LoadFont(mainfont, gscreen);

    score_text_2.SetText("Score 2: 0");
    score_text_2.LoadFont(mainfont, gscreen);
    
			
	Menu menu;
	Menu _tutorial;
	Menu winner;


	bool quit = false;
	int state=0;
	enum STATE {
		isPlaying = 1,
		isGameover = 2,
		isTutorial = 3,
		isWin = 4,
	};

	int level = 1;

	Mix_PlayMusic(menu_music, -1); //nhac lap vo han
	if (menu.loadMenu(gscreen, mainfont) == 0) {
		state = isTutorial;
	}
	if (menu.loadMenu(gscreen, mainfont) == QUIT) {
		quit = true;
	}
	if(menu.loadMenu(gscreen, mainfont) == 3)
    {	
        Mix_PlayMusic(background_music, -1);
        HKgame.load_files();
        cout << HKgame.getLV();
        level = HKgame.getLV();
		if(level == 1)
		{
			SDL_RenderCopy(gscreen, background1.gettexture(), nullptr, nullptr);
					cout << "background1-1 rendered" << endl;
			player1.setPos(332, 662);
			player2.setPos(400, 662);
			cutemus.setPos(230, 480);
			gate.setPos(1440,225);

			string b = mllist->getHead()->mapfile;
			const char* v = b.c_str();
			game_map.LoadMap(v);
			game_map.LoadTiles(gscreen);
			state = isPlaying;
		}
		else if(level == 2)
		{
			player1.setPos(275, 662);
			player2.setPos(275, 580);
			cutemus.setPos(1400, 610);
			gate.setPos(1440, 224);

			SDL_RenderCopy(gscreen, background2.gettexture(), nullptr, nullptr);
					cout << "background2-2 rendered" << endl;
		    mllist->nextNode();
			string b = mllist->getHead()->mapfile;
			const char* v = b.c_str();
			game_map.LoadMap(v);
			game_map.LoadTiles(gscreen);
			state = isPlaying;

		}

    }

	GameOver _gameover;
	while (!quit) {
		if (state == isGameover)
		{
			
			Mix_PlayMusic(gameover_music, 1); //lap 1 lan duy nhat
			if (_gameover.loadGameOver(gscreen, mainfont)==0) {
				player1.resetPoint();
				player2.resetPoint();
				Mix_PlayMusic(background_music, -1);
				string s = mllist->getHead()->mapfile;
				const char* c = s.c_str();
				game_map.LoadMap(c);
				game_map.LoadTiles(gscreen);

				player1.changeState();
				player2.changeState();
                if (level == 1)
                {
                	SDL_RenderCopy(gscreen, background1.gettexture(), nullptr, nullptr);
					cout << "background1-3 rendered" << endl;
					player1.setPos(332, 662);
					player2.setPos(400, 662);
					cutemus.setPos(230, 480);
					gate.setPos(1440,225);
				}
				if (level == 2)
                {
                	SDL_RenderCopy(gscreen, background2.gettexture(), nullptr, nullptr);
					cout << "background2-4 rendered" << endl;
                	player1.setPos(275, 662);
					player2.setPos(275, 580);
					cutemus.setPos(1400, 610);
					gate.setPos(1440, 224);
                }
				state = isPlaying;
			}
			else if (_gameover.loadGameOver(gscreen, mainfont) == QUIT) {
				quit = true;
			}
			else if (_gameover.isQuit()) quit = true;
			if (event.type == SDL_QUIT) {
				quit = true;
			}
		}

		else if (state == isTutorial)
		{
			if (_tutorial.loadTutorial(gscreen) == QUIT){
                quit = true;
            }
            else if (_tutorial.loadTutorial(gscreen) == SPACE){
            	Mix_PlayMusic(background_music, -1);
                quit = false;
                state = isPlaying;
            }
		}

		else if (state == isWin )
        {
            Mix_PlayMusic(winner_music, 1);
			winner.loadWinScreen(gscreen);
            if (winner.loadWinScreen(gscreen)==QUIT)
            {
                quit = true;
            }
        }

		else if (state == isPlaying)
		{
			fps_timer.start();

			while (SDL_PollEvent(&event) != 0) {
				if (event.type == SDL_QUIT) {
					quit = true;
				}
				else if (event.type == SDL_KEYDOWN) {
					switch (event.key.keysym.sym) {
					case SDLK_0:
						if (Mix_PlayingMusic() == 0) {
						}
						break;
					}
				}


				player1.changeState();
				player2.changeState();
				player1.handleEvent1(event, gscreen, sound);
				player2.handleEvent2(event, gscreen, sound);

			}
			
			
			if (level == 1) SDL_RenderCopy(gscreen, background1.gettexture(), nullptr, nullptr);
            else if (level == 2) SDL_RenderCopy(gscreen, background2.gettexture(), nullptr, nullptr);
            
			Map map_data = game_map.getMap();

            cutemus.show(gscreen);

			gate.show(gscreen);
			player1.DoPlayer1(map_data, 0);
            player1.CheckToGate(0,gate);
            player1.CheckToMus(0, cutemus);
			player1.show1(gscreen);
            if(player1.isEating_fish(map_data)) Mix_PlayChannel(-1, sound[1], 0);

			player2.DoPlayer2(map_data, 1);
            player2.CheckToGate(1,gate);
            player2.CheckToMus(1, cutemus);
			player2.show2(gscreen);
            if(player2.isEating_fish(map_data)) Mix_PlayChannel(-1, sound[1], 0);

			game_map.SetMap(map_data);
			game_map.DrawMap(gscreen);
			if (player1.checkNextLevelP1() == true && player2.checkNextLevelP2() == true) {

				level+=1;
				score_value_1=0;
				score_value_2=0;

				player1.resetPoint();
				player2.resetPoint();


				//if(level<2) level += 1;
				if (level > 2) 
				{
					level--;
					state = isWin;
					
				}
                if(level==2)
                {
                	SDL_RenderCopy(gscreen, background2.gettexture(), nullptr, nullptr);
					cout << "background2-7 rendered" << endl;
                	player1.setPos(275, 662);
					player2.setPos(275, 580);
					cutemus.setPos(1400, 610);
					gate.setPos(1440, 224);
                }
                mllist->nextNode();
				string s = mllist->getHead()->mapfile;
				const char* v = s.c_str();
				game_map.LoadMap(v);
				game_map.LoadTiles(gscreen);


			}
			if (player1.GameOver1() == 1 || player2.GameOver2() == 1){
				player1.resetMove();
				player2.resetMove();
				state = isGameover;

			}

			int real_time = fps_timer.get_tick();
			int time_per_frame = 1000 / FPS;
			

			int score_value_2 = 0;

			score_value_1 = player1.getScore1();

			std::string val_str_score1 = std::to_string(score_value_1);
   			std::string strScore1("Score 1: ");
    		strScore1 += val_str_score1;

    		score_text_1.SetText(strScore1);
    		score_text_1.LoadFont(mainfont, gscreen);

    
			


    		score_value_2 = player2.getScore2();

			std::string val_str_score2 = std::to_string(score_value_2);
    		std::string strScore2("Score 2: ");
    		strScore2 += val_str_score2;

            
    		score_text_2.SetText(strScore2);
    		score_text_2.LoadFont(mainfont, gscreen);
			score_text_1.RenderText(gscreen, 440, 55);
			score_text_2.RenderText(gscreen, 1050, 55);

			
			SDL_RenderPresent(gscreen);
			if (real_time < time_per_frame) {
				int delay = time_per_frame - real_time;
				if (delay >= 0) {
					SDL_Delay(delay);
				}
			}
			SDL_SetRenderDrawColor(gscreen, 0, 0, 0, 255);
			SDL_RenderClear(gscreen);
			score_text_1.Free();
			score_text_2.Free();
		}
	}
	close();
	score_text_1.Free();
	score_text_2.Free();
	HKgame.game_save(level);
	return 0;
}

