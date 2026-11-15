#include "common.hpp"

std::filesystem::path executable_path;
std::filesystem::path executable_dir;

std::string curr_page = "home";
std::string username = "noname";
std::string model_selected = "No model selected";

std::vector <stored_chat> stored_chat_list = {};

bool has_model_selected = false;