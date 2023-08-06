#include"Bodies.h"
#include"Game.h"
#include"FlappyBird.h"
#include"BlindHunters.h"
#include"TicTacToe.h"
#include"SpaceShooter.h"
#include<vector>
#include"SDL.h"
#include<ctime>


class Start{
    public:
    Start(SDL_Renderer* copy);
    void initialize();
    void loadImages();  
    void defineGame();
    void key_down(SDL_KeyboardEvent* event );
    void key_up(SDL_KeyboardEvent* event );
    void mouse_down(SDL_MouseButtonEvent* event);
    void move();
    void renderIcons(SDL_Renderer* renderer);
    void render(SDL_Renderer* renderer);

    SDL_Renderer* renderer;

    //game pointers
    Game* game;
    FlappyBird* bird = NULL;
    BlindHunters* hunter = NULL;
    Board* board = NULL;
    SpaceShooter* shooter = NULL;

    Bodies* selectionWindow; // selection window
    std::vector<Bodies*> gameType; //Blocks for games

    //asthetics
    int margin=10;
    int selectedWindow;
    int spaceSize=60;
    int gameCount=4;

    int gameRunning;
    bool memoryLeaks;
    bool running;
    bool hover;

    //mouseCoordinates
    int prevX, prevY;
    int Xmouse;
    int Ymouse;

    //gameIcons
    SDL_Texture* birdIcon;
    SDL_Texture* hunterIcon;
    SDL_Texture* tictactoeIcon;
    SDL_Texture* spaceShooterIcon;
    SDL_Texture* selectionWindowTexture;
    SDL_Texture* bgImage;

    //time
    time_t timer;
};