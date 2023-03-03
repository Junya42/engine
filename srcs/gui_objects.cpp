#include "../includes/gui.hpp"

void    select_window(Engine &engine) {

     engine.select = 0;
    if (engine.Targets.size()) {
            
            bool colorize = false;

            float           pos[3] = { 0.0f, 0.0f, 0.0f };
            float           rot[3] = { 0.0f, 0.0f, 0.0f };
            static float    col[3] = { 0.0f, 0.0f, 0.0f };

            std::string title = "Selected " + std::to_string(engine.Targets.size()) + " targets";
            ImGui::Begin("Selected objects", 0, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize);
            ImGui::BeginChild("Sub selected objects");
            ImGui::Text(title.c_str());
            ImGui::SeparatorEx(ImGuiSeparatorFlags_Horizontal);
            ImGui::SeparatorEx(ImGuiSeparatorFlags_Horizontal);
           
            ImGui::Text("Rotation X"); ImGui::SameLine();
            ImGui::Button("Rotation X +");  if (ImGui::IsItemActive())
                                                rot[0] += 1.0f;
            ImGui::SameLine();
            ImGui::Button("Rotation X -");  if (ImGui::IsItemActive())
                                                rot[0] -= 1.0f;
            ImGui::Text("Rotation Y"); ImGui::SameLine();
            ImGui::Button("Rotation Y +");  if (ImGui::IsItemActive())
                                                rot[1] += 1.0f;
            ImGui::SameLine();
            ImGui::Button("Rotation Y -");  if (ImGui::IsItemActive())
                                                rot[1] -= 1.0f;
            ImGui::Text("Rotation Z"); ImGui::SameLine();
            ImGui::Button("Rotation Z +");  if (ImGui::IsItemActive())
                                                rot[2] += 1.0f;
            ImGui::SameLine();
            ImGui::Button("Rotation Z -");  if (ImGui::IsItemActive())
                                                rot[2] -= 1.0f;

            ImGui::SeparatorEx(ImGuiSeparatorFlags_Horizontal);
            ImGui::SeparatorEx(ImGuiSeparatorFlags_Horizontal);
            ImGui::Text("Position X"); ImGui::SameLine();
            ImGui::Button("Position X +");  if (ImGui::IsItemActive())
                                                pos[0] += 1.0f;
            ImGui::SameLine();
            ImGui::Button("Position X -");  if (ImGui::IsItemActive())
                                                pos[0] -= 1.0f;
            ImGui::Text("Position Y"); ImGui::SameLine();
            ImGui::Button("Position Y +");  if (ImGui::IsItemActive())
                                                pos[1] -= 1.0f;
            ImGui::SameLine();
            ImGui::Button("Position Y -");  if (ImGui::IsItemActive())
                                                pos[1] += 1.0f;
            ImGui::Text("Position Z"); ImGui::SameLine();
            ImGui::Button("Position Z +");  if (ImGui::IsItemActive())
                                                pos[2] += 1.0f;
            ImGui::SameLine();
            ImGui::Button("Position Z -");  if (ImGui::IsItemActive())
                                                pos[2] -= 1.0f;

            ImGui::SeparatorEx(ImGuiSeparatorFlags_Horizontal);
            ImGui::SeparatorEx(ImGuiSeparatorFlags_Horizontal);
            
            ImGui::ColorEdit3("Color Circle", col);
            ImGui::SeparatorEx(ImGuiSeparatorFlags_Horizontal);
            if (ImGui::Button("Apply color to targets"))
                colorize = true;
            ImGui::EndChild();
            ImGui::End();
        
        for (auto target: engine.Targets) {
            target.second->pos[0] += pos[0];
            target.second->pos[1] += pos[1];
            target.second->pos[2] += pos[2];
            target.second->rot[0] += rot[0];

            if (target.second->rot[0] > 359)
                target.second->rot[0] -= 360;
            else if (target.second->rot[0] < 0)
                target.second->rot[0] += 360;

            target.second->rot[1] += rot[1];
            if (target.second->rot[1] > 359)
                target.second->rot[1] -= 360;
            else if (target.second->rot[1] < 0)
                target.second->rot[1] += 360;

            target.second->rot[2] += rot[2];
            if (target.second->rot[2] > 359)
                target.second->rot[2] -= 360;
            else if (target.second->rot[2] < 0)
                target.second->rot[2] += 360;
            
            if (colorize) {
                target.second->col[0] = col[0];
                target.second->col[1] = col[1];
                target.second->col[2] = col[2];
            }
        }
    }
    engine.mouse = sf::Mouse::getPosition(engine.window);
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
        engine.select = 1;
    else if (sf::Mouse::isButtonPressed(sf::Mouse::Right))
        engine.select = 2;
}


void    object_window(Engine &engine) {
      
      ImGui::Begin("Objects list", 0, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize);
      static size_t curr = 0;
            ImGui::BeginChild("##LeftSide", ImVec2(250, ImGui::GetContentRegionAvail().y), true);
            {
                if (ImGui::Button("Create a cube")) {
                    engine.onUserCreate("obj_files/cube.obj");
                }
                ImGui::SeparatorEx(ImGuiSeparatorFlags_Horizontal);
                ImGui::SeparatorEx(ImGuiSeparatorFlags_Horizontal);
                char buf[255];
                if (ImGui::InputText("Load an object", buf, sizeof(buf), 32)) {
                    engine.onUserCreate(buf);
                }
                ImGui::SeparatorEx(ImGuiSeparatorFlags_Horizontal);
                ImGui::SeparatorEx(ImGuiSeparatorFlags_Horizontal);
                std::string tmp;
                for (size_t index = 0; index < engine.meshCube.size(); index++) {
                    bool selected = (curr == index);
                    tmp = engine.meshCube[index].name + " " + std::to_string(index);
                    if (ImGui::Selectable(tmp.c_str(), &selected))
                        curr = index;
                    if (selected)
                        ImGui::SetItemDefaultFocus();
                }
            }
            ImGui::EndChild();
            {
                ImGui::SameLine(0);
                ImGui::SeparatorEx(ImGuiSeparatorFlags_Vertical);
                ImGui::SameLine();
            }
            ImGui::BeginChild("##RightSide", ImVec2(ImGui::GetContentRegionAvail().x, ImGui::GetContentRegionAvail().y), true);
            {
                if (engine.meshCube.size()) {
                    auto &currMesh = engine.meshCube[curr];
                    auto center = [] (float avail_width, float elem_width, float padding = 0) {
                        ImGui::SameLine(( avail_width * 0.5) - (elem_width * 0.5) + padding);
                    };
                    auto center_text = [&] (const char *format, ImColor color = ImColor(255,255,255)) {
                        center(ImGui::GetContentRegionAvail().x, ImGui::CalcTextSize(format).x);
                        ImGui::TextColored(color.Value, format);
                    };
                    center_text(currMesh.name.c_str());
                    ImGui::Checkbox("Render", &currMesh.render);
                    ImGui::Checkbox("Debug", &currMesh.debug);
                    ImGui::SeparatorEx(ImGuiSeparatorFlags_Horizontal);
                    ImGui::SeparatorEx(ImGuiSeparatorFlags_Horizontal);
                    ImGui::SliderFloat("Rotation X", &currMesh.rot[0], 0.0f, 360.0f);
                    ImGui::SliderFloat("Rotation Y", &currMesh.rot[1], 0.0f, 360.0f);
                    ImGui::SliderFloat("Rotation Z", &currMesh.rot[2], 0.0f, 360.0f);
                    if (ImGui::Button("Reset")) {
                        currMesh.rot[0] = 180.0f;
                        currMesh.rot[1] = 180.0f;
                        currMesh.rot[2] = 0.0f;
                    }
                    ImGui::SeparatorEx(ImGuiSeparatorFlags_Horizontal);
                    ImGui::SeparatorEx(ImGuiSeparatorFlags_Horizontal);
                    ImGui::SliderFloat("Position X", &currMesh.pos[0], -500.0f, 500.0f);
                    ImGui::SliderFloat("Position Y", &currMesh.pos[1], -500.0f, 500.0f);
                    ImGui::SliderFloat("Position Z", &currMesh.pos[2], -500.0f, 500.0f);
                    ImGui::SeparatorEx(ImGuiSeparatorFlags_Horizontal);
                    ImGui::SeparatorEx(ImGuiSeparatorFlags_Horizontal);
                    ImGui::ColorEdit3("Color Circle", currMesh.col);
                    ImGui::SeparatorEx(ImGuiSeparatorFlags_Horizontal);
                    ImGui::SeparatorEx(ImGuiSeparatorFlags_Horizontal);
                    if (ImGui::Button("Duplicate object")) {
                        engine.meshCube.push_back(currMesh);
                        engine.objCount++;
                        engine.meshCube[engine.meshCube.size() - 1].id = engine.objCount;
                    }
                }
            }
            ImGui::EndChild();
        ImGui::End();
}
