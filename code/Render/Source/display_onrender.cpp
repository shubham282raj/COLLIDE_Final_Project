#include"display.h"

void display::OnRender(){

    SDL_SetRenderDrawColor(renderer, 96, 128, 255, 255);
	SDL_RenderClear(renderer);

    
    start->render(renderer);

    
    SDL_RenderPresent(renderer);
}