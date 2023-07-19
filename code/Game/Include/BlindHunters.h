#include"Bodies.h"
#include<vector>
#include"SDL.h"
#include<ctime>

class BlindHunters{
    public:
    BlindHunters(SDL_Renderer* rendererPointer,int* gameReset);
    void initialize();
    void loadImages();
    void move_obstacle();
    void key_down(SDL_KeyboardEvent* event );
    void key_up(SDL_KeyboardEvent* event );
    void move();
    void render();

    private:

    Bodies* player;
    std::vector<Bodies*> hunters;

    int playerSize=40;
    int hunterSize=40;
    int hunterCount=7;
    int difficulty=15;

    bool running;
    bool moving;

    int* gameRunning;

    //renderer and textures
    SDL_Renderer* renderer;
    SDL_Texture* backgroundTexture;
    SDL_Texture* playerTexture;
    SDL_Texture* hunterTexture;


};