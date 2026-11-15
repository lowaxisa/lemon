#include "umbrella.hpp"

std::string debug_page_console_src = "lemon debug console\n> ";

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
        "lcsf_help - show lcsf commands\n"
        "clear - clear console";
}

void console_clear(std::vector <std::string> args) {
    debug_page_console_src = "";
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

// LCSF DEBUG COMMANDS
std::filesystem::path lcsf_target_file;
std::vector <lcsf::lcsf_pair> lcsf_cache;
std::string lcsf_cache_target_key;

void console_lcsf_dump(std::vector <std::string> args) {
    for (lcsf::lcsf_pair pair : lcsf_cache) {
        debug_page_console_src += pair.key + ":\n";
            for (std::string line : pair.lines) {
                debug_page_console_src += "    " + line + "\n";
            }
    }
}

void console_lcsf_load(std::vector <std::string> args) {
    lcsf_target_file = executable_dir / args[1];
    lcsf_cache = lcsf::parse_file(lcsf_target_file.string());
    console_lcsf_dump({});
}

void console_lcsf_find(std::vector <std::string> args) {
    lcsf_cache_target_key = args[1];
    if (lcsf::find_key(lcsf_cache, lcsf_cache_target_key) == -1) {
        debug_page_console_src += "this key doens't exists\n";
    }
}

void console_lcsf_edit(std::vector <std::string> args) {
    std::string temp = "";

    for (std::size_t i = 2; i < args.size(); i++) {
        temp += args[i];
        if (i + 1 < args.size()) {
            temp += " ";
        }
    }

    std::vector <std::string> new_values = lcsf_cache[lcsf::find_key(lcsf_cache, lcsf_cache_target_key)].lines;
    new_values[std::stoi(args[1])] = temp;

    lcsf::edit_key(lcsf_cache, lcsf_cache_target_key, new_values);
}

void console_lcsf_store(std::vector <std::string> args) {
    lcsf::store_file(lcsf_cache, lcsf_target_file.string());
}

void console_lcsf_addline(std::vector <std::string> args) {
    std::size_t target_idx = std::stoi(args[1]) + 1;
    std::vector <std::string> &lcsf_cache_lines = lcsf_cache[lcsf::find_key(lcsf_cache, lcsf_cache_target_key)].lines;
    if (target_idx >= lcsf_cache_lines.size()) {
        lcsf_cache_lines.push_back("");
    } else lcsf_cache_lines.insert(lcsf_cache_lines.begin() + target_idx, "");
}

void console_lcsf_delline(std::vector <std::string> args) {
    std::size_t target_idx = std::stoi(args[1]);
    std::vector <std::string> &lcsf_cache_lines = lcsf_cache[lcsf::find_key(lcsf_cache, lcsf_cache_target_key)].lines;
    lcsf_cache_lines.erase(lcsf_cache_lines.begin() + target_idx);
}

void console_lcsf_addkey(std::vector <std::string> args) {
    lcsf::new_key(lcsf_cache, args[1], {});
    lcsf_cache_target_key = args[1];
}

void console_lcsf_delkey(std::vector <std::string> args) {
    lcsf::delete_key(lcsf_cache, args[1]);
}

void console_lcsf_help(std::vector <std::string> args) {
    debug_page_console_src +=
        "lcsf commands list\n"
        "lcsf_help - show this message\n"
        "lcsf_load [path] - load a file in cache and dump\n"
        "lcsf_find [key] - find a key in cache and set he as target\n"
        "lcsf_edit [line idx] [content] - change line content in target\n"
        "lcsf_addline [idx] - add a line in target after idx\n"
        "lcsf_delline [idx] - remove line in target\n"
        "lcsf_store - store cache in file loaded\n"
        "lcsf_dump - dump cache\n"
        "lcsf_addkey [keyname] - add a new key in lcsf cache and auto focus\n"
        "lcsf_delkey [keyname] - delete key in lcsf cache\n";
}

cmd_pair cmd_list[] = {
    {"help", console_help},
    {"say", console_say},
    {"lcsf_load", console_lcsf_load},
    {"lcsf_dump", console_lcsf_dump},
    {"lcsf_find", console_lcsf_find},
    {"lcsf_edit", console_lcsf_edit},
    {"lcsf_store", console_lcsf_store},
    {"lcsf_addline", console_lcsf_addline},
    {"lcsf_delline", console_lcsf_delline},
    {"lcsf_help", console_lcsf_help},
    {"lcsf_addkey", console_lcsf_addkey},
    {"lcsf_delkey", console_lcsf_delkey},
    {"clear", console_clear},
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
    ImGui::BeginChild("degub_output_console", ImVec2(900, 600), ImGuiChildFlags_Borders);
    ImGui::Text("Output Console");
    ImGui::TextUnformatted((const char *) debug_page_console_src.c_str());
    
    if (ImGui::GetScrollY() >= ImGui::GetScrollMaxY()) {
        ImGui::SetScrollHereY(1.0f);
    }

    ImGui::EndChild();

    // console input
    ImGui::BeginChild("debug_input_console", ImVec2(900, 50), true);
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