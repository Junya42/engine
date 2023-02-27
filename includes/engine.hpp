#ifndef ENGINE_HPP
# define ENGINE_HPP

#include "event.hpp"
#include "player.hpp"
#include "define.hpp"
#include "mesh.hpp"

#include <SFML/Graphics/Image.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Window/VideoMode.hpp>

struct mat4x4 {
    float m[4][4] = {0};
};

struct Engine {

    Engine(void);
    ~Engine(void);

    int create_window(sf::VideoMode mode, 
                    const std::string &title, 
                    uint32_t style = sf::Style::Default, 
                    const sf::ContextSettings &settings = sf::ContextSettings());

    void    MultiplyMatrixVector(vec3d &i, vec3d &o, mat4x4 &m) {

        o.x = i.x * m.m[0][0] + i.y * m.m[1][0] + i.z * m.m[2][0] + m.m[3][0];
        o.y = i.x * m.m[0][1] + i.y * m.m[1][1] + i.z * m.m[2][1] + m.m[3][1];
        o.z = i.x * m.m[0][2] + i.y * m.m[1][2] + i.z * m.m[2][2] + m.m[3][2];

        float w;
        
        w = i.x * m.m[0][3] + i.y * m.m[1][3] + i.z * m.m[2][3] + m.m[3][3];

        if (w != 0.0f) {
            o.x /= w; o.y /= w; o.z /= w;
        }
    }
    bool    onUserCreate() {
        
		meshCube.tris = {

		// SOUTH
		{ 0.0f, 0.0f, 0.0f,    0.0f, 1.0f, 0.0f,    1.0f, 1.0f, 0.0f },
		{ 0.0f, 0.0f, 0.0f,    1.0f, 1.0f, 0.0f,    1.0f, 0.0f, 0.0f },

		// EAST                                                      
		{ 1.0f, 0.0f, 0.0f,    1.0f, 1.0f, 0.0f,    1.0f, 1.0f, 1.0f },
		{ 1.0f, 0.0f, 0.0f,    1.0f, 1.0f, 1.0f,    1.0f, 0.0f, 1.0f },

		// NORTH                                                     
		{ 1.0f, 0.0f, 1.0f,    1.0f, 1.0f, 1.0f,    0.0f, 1.0f, 1.0f },
		{ 1.0f, 0.0f, 1.0f,    0.0f, 1.0f, 1.0f,    0.0f, 0.0f, 1.0f },

		// WEST                                                      
		{ 0.0f, 0.0f, 1.0f,    0.0f, 1.0f, 1.0f,    0.0f, 1.0f, 0.0f },
		{ 0.0f, 0.0f, 1.0f,    0.0f, 1.0f, 0.0f,    0.0f, 0.0f, 0.0f },

		// TOP                                                       
		{ 0.0f, 1.0f, 0.0f,    0.0f, 1.0f, 1.0f,    1.0f, 1.0f, 1.0f },
		{ 0.0f, 1.0f, 0.0f,    1.0f, 1.0f, 1.0f,    1.0f, 1.0f, 0.0f },

		// BOTTOM                                                    
		{ 1.0f, 0.0f, 1.0f,    0.0f, 0.0f, 1.0f,    0.0f, 0.0f, 0.0f },
		{ 1.0f, 0.0f, 1.0f,    0.0f, 0.0f, 0.0f,    1.0f, 0.0f, 0.0f },

		};

        // Projection Matrix

        float   fNear = 0.1f;
        float   fFar = 1000.0f;
        float   fFov = (float)FieldOfView;
        float   fAspectRatio = (float)ScreenHeight / (float)ScreenWidth;
        float   fFovRad = 1.0f / tanf(fFov * 0.5f / 180.0f * 3.14159f);

        matProj.m[0][0] = fAspectRatio * fFovRad;
        matProj.m[1][1] = fFovRad;
        matProj.m[2][2] = fFar / (fFar - fNear);
        matProj.m[3][2] = (-fFar * fNear) / (fFar - fNear);
        matProj.m[2][3] = 1.0f;
        matProj.m[3][3] = 0.0f;

        return true;
    }

    bool    onUserUpdate(void) {
        window.clear();

        int i = 0;
        for (auto tri: meshCube.tris) {
            triangle triProjected, triTranslated;

            triTranslated = tri;

            triTranslated.p[0].z = tri.p[0].z + 3.0f;
            triTranslated.p[1].z = tri.p[1].z + 3.0f;
            triTranslated.p[2].z = tri.p[2].z + 3.0f;

            MultiplyMatrixVector(triTranslated.p[0], triProjected.p[0], matProj);
            MultiplyMatrixVector(triTranslated.p[1], triProjected.p[1], matProj);
            MultiplyMatrixVector(triTranslated.p[2], triProjected.p[2], matProj);

            /*sf::VertexArray tmp(sf::Triangles, 3);

            tmp[0].position = sf::Vector2f(triProjected.p[0].x, triProjected.p[0].y);
            tmp[1].position = sf::Vector2f(triProjected.p[1].x, triProjected.p[1].y);
            tmp[2].position = sf::Vector2f(triProjected.p[2].x, triProjected.p[2].y);

            tmp[0].color = sf::Color::Red;
            tmp[1].color = sf::Color::Blue;
            tmp[1].color = sf::Color::Green;
            */

            triProjected.p[0].x += 1.0f; triProjected.p[0].y += 1.0f;
            triProjected.p[1].x += 1.0f; triProjected.p[1].y += 1.0f;
            triProjected.p[2].x += 1.0f; triProjected.p[2].y += 1.0f;

            triProjected.p[0].x *= 0.5f * (float)ScreenWidth;
            triProjected.p[0].y *= 0.5f * (float)ScreenHeight;
            triProjected.p[1].x *= 0.5f * (float)ScreenWidth;
            triProjected.p[1].y *= 0.5f * (float)ScreenHeight;
            triProjected.p[2].x *= 0.5f * (float)ScreenWidth;
            triProjected.p[2].y *= 0.5f * (float)ScreenHeight;

            sf::VertexArray tmp(sf::LinesStrip, 3);

            tmp[0].position = sf::Vector2f(triProjected.p[0].x, triProjected.p[0].y);
            tmp[1].position = sf::Vector2f(triProjected.p[1].x, triProjected.p[1].y);
            tmp[2].position = sf::Vector2f(triProjected.p[2].x, triProjected.p[2].y);

            window.draw(tmp);
            i++;
        }
        return true;
    }
    sf::RenderWindow window;
    mesh meshCube;
    std::vector<Player> players;
    mat4x4 matProj;
};

#endif