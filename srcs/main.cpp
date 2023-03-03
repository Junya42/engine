#include "../includes/event.hpp"
#include "../includes/engine.hpp"
#include "../includes/gui.hpp"

#include "imconfig.h"
#include "imgui-SFML.h"
#include "imgui-SFML_export.h"
#include "imgui.h"
#include "imgui_internal.h"
#include "imstb_rectpack.h"
#include "imstb_textedit.h"
#include "imstb_truetype.h"

#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/Window/Event.hpp>

#include <algorithm>

int main()
{

    Engine engine;
    
    if (engine.create_window(sf::VideoMode(ScreenWidth, ScreenHeight), "Hello World!"))
        return 1;
    //engine.onUserCreate("obj_files/axis.obj");
    ImGui::SFML::Init(engine.window); 
    
    float   time = 0;
    sf::Clock deltaClock;

    GUIColors();

    while (engine.window.isOpen()) {

        eventloop(engine.window, engine.player);
        
        ImGui::SFML::Update(engine.window, deltaClock.restart());

        
        object_window(engine);
        select_window(engine);
        save_load_window(engine);
        
        engine.onUserUpdate(time);

        ImGui::SFML::Render(engine.window);
        engine.window.display();
        if (!engine.player.pause)
            time += 0.001f;
    }
    ImGui::SFML::Shutdown();
    return 0;
}