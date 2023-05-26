#include"Game.h"
#include"defs.h"
#include<iostream>

Game::Game(){
    running = true;
    timer= 0;
    initialize();
}
void Game::initialize(){
    //Clear the list of bodies
    while(listOfBodies.size()) listOfBodies.pop_back();

    //Add player
    Bodies* B = new Bodies(WIDTH/2-10,HEIGHT/2-10,20,20,0);
    B->SetColour(255,0,0);
    listOfBodies.push_back(B);

    // Add one obstacle
    Bodies* obs = new Bodies(WIDTH/2-50,HEIGHT/2-40,20,20,1);
    obs->SetColour(0,0,0);
    listOfBodies.push_back(obs);
}

void Game::key_down(SDL_KeyboardEvent* event ){

    if(event->repeat==0){
        // Press any key to restart game
        if(timer>RESET_TIME && !running){ 
            running = true;
            initialize();
        }
        switch (event->keysym.scancode){
            case SDL_SCANCODE_UP:
                listOfBodies[0]->vel_y-=5;
                break;

            case SDL_SCANCODE_DOWN:
                listOfBodies[0]->vel_y+=5;
                break;

            case SDL_SCANCODE_LEFT:
                listOfBodies[0]->vel_x-=5;
                break;

            case SDL_SCANCODE_RIGHT:
                listOfBodies[0]->vel_x+=5;   
                break;
            default:
                break;
        }
    }
}


void Game::key_up(SDL_KeyboardEvent* event ){
    if(event->repeat==0){
        switch (event->keysym.scancode){
            case SDL_SCANCODE_UP:
                listOfBodies[0]->vel_y+=5;
                break;
            case SDL_SCANCODE_DOWN:
                listOfBodies[0]->vel_y-=5;
                break;
            case SDL_SCANCODE_LEFT:
                listOfBodies[0]->vel_x+=5;
                break;
            case SDL_SCANCODE_RIGHT:
                listOfBodies[0]->vel_x-=5;   
                break;
            default:
                break;
        }
    }
}


void Game::move(){
    if(running){    
        //move the bodies
        for(int i=0; i<listOfBodies.size();i++){
            listOfBodies[i]->move();
        }

        //check for collision
        for(int i=1; i<listOfBodies.size();i++){
            if(listOfBodies[0]->check_col(listOfBodies[i]))
            {
                running = false;
                break;
            }
        }
    }
    else timer++;
}

//render
void Game::render(SDL_Renderer* renderer){
    if(running){
        for(int i=0; i<listOfBodies.size();i++){
            listOfBodies[i]->display(renderer);
        }
    }
}