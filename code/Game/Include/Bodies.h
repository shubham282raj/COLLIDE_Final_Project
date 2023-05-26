#ifndef _BODIES_H_
#define _BODIES_H_

#include"SDL.h"

class Bodies{
    public:
    Bodies(double u, double v, double w, double h, int type);
    bool check_col(Bodies* B);
    void display(SDL_Renderer* renderer);
    void SetColour(int ri, int gi, int bi);
    void SetVel(int ux, int uy);
    void move();

    double x,y;
    double vel_x,vel_y;
    
    private:
    double wid,hei;
    int type;
    int r,g,b,o;
};

#endif