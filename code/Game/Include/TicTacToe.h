#include"Bodies.h"
#include<vector>
#include"SDL.h"
#include<iostream>

class Board{
    public:
    Board(SDL_Renderer* rendererPointer, int* gameReset);
    void initialize();
    void loadImages();    
    void key_down(SDL_KeyboardEvent* event );
    void mouse_down(SDL_MouseButtonEvent* event);
    void checkWin();
    void move();
    void render();

    private:
    int* gameRunning;
    int boxSize=180;
    int boxGap=30;

    int Xmouse;
    int Ymouse;

    int x, y;
    bool hover;


    Bodies*** box;
    Bodies* winner;
    Bodies* board;
    int arr[3][3];
    int chance=1;
    int win=0;
    bool animation;
    int animationSpeed=5;
    int sizeIncSpeed=3;
    bool running=true;

    SDL_Renderer* renderer;
    SDL_Texture* cross;//-1
    SDL_Texture* circle;//1
    SDL_Texture* tie;//2
    SDL_Texture* checkBoard;
};