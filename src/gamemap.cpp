#include "gamemap.h"

GameMap::GameMap()
{}

GameMap::~GameMap()
{}

//  Read map data from a file
void GameMap::LoadMap(const char* name) {
	FILE* fp = fopen(name, "rb");
        if (fp == NULL) 
        {
            // Xử lý lỗi
            return;
        }

	gamemap.maxx = 0;
	gamemap.maxy = 0;
	for (int i = 0;i < MAP_MAP_Y;i++) {
		for (int j = 0;j < MAP_MAP_X;j++) {
			fscanf(fp, "%d", &gamemap.tile[i][j]);

			if (gamemap.tile[i][j] > 0) {
				if (j > gamemap.maxx) {
					gamemap.maxx = j;
				}
				if (i > gamemap.maxy) {
					gamemap.maxy = i;
				}
			}
		}
	}

	gamemap.maxx = (gamemap.maxx + 1) * TILE_SIZE;
	gamemap.maxy = (gamemap.maxy + 1) * TILE_SIZE;

	gamemap.startx = 0;
	gamemap.starty = 0;

	gamemap.mapfile = name;
	fclose(fp);
}

//Load map assets
void GameMap::LoadTiles(SDL_Renderer* screen) {
	char file_img[60];
	FILE* fp = NULL;
    for(int i = 1; i <= MAX_TILES; i++){
        snprintf(file_img, sizeof(file_img), "./assets/block%d.png", i); //luu gtri cua i vao 
        // file_img.insert(25,to_string(i));
        //cuoi chuoi "...", ket qua chuyen vao file_img
        fp = fopen(file_img, "rb");
            if (fp == NULL)
            {
            // Xử lý lỗi
            // cout << "khong tim thay file block: " << file_img << endl;
            continue;
            }
        fclose(fp);

		tilemap[i].LoadImg(file_img, screen);
	}
}

//vẽ 
void  GameMap::DrawMap(SDL_Renderer* des) {
	int x1 = 0;
	int x2 = 0;

	int y1 = 0;
	int y2 = 0;

	// chỉ số 1 ô trên bản đồ
	int mapx = 0;
	int mapy = 0;

	mapx = gamemap.startx / TILE_SIZE;

	x1 = (gamemap.startx % TILE_SIZE) * -1;
	x2 = x1 + 1760 + (x1 == 0 ? 0:TILE_SIZE);

	mapy = gamemap.starty / TILE_SIZE;

	y1 = (gamemap.starty % TILE_SIZE) * -1;
	y2 = y1 + 960 + (y1 == 0 ? 0 : TILE_SIZE);

	for (int i = y1;i < y2;i += TILE_SIZE) {
		mapx = gamemap.startx / TILE_SIZE;
		for (int j = x1;j < x2;j += TILE_SIZE) {
			if (gamemap.tile[mapy][mapx] >0) {
				tilemap[gamemap.tile[mapy][mapx]].SetRect(j, i);
				tilemap[gamemap.tile[mapy][mapx]].Render(des);
			}
			mapx++;
		}
		mapy++;
	}
}
