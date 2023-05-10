#include "Player.h"
#include "OtherObj.h"

Player::Player()
{
    frame = 0;
    xpos = 332;
    ypos = 664;
    xval = 0;
    yval = 0;
    widthframe = 0;
    heightframe = 0;
    status = -1;
    onground = false;
    input_type.left = 0;
    input_type.right = 0;
    input_type.stayleft = 0;
    input_type.stayright = 0;
    input_type.jump = 0;

    pinkfish1 = 0;
    blackfish1 = 0;

    pinkfish2 = 0;
	blackfish2=0;

	pinkfish2 = 0;
	blackfish2=0;
}


Player::~Player() {
	Free();
}

//để tái sử dụng mà ko cần viết lại => sd hàm ảo
//Load image at specified path
bool Player::LoadImg(string path, SDL_Renderer* renderer) {
	bool ktra = BaseObj::LoadImg(path, renderer);

	if (ktra == true) {
		widthframe = 32;
		heightframe = 32;
	}
	return ktra;
}

//Array of the player's state
void Player::setclip() {
	if (widthframe > 0 && heightframe > 0) {
		FRAME_CLIP[0].x = 0;
		FRAME_CLIP[0].y = 0;
		FRAME_CLIP[0].w = widthframe;
		FRAME_CLIP[0].h = heightframe;

		FRAME_CLIP[1].x = widthframe;
		FRAME_CLIP[1].y = 0;
		FRAME_CLIP[1].w = widthframe;
		FRAME_CLIP[1].h = heightframe;

		FRAME_CLIP[2].x = widthframe*2;
		FRAME_CLIP[2].y = 0;
		FRAME_CLIP[2].w = widthframe;
		FRAME_CLIP[2].h = heightframe;

		FRAME_CLIP[3].x = widthframe*3 ;
		FRAME_CLIP[3].y = 0;
		FRAME_CLIP[3].w = widthframe;
		FRAME_CLIP[3].h = heightframe;

		FRAME_CLIP[4].x = widthframe*2;
		FRAME_CLIP[4].y = 0;
		FRAME_CLIP[4].w = widthframe;
		FRAME_CLIP[4].h = heightframe;

		FRAME_CLIP[5].x = widthframe;
		FRAME_CLIP[5].y = 0;
		FRAME_CLIP[5].w = widthframe;
		FRAME_CLIP[5].h = heightframe;

		FRAME_CLIP[6].x = 0;
		FRAME_CLIP[6].y = 0;
		FRAME_CLIP[6].w = widthframe;
		FRAME_CLIP[6].h = heightframe;


	}
}

//show the player

void Player::show1(SDL_Renderer* des) {
	UpdateImgPlayer1(des);
	if ((input_type.left == 1 || input_type.right == 1|| input_type.stayright == 1|| input_type.stayleft == 1)&&onground==true&&input_type.jump==0) {
		if (frame >= 0) {
			++frame;
		}

	}
	else {
		frame = 0;
	}
	if (input_type.jump == 1) {
		frame = 0;
	}

	 if (frame / 6 >= 6) {
		frame=0;
	}

	rect.x = xpos;
	rect.y = ypos;
 // set để fit kích thước ảnh
	SDL_Rect* currentclip = &FRAME_CLIP[frame/6];
	SDL_Rect renderQuad = {rect.x,rect.y,widthframe*3,heightframe*3 };

	if (currentclip != NULL)
	{
		renderQuad.w = 3*currentclip->w;
		renderQuad.h = 3*currentclip->h;
	}


	SDL_RenderCopy(des, texture, currentclip, &renderQuad);
}


void Player::show2(SDL_Renderer* des) {
	UpdateImgPlayer2(des);
	if ((input_type.left == 1 || input_type.right == 1 || input_type.stayright == 1 || input_type.stayleft == 1) && onground == true && input_type.jump == 0) {
		//Nếu liên tục bấm -> tăng frame
		if (frame >= 0) {
			++frame;
		}
	}
	else { //Nếu không bấm thì giữ frame = 0
		frame = 0;
	}
	if (input_type.jump == 1) {
		frame = 0;
	}
	//Nếu như chạy hết 6 frame rồi -> quay lại
	if (frame / 6 >= 6) {
		frame = 0;
	}

	rect.x = xpos;
	rect.y = ypos;

	SDL_Rect* currentclip = &FRAME_CLIP[frame / 6];
	SDL_Rect renderQuad = { rect.x,rect.y,widthframe * 3,heightframe * 3 };

	if (currentclip != NULL)
	{
		renderQuad.w = 3 * currentclip->w;
		renderQuad.h = 3 * currentclip->h;
	}

	SDL_RenderCopy(des, texture, currentclip, &renderQuad);
}

//Receive keyboard input and manage the player's state


void Player::handleEvent1(SDL_Event e, SDL_Renderer* renderer, Mix_Chunk* sound[5])
{
	if (e.type == SDL_KEYDOWN) { //nhan phim
		switch (e.key.keysym.sym) {
		case SDLK_RIGHT:
			status = WALK_RIGHT;
			input_type.stayleft = 0;
			input_type.stayright = 0;
			input_type.right = 1;
			input_type.left = 0;

			UpdateImgPlayer1(renderer);
			break;

		case SDLK_LEFT:
			status = WALK_LEFT;
			input_type.stayleft = 0;
			input_type.stayright = 0;
			input_type.left = 1;
			input_type.right = 0;

			UpdateImgPlayer1(renderer);

			break;
		case SDLK_UP:
			if (onground ) {
				Mix_PlayChannel(-1, sound[0], 0);
				input_type.jump = 1;
				input_type.stayleft = 0;
				input_type.stayright = 0;
			}
			break;
		default:
			break;
		}
	}
	else if (e.type == SDL_KEYUP) { //nha phim
		switch (e.key.keysym.sym) {
		case SDLK_RIGHT:
			status = STAY_RIGHT;
			if (onground == true) {
				input_type.stayright = 1;
				input_type.right = 0;
				input_type.stayleft = 0;
			}
			input_type.right = 0;
			input_type.stayleft = 0;

			UpdateImgPlayer1(renderer);

			break;
		case SDLK_LEFT:
			status = STAY_LEFT;
			if (onground == true) {
				input_type.stayleft = 1;
				input_type.left = 0;
				input_type.stayright = 0;
			}
			input_type.left = 0;
			input_type.stayright = 0;

			UpdateImgPlayer1(renderer);

			break;
		default:
			break;
		}
	}
}

void Player::resetMove() {
	input_type.stayleft = 0;
	input_type.stayright = 0;
	input_type.right = 0;
	input_type.left = 0;
}

void Player::handleEvent2(SDL_Event e,SDL_Renderer* renderer,Mix_Chunk* sound[5]) {
	if (e.type == SDL_KEYDOWN) {
		switch (e.key.keysym.sym) {
		case SDLK_d:
			status = WALK_RIGHT;
			input_type.stayleft = 0;
			input_type.stayright = 0;
			input_type.right = 1;
			input_type.left = 0;

			UpdateImgPlayer2(renderer);
			break;

		case SDLK_a:
			status = WALK_LEFT;
			input_type.stayleft = 0;
			input_type.stayright = 0;
			input_type.left = 1;
			input_type.right = 0;

			UpdateImgPlayer2(renderer);

			break;
		case SDLK_w:
			status = JUMP;
			if (onground) {
				Mix_PlayChannel(-1, sound[0], 0);
				input_type.jump = 1;
				input_type.stayleft = 0;
				input_type.stayright = 0;
			}

			break;
		default:

			break;
		}
	}
	else if (e.type == SDL_KEYUP) {
		switch (e.key.keysym.sym) {
		case SDLK_d:
			status = STAY_RIGHT;
			if (onground == true) {
				input_type.stayright = 1;
				input_type.right = 0;
				input_type.stayleft = 0;
			}
			input_type.right = 0;
			input_type.stayleft = 0;

			UpdateImgPlayer2(renderer);

			break;
		case SDLK_a:
			status = STAY_LEFT;
			if (onground == true) {
				input_type.stayleft = 1;
				input_type.left = 0;
				input_type.stayright = 0;
			}
			input_type.left = 0;
			input_type.stayright = 0;

			UpdateImgPlayer2(renderer);

			break;
		default:
			break;
		}
	}

}

 //ham xử lí chuyển động - movement
void Player::DoPlayer1(Map& mapdata, int p) {
	xval = 0;
	 //Khi y_val_ cộng lên dần thì nhân vật rơi dần từ trên xuống
    //Tốc độ rơi
	yval += GRAVITY_SPEED;

	if (yval >= MAX_FALL_SPEED) {
		yval = MAX_FALL_SPEED;
	}
	if (input_type.left == 1) {
		xval -= PLAYER_SPEED;
	}
	if (input_type.right == 1) {
		xval += PLAYER_SPEED;
	}
	if (input_type.jump == 1) {
		if (onground==true) {
			yval -= JUMP_VAL;
		}
		onground = false;

		input_type.jump = 0;
	}
	//Để đứng trên đất mà không rơi qua đất 
	CheckToMap1(mapdata);
	//CheckToFish(mapdata);

}


void Player::DoPlayer2(Map& mapdata, int p) {
	xval = 0;
	yval += GRAVITY_SPEED;

	if (yval >= MAX_FALL_SPEED) {
		yval = MAX_FALL_SPEED;
	}
	if (input_type.left == 1) {
		xval -= PLAYER_SPEED;
	}
	if (input_type.right == 1) {
		xval += PLAYER_SPEED;
	}
	if (input_type.jump == 1) {
		if (onground == true) {
			yval -= JUMP_VAL;
		}
		onground = false;

		input_type.jump = 0;
	}

	CheckToMap2(mapdata);
	//CheckToFish(mapdata);

}

//Check for player-map collisions  //Check va cham voi map
void Player::CheckToMap1(Map& mapdata) {
	//gioi han ktra theo chieu x1 -> x2
	int x1 = 0;
	int x2 = 0;

	int y1 = 0;
	int y2 = 0;

	/*
        x1,y1********x2,y1
        *               *
        *               *
        *               *
        x1,y2********x2,y2
    */

	//check horizontal - chieu ngang - nvat dang nam tu o thu bao nhieu den o thu bnhiu cua map 
	int height_min = (heightframe * 3 < TILE_SIZE ? heightframe * 3 : TILE_SIZE);
	//Xác định Ô BẮT ĐẦU mà nhân vật đang đứng
	x1 = (xpos+xval+10)/TILE_SIZE;
	x2 = (xpos + xval + widthframe*3 -10)/ TILE_SIZE;

	y1 = (ypos+30) / TILE_SIZE;
	y2 = (ypos + height_min +20) / TILE_SIZE;

	//Kiểm tra xem có đang nằm trong bản đồ không
	if (x1 >= 0 && x2 < MAP_MAP_X && y1 >= 0 && y2 < MAP_MAP_Y) {
		if (xval > 0) // nếu sang phải
		{

			if (mapdata.tile[y1][x2] == PINK_FISH) {
				mapdata.tile[y1][x2] = 0;
				PinkFish_Player1();
			}
			if (mapdata.tile[y2][x2] == PINK_FISH) {
				mapdata.tile[y2][x2] = 0;
				PinkFish_Player1();
			}
			if (mapdata.tile[y1][x2] == BLACK_FISH) {
				mapdata.tile[y1][x2] = 0;
				BlackFish_Player1();
			}
			if (mapdata.tile[y2][x2] == BLACK_FISH) {
				mapdata.tile[y2][x2] = 0;
				BlackFish_Player1();
			}

			else if (mapdata.tile[y1][x2] == BLACK_LIQUID || mapdata.tile[y2][x2] == BLACK_LIQUID) gameoverState = 1;
			else if (mapdata.tile[y1][x2] == POISON || mapdata.tile[y2][x2] == POISON) gameoverState = 1;
			else if (mapdata.tile[y1][x2] == PINK_LIQUID && mapdata.tile[y2][x2] == PINK_LIQUID) {}
			else {
				if ((mapdata.tile[y1][x2] != BLANK_TILE || mapdata.tile[y2][x2] != BLANK_TILE)) {
					xpos = (x2)*TILE_SIZE;
					xpos -= widthframe * 3 - 10;
					xval = 0;
				}
			}
		}
		else if (xval < 0) //player move to the left
		{

			if (mapdata.tile[y2][x1] == PINK_FISH ) {
				mapdata.tile[y2][x1] = 0;
				PinkFish_Player1();
			}
			else if (mapdata.tile[y1][x1]==PINK_FISH) {
				mapdata.tile[y1][x1] = 0;
				PinkFish_Player1();
			}
			else if (mapdata.tile[y1][x1] == BLACK_FISH  )
			{
                mapdata.tile[y1][x1] = 0;
                BlackFish_Player1();
			}
			else if (mapdata.tile[y2][x1] == BLACK_FISH)
            {
                mapdata.tile[y2][x1]=0;
                BlackFish_Player1();
            }

			else if (mapdata.tile[y1][x1] == BLACK_LIQUID || mapdata.tile[y2][x1] == BLACK_LIQUID) gameoverState = 1;
			else if (mapdata.tile[y1][x1] == POISON || mapdata.tile[y2][x1] == POISON) gameoverState = 1;
			else if (mapdata.tile[y1][x1] == PINK_LIQUID || mapdata.tile[y2][x1] == PINK_LIQUID)
			{}
			else {
				if (mapdata.tile[y1][x1] != BLANK_TILE || mapdata.tile[y2][x1] != BLANK_TILE) {
					xpos = (x1)*TILE_SIZE + 20;
					xval = 0;
				}
			}
		}

	}
	//check vertical - chiều dọc
	int width_min = widthframe*3< TILE_SIZE ? widthframe*3 : TILE_SIZE;
	x1 = (xpos+25) / TILE_SIZE;
	x2 = (xpos + width_min+40) / TILE_SIZE;

	y1 = (ypos + yval) / TILE_SIZE;
	y2 = (ypos + yval + heightframe*3 -17) / TILE_SIZE;

	if (x1 >= 0 && x2 < MAP_MAP_X && y1 >= 0 && y2 < MAP_MAP_Y) {
		if (yval > 0) //check movement by gravity force - rơi tự do
		{
			if (mapdata.tile[y2][x2] == PINK_FISH) {
				mapdata.tile[y2][x2] = 0;
				PinkFish_Player1();
			}
			else if (mapdata.tile[y2][x1] == PINK_FISH) {
				mapdata.tile[y2][x1] = 0;
				PinkFish_Player1();
			}
			else if (mapdata.tile[y2][x1] == BLACK_FISH)
			{
                mapdata.tile[y2][x1] = 0;
                BlackFish_Player1();
			}
			else if (mapdata.tile[y2][x2] == BLACK_FISH)
            {
                mapdata.tile[y2][x2] = 0;
                BlackFish_Player1();
            }
			else if (mapdata.tile[y2][x1] == BLACK_LIQUID || mapdata.tile[y2][x2] == BLACK_LIQUID) gameoverState = 1;
			else if (mapdata.tile[y2][x1] == POISON || mapdata.tile[y2][x2] == POISON) gameoverState = 1;
			else if (mapdata.tile[y2][x1] == PINK_LIQUID && mapdata.tile[y2][x2] == PINK_LIQUID) {}
			else {
				if (mapdata.tile[y2][x1] != BLANK_TILE || mapdata.tile[y2][x2] != BLANK_TILE) {
					ypos = y2 * TILE_SIZE;
					ypos -= heightframe * 3 - 17;
					yval = 0;
					onground = true;
				}
			}
		}
		else if (yval < 0) //PLAYER JUMPS
		{

			if (mapdata.tile[y1][x2] == PINK_FISH) {
				mapdata.tile[y1][x2] = 0;
				PinkFish_Player1();
			}
			else if (mapdata.tile[y1][x1] == PINK_FISH) {
				mapdata.tile[y1][x1] = 0;
				PinkFish_Player1();
			}
			else if (mapdata.tile[y1][x1] == BLACK_FISH)
			{
			    mapdata.tile[y1][x1] = 0;
			    BlackFish_Player1();
			}
			else if (mapdata.tile[y1][x2] == BLACK_FISH)
            {
                mapdata.tile[y1][x2] = 0;
                BlackFish_Player1();
            }
			else if (mapdata.tile[y1][x2] == BLACK_LIQUID&& mapdata.tile[y1][x1] == BLACK_LIQUID) gameoverState = 1;
			else if (mapdata.tile[y1][x2] == POISON && mapdata.tile[y1][x1] == POISON) gameoverState = 1;

			else if (mapdata.tile[y1][x1] == PINK_LIQUID || mapdata.tile[y1][x2] == PINK_LIQUID) {}
			else{
			if (mapdata.tile[y1][x1] != BLANK_TILE || mapdata.tile[y1][x2] != BLANK_TILE) {
				ypos = (y1)*TILE_SIZE+5;
				yval = 0;
				}
			}
		}
	}

	xpos += xval;
	ypos += yval;
	if (xpos < 0) {
		xpos = 0;
	}
	else if ((xpos + widthframe*3) > mapdata.maxx) {
		xpos = mapdata.maxx - widthframe*3 -1;
	}

	if (ypos < 0) {
		ypos = 0;
	}
}

//Score calculations
void Player::PinkFish_Player1() {
	pinkfish1 +=10;
}
void Player::BlackFish_Player1(){
    blackfish1 -= 15;
}


void Player::CheckToMap2(Map& mapdata) {
	int x1 = 0;
	int x2 = 0;

	int y1 = 0;
	int y2 = 0;


	//check horizontal
	int height_min = (heightframe * 3 < TILE_SIZE ? heightframe * 3 : TILE_SIZE);

	x1 = (xpos + xval + 10) / TILE_SIZE;
	x2 = (xpos + xval + widthframe * 3 - 10) / TILE_SIZE;

	y1 = (ypos + 30) / TILE_SIZE;
	y2 = (ypos + height_min + 20) / TILE_SIZE;

	if (x1 >= 0 && x2 < MAP_MAP_X && y1 >= 0 && y2 < MAP_MAP_Y) {
		if (xval > 0) //player moves to the right
		{

			if (mapdata.tile[y1][x2] == BLACK_FISH) {
				mapdata.tile[y1][x2] = 0;
				BlackFish_Player2();
			}
			else if (mapdata.tile[y2][x2] == BLACK_FISH) {
				mapdata.tile[y2][x2] = 0;
				BlackFish_Player2();
			}
			else if (mapdata.tile[y1][x2] == PINK_FISH )
			{
			    mapdata.tile[y1][x2] = 0;
			    PinkFish_Player2();
			}
			else if (mapdata.tile[y2][x2] == PINK_FISH)
            {
                mapdata.tile[y2][x2] = 0;
			    PinkFish_Player2();
            }
			else if (mapdata.tile[y2][x2] == PINK_LIQUID) gameoverState = 1;
			else if (mapdata.tile[y2][x2] == POISON) gameoverState = 1;
			else if (mapdata.tile[y1][x2] == BLACK_LIQUID || mapdata.tile[y2][x2] == BLACK_LIQUID){}
			else if (mapdata.tile[y2][x2] == PINK_FISH)
            {
                mapdata.tile[y2][x2] = 0;
			    PinkFish_Player2();
            }

			else {
				if ((mapdata.tile[y1][x2] != BLANK_TILE || mapdata.tile[y2][x2] != BLANK_TILE)) {
					xpos = (x2)*TILE_SIZE;
					xpos -= widthframe * 3 - 10;
					xval = 0;
				}
			}
		}
		else if (xval < 0) //player moves to the left
		{

			if (mapdata.tile[y2][x1] == BLACK_FISH) {
				mapdata.tile[y2][x1] = 0;
				BlackFish_Player2();
			}
			else if (mapdata.tile[y1][x1] == BLACK_FISH) {
				mapdata.tile[y1][x1] = 0;
				BlackFish_Player2();
			}

			else if (mapdata.tile[y1][x1] == PINK_FISH )
			{
			    mapdata.tile[y1][x1] = 0;
				PinkFish_Player2();
			}
			else if (mapdata.tile[y2][x1] == PINK_FISH)
            {
                mapdata.tile[2][x1] = 0;
				PinkFish_Player2();
            }
			else if (mapdata.tile[y2][x1] == PINK_LIQUID ) gameoverState = 1;
			else if (mapdata.tile[y2][x1] == POISON ) gameoverState = 1;
			else if (mapdata.tile[y2][x1] == BLACK_LIQUID ){}
			else {
				if (mapdata.tile[y1][x1] != BLANK_TILE || mapdata.tile[y2][x1] != BLANK_TILE) {
					xpos = (x1)*TILE_SIZE + 20;
					xval = 0;
				}
			}
		}
	}
	//check vertical
	int width_min = widthframe * 3 < TILE_SIZE ? widthframe * 3 : TILE_SIZE;
	x1 = (xpos + 25) / TILE_SIZE;
	x2 = (xpos + width_min + 40) / TILE_SIZE;

	y1 = (ypos + yval) / TILE_SIZE;
	y2 = (ypos + yval + heightframe * 3 - 17) / TILE_SIZE;

	if (x1 >= 0 && x2 < MAP_MAP_X && y1 >= 0 && y2 < MAP_MAP_Y) {
		if (yval > 0) //check movement by gravity force
		{

			if (mapdata.tile[y2][x2] == PINK_FISH) {
				mapdata.tile[y2][x2] = 0;
				PinkFish_Player2();
			}
			else if (mapdata.tile[y2][x1] == PINK_FISH) {
				mapdata.tile[y2][x1] = 0;
				PinkFish_Player2();
			}

			if (mapdata.tile[y2][x2] == BLACK_FISH) {
				mapdata.tile[y2][x2] = 0;
				BlackFish_Player2();
			}
			else if (mapdata.tile[y2][x1] == BLACK_FISH) {
				mapdata.tile[y2][x1] = 0;
				BlackFish_Player2();

			}

			
			else if (mapdata.tile[y2][x2] == PINK_LIQUID || mapdata.tile[y2][x1] == PINK_LIQUID) gameoverState = 1;
			else if (mapdata.tile[y2][x2] == POISON || mapdata.tile[y2][x1] == POISON) gameoverState = 1;
			else if (mapdata.tile[y2][x2] == BLACK_LIQUID && mapdata.tile[y2][x1] == BLACK_LIQUID) {}
			else {
				if (mapdata.tile[y2][x1] != BLANK_TILE || mapdata.tile[y2][x2] != BLANK_TILE) {
					ypos = y2 * TILE_SIZE;
					ypos -= heightframe * 3 - 17;
					yval = 0;
					onground = true;
				}
			}
		}
		else if (yval < 0) //player jumps
		{

			if (mapdata.tile[y1][x2] == BLACK_FISH) {
				mapdata.tile[y1][x2] = 0;
				BlackFish_Player2();
			}
			else if (mapdata.tile[y1][x1] == BLACK_FISH) {
				mapdata.tile[y1][x1] = 0;
				BlackFish_Player2();
			}
			else if (mapdata.tile[y1][x1] == PINK_FISH )
			{
			    mapdata.tile[y1][x1] = 0;
			    PinkFish_Player2();
			}
			else if (mapdata.tile[y1][x2] == PINK_FISH)
            {
                mapdata.tile[y1][x2] = 0;
                PinkFish_Player2();
            }
			
			else if (mapdata.tile[y1][x1] == PINK_LIQUID || mapdata.tile[y1][x2] == PINK_LIQUID) gameoverState = 1;
			else if (mapdata.tile[y1][x1] == POISON || mapdata.tile[y1][x2] == POISON) gameoverState = 1;
			else if (mapdata.tile[y1][x1] == BLACK_LIQUID || mapdata.tile[y1][x2] == BLACK_LIQUID) {}
			else {
				if (mapdata.tile[y1][x1] != BLANK_TILE || mapdata.tile[y1][x2] != BLANK_TILE) {
					ypos = (y1)*TILE_SIZE + 5;
					yval = 0;
				}
			}
		}
	}


	xpos += xval;
	ypos += yval;
	if (xpos < 0) {
		xpos = 0;
	}
	else if ((xpos + widthframe * 3) > mapdata.maxx) {
		xpos = mapdata.maxx - widthframe * 3 - 1;
	}

	if (ypos < 0) {
		ypos = 0;
	}

}

//score
void Player::PinkFish_Player2() {

	pinkfish2 -=15;
}
void Player::BlackFish_Player2(){
    blackfish2 +=10 ;

}



//update status
void Player::UpdateImgPlayer1(SDL_Renderer* des) {
	if (onground) {
		if (input_type.left==1) {
			LoadImg("./assets/player1left.png", des);
		}
		else if (input_type.right==1) {
			LoadImg("./assets/player1.png", des);
		}
		else if (status == STAY_LEFT && input_type.jump == 0&&input_type.left==0&&input_type.right==0) {
			LoadImg("./assets/stayleft.png",des);
		}
		else if (status == STAY_RIGHT && input_type.jump == 0 && input_type.left == 0 && input_type.right == 0) {
			LoadImg("./assets/stayright.png",des);
		}

	}
	else {
		if (input_type.left == 1) {
		LoadImg("./assets/jumpleft.png", des);
		}
		else if (input_type.right == 1) {
		LoadImg("./assets/jumpright.png", des);
		}
	}
}

void Player::UpdateImgPlayer2(SDL_Renderer* des) {
	if (onground) {
		if (input_type.left == 1) {
			LoadImg("./assets/player2left.png", des);
		}
		else if (input_type.right == 1) {
			LoadImg("./assets/player2.png", des);
		}
		else if (status == STAY_LEFT && input_type.jump == 0 && input_type.left == 0 && input_type.right == 0) {
			LoadImg("./assets/player2stayleft.png", des);
		}
		else if (status == STAY_RIGHT && input_type.jump == 0 && input_type.left == 0 && input_type.right == 0) {
			LoadImg("./assets/player2stayright.png", des);
		}
	}
	else {
		if (input_type.left == 1) {
			LoadImg("./assets/darkjumpleft.png", des);
		}
		else if (status == WALK_RIGHT) {
			LoadImg("./assets/darkjumpright.png", des);
		}
	}

}

//check va cham voi mus
void Player::CheckToMus(int p, OtherObj &mushroom) {

	int x1 = 0;
	int x2 = 0;

	int y1 = 0;
	int y2 = 0;

	bool checkCollision = false;
	int x1B = mushroom.Get_ObjPosx();
	int x2B = mushroom.Get_ObjPosx() + 32 * 3;
	int y1B = mushroom.Get_ObjPosy();
	int y2B = mushroom.Get_ObjPosy() + 32 * 3;
	//check chieu ngang
	int height_min = (heightframe * 3 < TILE_SIZE ? heightframe * 3 : TILE_SIZE);

	x1 = (xpos + xval + 0);
	x2 = (xpos + xval + widthframe * 3 - 30);

	y1 = (ypos + 20);
	y2 = (ypos + height_min + 20);

	if (x1 / TILE_SIZE >= 0 && x2 / TILE_SIZE < MAP_MAP_X && y1 / TILE_SIZE >= 0 && y2 / TILE_SIZE < MAP_MAP_Y) {
		if (x2 >= x1B && y2 >= y1B && x2 <= x2B && y2 <= y2B ||
			x1 >= x1B && y1 >= y1B && x1 <= x2B && y1 <= y2B ||
			x2 >= x1B && y1 >= y1B && x2 <= x2B && y1 <= y2B ||
			x1 >= x1B && y2 >= y1B && x1 <= x2B && y2 <= y2B
			) {
			checkCollision = true;
		}

		//If none of the sides from A are outside B\true;
		if (checkCollision) {
			if (xval > 0) {
				xpos = x2 + 80;
				xpos -= widthframe * 3 + 56;
				xval = 0;

			}
			else if (xval < 0) {
				xpos = x1 + 7;
				xval = 0;
			}
		}
	}
	//check chieu doc
	int width_min = widthframe * 3 < TILE_SIZE ? widthframe * 3 : TILE_SIZE;
	x1 = (xpos + 60);
	x2 = (xpos + width_min - 40);

	y1 = (ypos + yval);
	y2 = (ypos + yval + heightframe * 3 - 40);

	if (x1 / TILE_SIZE >= 0 && x2 / TILE_SIZE < MAP_MAP_X && y1 / TILE_SIZE >= 0 && y2 / TILE_SIZE < MAP_MAP_Y) {
		if (x2 >= x1B && y2 >= y1B && x2 <= x2B && y2 <= y2B) {
			checkCollision = true;
		}
		else if (x1 >= x1B && y1 >= y1B && x1 <= x2B && y1 <= y2B) {
			checkCollision = true;
		}
		else if (x2 >= x1B && y1 >= y1B && x2 <= x2B && y1 <= y2B) {
			checkCollision = true;
		}
		else if (x1 >= x1B && y2 >= y1B && x1 <= x2B && y2 <= y2B) {
			checkCollision = true;
		}
		else checkCollision = false;
		if (yval > 0) {
			if (checkCollision) {
				ypos = y2;
				ypos -= heightframe * 3 - 17;
				yval = -6;
			}
		}
		else if (yval < 0) {

			if (checkCollision) {
				ypos = y1 + 10;
				yval = 0;
			}
		}


	}
}

//Check va cham voi gate
void Player::CheckToGate(int p, OtherObj &gate_)
{

	int x1 = 0;
	int x2 = 0;

	int y1 = 0;
	int y2 = 0;

    bool checkCollision = false;
    int x1B = gate_.Get_ObjPosx();
    int x2B = gate_.Get_ObjPosx() + 32*3;
    int y1B = gate_.Get_ObjPosy();
    int y2B = gate_.Get_ObjPosy() + 32*3;
	
    //check chiều ngang
	int height_min = (heightframe * 3 < TILE_SIZE ? heightframe * 3 : TILE_SIZE);

	x1 = (xpos+xval+30);
	x2 = (xpos + xval + widthframe*3 -30);

	y1 = (ypos+20) ;
	y2 = (ypos + height_min +20) ;

	if (x1/TILE_SIZE >= 0 && x2/TILE_SIZE < MAP_MAP_X && y1/TILE_SIZE >= 0 && y2/TILE_SIZE < MAP_MAP_Y) {
             if(x2>=x1B&&y2>=y1B&&x2<=x2B&&y2<=y2B||
                x1>=x1B&&y1>=y1B&&x1<=x2B&&y1<=y2B||
                x2>=x1B&&y1>=y1B&&x2<=x2B&&y1<=y2B||
                x1>=x1B&&y2>=y1B&&x1<=x2B&&y2<=y2B
                )
                {
                    checkCollision=true;
                }
				if (checkCollision) {
					nextLevelPlayer[p] = true;
				}
				else nextLevelPlayer[p] = false;
		}
	//check chiều dọc
	int width_min = widthframe*3< TILE_SIZE ? widthframe*3 : TILE_SIZE;
	x1 = (xpos+60) ;
	x2 = (xpos + width_min-40) ;

	y1 = (ypos + yval) ;
	y2 = (ypos + yval + heightframe*3 -40) ;

	if (x1/TILE_SIZE >= 0 && x2/TILE_SIZE < MAP_MAP_X && y1/TILE_SIZE >= 0 && y2/TILE_SIZE < MAP_MAP_Y) {
                if(x2>=x1B&&y2>=y1B&&x2<=x2B&&y2<=y2B){
                    checkCollision=true;
                }
                else if(x1>=x1B&&y1>=y1B&&x1<=x2B&&y1<=y2B){
                    checkCollision=true;
                }
                else if(x2>=x1B&&y1>=y1B&&x2<=x2B&&y1<=y2B){
                    checkCollision=true;
                }
                else if(x1>=x1B&&y2>=y1B&&x1<=x2B&&y2<=y2B){
                    checkCollision=true;
                }
                else checkCollision=false;
    if(yval<0){
    if (checkCollision) {
            nextLevelPlayer[p] = true;
			}
		}
	}
}

bool Player::isEating_fish(Map& mapdata) {  //xu li am thanh cho su kien
	int x1 = 0;
	int x2 = 0;
	int y1 = 0;
	int y2 = 0;
	int height_min = (heightframe * 3 < TILE_SIZE ? heightframe * 3 : TILE_SIZE);

	x1 = (xpos+xval+10)/TILE_SIZE;
	x2 = (xpos + xval + widthframe*3 -10)/ TILE_SIZE;

	y1 = (ypos+30) / TILE_SIZE;
	y2 = (ypos + height_min +20) / TILE_SIZE;

	if (x1 >= 0 && x2 < MAP_MAP_X && y1 >= 0 && y2 < MAP_MAP_Y) {
		if (xval > 0)
		{
            if (mapdata.tile[y1][x2] == PINK_FISH  || mapdata.tile[y2][x2] == PINK_FISH) {
				isEatingFish = true;
			}
			else if (mapdata.tile[y1][x2] == BLACK_FISH || mapdata.tile[y2][x2] == BLACK_FISH)
			{
			    isEatingFish = true;
			}
			else
            {
                isEatingFish = false;
            }

		}
		else if (xval < 0)
		{

			if (mapdata.tile[y2][x1] == PINK_FISH  || mapdata.tile[y1][x1] == PINK_FISH) {
				isEatingFish = true;
			}
			else if (mapdata.tile[y2][x1] == BLACK_FISH || mapdata.tile[y1][x1] == BLACK_FISH)
			{
			    isEatingFish = true;
			}
			else
            {
                isEatingFish = false;
            }
		}
		if(isEatingFish) Mix_PlayChannel(1, sound[1], 0);
	}

	int width_min = widthframe*3< TILE_SIZE ? widthframe*3 : TILE_SIZE;
	x1 = (xpos+25) / TILE_SIZE;
	x2 = (xpos + width_min+40) / TILE_SIZE;

	y1 = (ypos + yval) / TILE_SIZE;
	y2 = (ypos + yval + heightframe*3 -17) / TILE_SIZE;

	if (x1 >= 0 && x2 < MAP_MAP_X && y1 >= 0 && y2 < MAP_MAP_Y) {
		if (yval > 0) 
		{
			if (mapdata.tile[y2][x2] == PINK_FISH  || mapdata.tile[y2][x1] == PINK_FISH) {
				isEatingFish = true;
			}
			else if (mapdata.tile[y2][x1] == BLACK_FISH || mapdata.tile[y2][x2] == BLACK_FISH)
			{
			    isEatingFish = true;
			}
			else
            {
                isEatingFish = false;
            }

		}
		else if (yval < 0) 
		{

			if (mapdata.tile[y1][x1] == PINK_FISH  || mapdata.tile[y1][x2] == PINK_FISH) {
				isEatingFish = true;
			}
			else if (mapdata.tile[y1][x1] == BLACK_FISH || mapdata.tile[y1][x2] == BLACK_FISH)
			{
			    isEatingFish = true;
			}
			else
            {
                isEatingFish = false;
            }

		}
		if(isEatingFish) Mix_PlayChannel(1, sound[1], 0);
	}
	return isEatingFish;
}










        




