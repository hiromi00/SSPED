#include "textLabel.h"

TextLabel::TextLabel(){
    //ctor
}

TextLabel::~TextLabel(){

}

TextLabel::TextLabel(SDL_Renderer *r, const std::string& fp, const int &fs,
             const std::string& st, const SDL_Color c) : points(0){
    if(TTF_Init() == -1) {
        std::cout<<"TTF_Init: "<<TTF_GetError();
    }
    renderer = r;
    fontPath = fp;
    fontSize = fs;
    scoreText = st;
    color = c;
}

void TextLabel::display(int x, int y, SDL_Renderer *renderer, const bool& flag){
    textRect.x = x;
    textRect.y = y;
    if(flag){
        renderSTextures();
    }else{
        renderTTextures();
    }
    SDL_RenderCopy(renderer, textTexture, nullptr, &textRect);
    //SDL_RenderPresent(renderer);
}

void TextLabel::renderSTextures(){
    textTexture = loadFont(renderer, fontPath, fontSize,
                           scoreText + sPoints(), color);
    SDL_QueryTexture(textTexture, nullptr, nullptr, &textRect.w, &textRect.h);
}

void TextLabel::renderTTextures(){
    textTexture = loadFont(renderer, fontPath, fontSize,
                           scoreText + text, color);
    SDL_QueryTexture(textTexture, nullptr, nullptr, &textRect.w, &textRect.h);
}


SDL_Texture* TextLabel::loadFont(SDL_Renderer *renderer, const std::string &fontPath,
                             const int fontSize, const std::string &scoreText, const SDL_Color color){

    TTF_Font *font = TTF_OpenFont(fontPath.c_str(), fontSize);
    if(!font){
        std::cout<<"Couldn't load the font"<<std::endl;
    }
    SDL_Surface *textSurface = TTF_RenderText_Solid(font, scoreText.c_str(), color);
    TTF_CloseFont(font);
    if (!textSurface){
        std::cout<<"Couldn't create the surface"<<std::endl;
    }
    SDL_Texture *textTextures = SDL_CreateTextureFromSurface(renderer, textSurface);
    if (!textTextures){
        std::cout<<"Couldn't create the text textures"<<std::endl;
    }
    SDL_FreeSurface(textSurface);
    return textTextures;
}

void TextLabel::closeTextLabel(){
    SDL_DestroyTexture(textTexture);

    TTF_Quit();
}

void TextLabel::update(){
    points++;
    SDL_DestroyTexture(textTexture);
}

std::string TextLabel::sPoints(){
    char cPoints[11];
    sprintf(cPoints, "%05i", points);

    return cPoints;
}

int TextLabel::getPoints(){
    return points;
}

void TextLabel::setPoints(const int&p){
    points = p;
}

void TextLabel::setText(const std::string&t){
    text = t;
}

std::string TextLabel::getText(){
    return text;
}


