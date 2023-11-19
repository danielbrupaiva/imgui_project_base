#pragma once
#include <cstdint>
#include <iostream>
#include <string>
#include <memory>
#include <vector>
#include <numeric>

#include "filelogger.h"
#include "imgui.h"
#include "imgui_impl_sdl3.h"
#include "imgui_impl_sdlrenderer3.h"
#include <stdio.h>
#include <SDL3/SDL.h>
#if defined(IMGUI_IMPL_OPENGL_ES2)
#include <SDL3/SDL_opengles2.h>
#else
#include <SDL3/SDL_opengl.h>
#endif

#include "SDL3_image/SDL_image.h"

#define NUM_OF_STATES 5

class App;

void screen1_render(App *app);
void screen2_render(App *app);
void screen3_render(App *app);
void screen4_render(App *app);
void screen5_render(App *app);

//FSM - Circular screen sequence
static bool isTransition[NUM_OF_STATES];

class FSM
{
public:
    enum systemState_t { SCREEN1, SCREEN2, SCREEN3, SCREEN4, SCREEN5 } ;
    void (*pfHandler)(App* app);
    bool (*transition);
    uint32_t waitTime;
    systemState_t nextState[2];
};

class App
{
public:
    //TODO: implement others backends
    enum class BACKEND{ SDL3 };
private:
    bool m_isAppDone;
    bool isDragState;
    const char* m_title;
    ImVec2 m_size;
    //Setup backend
    BACKEND m_backend;
    //SDL2 members variables
    SDL_WindowFlags m_SDL_window_flags;
    SDL_Window* m_SDL_window=nullptr;
    SDL_Renderer* m_SDL_renderer = nullptr;
    //SDL_image
public:
    ImVec2 m_logo_size;
    SDL_Texture* m_SDL_logoTexture = nullptr;
    //ImGUI members variables
    ImVec4 m_clear_color = ImVec4(0.15f, 0.15f, 0.15f, 0.0f);
    //ImVec4 m_clear_color = ImVec4(1.0f, 1.0f, 1.0f, 0.0f);
public:
    std::vector< FSM > m_fsm = {
        { screen1_render, &isTransition[FSM::SCREEN1], 0U, {FSM::SCREEN5,FSM::SCREEN2} },
        { screen2_render, &isTransition[FSM::SCREEN2], 0U, {FSM::SCREEN1,FSM::SCREEN3} },
        { screen3_render, &isTransition[FSM::SCREEN3], 0U, {FSM::SCREEN2,FSM::SCREEN4} },
        { screen4_render, &isTransition[FSM::SCREEN4], 0U, {FSM::SCREEN3,FSM::SCREEN5} },
        { screen5_render, &isTransition[FSM::SCREEN5], 0U, {FSM::SCREEN4,FSM::SCREEN1} }
    };
    FSM::systemState_t m_currentState = FSM::SCREEN1;
public:
    App(ImVec2 _size, const char* _title, BACKEND _backend);
    ~App();
public://methods
    bool SetupBackend(BACKEND _backend);
    bool LoadTextureFromFile(const char *_filename, SDL_Texture **_texture_ptr, float &_width, float &_height, SDL_Renderer *_renderer);
    void EventHandler();
    void Begin();
    void Render();
public:
    void DrawGrid(float scale, const ImVec4& color, bool filled);
    void MouseHandler(float threshold);
    void SetAppStyle();
    void DebugScreen(App* app);
public: //inline methods
    inline bool getIsAppDone() const { return (m_isAppDone );}
    inline void setAppDone(bool appDone){m_isAppDone = appDone;}
};

