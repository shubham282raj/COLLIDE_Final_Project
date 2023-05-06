#ifndef _CAPP_H_
#define _CAPP_H_
 
#include <SDL.h>
#include "defs.h"
#include "Game.h"

class display {
    private:
    bool running;
    SDL_Window* window;
    SDL_Renderer* renderer;
    Game* game;

    public:

    display();
    int OnExecute();
    
    bool OnInit();
  
    void OnEvent(SDL_Event* Event);
    void key_down_event(SDL_KeyboardEvent* Event);
    void key_up_event(SDL_KeyboardEvent* Event);
    void OnLoop();
    void OnRender();
    void OnCleanup();
 
};
 
#endif