#include "game.h"

Game::Game(){
    //ctor
}

Game::~Game(){
    //dtor
}

void Game::setScreenWigth(int& value){
    screenWigth = value;
}

void Game::setScreenHeight(int& value){
    screenHeight = value;
}

void Game::setIsRunning(bool value){
    isRunning = value;
}

void Game::setWindow(SDL_Window* value){
    window = value;
}

void Game::setRenderer(SDL_Renderer* value){
    renderer = value;
}

int Game::getScreenWight() const{
    return screenWigth;
}

int Game::getScreenHeight() const{
    return screenHeight;
}

bool Game::getIsRunning() const{
    return isRunning;
}

SDL_Window* Game::getWindow() const{
    return window;
}

SDL_Renderer* Game::getRenderer() const{
    return renderer;
}

void Game::init(const char* title, int w, int h, bool fullScreen){
    int flag = 0;
    if(fullScreen){
        flag = SDL_WINDOW_FULLSCREEN;
    }

    if(SDL_Init(SDL_INIT_EVERYTHING) == 0){
        screenWigth = w;
        screenHeight = h;

        window = SDL_CreateWindow(title,
                                  SDL_WINDOWPOS_CENTERED,
                                  SDL_WINDOWPOS_CENTERED,
                                  screenWigth,
                                  screenHeight,
                                  flag);

        renderer = SDL_CreateRenderer(window, -1, 0);
        if(renderer){
            SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
            SDL_RenderPresent(renderer);
            isRunning = true;
        }else{
            std::cout<<"Couldn't initialize the renderer"<<SDL_GetError();
        }
    }
}













