#ifndef _BODIES_H_
#define _BODIES_H_

#include"SDL.h"

class Bodies{
    public:
    Bodies(double u, double v, double w, double h, int type);
    bool check_col(Bodies* obs);
    bool check_col_and_rebound(Bodies* B);
    void display(SDL_Renderer* renderer);
    void display(SDL_Renderer* renderer,SDL_Texture* texture);
    void displayWithAngle(SDL_Renderer* renderer, SDL_Texture* texture);
    void SetColour(int ri, int gi, int bi);
    void SetColour(int ri, int gi, int bi, int oi);
    void SetCoordinates(int, int);
    void SetVel(int ux, int uy);
    bool move();
    bool moveInParts(int numofparts);
    bool moveAndCheckWallCollision();
    void giveAngle();


    SDL_Point center;
    float angle;
    double x,y;
    double vel_x,vel_y;
    double wid,hei;
    int type;
    int r,g,b,o;
    bool move_check;
};

#endif
