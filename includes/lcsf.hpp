#ifndef LCSF_HPP
#define LCSF_HPP

#include <vector>
#include <string>
#include <fstream>

namespace lcsf {
    // returns [[key: [lines]]]
    struct lcsf_pair {
        std::string key;
        std::vector <std::string> lines;
    };
    #define lcsf_ptr std::vector <lcsf_pair> &data // ngm merece encher o codigo disso

    // IO
    std::vector <lcsf_pair> parse_file(std::string path); // wrapper for parse
    void store_file(lcsf_ptr, std::string path);

    // LOGIC
    std::vector <lcsf_pair> decode(const std::vector <std::string> data); // get raw string arrays
    std::vector <std::string> encode(const std::vector <lcsf_pair> data); // extrated to raw string array

    // TOOLS
    std::size_t find_key(lcsf_ptr, std::string key); // return key index in lcsf_ptr
    void edit_key(lcsf_ptr, std::string key, std::vector <std::string> values); // replace key value
    std::vector <std::string> read_key(lcsf_ptr, std::string key); // return key lines

    // LIFE CYCLE
    bool new_key(lcsf_ptr, std::string key, std::vector <std::string> values); // return true if has created else key exists
    void delete_key(lcsf_ptr, std::string key); // erase key
    #undef lcsf_ptr
};

#endif