#include <SFML/Graphics.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <iostream>
#include <cstdlib>
#include <unistd.h>
#include <cmath>
#include "../includes/player.hpp"
#include "mesh.hpp"

vec3d    eventloop(sf::RenderWindow &window, Player &player);