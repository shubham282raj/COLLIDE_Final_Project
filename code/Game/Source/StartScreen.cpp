#include "StartScreen.h"
#include"defs.h"

Start::Start(SDL_Renderer* copy){
    running=true;
    renderer=copy;
    time(&timer);
    initialize();
}

void Start::initialize(){
    selectedWindow=0;
    gameRunning=-1;
    memoryLeaks=false;

    while(gameType.size())
        gameType.pop_back();

    int sqrSize=(WIDTH-(gameCount+1)*spaceSize)/gameCount;

    for(int i=0; i<gameCount; i++){
        Bodies* body =  new Bodies(spaceSize+i*(spaceSize+sqrSize),HEIGHT/2-sqrSize/2,sqrSize,sqrSize,1);
        body->SetColour(0,255,0);
        gameType.push_back(body);
    }

    selectionWindow = new Bodies(gameType[selectedWindow]->x-margin,HEIGHT/2-margin-sqrSize/2,sqrSize+2*margin,sqrSize+2*margin,0);

    loadImages();
}

void Start::loadImages(){
    SDL_Surface* image = SDL_LoadBMP("Images/FlappyBirdIcon.bmp");
    birdIcon = SDL_CreateTextureFromSurface(renderer, image);
    image = SDL_LoadBMP("Images/HunterIcon.bmp");
    hunterIcon = SDL_CreateTextureFromSurface(renderer, image);
    image = SDL_LoadBMP("Images/TicTacToeIcon.bmp");
    tictactoeIcon = SDL_CreateTextureFromSurface(renderer, image);
    image = SDL_LoadBMP("Images/spaceShooterIcon.bmp");
    spaceShooterIcon = SDL_CreateTextureFromSurface(renderer, image);
    image = SDL_LoadBMP("Images/selectionWindow.bmp");
    selectionWindowTexture = SDL_CreateTextureFromSurface(renderer, image);
    image = SDL_LoadBMP("Images/startScreen.bmp");
    bgImage = SDL_CreateTextureFromSurface(renderer, image);
}

void Start::defineGame(){
    // if(memoryLeaks){
    //     delete bird;
    //     delete hunter;
    // }
    // memoryLeaks=true;
    switch(gameRunning){
        case 0:
            bird = new FlappyBird(renderer,&gameRunning);
            break;
        case 1:
            hunter = new BlindHunters(renderer,&gameRunning);
            break;
        case 2:
            board = new Board(renderer,&gameRunning);
            break;
        case 3:
            shooter = new SpaceShooter(renderer,&gameRunning);
            break;
        default:
            break;
    }
}

void Start::key_down(SDL_KeyboardEvent* event ){
    switch(gameRunning){
        case -1:
            if(event->repeat==0){
                switch (event->keysym.scancode){
                    case SDL_SCANCODE_RIGHT:
                        if(selectedWindow+1<gameCount){
                            selectedWindow++;
                        }else{
                            selectedWindow=0;
                        }
                        selectionWindow->x=gameType[selectedWindow]->x-margin;
                        break;
                    case SDL_SCANCODE_LEFT:
                        if(selectedWindow>0){
                            selectedWindow--;
                        }else{
                            selectedWindow=gameCount-1;
                        }
                        selectionWindow->x=gameType[selectedWindow]->x-margin;
                        break;
                    case SDL_SCANCODE_RETURN:
                        if(time(NULL)-timer>=1){
                            gameRunning=selectedWindow;
                            defineGame();
                        }
                        break;
                    case SDL_SCANCODE_ESCAPE:
                        running=false;
                        break; 
                    default:
                        break;
                }
            }
            break;
        case 0:
            bird->key_down(event);
            break;
        case 1:
            hunter->key_down(event);
            break;
        case 2:
            board->key_down(event);
            break;
        case 3:
            shooter->key_down(event);
            break;
        default:
            break;
    }
}

void Start::key_up(SDL_KeyboardEvent* event ){
    switch(gameRunning){
        case -1:
            if(event->repeat==0){
                switch (event->keysym.scancode){
                    default:
                        break;
                }
            }
            break;
        case 0:
            bird->key_up(event);
            break;
        case 1:
            hunter->key_up(event);
            break;
        case 2:
            break;
        case 3:
            shooter->key_up(event);
            break;
        default:
            break;
    }
}

void Start::mouse_down(SDL_MouseButtonEvent* event){
    switch(gameRunning){
        case -1:
            switch(event->button){
                case SDL_BUTTON_LEFT:
                    if(running==true && hover==true){
                        gameRunning=selectedWindow;
                        defineGame();
                    }
                    break;
            }
            break;
        case 0:
            bird->mouse_down(event);
            break;
        case 2:
            board->mouse_down(event);
            break;
        case 3:
            break;
        default:
            break;
    }
}

void Start::move(){
    switch(gameRunning){
        case -1:
            // std::cout << hover << "\n";
            SDL_GetMouseState(&Xmouse,&Ymouse);
            if(Xmouse==prevX && Ymouse==prevY){
                break;
            }else{
                prevX=Xmouse, prevY=Ymouse;
                hover=false;
                for(int i=0; i<gameCount; i++){
                    if(Xmouse>=gameType[i]->x && Xmouse<=gameType[i]->x+gameType[i]->wid && Ymouse>=gameType[i]->y && Ymouse<=gameType[i]->y+gameType[i]->hei){
                        hover=true;
                        selectedWindow=i;
                        selectionWindow->x=gameType[selectedWindow]->x-margin;
                    }
                }
            }
            break;
        case 0:
            bird->move();
            break;
        case 1:
            hunter->move();
            break;
        case 2:
            board->move();
            break;
        case 3:
            shooter->move();
            break;
        default:
            break;
    }
}

void Start::renderIcons(SDL_Renderer* renderer){
    gameType[0]->display(renderer,birdIcon);
    gameType[1]->display(renderer,hunterIcon);
    gameType[2]->display(renderer,tictactoeIcon);
    gameType[3]->display(renderer,spaceShooterIcon);
}

void Start::render(SDL_Renderer* renderer){
    if(running)
        switch(gameRunning){
            case -1:
                SDL_RenderCopy(renderer, bgImage, NULL, NULL);
                selectionWindow->display(renderer,selectionWindowTexture);
                selectionWindow->SetColour(255,255,255);
                // for(int i=0; i<gameType.size(); i++){
                //     gameType[i]->display(renderer);
                // }
                renderIcons(renderer);
                break;
            case 0:
                bird->render();
                break;
            case 1:
                hunter->render();
                break;
            case 2:
                board->render();
                break;
            case 3:
                shooter->render();
                break;
            default:
                break;
        }
}
