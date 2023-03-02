#include "../includes/gui.hpp"

void    GUIColors() {
    ImGuiStyle &style = ImGui::GetStyle();
    
    style.Colors[ImGuiCol_WindowBg] = ImColor(16, 16, 16, 50);
    style.Colors[ImGuiCol_ChildBg] = ImColor(47, 52, 77, 50);
    style.Colors[ImGuiCol_Text] = ImColor(255, 255, 255);

}