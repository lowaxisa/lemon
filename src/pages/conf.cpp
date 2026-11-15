#include "umbrella.hpp"

std::string subpage = "preferences";
std::vector <std::string> subpage_list = {"preferences", "about"};
extern const char about_string[];

// subpages prototype
void subpage_preferences();
void subpage_about();

void page_conf() {
    float ViewportSizeX = ImGui::GetMainViewport()->WorkSize.x;
    float ViewportSizeY = ImGui::GetMainViewport()->WorkSize.y;

    ImGui::SetNextWindowPos(ImGui::GetMainViewport()->WorkPos);
    ImGui::SetNextWindowSize(ImGui::GetMainViewport()->WorkSize);
    ImGui::Begin("this_dont_appear_conf", nullptr, ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoScrollWithMouse);

    // top painel
    ImGui::SetCursorPos(ImVec2(0, 0));
    ImGui::BeginChild("conf_painel_top", ImVec2(ViewportSizeX, 35), ImGuiChildFlags_Borders);

    if (ImGui::Button("return to home")) {
        curr_page = "home";
    }
    ImGui::SameLine();
    ImGui::SetCursorPosX(ImGui::GetWindowContentRegionMax().x - ImGui::CalcTextSize("lemon - conf").x);
    ImGui::Text("lemon - conf");

    ImGui::EndChild();

    // lateral painel
    ImGui::SetCursorPos(ImVec2(0, 35));
    ImGui::BeginChild("conf_painel_lateral", ImVec2(250, ViewportSizeY - 35), ImGuiChildFlags_Borders, ImGuiWindowFlags_NoScrollWithMouse | ImGuiWindowFlags_NoScrollbar);

    // draw subpages access button
    for (std::size_t i = 0; i < subpage_list.size(); i++) {
        if (ImGui::Button(subpage_list[i].c_str())) {
            subpage = subpage_list[i];
        }
    }

    ImGui::EndChild();

    // subpage painel
    ImGui::SetCursorPos(ImVec2(250, 35));
    ImGui::BeginChild("conf_painel_subpainel", ImVec2(ViewportSizeX - 250, ViewportSizeY - 35));

    ImGui::SetCursorPos(ImVec2(5, 5));
    ImGui::Text(subpage.c_str());

    if (subpage == "preferences") subpage_preferences();
    if (subpage == "about") subpage_about();

    ImGui::EndChild();

    ImGui::End();
}

char preferences_namebuffer[256];
void subpage_preferences() {
    // por enquanto so vai ter opcao pra mudar o nome
    if (ImGui::InputText("Username (press enter to save)", preferences_namebuffer, 256, ImGuiInputTextFlags_EnterReturnsTrue)) {
        std::string new_username(preferences_namebuffer);
        username = new_username;
        // dps adicionar pra salvar em settings.txt
        std::vector <lcsf::lcsf_pair> settings = lcsf::parse_file((executable_dir / "settings.txt").string());
        lcsf::edit_key(settings, "USERNAME", {new_username});
        lcsf::store_file(settings, (executable_dir / "settings.txt").string());
    }
}

void subpage_about() {
    ImGui::SetCursorPosX(5);
    ImGui::TextUnformatted(about_string);
}

// chamado quando essa pagina carrega
void on_conf_page() {
    // subpage preferences
    // preciso atualizar o username no charbuffer pro atual
    memcpy(preferences_namebuffer, username.c_str(), username.length());
}

static const char about_string[] = R"(
--- All licenses ---
Lemon license:

MIT License

Copyright (c) 2026 lowaxisa

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.



ImGui license:
The MIT License (MIT)

Copyright (c) 2014-2026 Omar Cornut

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.



Llama.cpp license:
MIT License

Copyright (c) 2023-2026 The ggml authors

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.



SDL license:
Copyright (C) 1997-2026 Sam Lantinga <slouken@libsdl.org>
  
This software is provided 'as-is', without any express or implied
warranty.  In no event will the authors be held liable for any damages
arising from the use of this software.

Permission is granted to anyone to use this software for any purpose,
including commercial applications, and to alter it and redistribute it
freely, subject to the following restrictions:
  
1. The origin of this software must not be misrepresented; you must not
   claim that you wrote the original software. If you use this software
   in a product, an acknowledgment in the product documentation would be
   appreciated but is not required. 
2. Altered source versions must be plainly marked as such, and must not be
   misrepresented as being the original software.
3. This notice may not be removed or altered from any source distribution.

)";