#include "umbrella.hpp"

void page_conf() {
    ImGui::SetNextWindowPos(ImGui::GetMainViewport()->WorkPos);
    ImGui::SetNextWindowSize(ImGui::GetMainViewport()->WorkSize);
    ImGui::Begin("this_dont_appear_conf", nullptr, ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoMove);

    if (ImGui::Button("return to home")) {
        curr_page = "home";
    }
    ImGui::SameLine();
    ImGui::SetCursorPosX(ImGui::GetWindowContentRegionMax().x - ImGui::CalcTextSize("lemon - conf").x);
    ImGui::Text("lemon - conf");

    ImGui::End();
}