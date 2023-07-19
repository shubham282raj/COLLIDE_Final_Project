#include"BlindHunters.h"
#include"defs.h"
#include<cstdlib>
#include<iostream>

BlindHunters::BlindHunters(SDL_Renderer* rendererPointer, int* gameReset){
    running = true;
    moving=false;
    renderer=rendererPointer;
    gameRunning=gameReset;
    initialize();
}

void BlindHunters::move_obstacle(){
    if(moving==false)
        for(int i=0; i<hunterCount; i++){
            hunters[i]->SetVel(-difficulty/2+rand()%difficulty,-difficulty/2+rand()%difficulty);
        }
}

void BlindHunters::initialize(){

    //clear the list of players
    while(hunters.size())
        hunters.pop_back();
    
    //Add the player
    player = new Bodies((WIDTH+playerSize)/2,(HEIGHT+playerSize)/2+300,playerSize,playerSize,0);
    
    //Add the hunters
    int j=0, row=7;
    for(int i=-row/2; i<-row/2+hunterCount; i++){
        Bodies* obs = new Bodies(WIDTH/2+100*i-row*100*int(j/7),HEIGHT/2-200*int(j/7),hunterSize,hunterSize,1);
        obs->SetColour(225,0,0);
        hunters.push_back(obs);
        j++;
    }

    loadImages();
}

void BlindHunters::loadImages(){
    SDL_Surface* image = SDL_LoadBMP("Images/hero.bmp");
    playerTexture = SDL_CreateTextureFromSurface(renderer,image);
    image = SDL_LoadBMP("Images/hunter.bmp");
    hunterTexture = SDL_CreateTextureFromSurface(renderer,image);
    image = SDL_LoadBMP("Images/hunterBG.bmp");
    backgroundTexture = SDL_CreateTextureFromSurface(renderer,image);
}

void BlindHunters::key_down(SDL_KeyboardEvent* event ){

    if(event->repeat==0){
        switch (event->keysym.scancode){
            case SDL_SCANCODE_UP:
                player->vel_y-=5;
                break;

            case SDL_SCANCODE_DOWN:
                player->vel_y+=5;
                break;

            case SDL_SCANCODE_LEFT:
                player->vel_x-=5;
                break;

            case SDL_SCANCODE_RIGHT:
                player->vel_x+=5;   
                break;
            case SDL_SCANCODE_SPACE:
                if(!running){
                    running=true;
                    initialize();
                    moving=false;
                }else if(moving==false){
                    move_obstacle();
                    moving=true;
                }
                break;
            case SDL_SCANCODE_ESCAPE:
                *gameRunning=-1;
                break;
            default:
                break;
        }
        
    }
}


void BlindHunters::key_up(SDL_KeyboardEvent* event ){
    if(event->repeat==0){
        switch (event->keysym.scancode){
            case SDL_SCANCODE_UP:
                player->vel_y+=5;
                break;
            case SDL_SCANCODE_DOWN:
                player->vel_y-=5;
                break;
            case SDL_SCANCODE_LEFT:
                player->vel_x+=5;
                break;
            case SDL_SCANCODE_RIGHT:
                player->vel_x-=5;   
                break;
            default:
                break;
        }
    }
}

void BlindHunters::move(){
    
    if(running){
        //move the player
        player->move();

        //move the bodies
        for(int i=0; i<hunters.size();i++){
            hunters[i]->move();
        }

        //rebounding collision between bodies
        for(int i=0; i<hunters.size(); i++){
            for(int j=i+1; j<hunters.size(); j++){
                hunters[i]->check_col_and_rebound(hunters[j]);
            }
        }

        //check for collision
        for(int i=0; i<hunters.size();i++){
            if(player->check_col(hunters[i])){
                running = false;
            }
        }
        // cout << max_distance << endl;
    }
}


//render
void BlindHunters::render(){
    if(true){
        SDL_RenderCopy(renderer,backgroundTexture,NULL,NULL);

        // player->display(renderer);
        player->display(renderer,playerTexture);
        
        for(int i=0; i<hunters.size();i++){
            hunters[i]->display(renderer,hunterTexture);
        }
    }
}