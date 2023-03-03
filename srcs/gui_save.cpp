#include "../includes/gui.hpp"
#include <fstream>


void    save_engine(Engine &engine) {

    std::ofstream file(engine.savefile.c_str(), std::ios_base::in | std::ios_base::trunc);

    std::cout << "Save filename:" << engine.savefile.c_str() << std::endl;
    if (file.is_open()) {
        std::cout << "\033[1;34msave file open\033[0m" << std::endl;
        file << "Engine\n";
        file << "objCount " << engine.objCount << "\n\n";
        for (auto &currMesh : engine.meshCube) {
            file << "Mesh " << currMesh.name << "\n";
            file << "id " << currMesh.id << "\n";
            file << "render " << currMesh.render << "\n";
            file << "debug " << currMesh.debug << "\n";
            file << "position " << currMesh.pos[0] << " " << currMesh.pos[1] << " " << currMesh.pos[2] << "\n";
            file << "rotation " << currMesh.rot[0] << " " << currMesh.rot[1] << " " << currMesh.rot[2] << "\n";
            file << "color " << currMesh.col[0] << " " << currMesh.col[1] << " " << currMesh.col[2] << "\n";
            file << "\n";
            int fcount = 1;
            for (auto &tri : currMesh.tris) {
                for (int x = 0; x < 3; x++) {
                    file << "v " << tri.p[x].x << " " << tri.p[x].y << " " << tri.p[x].z << "\n";
                    fcount++;
                }
            }
            for (int f = 1; f < fcount; f+=3)
                    file << "f " << f << " " << f + 1 << " " << f + 2 << "\n";
        }
        file.close();
    }
    else
        std::cout << "\033[1;31mCan't open save file\033[0m" << std::endl;
}

void    save_load_window(Engine &engine) {

    ImGui::Begin("Save/Load", 0, ImGuiWindowFlags_NoTitleBar);
    ImGui::BeginChild("Sub save/load");
        if (ImGui::Button("Save"))
            save_engine(engine);
        ImGui::SameLine();
        if (ImGui::Button("Load"))
            load_engine(engine);
        ImGui::SameLine();
        ImGui::Text(engine.savefile.c_str());
        char buf[255];
        buf[0] = 's';
        buf[1] = 'a';
        buf[2] = 'v';
        buf[3] = 'e';
        buf[4] = '/';
        if (ImGui::InputText("Set current save/load file", buf, sizeof(buf), 32))
            engine.savefile = buf;

    ImGui::EndChild();
    ImGui::End();
}