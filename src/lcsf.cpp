#include "../includes/lcsf.hpp"
#define lcsf_ptr std::vector <lcsf::lcsf_pair> &data // ngm merece encher o codigo disso

/*
std::vector <lcsf::lcsf_pair> lcsf::parse_file(std::string path) { // wrapper for parse
}

void lcsf::store_file(lcsf_ptr, std::string path) {
}

// LOGIC
std::vector <lcsf::lcsf_pair> lcsf::decode(const std::vector <std::string> data) { // get raw string arrays
}
std::vector <std::string> lcsf::encode(const std::vector <lcsf_pair> data) { // extrated to raw string array
}

// TOOLS
std::size_t lcsf::find_key(lcsf_ptr, std::string key) { // return key index in lcsf_ptr
}
void lcsf::edit_key(lcsf_ptr, std::string key, std::vector <std::string> values) { // replace key value
}
std::vector <std::string> lcsf::read_key(lcsf_ptr, std::string key) { // return key lines
}

// LIFE CYCLE
bool lcsf::new_key(lcsf_ptr, std::string key, std::vector <std::string> values) { // return true if has created else key exists
}
void lcsf::delete_key(lcsf_ptr, std::string key) { // erase key
}
*/

#undef lcsf_ptr