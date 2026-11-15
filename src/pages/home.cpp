#include "umbrella.hpp"

bool chatconf_box = false;

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

    // chats history
    ImGui::SetCursorPos(ImVec2(0, 35));
    ImGui::BeginChild("home_lateral_painel_chat_history", ImVec2(250, ViewportSizeX - 70));
    ImGui::SetCursorPos(ImVec2(5, 5));
    ImGui::Text("Your chats");
    ImGui::SameLine();
    if (ImGui::Button("New chat")) {
        // fazer alguma coisa
    }

    ImGui::SetCursorPosX(5);
    ImGui::BeginChild("home_lateral_painel_chat_history_chat_list", ImVec2(240, 600), ImGuiChildFlags_Borders);
    if (stored_chat_list.empty()) {
        ImGui::TextWrapped("You don't have saved chats");
    }
    ImGui::EndChild();

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
        on_conf_page();
    }
    ImGui::EndChild();

    // msg send box
    ImGui::SetCursorPos(ImVec2(300, ViewportSizeY - 150));
    ImGui::BeginChild("home_msgbox", ImVec2(ViewportSizeX - 350, 125), ImGuiChildFlags_Borders);

    static char msg_buffer[2048] = {};
    ImGui::SetCursorPos(ImVec2(5, 5));
    ImGui::InputTextMultiline("", msg_buffer, 2048, IMREL2(0.8, 0.95));
    ImGui::SameLine();
    ImGui::SetCursorPos(IMREL2(0.95, 0.75));
    
    ImGui::SetWindowFontScale(1.5f);
    if (ImGui::Button("Send")) {
        ImGui::SetWindowFontScale(1.0f);
        std::string msg(msg_buffer);
        memset(msg_buffer, '\0', 2048);
        ImGui::SetKeyboardFocusHere(-1);
    }

    ImGui::EndChild();

    // chat conf panel box button
    ImGui::SetCursorPos(ImVec2(ViewportSizeX - ImGui::CalcTextSize("Chat settings  ").x, 40));
    if (ImGui::Button("Chat settings")) chatconf_box = true;
    ImGui::SetCursorPos(ImVec2(ViewportSizeX - ImGui::CalcTextSize((model_selected + "  Chat settings  ").c_str()).x, 40));
    ImGui::Text(model_selected.c_str());

    if (chatconf_box) {
        ImGui::SetCursorPos(ImVec2(250, 35));
        ImGui::PushStyleColor(ImGuiCol_ChildBg, ImVec4(255, 255, 255, 255));
        ImGui::BeginChild("chatconf_box", ImVec2(ViewportSizeX - 250, ViewportSizeY - 35), ImGuiChildFlags_Borders);
        ImGui::PopStyleColor();

        ImGui::SetCursorPosX(ImGui::GetContentRegionMax().x - ImGui::CalcTextSize("Close  ").x);
        if (ImGui::Button("Close")) {
            chatconf_box = false;
        }

        ImGui::EndChild();
    }

    ImGui::End();
}