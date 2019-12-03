#ifndef MAINMENU_H
#define MAINMENU_H

#include <iostream>
#include <vector>
#include <list>
#include <fstream>
#include <algorithm>

#include <random>
#include <chrono>
#include <functional>
#include <SDL2/SDL_mixer.h>

#include "game.h"
#include "snake.h"
#include "player.h"
#include "character.h"
#include "textLabel.h"
#include "playerName.h"

class MainMenu : public Game{
    private:
        static const int FPS = 30;
        static const int FRAME_DELAY = 1000/FPS;
        static const int LIMIT_X = 150;
        static const int LIMIT_Y = 200;
        static const int LIMIT_IMG_X_YOSHI = 10;
        static const int LIMIT_IMG_Y_YOSHI = 10;
        static const int WIDTH_YOSHI = 100;
        static const int TEXT_SPACE = 80;
        static const int JUMP_LINE = 15;
        int TEXT_SIZE;
        int frameCounter;

        Snake snake;
        SDL_Rect food;
        TextLabel score;
        Player player;
        std::vector<Player> playersScore;
        bool isRunningSnake;
        std::string testText;
        bool snakeFlag;
        TextLabel playerN;
        TextLabel playerScore;
        int finalScore;
        TextLabel maxScores;
        std::list<TextLabel> showPlayersScore;

        void run();
        void handleeEvent();
        void mouseEvent();
        void update();
        void render();
        void clean();


        TextLabel mainText;
        TextLabel yoshiFinal;

        TextLabel opt1;
        TextLabel opt2;
        TextLabel optS;


        Mix_Music* yoshiBackgroud;
        Mix_Chunk* yoshiWin;
        Mix_Chunk* yoshiLose;

        Mix_Music* mainBackground;
        Mix_Chunk* menuSelector;

        Mix_Music* snakeBackground;
        Mix_Chunk* snakeLose;
        Mix_Chunk* snakeEat;

        enum OPTIONS{
            OPT_SNAKE = 1,
            OPT_YOSHIS,
            OPT_EXIT
        };

        int chCounter[6];
        int higher;
        bool isRunningYoshi;

        std::vector<int> diceValues;

        std::vector<std::string> files;
        std::vector<std::string> files2;
        std::vector<std::string> spritesY;

        std::list<Character> characters1;
        std::list<Character> characters2;
        std::list<Character> yoshis;

        std::list<TextLabel> showCounters;
        TextLabel counter;

        int optionSelected;
        void playYoshiGame(const int&);
        void loadYoshis();
        void fillValues();
        void fillList();
        void fillCounters();
        void renderYoshis();


        void playSnakeGame(const int&);
        void snakeHandleeEvent();
        void createFood();
        void snakeRender();

        void writeToDisk(const std::string&);
        void readFromDisk(const std::string&);
        void testHandleeEvent();


        static bool compareScores(Player, Player);
    public:
        MainMenu();
        virtual ~MainMenu();
};

#endif // MAINMENU_H
