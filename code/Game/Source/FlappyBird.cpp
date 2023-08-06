#include"FlappyBird.h"
#include"defs.h"
#include<iostream>
#include<cstdlib>
#include<cmath>

FlappyBird::FlappyBird(SDL_Renderer* copy, int* n){//copy is renderer's pointer
    running = true;
    renderer = copy;
    gameRunning=n; 
    highScore=0;
    loadImages();
    // numberTexture.loadTexture(renderer);
    initialize();
}
void FlappyBird::initialize(){
    score=0;
    numberTexture.updateNumberArray(score);
    //Clear the list of wall
    while(wall.size()) wall.pop_back();

    //Add bird
    bird = new Bodies(WIDTH/2-birdSize/2,HEIGHT/2-birdSize/2,birdSize,birdSize,0);
    bird->SetColour(0,255,0);

    // Add pipes
    int temp=0;
    for(int i=0; i<10; i++){
        int random=rand()%inaccuracy;
        Bodies* obs = new Bodies(WIDTH-poleThickness+horSpace*(i/2),temp,poleThickness,HEIGHT/2-vertSpace/2-horSpace/2-poleThickness/2+random,1);
            if(i%2==0){
                temp=obs->y+(obs->hei)+vertSpace;
            }else{
                obs->hei=HEIGHT-temp;
                temp=0;
            }
        obs->SetColour(1,50,32);
        wall.push_back(obs);
    }
}

void FlappyBird::loadImages(){
    numberTexture.loadTexture(renderer);
    SDL_Surface* image = SDL_LoadBMP("Images/flappyBG.bmp");
    bg_texture = SDL_CreateTextureFromSurface(renderer, image);
    image = SDL_LoadBMP("Images/bird.bmp");
    bird_texture = SDL_CreateTextureFromSurface(renderer, image);
    image = SDL_LoadBMP("Images/pipeTexture.bmp");
    pipe_texture = SDL_CreateTextureFromSurface(renderer,image);
    image = SDL_LoadBMP("Images/boom.bmp");
    boom = SDL_CreateTextureFromSurface(renderer,image);

}

void FlappyBird::giveVelocity(){
    for(int i=0; i<wall.size(); i++){
        wall[i]->SetVel(poleVelocity,0);
    }
    bird->vel_y=-jump_velocity;
}

void FlappyBird::key_down(SDL_KeyboardEvent* event ){

    if(event->repeat==0){
        switch (event->keysym.scancode){
            case SDL_SCANCODE_SPACE:
                if(moving){
                    bird->vel_y=-jump_velocity;
                }else{
                    moving=true;
                    giveVelocity();
                }
                if(!running){
                    moving=false;
                    running=true;
                    initialize();
                }
                break;
            case SDL_SCANCODE_RETURN:
                if(!running){
                    moving=false;
                    running=true;
                    initialize();
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


void FlappyBird::key_up(SDL_KeyboardEvent* event ){
    //this game for now doesn't need keyUP
}

void FlappyBird::mouse_down(SDL_MouseButtonEvent* event){
    switch(event->button){
        case SDL_BUTTON_LEFT:
            if(moving){
                bird->vel_y=-jump_velocity;
            }else{
                moving=true;
                giveVelocity();
            }
            if(!running){
                moving=false;
                running=true;
                initialize();
            }
            break;
    }    
}

void FlappyBird::move(){
    if(running){    
        //move the bird
        bird->move();

        //gravity for the bird
        if(moving)  bird->vel_y+=gravity;

        //move the walls
        for(int i=0; i<wall.size(); i++){
            wall[i]->x+=wall[i]->vel_x;
            // wall[i]->y+=wall[i]->vel_y;
            if(i%2==0 && wall[i]->x+wall[i]->wid==bird->x){
                score++;
                numberTexture.updateNumberArray(score);
            }
            if(wall[i]->x<=-poleThickness){
                wall[i]->x+=(wall.size()/2)*(horSpace);
                if(i%2==0){  
                    wall[i]->hei=HEIGHT/2-vertSpace/2-horSpace/2-10+rand()%inaccuracy;
                }else{
                    wall[i]->y=wall[i-1]->hei+vertSpace;
                    wall[i]->hei=HEIGHT-wall[i]->y;
                }
            }
        }

        //check for collision
        for(int i=0; i<wall.size();i++){
            if(bird->check_col(wall[i]))
            {
                dyingX=bird->x;
                dyingY=bird->y;
                running = false;
                moving = false;
                if(score>highScore){
                    highScore=score;
                    std::cout << "Yippe! You made a new High Score " << score << std::endl;
                }else{
                    std::cout << "\tYour Score " << score << std::endl;
                }
                break;
            }
        }
    }else if(!moving){
        bird->vel_y+=gravity/2;
        bird->move();
    }
}

//render
void FlappyBird::render(){
    if(true){

        SDL_RenderCopy(renderer, bg_texture, NULL, NULL);
        // SDL_RenderPresent(renderer);
        
        if(!running){
            SDL_Rect fillRect = {dyingX ,dyingY ,bird->wid,bird->hei};
            SDL_RenderCopy(renderer, boom, NULL, &fillRect);
        }

        // bird->display(renderer,bird_texture);
        bird_render();

        for(int i=0; i<wall.size();i++){
            wall[i]->display(renderer,pipe_texture);
        }

        numberTexture.renderNumber(renderer);
    }
    
}

void FlappyBird::bird_render(){
    center = { bird->wid/2 , bird->hei/2 };
    angle = atan(float(-(bird->vel_y)/poleVelocity))*90/3.14-15;
    SDL_Rect fillRect = {bird->x ,bird->y ,bird->wid,bird->hei};
    SDL_RenderCopyEx(renderer, bird_texture, NULL, &fillRect, angle, &center, SDL_FLIP_NONE );
}