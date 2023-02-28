#include "../includes/event.hpp"
#include "../includes/engine.hpp"


int main()
{

    Engine engine;
    
    if (engine.create_window(sf::VideoMode(ScreenWidth, ScreenHeight), "Hello World!"))
        return 1;

    engine.onUserCreate("obj_files/spaceship.obj");
    
    float   time = 0;
    while (engine.window.isOpen()) {

        eventloop(engine.window, engine.player);
        engine.onUserUpdate(time);
        engine.window.display();
        if (!engine.player.pause)
            time += 0.005f;
    }
    return 0;
}
