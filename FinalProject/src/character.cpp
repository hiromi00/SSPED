#include "character.h"
Character::Character(){}

Character::Character(SDL_Renderer *r){
    renderer = r;
}

Character::~Character(){
    //dtor
}

void Character::loadImage(std::string & img, int x, int y){
    tempSurface = IMG_Load(img.c_str());
    characterTexture = SDL_CreateTextureFromSurface(renderer, tempSurface);
    SDL_FreeSurface(tempSurface);

    characterRect.w = SPRITE_WIDTH;
    characterRect.h = SPRITE_HEIGHT;
    characterRect.x = x;
    characterRect.y = y; //100

    characterSource.w = SPRITE_WIDTH;
    characterSource.h = SPRITE_HEIGHT;
    characterSource.x = 0;
    characterSource.y = 0;
}

void Character::loadImage2(std::string & img, int x, int y){
    tempSurface = IMG_Load(img.c_str());
    characterTexture = SDL_CreateTextureFromSurface(renderer, tempSurface);
    SDL_FreeSurface(tempSurface);

    characterRect.w = SPRITE_WIDTH;
    characterRect.h = SPRITE_HEIGHT;
    characterRect.x = x;
    characterRect.y = y; //300

    characterSource.w = SPRITE_WIDTH;
    characterSource.h = SPRITE_HEIGHT;
    characterSource.x = 150;
    characterSource.y = 0;
}

void Character::loadLargeImage(std::string& img, int x, int y){
    tempSurface = IMG_Load(img.c_str());
    characterTexture = SDL_CreateTextureFromSurface(renderer, tempSurface);
    SDL_FreeSurface(tempSurface);

    characterRect.w = SPRITE_LARGE_W;
    characterRect.h = SPRITE_LARGE_H;
    characterRect.x = x;
    characterRect.y = y; //300

    characterSource.w = SPRITE_LARGE_W;
    characterSource.h = SPRITE_LARGE_H;
    characterSource.x = 0;
    characterSource.y = 0;
}


void Character::renderCharacter(SDL_Renderer* r, int& frameCounter){
    SDL_RenderCopy(r, characterTexture, &characterSource, &characterRect);
    if(frameCounter % 2 == 0){
        characterSource.x = (characterSource.x + SPRITE_WIDTH) % 150;
        frameCounter %= 2;
        characterRect.x += 10;
    }
}

void Character::renderCharacter2(SDL_Renderer* r, int& frameCounter){
    SDL_RenderCopy(r, characterTexture, &characterSource, &characterRect);
    if(frameCounter % 2 == 0){
        characterSource.x = (characterSource.x + SPRITE_WIDTH) % 150;
        frameCounter %= 2;
        characterRect.x -= 10;
    }
}

void Character::renderOnlyImage(SDL_Renderer* r, int& frameCounter){
    SDL_RenderCopy(r,characterTexture, &characterSource, &characterRect);
}

int Character::chPos(){
    return characterRect.x;
}


void Character::freeTextures(){
    SDL_DestroyTexture(characterTexture);
}

int Character::getxRectYoshi(){
    return characterRect.x;
}

int Character::getyRectYoshi(){
    return characterRect.y;
}

int Character::getwRectYoshi(){
    return characterRect.w;
}

int Character::gethRectYoshi(){
    return characterRect.h;
}

void Character::closeCharacter(){
    SDL_DestroyTexture(characterTexture);
}




