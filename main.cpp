#include <SDL3/SDL.h>
#include "imgui.h"
#include "imgui_impl_sdl3.h"
#include "imgui_impl_sdlrenderer3.h"

#include <filesystem>
#include <string>
#include <vector>
#include <windows.h>
#include <sstream>

// misc
namespace fs = std::filesystem;

// functions prototype
void check_dir();
void page_home();
void page_debug();
std::vector <std::string> slice_cmd(std::string str);

// global vars
std::filesystem::path executable_path;
std::filesystem::path executable_dir;
std::string curr_page = "home";

// debug page vars
std::string debug_page_console_src = "lemon debug console\n> ";

int main(int argc, char *argv[]) {
    // get executable directory
    wchar_t buffer[MAX_PATH];
    DWORD length = GetModuleFileNameW(nullptr, buffer, MAX_PATH);
    executable_path = std::filesystem::path(buffer);
    executable_dir = executable_path.parent_path();

    check_dir(); // setup directorys
    // setup sdl
    SDL_Init(SDL_INIT_VIDEO);

    SDL_Window   *window   = SDL_CreateWindow("lemon", 1280, 720, NULL);
    SDL_Renderer *renderer = SDL_CreateRenderer(window, NULL);
    SDL_Event event;
    SDL_ShowWindow(window);

    // setup imgui
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO &io = ImGui::GetIO(); (void)io; // (void)io to bypass unusued warnings

    ImGui::StyleColorsLight(); // Set imgui style
    ImGui_ImplSDL3_InitForSDLRenderer(window, renderer); // init imgui backend
    ImGui_ImplSDLRenderer3_Init(renderer);

    bool is_running = true;

    while (is_running) {
        while(SDL_PollEvent(&event)) {
            ImGui_ImplSDL3_ProcessEvent(&event);
            if (event.type == SDL_EVENT_QUIT) is_running = false;
        }

        // create a new frame
        ImGui_ImplSDLRenderer3_NewFrame();
        ImGui_ImplSDL3_NewFrame();
        ImGui::NewFrame();

        if (curr_page == "home")  page_home();
        if (curr_page == "debug") page_debug();

        // proccess frame
        ImGui::Render();

        // clear sdl window
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        // render
        ImGui_ImplSDLRenderer3_RenderDrawData(ImGui::GetDrawData(), renderer);
        SDL_RenderPresent(renderer);
    }

    // Stop ImGui
    ImGui_ImplSDLRenderer3_Shutdown();
    ImGui_ImplSDL3_Shutdown();
    ImGui::DestroyContext();

    // Destroy sdl
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}

void check_dir() { // create base directorys for exe if they doesnt exists
    std::vector <std::string> paths = {"backends", "models", "chats", "prompts"};

    for (std::string &dir : paths) {
        std::filesystem::path target_dir = executable_dir / dir;

        if (!fs::exists(target_dir)) {
            fs::create_directory(target_dir);
        }
    }
}

// PAGES
// HOME PAGE
void page_home() {
    ImGui::SetNextWindowPos(ImGui::GetMainViewport()->WorkPos);
    ImGui::SetNextWindowSize(ImGui::GetMainViewport()->WorkSize);
    ImGui::Begin("this_dont_appear_home", nullptr, ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoMove);

    if (ImGui::Button("debug mode")) {
        curr_page = "debug";
    }

    ImGui::End();
}



// DEBUG PAGE
struct cmd_pair {
    std::string cmd;
    void (*func)(std::vector <std::string> args);
};

// commands
void console_help(std::vector <std::string> args) {
    debug_page_console_src +=
        "console commands list\n"
        "help - show this message\n"
        "say [msg] - is a test for args\n";
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

cmd_pair cmd_list[] = {
    {"help", console_help},
    {"say", console_say},
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

// AUXILIAR FUNCTIONS
std::vector <std::string> slice_cmd(std::string str) {
    std::vector <std::string> out;
    std::stringstream ss(str);
    std::string token;

    while (ss >> token) {
        out.push_back(token);
    }

    return out;
}