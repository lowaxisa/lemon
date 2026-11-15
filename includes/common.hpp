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

// get all of common.cpp
// global vars
extern std::filesystem::path executable_path;
extern std::filesystem::path executable_dir;
extern std::string curr_page;
extern std::string username;

#endif