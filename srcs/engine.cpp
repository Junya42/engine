#include "../includes/engine.hpp"

Engine::Engine(void){}

Engine::~Engine(void){}

int     Engine::create_window(sf::VideoMode mode, 
    const std::string &title, uint32_t style, const sf::ContextSettings& settings) {

    window.create(mode, title, style, settings);
    if (!window.isOpen())
        return 1;
    return 0;
}