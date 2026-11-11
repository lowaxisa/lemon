#include <SDL3/SDL.h>
#include "imgui.h"
#include "imgui_impl_sdl3.h"
#include "imgui_impl_sdlrenderer3.h"

int main(int argc, char *argv[]) {
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

        ImGui::ShowDemoWindow();

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