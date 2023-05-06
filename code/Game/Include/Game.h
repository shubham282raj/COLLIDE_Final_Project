#include"Player.h"
#include"SDL.h"

class Game{
    public:
    Player* player;
    Game();
    Game(int u, int v);
    void key_down(SDL_KeyboardEvent* event );
    void key_up(SDL_KeyboardEvent* event );
    void move();
    void render(SDL_Renderer* renderer);
};