#pragma once
#include <cstdint>
#include <iostream>
#include <string>
#include <memory>
#include <numeric>

#include "globals.hpp"
#include "filelogger.hpp"
#include "database.hpp"

#include "imgui.h"
#include "imgui_stdlib.h"
#include "imgui_impl_sdl3.h"
#include "imgui_impl_sdlrenderer3.h"
#include <SDL3/SDL.h>
#if defined(IMGUI_IMPL_OPENGL_ES2)
#include <SDL3/SDL_opengles2.h>
#else
#include <SDL3/SDL_opengl.h>
#endif
#include "SDL3_image/SDL_image.h"


namespace Application {
class UI
{
public:
    // TODO: implement others backends
    enum class BACKEND { SDL3 };
public:
    UI(ImVec2 _size, const std::string _title, BACKEND _backend);
    ~UI();
private:
    bool m_is_app_done;
    bool m_is_drag_state;
    const std::string m_title;
    ImVec2 m_size;
    /**  Setup backend **/
    BACKEND m_backend;
    /** SDL2 members variables **/
    SDL_WindowFlags m_SDL_window_flags;
    SDL_Window* m_SDL_window = nullptr;
    SDL_Renderer* m_SDL_renderer = nullptr;
    /** SDL surface (logo) **/
    ImVec2 m_logo_size;
    SDL_Texture* m_SDL_logo_texture = nullptr;
    ImVec4 m_clear_color = ImVec4(0.15f, 0.15f, 0.15f, 0.0f);
public: // methods
    bool setup_backend(BACKEND _backend);
    bool load_texture_from_file(const char *_filename, SDL_Texture **_texture_ptr, float &_width, float &_height, SDL_Renderer *_renderer);
    void event_handler();
    void begin();
    void render();
    void draw_grid(float scale, const ImVec4 &color, bool filled);
    void mouse_handler(float threshold);
    void set_app_style();
    void debug_screen(UI& app);
public:/**Getter and Setters **/
    inline bool get_is_app_done() const { return (m_is_app_done); }
    inline void set_app_done(bool appDone) { m_is_app_done = appDone; }
    inline ImVec2 get_logo_size() const { return m_logo_size; }
    inline void set_logo_size(const ImVec2 &newLogo_size) { m_logo_size = newLogo_size; }
    inline SDL_Texture* get_SDL_logo_texture() const { return m_SDL_logo_texture; }
    inline void set_SDL_logo_texture(SDL_Texture *newSDL_logo_texture) { m_SDL_logo_texture = newSDL_logo_texture; }
    inline ImVec4 get_clear_color() const { return m_clear_color; }
    inline void set_clear_color(const ImVec4 &newClear_color) { m_clear_color = newClear_color; }
};
} // namespace Application
