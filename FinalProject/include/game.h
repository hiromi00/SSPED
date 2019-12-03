#ifndef GAME_H
#define GAME_H

#include <iostream>
#include "SDL2/SDL.h"


class Game{
    public:
        Game();
        virtual ~Game();

        void setScreenWigth(int &value);
        void setScreenHeight(int &value);
        void setIsRunning(bool value);
        void setWindow(SDL_Window* value);
        void setRenderer(SDL_Renderer* value);

        int getScreenWight()const;
        int getScreenHeight()const;
        bool getIsRunning()const;
        SDL_Window* getWindow()const;
        SDL_Renderer* getRenderer()const;

        void init(const char* title, int w, int h, bool fullScreen);
        virtual void run() = 0;
        virtual void handleeEvent() = 0;
        virtual void render() = 0;
        virtual void clean() = 0;
        virtual void mouseEvent() = 0;
        virtual void update() = 0;

    protected:

    private:
        int screenWigth;
        int screenHeight;
        bool isRunning;
        SDL_Window* window;
        SDL_Renderer* renderer;

};




#endif // GAME_H
