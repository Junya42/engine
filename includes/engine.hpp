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
#include <algorithm>

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
		float w = i.x * m.m[0][3] + i.y * m.m[1][3] + i.z * m.m[2][3] + m.m[3][3];

		if (w != 0.0f)
		{
			o.x /= w; o.y /= w; o.z /= w;
		}
    }
    bool    onUserCreate(std::string filename) {
        
        /*
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
        */
        if (meshCube.LoadObjectFile(filename) == false) {
            std::cerr << "Couldn't load: " << filename << std::endl;
            exit(1);
        }

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

    bool    onUserUpdate(float fElapsedTime) {
        window.clear();

        mat4x4 matRotZ, matRotX;

        fTheta = 1.0f * fElapsedTime;

        matRotZ.m[0][0] = cosf(fTheta);
        matRotZ.m[0][1] = sinf(fTheta);
        matRotZ.m[1][0] = -sinf(fTheta);
        matRotZ.m[1][1] = cosf(fTheta);
        matRotZ.m[2][2] = 1;
        matRotZ.m[3][3] = 1;

        matRotX.m[0][0] = 1;
        matRotX.m[1][1] = cosf(fTheta * 0.5f);
        matRotX.m[1][2] = sinf(fTheta * 0.5f);
        matRotX.m[2][1] = -sinf(fTheta * 0.5f);
        matRotX.m[2][2] = cosf(fTheta * 0.5f);
        matRotX.m[3][3] = 1;

        sf::VertexArray save(sf::LinesStrip, 4);


        std::vector<triangle> TriToRaster;

        for (auto tri: meshCube.tris) {
            
            triangle triProjected, triTranslated, triRotatedZ, triRotatedZX;

            MultiplyMatrixVector(tri.p[0], triRotatedZ.p[0], matRotZ);
            MultiplyMatrixVector(tri.p[1], triRotatedZ.p[1], matRotZ);
            MultiplyMatrixVector(tri.p[2], triRotatedZ.p[2], matRotZ);

            MultiplyMatrixVector(triRotatedZ.p[0], triRotatedZX.p[0], matRotX);
            MultiplyMatrixVector(triRotatedZ.p[1], triRotatedZX.p[1], matRotX);
            MultiplyMatrixVector(triRotatedZ.p[2], triRotatedZX.p[2], matRotX);

            triTranslated = triRotatedZX;

            triTranslated.p[0].z = triRotatedZX.p[0].z + 8.0f;
            triTranslated.p[1].z = triRotatedZX.p[1].z + 8.0f;
            triTranslated.p[2].z = triRotatedZX.p[2].z + 8.0f;

            vec3d normal, line1, line2;

            line1.x = triTranslated.p[1].x - triTranslated.p[0].x;
            line1.y = triTranslated.p[1].y - triTranslated.p[0].y;
            line1.z = triTranslated.p[1].z - triTranslated.p[0].z;

            line2.x = triTranslated.p[2].x - triTranslated.p[0].x;
            line2.y = triTranslated.p[2].y - triTranslated.p[0].y;
            line2.z = triTranslated.p[2].z - triTranslated.p[0].z;

            normal.x = line1.y * line2.z - line1.z * line2.y;
            normal.y = line1.z * line2.x - line1.x * line2.z;
            normal.z = line1.x * line2.y - line1.y * line2.x;

            float lenght = sqrtf(powf(normal.x, 2) + powf(normal.y, 2) + powf(normal.z, 2));

            normal.x /= lenght; normal.y /= lenght; normal.z /= lenght;

            if (normal.x * (triTranslated.p[0].x - player.vCam.x) +
                    normal.y * (triTranslated.p[0].y - player.vCam.y) +
                       normal.z * (triTranslated.p[0].z - player.vCam.z) < 0.0f) {

                vec3d   light_dir = {0.0f, 0.0f, -1.0f};

                lenght = sqrtf(powf(light_dir.x, 2) + powf(light_dir.y, 2) + powf(light_dir.z, 2));
                light_dir.x /= lenght; light_dir.y /= lenght; light_dir.z /= lenght;

                float dp = normal.x * light_dir.x + normal.y * light_dir.y + normal.z * light_dir.z;
                
                triProjected.color.r = 255 * dp;
                triProjected.color.g = 255 * dp;
                triProjected.color.b = 255 * dp;
                //std::cout << dp << std::endl;

                MultiplyMatrixVector(triTranslated.p[0], triProjected.p[0], matProj);
                MultiplyMatrixVector(triTranslated.p[1], triProjected.p[1], matProj);
                MultiplyMatrixVector(triTranslated.p[2], triProjected.p[2], matProj);

                triProjected.p[0].x += 1.0f; triProjected.p[0].y += 1.0f;
                triProjected.p[1].x += 1.0f; triProjected.p[1].y += 1.0f;
                triProjected.p[2].x += 1.0f; triProjected.p[2].y += 1.0f;

                triProjected.p[0].x *= 0.5f * (float)ScreenWidth;
                triProjected.p[0].y *= 0.5f * (float)ScreenHeight;
                triProjected.p[1].x *= 0.5f * (float)ScreenWidth;
                triProjected.p[1].y *= 0.5f * (float)ScreenHeight;
                triProjected.p[2].x *= 0.5f * (float)ScreenWidth;
                triProjected.p[2].y *= 0.5f * (float)ScreenHeight;

                TriToRaster.push_back(triProjected);
            }
        }

        std::sort(TriToRaster.begin(), TriToRaster.end(), [](triangle &t1, triangle &t2) {
                
            float z1 = (t1.p[0].z + t1.p[1].z + t1.p[2].z) / 3.0f;
			float z2 = (t2.p[0].z + t2.p[1].z + t2.p[2].z) / 3.0f;
			return z1 > z2;
        });

        int i = 0;
        for (auto &triProjected: TriToRaster) {
            
            eventloop(window, player);
            if (i && player.part)
                window.draw(save);
            if (player.part) {
                save[0].position = sf::Vector2f(triProjected.p[0].x, triProjected.p[0].y);
                save[1].position = sf::Vector2f(triProjected.p[1].x, triProjected.p[1].y);
                save[2].position = sf::Vector2f(triProjected.p[2].x, triProjected.p[2].y);
                save[3].position = sf::Vector2f(triProjected.p[0].x, triProjected.p[0].y);

                save[0].color = sf::Color::White;
                save[1].color = sf::Color::White;
                save[2].color = sf::Color::White;
                save[3].color = sf::Color::White;
            }
            if (player.part) {
                
                sf::VertexArray tmp(sf::LinesStrip, 4);

                tmp[0].position = sf::Vector2f(triProjected.p[0].x, triProjected.p[0].y);
                tmp[1].position = sf::Vector2f(triProjected.p[1].x, triProjected.p[1].y);
                tmp[2].position = sf::Vector2f(triProjected.p[2].x, triProjected.p[2].y);
                tmp[3].position = sf::Vector2f(triProjected.p[0].x, triProjected.p[0].y);

                tmp[0].color = sf::Color::Blue;
                tmp[1].color = sf::Color::Blue;
                tmp[2].color = sf::Color::Blue;
                tmp[3].color = sf::Color::Blue;
                window.draw(tmp);  
            }
            else {

                sf::VertexArray tmp(sf::Triangles, 4);

                tmp[0].position = sf::Vector2f(triProjected.p[0].x, triProjected.p[0].y);
                tmp[1].position = sf::Vector2f(triProjected.p[1].x, triProjected.p[1].y);
                tmp[2].position = sf::Vector2f(triProjected.p[2].x, triProjected.p[2].y);
                tmp[3].position = sf::Vector2f(triProjected.p[0].x, triProjected.p[0].y);

                tmp[0].color = triProjected.color;
                tmp[1].color = triProjected.color;
                tmp[2].color = triProjected.color;

                window.draw(tmp);
                if (player.debug) {

                    sf::VertexArray tmpline(sf::LinesStrip, 4);

                    tmpline[0].position = sf::Vector2f(triProjected.p[0].x, triProjected.p[0].y);
                    tmpline[1].position = sf::Vector2f(triProjected.p[1].x, triProjected.p[1].y);
                    tmpline[2].position = sf::Vector2f(triProjected.p[2].x, triProjected.p[2].y);
                    tmpline[3].position = sf::Vector2f(triProjected.p[0].x, triProjected.p[0].y);

                    tmpline[0].color = sf::Color::Blue;
                    tmpline[1].color = sf::Color::Blue;
                    tmpline[2].color = sf::Color::Blue;
                    tmpline[3].color = sf::Color::Blue;
                    window.draw(tmpline); 
                }
            }
            i++;
            if (player.part) {
                std::cout << "i: " << i << std::endl;
                usleep(500000);
                window.display();
            }

        }
            
        if (player.part)
            std::cout << std::endl;
        return true;
    }

    sf::RenderWindow window;
    mesh meshCube;
    Player player;
    mat4x4 matProj;
    float   fTheta;
};

#endif