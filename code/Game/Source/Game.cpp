#include"Game.h"


Game::Game(){
    player = new Player();
}
Game::Game(int u, int v){
    player = new Player(u,v);
}

void Game::key_down(SDL_KeyboardEvent* event ){

    if(event->repeat==0){
        switch (event->keysym.scancode){
            case SDL_SCANCODE_UP:
                player->inc_vel_y(-5);
                break;

            case SDL_SCANCODE_DOWN:
                player->inc_vel_y(5);
                break;

            case SDL_SCANCODE_LEFT:
                player->inc_vel_x(-5);
                break;

            case SDL_SCANCODE_RIGHT:
                player->inc_vel_x(5);   
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
                player->inc_vel_y(5);
                break;
            case SDL_SCANCODE_DOWN:
                player->inc_vel_y(-5);
                break;
            case SDL_SCANCODE_LEFT:
                player->inc_vel_x(5);
                break;
            case SDL_SCANCODE_RIGHT:
                player->inc_vel_x(-5);   
                break;
            default:
                break;
        }
    }
}


void Game::move(){
    player->move();
}


void Game::render(SDL_Renderer* renderer){
    
    SDL_Rect fillRect = {player->get_x() - PLAYER_SIZE/2 , player->get_y() - PLAYER_SIZE/2 ,PLAYER_SIZE,PLAYER_SIZE};
    SDL_SetRenderDrawColor( renderer, 0xFF, 0x00, 0x00, 0xFF );

    SDL_RenderFillRect( renderer, &fillRect );
}