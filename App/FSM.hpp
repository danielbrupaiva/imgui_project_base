#pragma once
#include <iostream>
#include <vector>

#define NUM_OF_STATES 5

class App;
struct FSM
{
    enum class eSystemState { UI_SCREEN1, UI_SCREEN2, UI_SCREEN3, UI_SCREEN4, UI_SCREEN5 };
    void (*pfHandler)(App *app);
    bool (*transition);
    unsigned int waitTime;
    eSystemState nextState[2];
};

extern void screen1_render(App *app);
extern void screen2_render(App *app);
extern void screen3_render(App *app);
extern void screen4_render(App *app);
extern void screen5_render(App *app);
