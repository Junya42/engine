#include "../includes/event.hpp"
#include "../includes/engine.hpp"

/*
void    draw3d(Player &player, sf::RenderWindow &window) {

    int wx[4], wy[4], wz[4];
    float   CS = player.tcos[player.angle];
    float   SN = player.tsin[player.angle];

    int x1 = 40 - player.x;
    int x2 = 40 - player.x;

    int y1 = 10 - player.y;
    int y2 = 290 - player.y;

    wx[0] = x1 * CS - y1 * SN;
    wx[1] = x2 * CS - y2 * SN;

    wy[0] = y1 * CS + x1 * SN;
    wy[1] = y2 * CS + x2 * SN;

    wz[0] = 0 - player.z;
    wz[1] = 0 - player.z;

    wx[0] = wx[0] * 200 / wy[0] + SW2;
    wy[0] = wz[0] * 200 / wy[0] + SH2;

    wx[1] = wx[1] * 200 / wy[1] + SW2;
    wy[1] = wz[1] * 200 / wy[1] + SH2;

    sf::Vertex v1[2];

    v1[0].position = sf::Vector2f(wx[0], wy[0]);
    v1[1].position = sf::Vector2f(wx[0], wy[0]);

    v1[0].color = sf::Color::Red;
    v1[1].color = sf::Color::Red;


    sf::Vertex v2[2];

    v2[0].position = sf::Vector2f(wx[1], wy[0]);
    v2[1].position = sf::Vector2f(wx[1], wy[0]);

    v2[0].color = sf::Color::Blue;
    v2[1].color = sf::Color::Blue;

    window.draw(v1, 2, sf::Lines);
    window.draw(v2, 2, sf::Lines);

}
*/

void    drawRec(Player &player, sf::RenderWindow &window) {
    float x, y, z;

    x = y = z = 500.f;
    
    (void)x;
    (void)y;
    (void)z;
    (void)player;
    (void)window;

    sf::VertexArray triangle(sf::Triangles, 3);

    triangle[0].position = sf::Vector2f(x, y - 100); //top
    triangle[1].position = sf::Vector2f(x - 100, y + 100); //left
    triangle[2].position = sf::Vector2f(x + 100, y + 100); //right
    // on définit la couleur des sommets du triangle
    triangle[0].color = sf::Color::Red; //top
    triangle[1].color = sf::Color::Blue; //left
    triangle[2].color = sf::Color::Green; //right

    window.draw(triangle);
}

int main()
{
    /*sf::RenderWindow window(sf::VideoMode(1000, 1000), "SFML Window");

    Player player;
    while (window.isOpen())
    {
        eventloop(window, player);
        player.move();
        window.clear();
        drawRec(player, window);
      //  window.draw(shape);
        window.display();
    }*/

    Engine engine;
    Player player;

    if (engine.create_window(sf::VideoMode(ScreenWidth, ScreenHeight), "Hello World!"))
        return 1;

    engine.onUserCreate();
    //engine.onUserUpdate();
    while (engine.window.isOpen()) {
        eventloop(engine.window, player);
        engine.onUserUpdate();
        engine.window.display();
    }

    return 0;
}
