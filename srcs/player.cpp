#include "../includes/player.hpp"

double Convert(double degree) {
    double pi = 3.14159265359;
    return (degree * (pi / 180));
}

Player::Player(void) {

    upper = lower = w = a = s = d = up = left = down = right = 0;

    x = 70;
    y = -110;
    z = 20;

    view = 0;
    angle = 0;
    
    double  current;
    for (int i = 0; i < 360; i++) {
        current = Convert(i);
        tcos[i] = cos(current);
        tsin[i] = sin(current);
    }
}

Player::~Player(void) {
}

void    Player::secure_angle(int n) {
    
    angle += n;
        
    if (angle < 0)
        angle += 360;
    else if (angle > 359)
        angle -= 360;
}

void    Player::move(void) {

    if (left)
        secure_angle(-4);
    else if (right)
        secure_angle(4);

    int dx = tsin[angle] * 10.0;
    int dy = tcos[angle] * 10.0;
    
    if (w) {
        x += dx;
        y += dy;
    }
    else if (s) {
        x -= dx;
        y -= dy;
    }

    if (a) {
        x -= dy;
        y += dx;
    }
    else if (d) {
        x += dy;
        y -= dx;
    }

    if (up)
        view -= 1;
    else if (down)
        view += 1;

    if (upper)
        z -= 4;
    else if (lower)
        z += 4;
}