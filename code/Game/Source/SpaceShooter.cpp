#include"SpaceShooter.h"
#include"defs.h"
#include<iostream>
#include<cstdlib>
#include<cmath>

SpaceShooter::SpaceShooter(SDL_Renderer* rendererPointer, int* gameReset){
    renderer=rendererPointer;
    gameRunning=gameReset;
    loadImages();
    initialize();
}

void SpaceShooter::initialize(){
    instructionScreen=true;
    endScreen=false;
    running=true;
    level=0;
    bulletCount=3;
    lives=2;
    loadLevel();
}

void SpaceShooter::loadLevel(){
    level++;
    bulletCount+=level*2;
    lives++;
    playerCollide=false;
    difficulty+=1;
    lastBullet=time(NULL);
    Xdir=0; Ydir=-1;
    enemyIsMoving=false;

    while(enemy.size())     enemy.pop_back();
    while(bullet.size())    bullet.pop_back();

    if(player==NULL) {
        player = new Bodies(WIDTH/2,HEIGHT/2+300,playerSize,playerSize,0);
        player->SetVel(0,0);
    }
    player->x=WIDTH/2; player->y=HEIGHT/2+300;
    
    int j=0, row=7;
    for(int i=-row/2; i<-row/2+level; i++){
        Bodies* obs = new Bodies(WIDTH/2+100*i-row*100*int(j/7),HEIGHT/2-200*int(j/7),enemySize,enemySize,1);
        obs->SetColour(225,0,0);
        enemy.push_back(obs);
        j++;
    }
    moveEnemy();
}

void SpaceShooter::loadImages(){
    SDL_Surface* image = SDL_LoadBMP("Images/blueSpaceShip.bmp");
    playerShipTexture = SDL_CreateTextureFromSurface(renderer, image);
    image = SDL_LoadBMP("Images/orangeSpaceShip.bmp");
    enemyShipTexture = SDL_CreateTextureFromSurface(renderer, image);
    image = SDL_LoadBMP("Images/spaceShooterInstructions.bmp");
    instructionScreenTexture = SDL_CreateTextureFromSurface(renderer, image);
    image = SDL_LoadBMP("Images/spaceShooterBG.bmp");
    backgroundTexture = SDL_CreateTextureFromSurface(renderer, image);
    image = SDL_LoadBMP("Images/fireBall.bmp");
    fireBallTexture = SDL_CreateTextureFromSurface(renderer, image);
    image = SDL_LoadBMP("Images/iceBall.bmp");
    iceBallTexture = SDL_CreateTextureFromSurface(renderer, image);
    image = SDL_LoadBMP("Images/ammoCrate.bmp");
    ammoCrate = SDL_CreateTextureFromSurface(renderer, image);
    image = SDL_LoadBMP("Images/heartIcon.bmp");
    heartTexture = SDL_CreateTextureFromSurface(renderer, image);
    image = SDL_LoadBMP("Images/gameOver.bmp");
    gameOverTexture = SDL_CreateTextureFromSurface(renderer, image);
}

void SpaceShooter::shootBullet(){
    if(time(NULL)-lastBullet>=rechargeTime && bulletCount>0){
        Bodies* obs = new Bodies(player->x+player->wid/2-bulletSize/2, player->y+player->wid/2-bulletSize/2, bulletSize, bulletSize, 2);
            obs->SetVel(Xdir*bulletStepSize,Ydir*bulletStepSize);
        obs->SetColour(255,0,0);
        bullet.push_back(obs);
        lastBullet=time(NULL);
        bulletCount--;
    }
}

void SpaceShooter::moveEnemy(){
    srand(time(NULL));
    for(int i=0; i<enemy.size(); i++){
        enemy[i]->SetVel(-difficulty/2+rand()%difficulty,-difficulty/2+rand()%difficulty);
    }
}

void SpaceShooter::key_down(SDL_KeyboardEvent* event ){
    if(event->repeat==0){
        switch (event->keysym.scancode)
        {
            case SDL_SCANCODE_UP:
                player->vel_y-=playerSpeed;
                break;
            case SDL_SCANCODE_DOWN:
                player->vel_y+=playerSpeed;
                break;
            case SDL_SCANCODE_LEFT:
                player->vel_x-=playerSpeed;
                break;
            case SDL_SCANCODE_RIGHT:
                player->vel_x+=playerSpeed; 
                break;
            case SDL_SCANCODE_SPACE:
                if(instructionScreen){
                    instructionScreen=false;
                    break;
                }
                if(enemyIsMoving==false){
                    if(playerCollide==true){
                        // while(true){
                        //     player->SetCoordinates(50+rand()%(WIDTH-100), 50+rand()%(HEIGHT-100));
                        //     bool safeCoordinates=true;
                        //     for(int i=0 ;i<enemy.size(); i++){
                        //         if(player->check_col(enemy[i])){
                        //             safeCoordinates=false;
                        //         }
                        //     }
                        //     if(safeCoordinates==true){
                        //         break;
                        //     }
                        // }
                        playerCollide=false;
                    }else{
                        enemyIsMoving=true;
                    }
                }else{
                    shootBullet();
                }
                break;
            case SDL_SCANCODE_ESCAPE:
                *gameRunning=-1;
                break;
            case SDL_SCANCODE_RETURN:
                if(instructionScreen){
                    instructionScreen=false;
                }else if(endScreen){
                    initialize();
                }
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
                player->vel_y+=playerSpeed;
                break;
            case SDL_SCANCODE_DOWN:
                player->vel_y-=playerSpeed;
                break;
            case SDL_SCANCODE_LEFT:
                player->vel_x+=playerSpeed;
                break;
            case SDL_SCANCODE_RIGHT:
                player->vel_x-=playerSpeed;
                break;
            default:
                break;
        }
    }
}

void SpaceShooter::move(){
    if(playerCollide==true){
        return;
    }
    //movement of player and enemies
    player->move();
    if(enemyIsMoving==false){
        return;
    }
    //movement of enemies
    if(enemyIsMoving)
        for(int i=0; i<enemy.size(); i++){
            enemy[i]->move();
        }

    //setting direction for the player's spaceship
    if(int(player->vel_x+0.1)==0){
        if(int(player->vel_y+0.1)!=0)   Xdir=0;}
    else if(int(player->vel_x+0.1)<0)   Xdir=-1;
    else if(int(player->vel_x+0.1)>0)   Xdir=1;

    if(int(player->vel_y+0.1)==0){
        if(int(player->vel_x+0.1)!=0)   Ydir=0;}
    else if(int(player->vel_y+0.1)<0)   Ydir=-1;
    else if(int(player->vel_y+0.1)>0)   Ydir=1;
    

    //check collision (enemy and bullet) and moving the bullet
    for(int i=0; i<bullet.size(); i++){
        for(int k=0; k<bulletSpeed/bulletStepSize; k++){
            bool del=false;
            for(int j=0; j<enemy.size(); j++){
                if(bullet[i]->check_col(enemy[j])){
                    enemy.erase(enemy.begin()+j);
                    bullet.erase(bullet.begin()+i);
                    i--; j--;
                    del=true;
                    break;
                }
            }
            if(del==true)
                break;
            if(bullet[i]->moveAndCheckWallCollision()==false){
                bullet.erase(bullet.begin()+i);
                i--;
                del=true;
                break;
            }
        }
    }

    //checking collision between enemy and player
    for(int i=0; i<enemy.size(); i++){
        if(player->check_col(enemy[i])){
            lives--;
            enemyIsMoving=false;
            playerCollide=true;
            while(bullet.size())    bullet.pop_back();
            if(lives==0){
                endScreen=true;
            }
            break;
        }
    }

    // win to load next level
    if(enemy.size()==0){
        std::cout << "Level " << level << " completed\n";
        loadLevel();
    }

    //bullet == 0 gets you exited
    if(bulletCount==0){
        endScreen=true;
    }
}

void SpaceShooter::render(){
    //rendering instruction screen
    if(instructionScreen==true){
        SDL_RenderCopy(renderer, instructionScreenTexture, NULL, NULL);
        return;
    }
    //end screen
    if(endScreen==true){
        SDL_RenderCopy(renderer, gameOverTexture, NULL, NULL);
        return;
    }
    SDL_RenderCopy(renderer, backgroundTexture, NULL, NULL);
    
    //if crash message
    if(playerCollide){
        if(!enemyIsMoving){
            //renderIcons(WIDTH/2-WIDTH/4, HEIGHT/2, WIDTH/2, HEIGHT/2, crashMessage);
        }
    }

    //heart icons
    for(int i=0; i<lives; i++){
        renderIcons(WIDTH-(iconSize+iconSpacing)*i-iconSize-iconIntending, iconIntending, iconSize, iconSize, heartTexture);
    }
    //bulletIcons
    for(int i=0, j=0, k=0; i<bulletCount; i++, j++){
        renderIcons(iconIntending+(iconSize+iconSpacing)*j, iconIntending+k*(iconSize+iconSpacing), iconSize, iconSize, fireBallTexture);
        if(j==10){
            j=-1;    k++;
        }
    }

    //the player
    player->displayWithAngle(renderer, playerShipTexture);
    //the enemies
    for(int i=0; i<enemy.size(); i++){
        enemy[i]->displayWithAngle(renderer, enemyShipTexture);
    }
    //the bullets
    for(int i=0; i<bullet.size(); i++){
        bullet[i]->display(renderer,fireBallTexture);
    }
}

void SpaceShooter::renderIcons(int x, int y, int wid, int hei, SDL_Texture* texture){
    SDL_Rect fillRect = {x, y, wid, hei};
    SDL_RenderCopy(renderer, texture, NULL, &fillRect);
}
