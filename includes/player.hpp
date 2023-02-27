#ifndef PLAYER_HPP
# define PLAYER_HPP

#include "define.hpp"
#include <cmath>

struct Player {
    Player(void);
    ~Player(void);

    void    secure_angle(int n);
    void    move(void);

    float   x, y, z;
    int     angle;
    int     view;
    int w, a, s, d;
    int up, left, down, right;
    int upper, lower;

    float   tcos[360];
    float   tsin[360];
};

#endif