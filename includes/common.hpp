#ifndef LEMON_COMMON_HPP
#define LEMON_COMMON_HPP

#include <SDL3/SDL.h>
#include "imgui.h"
#include "imgui_impl_sdl3.h"
#include "imgui_impl_sdlrenderer3.h"

#include <filesystem>
#include <string>
#include <vector>
#include <windows.h>
#include <sstream>

struct stored_chat {
    std::string name;
    std::string path;
};

// get all of common.cpp
// global vars
extern std::filesystem::path executable_path;
extern std::filesystem::path executable_dir;
extern std::string curr_page;
extern std::string username;
extern std::string model_selected;
extern std::vector <stored_chat> stored_chat_list;
extern bool has_model_selected;

// imgui helpers
#define IMREL2(XP, YP) ImVec2(ImGui::GetContentRegionMax().x * (XP), ImGui::GetContentRegionMax().y * (YP))

#endif