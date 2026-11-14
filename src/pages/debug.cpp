#include "umbrella.hpp"

std::vector <std::string> slice_cmd(std::string str);

struct cmd_pair {
    std::string cmd;
    void (*func)(std::vector <std::string> args);
};

// commands
void console_help(std::vector <std::string> args) {
    debug_page_console_src +=
        "console commands list\n"
        "help - show this message\n"
        "say [msg] - is a test for args\n"
        "lcsf_load - load a file and dump\n";
}

void console_say(std::vector <std::string> args) {
    for (std::size_t i = 1; i < args.size(); i++) {
        debug_page_console_src += args[i];
        if (i + 1 < args.size()) {
            debug_page_console_src += " ";
        } else {
            debug_page_console_src += "\n";
        }
    }
}

void console_lcsf_load(std::vector <std::string> args) {
    std::filesystem::path fullpath(executable_dir / args[1]);
    std::vector <lcsf::lcsf_pair> src = lcsf::parse_file(fullpath.string());

    for (lcsf::lcsf_pair pair : src) {
        debug_page_console_src += pair.key + ":\n";
            for (std::string line : pair.lines) {
                debug_page_console_src += "    " + line + "\n";
            }
    }
}

cmd_pair cmd_list[] = {
    {"help", console_help},
    {"say", console_say},
    {"lcsf_load", console_lcsf_load},
};

void page_debug_cmd_handler(std::string full_cmd) {
    if (full_cmd == "") {
        debug_page_console_src += "> ";
        return;
    }
    std::vector <std::string> cmd_args = slice_cmd(full_cmd);
    std::string cmd = cmd_args[0];

    bool found = false;
    for (const cmd_pair pair : cmd_list) {
        if (cmd == pair.cmd) {
            found = true;
            pair.func(cmd_args);
        }
    }

    if (!found) {
        debug_page_console_src += "this command doenst exists, use help to see more\n";
    }
    debug_page_console_src += "> ";
}

void page_debug() {
    ImGui::SetNextWindowPos(ImGui::GetMainViewport()->WorkPos);
    ImGui::SetNextWindowSize(ImGui::GetMainViewport()->WorkSize);
    ImGui::Begin("this_dont_appear_debug", nullptr, ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoMove);

    if (ImGui::Button("return to home")) {
        curr_page = "home";
    }
    ImGui::SameLine();
    ImGui::SetCursorPosX(ImGui::GetWindowContentRegionMax().x - ImGui::CalcTextSize("lemon - debug").x);
    ImGui::Text("lemon - debug");

    ImGui::Spacing();
    ImGui::BeginChild("degub_output_console", ImVec2(400, 300), true);
    ImGui::Text("Output Console");
    ImGui::TextUnformatted((const char *) debug_page_console_src.c_str());
    
    if (ImGui::GetScrollY() >= ImGui::GetScrollMaxY()) {
        ImGui::SetScrollHereY(1.0f);
    }

    ImGui::EndChild();

    // console input
    ImGui::BeginChild("debug_input_console", ImVec2(400, 50), true);
    static char debug_input_console_buffer[256] = "";
    if (ImGui::InputText("Input Console", debug_input_console_buffer, 256, ImGuiInputTextFlags_EnterReturnsTrue)) {
        std::string cmd(debug_input_console_buffer);
        debug_page_console_src += cmd + "\n";
        page_debug_cmd_handler(cmd);
        
        memset(debug_input_console_buffer, '\0', 256);
        ImGui::SetKeyboardFocusHere(-1);
    }
    ImGui::EndChild();

    ImGui::End();
}

// AUX functions
std::vector <std::string> slice_cmd(std::string str) {
    std::vector <std::string> out;
    std::stringstream ss(str);
    std::string token;

    while (ss >> token) {
        out.push_back(token);
    }

    return out;
}