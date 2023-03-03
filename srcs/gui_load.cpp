#include "../includes/gui.hpp"
#include <fstream>


void    load_engine(Engine &engine) {

    std::ifstream file(engine.savefile.c_str());

    if (file.is_open()) {
        std::cout << "\033[1;34mLoad file open\033[0m" << std::endl;
        engine.meshCube.clear();
        engine.objCount = 0;
        engine.Targets.clear();

        int i = -1;
        std::vector<vec3d> verts;

        engine.matProj = engine.Matrix_MakeProjection((float)FieldOfView, (float)ScreenHeight / (float)ScreenWidth, 0.1f, 1000.0f);
        while (!file.eof()) {

            char line[128];
            file.getline(line, 128);

            std::istringstream s(line);

            std::string junk;
            std::string tmpjunk;
            s >> junk;
            if (junk == "objCount")
                s >> engine.objCount;
            else if (junk == "Mesh") {
                mesh newMesh;

                s >> newMesh.name;
                engine.meshCube.push_back(newMesh);
                verts.clear();
                i++;
            }
            else if (junk == "id")
                s >> engine.meshCube[i].id;
            else if (junk == "render")
                s >> tmpjunk;
            else if (junk == "debug")
                s >> tmpjunk;
            else if (junk == "position")
                s >> engine.meshCube[i].pos[0] >> engine.meshCube[i].pos[1] >> engine.meshCube[i].pos[2];
            else if (junk == "rotation")
                s >> engine.meshCube[i].rot[0] >> engine.meshCube[i].rot[1] >> engine.meshCube[i].rot[2];
            else if (junk == "color")
                s >> engine.meshCube[i].col[0] >> engine.meshCube[i].col[1] >> engine.meshCube[i].col[2];
            else if (junk == "v") {
                vec3d vec;
                s >> vec.x >> vec.y >> vec.z;
                verts.push_back(vec);
            }
            else if (junk == "f") {
                int f[3];
                s >> f[0] >> f[1] >> f[2];
                engine.meshCube[i].tris.push_back({verts[f[0] - 1], verts[f[1] - 1], verts[f[2] - 1]});
            }

        }
        file.close();
    }
    else
        std::cout << "\033[1;31mCan't open load file\033[0m" << std::endl;
}