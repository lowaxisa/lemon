#include "umbrella.hpp"

void check_dir() { // create base directorys for exe if they doesnt exists
    std::vector <std::string> paths = {"backends", "models", "chats", "prompts"};

    for (std::string &dir : paths) {
        std::filesystem::path target_dir = executable_dir / dir;

        if (!std::filesystem::exists(target_dir)) {
            std::filesystem::create_directory(target_dir);
        }
    }
}

void check_file() {
    std::filesystem::path settings_file = executable_dir / "settings.txt";

    if (!std::filesystem::exists(settings_file)) {
        std::ofstream file(settings_file);
        file << "USERNAME 1\nnoname";
        file.close();
    }
}

void load_settings() {
    std::string path(executable_dir.string() + "\\settings.txt");
    std::vector <lcsf::lcsf_pair> src = lcsf::parse_file(path);

    username = lcsf::read_key(src, "USERNAME")[0];
}

// checa diretorios, arquivos principais e recarrega tudo
void lemon_boot() {
    check_dir();
    check_file();
    load_settings();
}