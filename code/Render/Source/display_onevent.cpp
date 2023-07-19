#include"display.h"

void display::OnEvent(SDL_Event* event){
    
    while(SDL_PollEvent(event)){
        switch (event->type){
            case SDL_QUIT:
                start->running = false;
                break;

            case SDL_KEYDOWN:  
                start->key_down(&(event->key));
                break;

            case SDL_KEYUP:
                start->key_up(&(event->key));
                break;
            case SDL_MOUSEBUTTONDOWN:
                start->mouse_down(&(event->button));
                break;
            default:
                break;
        }
    }
    

}

