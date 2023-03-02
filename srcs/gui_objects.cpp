#include "../includes/gui.hpp"

void    object_window(Engine &engine) {
      static size_t curr = 0;
            ImGui::BeginChild("##LeftSide", ImVec2(250, ImGui::GetContentRegionAvail().y), true);
            {
                char buf[255];
                std::string tmp;
                if (ImGui::InputText("Load an object", buf, sizeof(buf), 32)) {
                    engine.onUserCreate(buf);
                }
                ImGui::SeparatorEx(ImGuiSeparatorFlags_Horizontal);
                ImGui::SeparatorEx(ImGuiSeparatorFlags_Horizontal);
                for (size_t index = 0; index < engine.meshCube.size(); index++) {
                    bool selected = (curr == index);
                    if (ImGui::Selectable(engine.meshCube[index].name.c_str(), &selected))
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
                ImGui::SeparatorEx(ImGuiSeparatorFlags_Horizontal);
                ImGui::SeparatorEx(ImGuiSeparatorFlags_Horizontal);
                ImGui::SliderFloat("Position X", &currMesh.pos[0], -500.0f, 500.0f);
                ImGui::SliderFloat("Position Y", &currMesh.pos[1], -500.0f, 500.0f);
                ImGui::SliderFloat("Position Z", &currMesh.pos[2], -500.0f, 500.0f);
                ImGui::SeparatorEx(ImGuiSeparatorFlags_Horizontal);
                ImGui::SeparatorEx(ImGuiSeparatorFlags_Horizontal);
                ImGui::ColorEdit3("Color Circle", currMesh.col);

            }
            ImGui::EndChild();
}
