#include "mainMenu.h"

MainMenu::MainMenu() : frameCounter(0),
                        optionSelected(0), TEXT_SIZE(30),
                        higher(0), finalScore(0){
    srand(time(NULL));
    init("Final Project", 750, 450, false);

    yoshiFinal = TextLabel(getRenderer(), "Fonts/yoshi bold.ttf",
               35, "What is the yoshi that appeared the most?",
               {0,0,0,255});
    score = TextLabel(getRenderer(), "Fonts/04B_30__.ttf", 15,
                      "Score: ", {255,255,250,255});

    mainText = TextLabel(getRenderer(), "Fonts/HOMINIS.ttf", 50,
                         "Menu", {35,66,88,255});
    opt1 = TextLabel(getRenderer(), "Fonts/HOMINIS.ttf", TEXT_SIZE,
                     "Play Snake", {34,139,34,255});
    opt2 = TextLabel(getRenderer(), "Fonts/HOMINIS.ttf", TEXT_SIZE,
                     "Play Yoshi's Game", {34,139,34,255});
    optS = TextLabel(getRenderer(), "Fonts/HOMINIS.ttf", TEXT_SIZE,
                     "Exit", {34,139,34,255});

    Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);

    mainBackground = Mix_LoadMUS("Music/kiki-duyu-lof-me-mamberroi.mp3");
    menuSelector = Mix_LoadWAV("Music/common_00014.wav");

    yoshiBackgroud = Mix_LoadMUS("Music/MusicBackGround.mp3");
    yoshiLose = Mix_LoadWAV("Music/death.wav");
    yoshiWin = Mix_LoadWAV("Music/celebrate2.wav");

    snakeBackground = Mix_LoadMUS("Music/uwu.mp3");
    snakeLose = Mix_LoadWAV("Music/snakeDeath.wav");
    snakeEat = Mix_LoadWAV("Music/soft-hitnormal.wav");

    playerN = TextLabel(getRenderer(), "Fonts/04B_30__.ttf",
                        15, "Your Name: ", {255,255,250,255});
    playerScore = TextLabel(getRenderer(), "Fonts/04B_30__.ttf",
                        15, "Your Score: ", {255,255,250,255});
    maxScores = TextLabel(getRenderer(), "Fonts/04B_30__.ttf",
                        20, "MAX SCORES", {255,255,250,255});
    run();
}

MainMenu::~MainMenu(){

}


void MainMenu::run(){
    bool flag(true);
    unsigned int r(10), g(150), b(130);
    unsigned int frameStart;
    unsigned int frameTime(0);

    Mix_VolumeMusic(30);
    Mix_VolumeChunk(menuSelector, 100);
    Mix_PlayMusic(mainBackground, -1);

    while(getIsRunning()){
        frameStart = SDL_GetTicks();
        handleeEvent();

        SDL_SetRenderDrawColor(getRenderer(), ++r%255, ++g%255, ++b%255,255);
        SDL_RenderClear(getRenderer());

        mainText.display(250,100,getRenderer(),false);
        opt1.display(LIMIT_X,LIMIT_Y,getRenderer(),false);
        opt2.display(LIMIT_X,LIMIT_Y+50,getRenderer(),false);
        optS.display(LIMIT_X,LIMIT_Y+100,getRenderer(),false);

        frameTime = SDL_GetTicks() - frameStart;
        SDL_RenderPresent(getRenderer());

        switch(optionSelected){
        case OPT_SNAKE:
            playSnakeGame(optionSelected);
            optionSelected = 0;
            Mix_PlayMusic(mainBackground, -1);
            finalScore = 0;
            showPlayersScore.clear();
            playersScore.clear();
            score.setPoints(0);
            break;
        case OPT_YOSHIS:
            playYoshiGame(optionSelected);
            optionSelected = 0;
            Mix_PlayMusic(mainBackground, -1);
            higher = 0;
            diceValues.clear();
            for(int i(0); i < 6; i++){
                chCounter[i] = 0;
            }
            frameCounter = 0;
            showCounters.clear();
            break;
        case OPT_EXIT:
            setIsRunning(false);
            break;
        }

        if(FRAME_DELAY > frameTime){
            SDL_Delay(FRAME_DELAY - frameTime);
        }

    }
    clean();

}

void MainMenu::handleeEvent(){
    SDL_Event event;
    SDL_PollEvent(&event);

    switch(event.type){
    case SDL_QUIT:
        setIsRunning(false);
        break;
    case SDL_MOUSEBUTTONDOWN:
        if(event.motion.x > LIMIT_X && event.motion.x < (LIMIT_X + 400)
           && event.motion.y > LIMIT_Y && event.motion.y < (LIMIT_Y + TEXT_SIZE*5)){
           if(event.motion.y > LIMIT_Y && event.motion.y < (LIMIT_Y+TEXT_SIZE)){
                optionSelected = OPT_SNAKE;

           }else if(event.motion.y > (LIMIT_Y+TEXT_SIZE+JUMP_LINE)
                    && event.motion.y < (LIMIT_Y+TEXT_SIZE*2+JUMP_LINE)){
                optionSelected = OPT_YOSHIS;

            }else if(event.motion.y > (LIMIT_Y+TEXT_SIZE*2+JUMP_LINE*2)
                     && event.motion.y < (LIMIT_Y+TEXT_SIZE*5)){
                optionSelected = OPT_EXIT;
            }
        }
        break;
    }
}

void MainMenu::mouseEvent(){
    SDL_Event event;
    SDL_PollEvent(&event);

    int tmpValueCoor;
    pair<int,int> cordinates{120,100};
    bool tmpFlag(false);
    bool flag(true);

    switch(event.type){
    case SDL_MOUSEBUTTONDOWN:
        if (event.motion.x > LIMIT_IMG_X_YOSHI && event.motion.x < (LIMIT_IMG_X_YOSHI+450)
            && event.motion.y > LIMIT_IMG_Y_YOSHI && event.motion.y < (LIMIT_IMG_Y_YOSHI+330)){
            if(event.motion.x > LIMIT_IMG_X_YOSHI &&
               event.motion.x < (LIMIT_IMG_X_YOSHI + WIDTH_YOSHI) && event.motion.y < LIMIT_X){
                tmpValueCoor = 0;
                tmpFlag = true;
                if(chCounter[tmpValueCoor] == higher){
                Mix_PlayChannel(-1, yoshiWin, 0);
                }else{
                    Mix_PlayChannel(-1, yoshiLose, 0);
                }

            }else if(event.motion.x > (LIMIT_IMG_X_YOSHI + WIDTH_YOSHI + TEXT_SPACE) &&
                     event.motion.x < (LIMIT_IMG_X_YOSHI + WIDTH_YOSHI*2 + TEXT_SPACE)
                     && event.motion.y < LIMIT_X){
                tmpValueCoor = 1;
                tmpFlag = true;
                if(chCounter[tmpValueCoor] == higher){
                Mix_PlayChannel(-1, yoshiWin, 0);
                }else{
                    Mix_PlayChannel(-1, yoshiLose, 0);
                }

            }else if(event.motion.x > (LIMIT_IMG_X_YOSHI + WIDTH_YOSHI*2 + TEXT_SPACE*2) &&
                     event.motion.x < (LIMIT_IMG_X_YOSHI + WIDTH_YOSHI*3 + TEXT_SPACE*3)
                     && event.motion.y < LIMIT_X){
                tmpValueCoor = 2;
                tmpFlag = true;
                if(chCounter[tmpValueCoor] == higher){
                Mix_PlayChannel(-1, yoshiWin, 0);
                }else{
                    Mix_PlayChannel(-1, yoshiLose, 0);
                }

            }else if(event.motion.x > LIMIT_IMG_X_YOSHI &&
                     event.motion.x < (LIMIT_IMG_X_YOSHI + WIDTH_YOSHI)
                     && event.motion.y > LIMIT_X+35){
                tmpValueCoor = 3;
                tmpFlag = true;
                if(chCounter[tmpValueCoor] == higher){
                Mix_PlayChannel(-1, yoshiWin, 0);
                }else{
                    Mix_PlayChannel(-1, yoshiLose, 0);
                }

            }else if(event.motion.x > (LIMIT_IMG_X_YOSHI + WIDTH_YOSHI + TEXT_SPACE) &&
                     event.motion.x < (LIMIT_IMG_X_YOSHI + WIDTH_YOSHI*2 + TEXT_SPACE)
                     && event.motion.y > LIMIT_X+35){
                Mix_PausedMusic();
                tmpValueCoor = 4;
                tmpFlag = true;
                if(chCounter[tmpValueCoor] == higher){
                Mix_PlayChannel(-1, yoshiWin, 0);
                }else{
                    Mix_PlayChannel(-1, yoshiLose, 0);
                }

            }else if(event.motion.x > (LIMIT_IMG_X_YOSHI+ WIDTH_YOSHI*2 + TEXT_SPACE*2) &&
                     event.motion.x < (LIMIT_IMG_X_YOSHI+ WIDTH_YOSHI*3 + TEXT_SPACE*3)
                     && event.motion.y > LIMIT_X+35){
                tmpValueCoor = 5;
                tmpFlag = true;
                if(chCounter[tmpValueCoor] == higher){
                Mix_PlayChannel(-1, yoshiWin, 0);
                }else{
                    Mix_PlayChannel(-1, yoshiLose, 0);
                }

            }
        if(tmpFlag){
            for(list<TextLabel>::iterator it = showCounters.begin();
                it != showCounters.end(); it++){
                (*it).display(cordinates.first, cordinates.second, getRenderer(), false);
                if(cordinates.first >= 420 && flag){
                    cordinates.first = 120;
                    cordinates.second = 300;
                    flag = false;
                }else if(flag == false){
                    cordinates.first += 180;
                }else{
                    cordinates.first += 180;
                }
            }
            SDL_RenderPresent(getRenderer());
            isRunningYoshi = false;

        }
        }
        break;

    case SDL_QUIT:
        isRunningYoshi = false;
        break;
    default:
        break;
    }
}

void MainMenu::render(){
    for(list<Character>::iterator it = characters1.begin();
        it != characters1.end(); it++){
            (*it).renderCharacter(getRenderer(), frameCounter);
        }
    for(list<Character>::iterator it = characters2.begin();
        it != characters2.end(); it++){
            (*it).renderCharacter2(getRenderer(), frameCounter);
        }
}

void MainMenu::clean(){
    SDL_DestroyWindow(getWindow());
    SDL_DestroyRenderer(getRenderer());
    Mix_FreeMusic(mainBackground);
    Mix_FreeMusic(snakeBackground);
    Mix_FreeMusic(yoshiBackgroud);
    Mix_FreeChunk(menuSelector);
    Mix_FreeChunk(snakeEat);
    Mix_FreeChunk(snakeLose);
    Mix_FreeChunk(yoshiWin);
    Mix_FreeChunk(yoshiLose);
    score.closeTextLabel();
    playersScore.clear();
    mainText.closeTextLabel();
    yoshiFinal.closeTextLabel();
    opt1.closeTextLabel();
    opt2.closeTextLabel();
    optS.closeTextLabel();
    files.clear();
    files2.clear();
    spritesY.clear();
    yoshis.clear();
    showCounters.clear();
    counter.closeTextLabel();
}


void MainMenu::loadYoshis(){
    Character yoshi(getRenderer());

    int i(0);
    int x(10);
    int y(10);

    bool flag(true);
    while(i < 6){
        yoshi.loadLargeImage(spritesY.at(i), x, y);
        i++;
        if(i > 2 && flag){
            x = 10;
            y = 200;
            flag = false;
        }else if(i > 2 && flag == false){
            x += 180;
        }else{
            x += 180;
        }

        yoshis.push_back(yoshi);
    }
}

void MainMenu::fillValues(){
    default_random_engine generator(chrono::system_clock::now().time_since_epoch().count());
    uniform_int_distribution <int> distribution(1, 50);
    uniform_int_distribution <int> chDistribution(0, 5);

    auto diceLimit = bind(distribution, generator);
    auto dice = bind(chDistribution, generator);

    files.push_back("Sprites/y1-1.png");
    files.push_back("Sprites/y2-2.png");
    files.push_back("Sprites/y3-3.png");
    files.push_back("Sprites/y4-4.png");
    files.push_back("Sprites/y5-5.png");
    files.push_back("Sprites/y6-6.png");

    files2.push_back("Sprites/y2.png");
    files2.push_back("Sprites/y3.png");
    files2.push_back("Sprites/y6.png");
    files2.push_back("Sprites/y5.png");
    files2.push_back("Sprites/y4.png");
    files2.push_back("Sprites/y1.png");

    spritesY.push_back("Sprites/yv.png");
    spritesY.push_back("Sprites/yaz.png");
    spritesY.push_back("Sprites/yn.png");
    spritesY.push_back("Sprites/yr.png");
    spritesY.push_back("Sprites/ym.png");
    spritesY.push_back("Sprites/ya.png");

    int limit(diceLimit());

    for(int i(0); i < limit; i++){
        diceValues.push_back(dice());
    }
    for(int i(0); i < 6; i++){
        chCounter[i] = 0;
    }
}

void MainMenu::fillList(){
    Character character(getRenderer());
    vector<int> tmpValues(diceValues);

    int x(-50*tmpValues.size());
    int y(100);
    for (int i(0); i < diceValues.size(); i++){
        switch(tmpValues.back()){
        case 0:
            character.loadImage(files.at(tmpValues.back()), x, y);
            chCounter[0] ++;
            break;
        case 1:
            character.loadImage(files.at(tmpValues.back()), x, y);
            chCounter[1] ++;
            break;
        case 2:
            character.loadImage(files.at(tmpValues.back()), x, y);
            chCounter[2] ++;
            break;
        case 3:
            character.loadImage(files.at(tmpValues.back()), x, y);
            chCounter[3] ++;
            break;
        case 4:
            character.loadImage(files.at(tmpValues.back()), x, y);
            chCounter[4] ++;
            break;
        case 5:
            character.loadImage(files.at(tmpValues.back()), x, y);
            chCounter[5] ++;

            break;
        default:
            break;
        }
        x += 50;
        characters1.push_back(character);
        tmpValues.pop_back();
    }

    tmpValues = vector<int>(diceValues);

    y = 300;
    x = 600+tmpValues.size()*50;

    for (int i(0); i < diceValues.size(); i++){
        switch(tmpValues.back()){
        case 0:
            character.loadImage(files2.at(tmpValues.back()), x, y);
            chCounter[1] ++;
            break;
        case 1:
            character.loadImage(files2.at(tmpValues.back()), x, y);
            chCounter[2] ++;
            break;
        case 2:
            character.loadImage(files2.at(tmpValues.back()), x, y);
            chCounter[5] ++;
            break;
        case 3:
            character.loadImage(files2.at(tmpValues.back()), x, y);
            chCounter[4] ++;
            break;
        case 4:
            character.loadImage(files2.at(tmpValues.back()), x, y);
            chCounter[3] ++;
            break;
        case 5:
            character.loadImage(files2.at(tmpValues.back()), x, y);
            chCounter[0] ++;
            break;
        default:
            break;
        }
        x -= 50;
        characters2.push_back(character);
        tmpValues.pop_back();
    }
}

void MainMenu::fillCounters(){
    for(int i(0); i < 6; i++){
        counter = TextLabel(getRenderer(),
                            "Fonts/yoshi bold.ttf", 30,
                            to_string(chCounter[i]),
                            {0,0,0,255});
        showCounters.push_back(counter);
    }
}

void MainMenu::renderYoshis(){
    for(list<Character>::iterator it = yoshis.begin();
        it != yoshis.end(); it++){
            (*it).renderOnlyImage(getRenderer(), frameCounter);
        }
}


void MainMenu::playYoshiGame(const int&opt){
    bool flag(true);
    unsigned int frameStart;
    unsigned int frameTime(0);

    Mix_VolumeMusic(50);
    Mix_VolumeChunk(yoshiWin, 100);
    Mix_VolumeChunk(yoshiLose, 100);

    fillValues();
    fillList();
    fillCounters();
    loadYoshis();

    for(int i(0); i < 6; i++){
        if(chCounter[i] > higher){
            higher = chCounter[i];
        }
    }
    Mix_PlayMusic(yoshiBackgroud, -1);
    isRunningYoshi = true;

    while(isRunningYoshi){
        frameStart = SDL_GetTicks();
        //handleeEvent();

        SDL_SetRenderDrawColor(getRenderer(), 0,200,10,255);
        SDL_RenderClear(getRenderer());

        if(flag == false){
            mouseEvent();
            yoshiFinal.display(0,400, getRenderer(), false);
            renderYoshis();
        }else{
            render();
        }

        frameTime = SDL_GetTicks() - frameStart;
        SDL_RenderPresent(getRenderer());
        if(FRAME_DELAY > frameTime){
            SDL_Delay(FRAME_DELAY - frameTime);
        }
        if(characters1.front().chPos() == 780){
            characters1.clear();
            characters2.clear();
            flag = false;
        }
        if(isRunningYoshi == false){
            SDL_Delay(5000);
        }

        frameCounter++;
    }


}


void MainMenu::playSnakeGame(const int& opt){
    readFromDisk("Scores.txt");
    int yPos(100);
    snake = Snake(50,50,getRenderer());
    unsigned int frameStart;
    unsigned int frameTime;
    Mix_PlayMusic(snakeBackground, -1);
    Mix_VolumeMusic(50);
    Mix_VolumeChunk(snakeEat, 100);
    Mix_VolumeChunk(snakeLose, 150);
    isRunningSnake = true;
    createFood();
    snakeFlag = true;
    testText = "";
    while(isRunningSnake){
        frameStart = SDL_GetTicks();
        SDL_RenderClear(getRenderer());
        if (snakeFlag == false){
            SDL_SetRenderDrawColor(getRenderer(), 0,0,0,255);
            testHandleeEvent();
            playerN.setText(testText);

            playerN.display(100,50,getRenderer(),false);
            playerScore.display(100,20,getRenderer(),true);
            maxScores.display(150,80,getRenderer(),false);
            for(list<TextLabel>::iterator it = showPlayersScore.begin();
                it != showPlayersScore.end(); it++){
                    (*it).display(100,yPos,getRenderer(),false);
                    (*it).display(350,yPos,getRenderer(),true);
                    yPos += 20;
                }
            yPos = 100;
        }else{
            SDL_SetRenderDrawColor(getRenderer(), rand() % 255,
                                   rand() % 255, rand() % 255, 255);
            SDL_RenderFillRect(getRenderer(), &food);
            snakeHandleeEvent();
            update();
            snake.render();
            score.display(20, 20, getRenderer(), true);
            SDL_SetRenderDrawColor(getRenderer(), 0, 0, 0, 255);
        }


        SDL_RenderPresent(getRenderer());

        frameTime = SDL_GetTicks() - frameStart;
        if(FRAME_DELAY > frameTime){
            SDL_Delay(FRAME_DELAY - frameTime);
        }

    }
}

void MainMenu::snakeHandleeEvent(){
    SDL_Event event;
    SDL_PollEvent(&event);
    switch(event.type){
    case SDL_QUIT:
        isRunningSnake = false;
        break;
    case SDL_KEYDOWN:
        switch(event.key.keysym.sym){
        case SDLK_w:
            snake.setDirection(0, -1);
            break;
        case SDLK_s:
            snake.setDirection(0, 1);
            break;
        case SDLK_a:
            snake.setDirection(-1, 0);
            break;
        case SDLK_d:
            snake.setDirection(1, 0);
            break;
        default:
            break;
        }
        break;
    default:
        break;
    }
}


void MainMenu::update(){
    if(snake.eating(food)){
        score.update();
        Mix_PlayChannel(-1, snakeEat, 0);
        createFood();
        snake.grow();
    }
    snake.update();
    if(snake.frameCollision(getScreenWight(), getScreenHeight())
       or snake.bodyCollision()){
            finalScore = score.getPoints();
            playerScore.setPoints(finalScore);
            Mix_PlayChannel(-1, snakeLose, 0);
            snakeFlag = false;
    }
}

void MainMenu::createFood(){
    food.x = rand() % (getScreenWight()/Snake::BLOCK_WIDTH) * Snake::BLOCK_WIDTH;
    food.y = rand() % (getScreenHeight()/Snake::BLOCK_HEIGH) * Snake::BLOCK_HEIGH;
    food.h = Snake::BLOCK_HEIGH;
    food.w = Snake::BLOCK_WIDTH;
}

void MainMenu::snakeRender(){
    SDL_RenderClear(getRenderer());
    SDL_SetRenderDrawColor(getRenderer(), rand() % 255,
                           rand() % 255, rand() % 255, 255);
    SDL_RenderFillRect(getRenderer(), &food);
    snake.render();
    SDL_SetRenderDrawColor(getRenderer(), 0, 0, 0, 255);
}


void MainMenu::testHandleeEvent(){
    SDL_Event event;
    SDL_PollEvent(&event);

    switch(event.type){
    case SDL_QUIT:
        isRunningSnake = false;
        break;
    case SDL_TEXTINPUT:
    case SDL_KEYDOWN:
        system("cls");
        if(event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_BACKSPACE
           && testText.length() > 0){
            testText = testText.substr(0, testText.length() - 1);
        }else if(event.type == SDL_TEXTINPUT){
            testText += event.text.text;

        }else if(event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_RETURN
           && testText.length() > 0){
                writeToDisk("Scores.txt");
                isRunningSnake = false;
                SDL_Delay(3000);
        }
        break;
    }
}


void MainMenu::writeToDisk(const std::string& fileName){
    std::ofstream output(fileName, ios::app);
    player.setName(testText);
    player.setScore(finalScore);

    if(!output.is_open()){
        std::cout<<"Error with the data (1)..."<<std::endl;
    }else{
        output << player;
        output.close();
    }
}

void MainMenu::readFromDisk(const std::string& fileName){
    TextLabel auxTL(getRenderer(),"Fonts/04B_30__.ttf",15,
                    "",{255,255,255,255});
    std::ifstream input(fileName);
    if(!input.is_open()){
        cout<<"Error with the data (2)..."<<endl;
    }else{
        int j(-1);
        while(input >> player){
            playersScore.push_back(player);
        }
        input.close();
        int i(0);
        sort(playersScore.begin(), playersScore.end(), compareScores); //Mayor a menor
        while(i < 10){
            auxTL.setText(playersScore.back().getName());
            auxTL.setPoints(playersScore.back().getScore());
            playersScore.pop_back();
            showPlayersScore.push_front(auxTL);
            if(playersScore.empty()){
                break;
            }
            i++;
        }
    }
}

bool MainMenu::compareScores(Player p1, Player p2){
    return p1.getScore() > p2.getScore();
}





