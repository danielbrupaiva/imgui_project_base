#pragma once
#include <iostream>
#include <vector>

namespace Application {
class UI;
}

struct FSM
{
    enum class eSystemState { UI_SCREEN1, UI_SCREEN2, UI_SCREEN3, UI_SCREEN4, UI_SCREEN5 };
    void (*pfHandler)(Application::UI& app);
    bool (*transition);
    unsigned int waitTime;
    eSystemState nextState[2];
};

extern void screen1_render(Application::UI& app);
extern void screen2_render(Application::UI& app);
extern void screen3_render(Application::UI& app);
extern void screen4_render(Application::UI& app);
extern void screen5_render(Application::UI& app);
