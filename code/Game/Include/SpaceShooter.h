#include"Bodies.h"
#include<vector>
#include"SDL.h"
#include<ctime>

class SpaceShooter{
    public:
    SpaceShooter(SDL_Renderer* rendererPointer, int* gameReset);
    void initialize();
    void loadLevel();
    void loadImages();
    void shootBullet();
    void moveEnemy();
    void key_down(SDL_KeyboardEvent* event );
    void key_up(SDL_KeyboardEvent* event );
    void move();
    void render();
    void renderIcons(int, int , int, int, SDL_Texture*);

    private:

    int level;
    
    //pointers
    std::vector<Bodies*> enemy;     //type 1
    std::vector<Bodies*> bullet;    //type 2
    Bodies* player=NULL;            //type 0
    
    //bullet details
    time_t lastBullet;//stores time of last bullet fired
    int rechargeTime=1;
    int bulletSize=20;
    int bulletSpeed=10;
    int bulletStepSize=5;
    int bulletCount;

    //playerStuff
    int playerSize=50;
    int Xdir, Ydir;
    int playerSpeed=5;
    int lives;
    bool playerCollide;

    //enemyStuff
    int enemySize=50;
    bool enemyIsMoving;
    int difficulty=10;
    

    //game related info
    bool keydowninfo;
    bool running;
    bool levelScreen;
    int* gameRunning;

    //heart and bullet counter details
    int iconSize=20;
    int iconSpacing=10;
    int iconIntending=10;

    //renderer and texture
    SDL_Renderer* renderer;
    SDL_Texture* instructionScreenTexture;
    SDL_Texture* gameOverTexture;
    SDL_Texture* backgroundTexture;
    SDL_Texture* playerShipTexture;
    SDL_Texture* enemyShipTexture;
    SDL_Texture* fireBallTexture;
    SDL_Texture* iceBallTexture;
    SDL_Texture* ammoCrate;
    SDL_Texture* heartTexture;
    SDL_Texture* crashMessage;
    bool instructionScreen;
    bool endScreen;
};