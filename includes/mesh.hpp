#ifndef MESH_HPP
# define MESH_HPP

#include <vector>
#include <SFML/Graphics/Image.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Window/VideoMode.hpp>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

struct vec3d
{
    float x, y, z;
};

struct triangle
{
    vec3d p[3];
    sf::Color color;
};

struct mesh
{
    std::vector<triangle> tris;

    bool    LoadObjectFile(std::string &filename) {

        std::ifstream f(filename);
        if (!f.is_open())
            return false;

        std::vector<vec3d> verts;

        std::cout << "Start loading" << std::endl;
        while (!f.eof()) {

            char line[128];
            f.getline(line, 128);

            std::istringstream s(line);

            std::cout << "\033[1;31m" << line << "\033[0m" << std::endl;
            char junk;
            if (line[0] == 'v' && line[1] == ' ') {

                vec3d v;
                s >> junk >> v.x >> v.y >> v.z;
                verts.push_back(v);
                std::cout << "V: " << v.x << " " << v.y << " " << v.z << std::endl;
            }
            
            else if (line[0] == 'f') {

                int f[3];
                s >> junk >> f[0] >> f[1] >> f[2];
                tris.push_back({verts[f[0] - 1], verts[f[1] - 1], verts[f[2] - 1]});
                std::cout << "f" << std::endl;
            }
            std::cout << std::endl;
        }
        std::cout << "Out of loading" << std::endl;
        return true;
    }
};

#endif