#pragma once
#include "filelogger.hpp"
#include "iscreen.hpp"

namespace Application {

class UI_Home_Screen
    : public IScreen
{
public:
    explicit UI_Home_Screen(Spec spec);;
    ~UI_Home_Screen();
    void render();
};
}
