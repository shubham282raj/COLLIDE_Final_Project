#include"Bodies.h"
#include<vector>
#include"SDL.h"

#define RESET_TIME 200

class FlappyBird{
    public:
    FlappyBird(SDL_Renderer* copy, int* n);
    void initialize();
    void loadImages();
    void giveVelocity();
    void key_down(SDL_KeyboardEvent* event );
    void key_up(SDL_KeyboardEvent* event );
    void mouse_down(SDL_MouseButtonEvent* event);
    void move();
    void render();
    void bird_render();

    private:
    int jump_velocity=8;
    int timer;
    Bodies* bird;
    std::vector<Bodies*> wall;
    bool running;
    bool moving=false;
    int* gameRunning;

    //measurements
    int inaccuracy=350;//how much up or down from mean the space can go
    int horSpace=350;
    int vertSpace=180;
    int birdSize=50;
    int poleThickness=60;
    int poleVelocity=-5;
    float gravity=0.4;

    //bird angle stuff
    SDL_Point center;
    float angle;
    int dyingX, dyingY;

    //renderer and textures
    SDL_Renderer* renderer;
    SDL_Texture* bg_texture;
    SDL_Texture* bird_texture;
    SDL_Texture* pipe_texture;
    SDL_Texture* boom;
};