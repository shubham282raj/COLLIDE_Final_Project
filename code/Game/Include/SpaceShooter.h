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
    void key_down(SDL_KeyboardEvent* event );
    void key_up(SDL_KeyboardEvent* event );
    void move();
    void render();
    void renderWithAngle(Bodies* body);
    float giveAngle();

    private:

    int level;

    //bullet details
    time_t lastBullet;//stores time of last bullet fired
    int rechargeTime=1;
    int bulletSize=10;
    int bulletSpeed=10;
    
    //pointers
    std::vector<Bodies*> enemy;     //type 1
    std::vector<Bodies*> bullet;    //type 2
    Bodies* player=NULL;            //type 0

    //playerStuff
    int playerSize=40;
    int Xdir, Ydir;

    //enemyStuff
    int enemySize=40;
    


    bool running;
    int* gameRunning;


    //renderer and texture
    SDL_Renderer* renderer;
    SDL_Texture* backgroundTexture;
    SDL_Texture* playerShipTexture;
    SDL_Texture* enemyShipTexture;
    SDL_Texture* bulletTexture;
    SDL_Texture* xyz;
    
};