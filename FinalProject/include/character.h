#ifndef CHARACTER_H
#define CHARACTER_H
#include <string>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL.h>

class Character{
    private:
        static const int SPRITE_WIDTH = 50;
        static const int SPRITE_HEIGHT = 50;

        static const int SPRITE_LARGE_W = 100;
        static const int SPRITE_LARGE_H = 135;

        SDL_Renderer *renderer;
        SDL_Texture *characterTexture;

        SDL_Rect characterRect;
        SDL_Rect characterSource;

        SDL_Surface *tempSurface;

        bool flag;
    public:
        Character();
        Character(SDL_Renderer *r);
        virtual ~Character();

        void freeTextures();
        void loadImage(std::string&, int x, int y);
        void loadImage2(std::string &, int x, int y);
        void loadLargeImage(std::string &, int x, int y);

        void renderCharacter(SDL_Renderer* r, int&);
        void renderCharacter2(SDL_Renderer* r, int&);
        void renderOnlyImage(SDL_Renderer* r, int&);

        void closeCharacter();

        int chPos();

        int getxRectYoshi();
        int getyRectYoshi();
        int getwRectYoshi();
        int gethRectYoshi();

    protected:

};

#endif // CHARACTER_H
