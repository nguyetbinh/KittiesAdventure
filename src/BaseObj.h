#pragma once
#include "CommonFunction.h"

using namespace std;
class BaseObj
{
public:
	BaseObj();
	~BaseObj();
	void SetRect(const int& x, const int& y) {
		rect.x = x;
		rect.y = y;
	}
	SDL_Rect getRect() const {
		return rect;
	}
	SDL_Texture* gettexture() const {
		return texture;
	}
	 //VIRTUAL để có thể tái sử dụng mà không cần đúng phải là đối tượng trong class đó
	virtual bool LoadImg(string path, SDL_Renderer* screen);
	void Render(SDL_Renderer* des, const SDL_Rect* clip = NULL);
	void Free();

protected:
	SDL_Texture* texture;  //Biến sử dụng để lưu trữ hình ảnh
	SDL_Rect rect; //Biến sử dụng để lưu trữ kích thước ảnh

};


