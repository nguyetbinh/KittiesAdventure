#pragma once
#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>
#include <bits/stdc++.h>

static SDL_Window* gwindow = NULL;
static SDL_Renderer* gscreen = NULL;
static SDL_Event event;

static Mix_Music* background_music;
static Mix_Music* menu_music;
static Mix_Music* gameover_music;
static Mix_Music* winner_music;

static Mix_Chunk* sound[50];


const int ColorKeyRed = 167;
const int ColorKeyGreen = 175;
const int ColorKeyBlue = 180;

const int QUIT = 2;
const int SPACE = 10;
const int TILE_SIZE = 32;
 
const int MAP_MAP_X = 55;
const int MAP_MAP_Y = 30;

const int SCREEN_WIDTH = 1760;
const int SCREEN_HEIGHT = 960;
typedef struct Input {
	int left;
	int right;
	int stayleft;
	int stayright;
	int jump;
}Input;
//1 biến kiểu Map là 1 ô để fill đất hoặc gạch hoặc chỗ trống
typedef struct Map {
	int startx;
	int starty;

	int maxx;
	int maxy;

	int tile[MAP_MAP_Y][MAP_MAP_X];
	const char* mapfile;
}Map;