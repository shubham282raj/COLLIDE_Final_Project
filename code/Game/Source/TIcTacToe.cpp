#include"TicTacToe.h"
#include"defs.h"

Board::Board(SDL_Renderer* rendererPointer, int* gameReset){
    renderer=rendererPointer;
    gameRunning=gameReset;
    initialize();
}

void Board::initialize(){
    running=true;
    chance=1;
    win=0;
    animation=true;
    box = new Bodies**[3];
    for(int i=0; i<3; i++){
        box[i] = new Bodies*[3];
        for(int j=0; j<3; j++){
            box[i][j] = new Bodies(WIDTH/2+i*(boxSize+boxGap)-boxGap-(boxSize*3)/2, HEIGHT/2+j*(boxSize+boxGap)-boxGap-(boxSize*3)/2,boxSize,boxSize,1);
            arr[i][j] = 0;
        }
    }
    winner = new Bodies(WIDTH/2-boxSize/2, -boxSize, boxSize, boxSize,1);
    board = new Bodies(box[0][0]->x,box[0][0]->y,3*boxSize+2*boxGap,3*boxSize+2*boxGap,1);
    loadImages();
}

void Board::loadImages(){
    SDL_Surface* image = SDL_LoadBMP("Images/cross.bmp");
    cross = SDL_CreateTextureFromSurface(renderer, image);
    image = SDL_LoadBMP("Images/circle.bmp");
    // bg_texture = SDL_CreateTextureFromSurface(renderer, image);
    circle = SDL_CreateTextureFromSurface(renderer, image);
    image = SDL_LoadBMP("Images/bird.bmp");
    tie = SDL_CreateTextureFromSurface(renderer, image);
    image = SDL_LoadBMP("Images/tictacboard.bmp");
    checkBoard = SDL_CreateTextureFromSurface(renderer, image);
    // image = SDL_LoadBMP("Images/bird.bmp");
}

void Board::key_down(SDL_KeyboardEvent* event){
    if(event->repeat==0){
        switch (event->keysym.scancode)
        {
            case SDL_SCANCODE_ESCAPE:
                *gameRunning=-1;
                break;
            default:
                break;
        }
    }

}

void Board::mouse_down(SDL_MouseButtonEvent* event){
        switch(event->button){
            case SDL_BUTTON_LEFT:
                if(running==true && hover==true && arr[x][y]==0){
                    arr[x][y]=chance;
                    chance*=-1;
                    checkWin();
                    if(win!=0){
                        running=false;
                        if(win==-1){
                            std::cout << "Cross Won\n";
                        }else if(win==1){
                            std::cout << "Circle Won\n";
                        }else if(win==2){
                            std::cout << "Tie\n";
                        }
                    }
                }else if(running==false && animation==false){
                    initialize();
                }
                break;
        }    
}

void Board::checkWin(){
    bool tie=true;
    int horizontalSum, verticalSum[3]={0}, diag=0, diagOpp=0;
    for(int i=0; i<3; i++){
        horizontalSum=0;
        for(int j=0; j<3; j++){
            if(arr[i][j]==0){
                tie=false;
            }
            horizontalSum+=arr[i][j];
            verticalSum[j]+=arr[i][j];
            if(j==i){
                diag+=arr[i][j];
            }
            if(i+j==2){
                diagOpp+=arr[i][j];
            }
        }
        //checking hortizontal scores
        if(horizontalSum==3){
            win=1;
            return;
        }else if(horizontalSum==-3){
            win=-1;
            return;
        }
    }

    //checking scores

    for(int i=0; i<3; i++){
        if(verticalSum[i]==3){
            win=1;
            return;
        }else if(verticalSum[i]==-3){
            win=-1;
            return;
        }
    }

    if(diag==3){
        win=1;
        return;
    }else if(diag==-3){
        win=-1;
        return;
    }

    if(diagOpp==3){
        win=1;
        return;
    }else if(diagOpp==-3){
        win=-1;
        return;
    }
    if(tie==true){
        win=2;
    }
}

void Board::move(){
    SDL_GetMouseState(&Xmouse,&Ymouse);
    
    //Xmouse>=box[i][j]->x && Xmouse<=box[i][j]->x+box[i][j]->wid
    //Ymouse>=box[i][j]->y && Ymouse<=box[i][j]->y+box[i][j]->hei

    hover=false;
    x=y=0;
    
    for(int i=0; i<3; i++){
        for(int j=0; j<3; j++){
            if(Xmouse>=box[i][j]->x && Xmouse<=box[i][j]->x+box[i][j]->wid && Ymouse>=box[i][j]->y && Ymouse<=box[i][j]->y+box[i][j]->hei){
                x=i; y=j;
                hover=true;
            }
        }
    }
}

void Board::render(){
    if(true){
        board->display(renderer,checkBoard);
        for(int i=0; i<3; i++){
            for(int j=0; j<3; j++){
                switch(arr[i][j]){
                    // case 0:
                    //     box[i][j]->display(renderer);
                    //     break;
                    case 1:
                        box[i][j]->display(renderer,circle);
                        break;
                    case -1:
                        box[i][j]->display(renderer,cross);
                }
            }
        }
        if(!running && win!=0 && animation){
            for(int i=0; i<3; i++){
                for(int j=0; j<3; j++){
                    box[i][j]->y+=2*animationSpeed;
                }
            }
            board->y+=2*animationSpeed;
            if(winner->y >= HEIGHT/2-winner->wid/2){
                animation=false;
            }
            winner->y+=animationSpeed-sizeIncSpeed/2;
            winner->x-=sizeIncSpeed/2;
            winner->wid+=sizeIncSpeed;
            winner->hei+=sizeIncSpeed;
        }
        if(win==1){
            winner->display(renderer,circle);
        }else if(win==-1){
            winner->display(renderer,cross);
        }else if(win==2){
            winner->display(renderer,tie);
        }
    }
}