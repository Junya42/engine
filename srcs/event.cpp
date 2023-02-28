#include "../includes/event.hpp"

void    eventloop(sf::RenderWindow &window, Player &player) {
    sf::Event event;

    while (window.pollEvent(event))
    {
        switch (event.type) {
            case sf::Event::Closed:
                window.close();
                break;
            case sf::Event::KeyPressed:
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
                    window.close();
                    break;
                }
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
                    if (player.pause)
                        player.pause = 0;
                    else
                        player.pause = 1;
                    std::cout << "Pause" << std::endl;
                }
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::P)) {
                    player.debug = 1;
                    std::cout << "Debug" << std::endl;          
                }
                else
                    player.debug = 0;
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z)) {
                    player.part = 1;
                    std::cout << "Partionning" << std::endl;          
                }
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::G)) {
                    if (player.part) {
                        player.part = 0;
                        std::cout << "DE-Partionning" << std::endl;
                    }
                }
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
                    player.left = 1;
                    std::cout << "Left" << std::endl;
                }
                else {
                    player.left = 0;
                }
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
                    player.right = 1;
                    std::cout << "Right" << std::endl;
                }
                else {
                    player.right = 0;
                }
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
                    player.up = 1;
                    std::cout << "Up" << std::endl;
                }
                else {
                    player.up = 0;
                }
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
                    player.down = 1;
                    std::cout << "Down" << std::endl;
                }
                else {
                    player.down = 0;
                }
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
                    player.w = 1;
                    std::cout << "W" << std::endl;
                }
                else {
                    player.w = 0;
                }
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
                    player.s = 1;
                    std::cout << "S" << std::endl;
                }
                else {
                    player.s = 0;
                }
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
                    player.d = 1;
                    std::cout << "D" << std::endl;
                }
                else {
                    player.d = 0;
                }
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
                    player.a = 1;
                    std::cout << "A" << std::endl;
                }
                else {
                    player.a = 0;
                }
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
                    player.upper = 1;
                    std::cout << "Upper" << std::endl;
                }
                else {
                    player.upper = 0;
                }
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::C)) {
                    player.lower = 1;
                    std::cout << "Lower" << std::endl;
                }
                else {
                    player.lower = 0;
                }
                break;
            default:
                break;
        }
    }
}