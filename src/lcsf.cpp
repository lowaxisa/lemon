#include "../includes/lcsf.hpp"
#define lcsf_ptr std::vector <lcsf::lcsf_pair> &data // ngm merece encher o codigo disso

std::vector <lcsf::lcsf_pair> lcsf::parse_file(std::string path) { // wrapper for parse
    std::ifstream file(path); // this is equal to std::ifstream file = std::ifstream(path)

    std::filebuf *fbuffer = file.rdbuf();
    std::vector <std::string> raw_lcsf;

    int c = fbuffer->sbumpc();
    std::string temp = "";
    bool found_invbar_r = false;
    while (c != EOF) {
        switch (c) {
            case (int) '\n':
                if (found_invbar_r) found_invbar_r = false;
                raw_lcsf.push_back(temp);
                temp = "";
                break;
            case (int) '\r':
                found_invbar_r = true;
                break; // bro \r is trashhhhhhhhhhhhhhhhhhhhhhhh for me
            default:
                if (found_invbar_r) {temp += '\r'; found_invbar_r = false;}
                temp += (char) c;
                break;
        }
        c = fbuffer->sbumpc();
    }
    if (found_invbar_r) {temp += '\r';}
    if (temp != "") {raw_lcsf.push_back(temp);}

    file.close();
    return lcsf::decode(raw_lcsf);
}

void lcsf::store_file(lcsf_ptr, std::string path) {
}

// LOGIC
std::vector <lcsf::lcsf_pair> lcsf::decode(const std::vector <std::string> data) { // get raw string arrays
    /*
    a logica eh
    se nao tem uma chave em processamento pegar a linha do topo e dividir pelo espaco
    a parte da esquerda eh a chave e a da direita eh o numero de linhas
    forzinho que vai removendo o numero de linhas e colocando no pair
    pushar ele pro vetor out
    */

    std::vector <lcsf::lcsf_pair> out;
    std::size_t curr_line = 0;
    while (curr_line < data.size()) {
        lcsf::lcsf_pair temp_pair;
        std::string header = data[0];
        std::string key = "";
        std::string line_numstr = "";

        std::size_t space_in_header_pos = 0;
        for (std::size_t i = 0; i < header.length(); i++) {
            if (header[i] == ' ') {
                space_in_header_pos = i;
                break;
            }
        }
        key = header.substr(0, space_in_header_pos);
        line_numstr = header.substr(space_in_header_pos + 1);
        temp_pair.key = key;

        // obs i need ignore header
        curr_line++;

        std::size_t line_num = std::stoi(line_numstr);
        std::size_t loop_end = curr_line + line_num;
        for (std::size_t i = curr_line; i < loop_end; i++) {
            temp_pair.lines.push_back(data[i]);
            curr_line++;
        }

        out.push_back(temp_pair);
    }

    return out;
}

/*
std::vector <std::string> lcsf::encode(const std::vector <lcsf_pair> data) { // extrated to raw string array
}

// TOOLS
int lcsf::find_key(lcsf_ptr, std::string key) { // return key index in lcsf_ptr if dont find return -1
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