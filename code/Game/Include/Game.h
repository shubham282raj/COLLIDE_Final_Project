#include"Bodies.h"
#include<vector>
#include"SDL.h"

#define RESET_TIME 200

class Game{
    public:
    Game();
    void initialize();
    void key_down(SDL_KeyboardEvent* event );
    void key_up(SDL_KeyboardEvent* event );
    void move();
    void render(SDL_Renderer* renderer);

    private:
    int timer;
    std::vector<Bodies*> listOfBodies;
    bool running;
};