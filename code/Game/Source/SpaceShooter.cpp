#include"SpaceShooter.h"
#include"defs.h"
#include<iostream>

SpaceShooter::SpaceShooter(SDL_Renderer* rendererPointer, int* gameReset){
    renderer=rendererPointer;
    gameRunning=gameReset;
    loadImages();
    initialize();
}

void SpaceShooter::initialize(){
    running=true;
    level=0;
    loadLevel();
}

void SpaceShooter::loadLevel(){
    level++;
    lastBullet=time(NULL);
    Xdir=0; Ydir=-1;

    if(player!=NULL){
        delete player;
    }
    while(enemy.size()) enemy.pop_back();

    player = new Bodies(WIDTH/2,HEIGHT/2+300,playerSize,playerSize,0);
    
    int j=0, row=7;
    for(int i=-row/2; i<-row/2+level; i++){
        Bodies* obs = new Bodies(WIDTH/2+100*i-row*100*int(j/7),HEIGHT/2-200*int(j/7),enemySize,enemySize,1);
        obs->SetColour(225,0,0);
        enemy.push_back(obs);
        j++;
    }
}

void SpaceShooter::loadImages(){
    SDL_Surface* image = SDL_LoadBMP("Images/playerShip.bmp");
    playerShipTexture = SDL_CreateTextureFromSurface(renderer, image);
}

void SpaceShooter::shootBullet(){
    static int counter;
    if(time(NULL)-lastBullet>=rechargeTime){
        std::cout << "shoot " << bullet.size() << "\n";
        Bodies* obs = new Bodies(player->x+player->wid/2-bulletSize/2, player->y+player->wid/2-bulletSize/2, bulletSize, bulletSize, 2);
        //BulletDirection
            // if(Xdir==0 || Ydir==0){
            //     obs->SetVel(Xdir*5,Ydir*5);
            // }else{
            //     obs->SetVel(Xdir*sqrt(5),Ydir*sqrt(5));
            // }
            obs->SetVel(Xdir*bulletSpeed,Ydir*bulletSpeed);
        //
        obs->SetColour(255,0,0);
        bullet.push_back(obs);
        lastBullet=time(NULL);
    }
}

void SpaceShooter::key_down(SDL_KeyboardEvent* event ){
    if(event->repeat==0){
        switch (event->keysym.scancode)
        {
            case SDL_SCANCODE_UP:
                player->vel_y-=5;
                Ydir=-1;
                break;

            case SDL_SCANCODE_DOWN:
                player->vel_y+=5;
                Ydir=1;
                break;

            case SDL_SCANCODE_LEFT:
                player->vel_x-=5;
                Xdir=-1;
                break;

            case SDL_SCANCODE_RIGHT:
                player->vel_x+=5; 
                Xdir=1;
                break;
            case SDL_SCANCODE_SPACE:
                shootBullet();
                break;
            case SDL_SCANCODE_ESCAPE:
                *gameRunning=-1;
                break;
            default:
                break;
        }
    }
}

void SpaceShooter::key_up(SDL_KeyboardEvent* event) {
    if(event->repeat==0){
        switch (event->keysym.scancode){
            case SDL_SCANCODE_UP:
                player->vel_y+=5;
                // if(int(player->vel_x+0.1)==0){
                //     Ydir=0;
                // }
                break;
            case SDL_SCANCODE_DOWN:
                player->vel_y-=5;
                // if(int(player->vel_x+0.1)==0){
                //     Ydir=0;
                // }
                break;
            case SDL_SCANCODE_LEFT:
                player->vel_x+=5;
                // if(int(player->vel_y+0.1)==0){
                //     Xdir=0;
                // }
                break;
            case SDL_SCANCODE_RIGHT:
                player->vel_x-=5;   
                // if(int(player->vel_y+0.1)==0){
                //     Xdir=0;
                // }
                break;
            default:
                break;
        }
    }
}

void SpaceShooter::move(){
    static int counter=0;
    //movement of player
    player->move();
    if(int(player->vel_y+0.1)!=0 && int(player->vel_x+0.1)==0){
        Xdir=0;
    }
    if(int(player->vel_x+0.1)!=0 && int(player->vel_y+0.1)==0){
        Ydir=0;
    }

    //movement of bullet
    for(int i=0; i<bullet.size(); i++){
        if(bullet[i]->moveAndFinish()==false){
            std::cout << "delete " << i << std::endl;
            bullet.erase(next(bullet.begin(),i));
            i-=1;
        }
    }
    counter++;
}

void SpaceShooter::render(){
    // player->display(renderer);
    renderWithAngle(player);

    for(int i=0; i<enemy.size(); i++){
        enemy[i]->display(renderer);
    }
    for(int i=0; i<bullet.size(); i++){
        bullet[i]->display(renderer);
    }
}

void SpaceShooter::renderWithAngle(Bodies* body){
    static int counter=0;
    body->center = {body->wid/2, body->hei/2};
    
    body->angle=giveAngle();

    SDL_Rect fillRect = {body->x, body->y, body->wid, body->hei};
    SDL_RenderCopyEx(renderer, playerShipTexture, NULL, &fillRect, body->angle, &body->center, SDL_FLIP_NONE);

}

float SpaceShooter::giveAngle(){
    float angle;
    static int counter=0;
        if(Xdir==0)
            if(Ydir==0)
                std::cout << "shubham " << counter++ << std::endl;
            else if(Ydir==1)
                angle = 90;
            else if(Ydir==-1)
                angle = -90;
            else
                std::cout << "error\n";
        else if(Xdir==1)
            if(Ydir==0)
                angle = 0;
            else if(Ydir==1)
                angle = 45;
            else if(Ydir==-1)
                angle = -45;
            else
                std::cout << "error\n";
        else if(Xdir==-1)
            if(Ydir==0)
                angle=180;
            else if(Ydir==1)
                angle=135;
            else if(Ydir==-1)
                angle=-135;
            else
                std::cout << "error\n";
        else
            std::cout << "error101\n";
    return angle;
}