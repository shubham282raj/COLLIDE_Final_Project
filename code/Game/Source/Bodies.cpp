#include"Bodies.h"
#include"defs.h"
#include<cmath>
#include<iostream>
using namespace std;

Bodies::Bodies(double u, double v, double w, double h,int type): x(u),y(v),wid(w),hei(h), type(type) {
    r = 0;
    g = 0;
    b = 0;
    o = 255;
    vel_x=0;
    vel_y = 0;
    center = {wid/2, hei/2};
}

void Bodies::SetColour(int ri, int gi, int bi){
    r = ri;
    g = gi;
    b = bi;
}

void Bodies::SetColour(int ri, int gi, int bi, int oi){
    r = ri;
    g = gi;
    b = bi;
    o = oi;
}

void Bodies::SetCoordinates(int xi, int yi){
    x=xi;
    y=yi;
}

void Bodies::SetVel(int ux, int uy){
    vel_x = ux;
    vel_y = uy;
}


bool Bodies::check_col(Bodies* obs){
    // if(x + wid >= obs->x && x <= obs->x + obs->wid){
    //     if(y + hei >= obs->y && y <= obs->y + obs->hei){
    //         return true;
    //     }
    // }
    if(((x+wid)-(obs->x))*(x-(obs->x+obs->wid))<=0){
        if(((y+hei)-(obs->y))*(y-(obs->y+obs->hei))<=0){
            return true;
        }
    }
    return false;  
}

bool Bodies::check_col_and_rebound(Bodies* B){
    if(abs(x-B->x)<=(wid+B->wid)/2 && abs(y-B->y)<=(hei+B->hei)/2)
        if(abs(x-B->x)<abs(y-B->y)){
            swap(vel_y,B->vel_y);
        }else if(abs(x-B->x)>abs(y-B->y)){
            swap(vel_x,B->vel_x);
        }
        else{
            swap(vel_x,B->vel_x);
            swap(vel_y,B->vel_y);
        }
}

void Bodies::display(SDL_Renderer* renderer){
    SDL_Rect fillRect = {x ,y ,wid,hei};
    SDL_SetRenderDrawColor( renderer, r, g, b, o );
    SDL_RenderFillRect( renderer, &fillRect );
}

void Bodies::display(SDL_Renderer* renderer,SDL_Texture* texture){
    SDL_Rect fillRect = {x ,y ,wid,hei};
    SDL_RenderCopy(renderer, texture, NULL, &fillRect);
}

void Bodies::displayWithAngle(SDL_Renderer* renderer,SDL_Texture* texture){
    giveAngle();
    SDL_Rect fillRect = {x, y, wid, hei};
    SDL_RenderCopyEx(renderer, texture, NULL, &fillRect, angle, &center, SDL_FLIP_NONE);
}

bool Bodies::move(){
    //type 0 ->cannot go outside
    //type 1 ->rebound from boundary

    if(!(x+vel_x<0 || x+vel_x+wid>WIDTH)) x+=vel_x;
    else if(type==1)    vel_x=-vel_x;
    if(!(y+vel_y<0 || y+vel_y+hei>HEIGHT)) y+=vel_y;
    else if(type==1)    vel_y=-vel_y;

    return true;
}


bool Bodies::moveAndCheckWallCollision(){
    bool ret=true;
    if(!(x+vel_x<0 || x+vel_x+wid>WIDTH)) x+=vel_x;
    else ret=false;

    if(!(y+vel_y<0 || y+vel_y+hei>HEIGHT)) y+=vel_y;
    else ret=false;
    
    if(ret==false)   return false;
    return true;
}

void Bodies::giveAngle(){
    if(int(vel_x)==0){
        if(int(vel_y)==0){
            return;
        }else if(vel_y>0){
            angle=90;
        }else{
            angle=270;
        }
        return;
    }
    if(int(vel_y)==0){
        if(vel_x>0){
            angle=0;
        }else{
            angle=180;
        }
        return;
    }
    angle=atan(abs(vel_y/vel_x))*180/3.14;
    if(vel_x>0){
        if(vel_y<0){
            angle=360-angle;
        }
    }else{
        if(vel_y>0){
            angle=180-angle;
        }else{
            angle+=180;
        }
    }
}