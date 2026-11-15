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
    /*
    ideia
    abrir
    encodar o lcsf
    salvar no arquivo
    */
    std::vector <std::string> encoded_data = lcsf::encode(data);
    std::ofstream file(path);

    for (std::size_t i = 0; i < encoded_data.size(); i++) {
        file << encoded_data[i] + '\n'; // enfia a linha e a quebra de linha
    }

    file.close();
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
        std::string header = data[curr_line];
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

std::vector <std::string> lcsf::encode(const std::vector <lcsf_pair> data) { // extrated to raw string array
    /*
    ideia
    varrer data
    criar um vetor alternativo com todos \n considerados (detectar os \n e quebrar a linha no vetor alternativo)
    */
    std::vector <std::string> out;

    for (std::size_t i = 0; i < data.size(); i++) {
        std::string key = data[i].key;
        std::vector <std::string> temp_lines = {};

        for (std::size_t j = 0; j < data[i].lines.size(); j++) { // varre o vetor de strings
            std::string buffer = ""; // buffer temporario pra strings sem \n

            for (std::size_t k = 0; k < data[i].lines[j].size(); k++) { // varre a string
                char c = data[i].lines[j][k];
                if (c == '\n') {
                    // salva a string e pula esse caractere \n
                    temp_lines.push_back(buffer);
                    buffer = "";
                } else {
                    // se for qualquer outra coisa
                    buffer += c;
                }
            }
            // pega oq sobra
            temp_lines.push_back(buffer);
        }

        std::size_t line_count = temp_lines.size(); // tanto de linha pra meter no cabecalho do lcsf
        std::string line_count_str = std::to_string(line_count);

        out.push_back(key + " " + line_count_str); // enfia o cabecalho
        for (std::size_t j = 0; j < temp_lines.size(); j++) { // varre o vetor de linhas limpas
            out.push_back(temp_lines[j]); // adiciona a linha
        }
    }

    return out;
}

// TOOLS
int lcsf::find_key(lcsf_ptr, std::string key) { // return key index in lcsf_ptr if dont find return -1
    int idx = -1;

    for (int i = 0; i < data.size(); i++) {
        lcsf::lcsf_pair pair = data[i];

        if (pair.key == key) {
            idx = i;
            break;
        }
    }

    return idx;
}

void lcsf::edit_key(lcsf_ptr, std::string key, std::vector <std::string> values) { // replace key value
    data[find_key(data, key)].lines = values;
}

std::vector <std::string> lcsf::read_key(lcsf_ptr, std::string key) { // return key lines
    return data[find_key(data, key)].lines;
}

// LIFE CYCLE
bool lcsf::new_key(lcsf_ptr, std::string key, std::vector <std::string> values) { // return true if has created else key exists
    if (find_key(data, key) == -1) {
        lcsf::lcsf_pair pair;
        pair.key = key;
        pair.lines = values;
        data.push_back(pair);
        return true;
    } else {return false;}
}

void lcsf::delete_key(lcsf_ptr, std::string key) { // erase key
    int i = find_key(data, key);
    if (i != -1) {
        data.erase(data.begin() + i);
    }
}

#undef lcsf_ptr