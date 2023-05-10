#pragma once
#include "CommonFunction.h"
using namespace std;
class Text
{
public:
    Text();
    ~Text();

    enum TextColor {
		WHITE=0,
		BLACK=1,
		PINK=2,

	};
	// lấy chữ
	bool LoadFont(TTF_Font* font, SDL_Renderer* renderer);

	void Free();
	// set màu
	void SetColor(Uint8 red, Uint8 green, Uint8 blue);
	void SetColor(int color);
	//xuất chữ
	void RenderText(SDL_Renderer* renderer, int xpos, int ypos, SDL_Rect* clip=NULL,double angle = 0.0,SDL_Point* center=NULL,SDL_RendererFlip flip=SDL_FLIP_NONE);
	void SetRect(const int& xp,const int& yp);
	SDL_Rect GetRect() const;

	int getwidth() { return wtext; };
	int getheight() { return htext; };

	void SetText(const string& text) {
		str = text;
	}
	string GetText() const{
		return str;
	}



private:
	SDL_Rect rec;
	string str;
	SDL_Color textcolor;
	SDL_Texture* texture;
	int xtext;
	int ytext;
	int wtext;
	int htext;
};

