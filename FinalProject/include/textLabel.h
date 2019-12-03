#ifndef SCORE_H
#define SCORE_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <string>
#include <iostream>
#include "game.h"

class TextLabel{
    public:
        TextLabel();
        TextLabel(SDL_Renderer *r, const std::string &fp, const int &fs,
              const std::string &st, const SDL_Color c);
        virtual ~TextLabel();

        void display(int x, int y, SDL_Renderer *renderer, const bool&);
        static SDL_Texture *loadFont(SDL_Renderer *renderer, const std::string &fontPath, const int fontSize,
                                     const std::string &scoreText, const SDL_Color color);
        int getPoints();
        void setPoints(const int&);

        void closeTextLabel();
        void update();
        std::string sPoints();
        void renderSTextures();
        void renderTTextures();

        void setText(const std::string&);
        std::string getText();
    private:
        std::string fontPath;
        int fontSize;
        std::string scoreText;
        std::string text;
        SDL_Color color;
        SDL_Renderer *renderer;
        int points;
        SDL_Texture *textTexture = nullptr;
        SDL_Rect textRect;

};

#endif // SCORE_H
