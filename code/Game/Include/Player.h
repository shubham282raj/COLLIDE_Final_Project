#ifndef _PLAYER_H_
#define _PLAYER_H_

#define PLAYER_SIZE 10
#define PLAYER_SPEED 0.1

class Player{
    private:
    int x,y;
    int vel_x,vel_y;

    public:
    Player();
    Player(int u, int v);
    int get_x();
    int get_y();
    void inc_vel_x(int u);
    void inc_vel_y(int u);
    void move();
};

#endif