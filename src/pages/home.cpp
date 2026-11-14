#include "umbrella.hpp"

void page_home() {
    float ViewportSizeX = ImGui::GetMainViewport()->WorkSize.x;
    float ViewportSizeY = ImGui::GetMainViewport()->WorkSize.y;

    ImGui::SetNextWindowPos(ImGui::GetMainViewport()->WorkPos);
    ImGui::SetNextWindowSize(ImGui::GetMainViewport()->WorkSize);
    ImGui::Begin("this_dont_appear_home", nullptr, ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoScrollWithMouse | ImGuiWindowFlags_NoScrollbar);

    ImGui::SetCursorPosX(ImGui::GetWindowContentRegionMax().x - ImGui::CalcTextSize("lemon - home").x);
    ImGui::Text("lemon - home");

    // lateral painel
    ImGui::SetCursorPos(ImVec2(0, 0));
    ImGui::BeginChild("home_lateral_painel", ImVec2(250, ViewportSizeY), ImGuiChildFlags_Borders, ImGuiWindowFlags_NoScrollWithMouse | ImGuiWindowFlags_NoScrollbar);
    
    ImGui::SetCursorPos(ImVec2(0, ViewportSizeY - 35));
    ImGui::BeginChild("home_lateral_painel_bottom", ImVec2(250, 35), ImGuiChildFlags_Borders);
    ImGui::Text(("Hi! " + username).c_str());
    ImGui::EndChild();

    ImGui::EndChild();

    // top painel
    ImGui::SetCursorPos(ImVec2(0, 0));
    ImGui::BeginChild("home_painel_top", ImVec2(ViewportSizeX, 35), ImGuiChildFlags_Borders);
    if (ImGui::Button("debug mode")) {
        curr_page = "debug";
    }
    ImGui::SameLine();
    if (ImGui::Button("configurations")) {
        curr_page = "conf";
    }
    ImGui::EndChild();

    ImGui::End();
}