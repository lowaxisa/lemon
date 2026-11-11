cmake_minimum_required(VERSION 3.16)
project(lemon LANGUAGES C CXX)

# assumirei que o compilador sera o MSVC

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

if(NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
    set(CMAKE_BUILD_TYPE Release)
endif()

# Runtime do C/C++ embutido no .exe (sem VCRUNTIME140.dll etc.)
# Precisa vir ANTES de qualquer add_library/add_subdirectory
set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")
add_compile_options(/utf-8)

set(THIRDPARTY ${CMAKE_CURRENT_SOURCE_DIR}/thirdparty)

# SDL3
set(SDL_SHARED            OFF CACHE BOOL "" FORCE)
set(SDL_STATIC            ON  CACHE BOOL "" FORCE)
set(SDL_FORCE_STATIC_VCRT ON  CACHE BOOL "" FORCE)
set(SDL_TEST_LIBRARY      OFF CACHE BOOL "" FORCE)
set(SDL_TESTS             OFF CACHE BOOL "" FORCE)
set(SDL_EXAMPLES          OFF CACHE BOOL "" FORCE)
set(SDL_DISABLE_INSTALL   ON  CACHE BOOL "" FORCE)
set(SDL_DISABLE_UNINSTALL ON  CACHE BOOL "" FORCE)
set(SDL_DBUS              OFF CACHE BOOL "" FORCE)
set(SDL_LIBUDEV           OFF CACHE BOOL "" FORCE)
add_subdirectory(${THIRDPARTY}/sdl EXCLUDE_FROM_ALL)

# dear imgui
set(IMGUI_DIR ${THIRDPARTY}/imgui)
add_library(imgui STATIC
    ${IMGUI_DIR}/imgui.cpp
    ${IMGUI_DIR}/imgui_draw.cpp
    ${IMGUI_DIR}/imgui_tables.cpp
    ${IMGUI_DIR}/imgui_widgets.cpp
    ${IMGUI_DIR}/imgui_demo.cpp
    ${IMGUI_DIR}/backends/imgui_impl_sdl3.cpp
    ${IMGUI_DIR}/backends/imgui_impl_sdlrenderer3.cpp
)
target_include_directories(imgui PUBLIC ${IMGUI_DIR} ${IMGUI_DIR}/backends)
target_link_libraries(imgui PUBLIC SDL3::SDL3)

# executavel unico
file(GLOB_RECURSE APP_SOURCES CONFIGURE_DEPENDS
    ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp
)

add_executable(lemon main.cpp ${APP_SOURCES})
target_include_directories(lemon PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/includes)
target_link_libraries(lemon PRIVATE imgui SDL3::SDL3)

set_target_properties(lemon PROPERTIES WIN32_EXECUTABLE ON)
target_link_options(lemon PRIVATE /ENTRY:mainCRTStartup)