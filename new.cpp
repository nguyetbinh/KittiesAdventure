#include <SDL.h>
#include<string>
#include<SDL_image.h>
#include <bits/stdc++.h>
using namespace std;

const int SCREEN_WIDTH = 1011;
const int SCREEN_HEIGHT = 370;
const string WINDOW_TITLE = "SDL test";

SDL_Texture* loadTexture(string path, SDL_Renderer* renderer);

void logSDLError(std::ostream& os, const std::string &msg, bool fatal);

void initSDL(SDL_Window* &window, SDL_Renderer* &renderer);

void quitSDL(SDL_Window* window, SDL_Renderer* renderer);

void waitUntilKeyPressed();




int main(int argv, char** args)
{
    //Create game screen
    SDL_Renderer* renderer;
    SDL_Window* window;
    SDL_Texture* texture = NULL;
    initSDL(window, renderer);
    SDL_RenderClear(renderer);

    //main program
    SDL_Texture* bg = loadTexture("./assets/img/bg.png", renderer);
   
    SDL_Texture* char1 = loadTexture("./assets/img/char1.png", renderer);
    SDL_Texture* char2 = loadTexture("./assets/img/char2.png", renderer);
    SDL_Rect charRect = { 50, 200, 127/3, 197/3};
    bool running = 1;
    int n = 0;
    bool isJumping = false;
    int vx = 0;
    int vy = -5;
    int ay = 1;
    while(running){
        SDL_RenderCopy(renderer,bg, NULL, NULL);
        SDL_Event event;
        while(SDL_PollEvent(&event)){
                if(event.type == SDL_QUIT){
                running = 0;
                quitSDL(window, renderer);
               } 
               if(event.type == SDL_KEYDOWN)
                switch(event.key.keysym.sym){
                    case SDLK_RIGHT:
                        charRect.x += 5;
                        n++;
                        break;

                    case SDLK_LEFT:
                        charRect.x -= 5;
                        n--;
                        break;

                    case SDLK_SPACE:
                        if (!isJumping) {
                                isJumping = true;
                                vy = -10;
                                vx = 10;
                            }
                        break;
                }
        }
                    // Nếu đang nhảy
                   if (isJumping) {
                    charRect.y += vy;

                 vy += ay;
                //vx -= ay;
            if (charRect.y >= 200) {
                charRect.y = 200;
                vy = -10;
                isJumping = false;
            }
        }
                        if(n % 2 == 0) SDL_RenderCopy(renderer, char1, NULL, &charRect);
                        else SDL_RenderCopy(renderer, char2, NULL, &charRect);
                        SDL_RenderPresent(renderer);
    }

    SDL_RenderPresent(renderer);

    //Quit game
    waitUntilKeyPressed();
    quitSDL(window, renderer);

	return 0;
}
SDL_Texture* loadTexture(string path, SDL_Renderer* renderer){
    SDL_Texture* newTexture = nullptr;
    SDL_Surface* loadedSurface = IMG_Load(path.c_str());
    if(loadedSurface == nullptr){
        cout<<"Unable to  load image " << path << " SDL_image Error: "
        << IMG_GetError() << endl;
    }
    else{
        newTexture = SDL_CreateTextureFromSurface(renderer, loadedSurface);
        if(newTexture == nullptr)
            cout<<"Unable to create texture from " << path << " SDL Error: "
                << SDL_GetError()<< endl;
                SDL_FreeSurface( loadedSurface);
    }
    return newTexture;
}
void logSDLError(std::ostream& os, const std::string &msg, bool fatal)
{
    os << msg << " Error: " << SDL_GetError() << std::endl;
    if (fatal) {
        SDL_Quit();
        exit(1);
    }
}
void initSDL(SDL_Window* &window, SDL_Renderer* &renderer)
{
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
        logSDLError(std::cout, "SDL_Init", true);

    window = SDL_CreateWindow(WINDOW_TITLE.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    //window = SDL_CreateWindow(WINDOW_TITLE.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_FULLSCREEN_DESKTOP);

    if (window == nullptr)
        logSDLError(std::cout, "CreateWindow", true);

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    //SDL_Renderer *renderer = SDL_CreateSoftwareRenderer(SDL_GetWindowSurface(window));
    if (renderer == nullptr)
        logSDLError(std::cout, "CreateRenderer", true);

    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");
    SDL_RenderSetLogicalSize(renderer, SCREEN_WIDTH, SCREEN_HEIGHT);
}

void quitSDL(SDL_Window* window, SDL_Renderer* renderer)
{
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
}
void waitUntilKeyPressed()
{
    SDL_Event e;
    while (true) {
        if ( SDL_WaitEvent(&e) != 0 &&
             ( e.type == SDL_QUIT) )
            return;
        SDL_Delay(100);

    }
}
    
