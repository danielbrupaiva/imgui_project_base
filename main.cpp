#include <iostream>
#include <string>
#define PRINT(x) std::cout << x << std::endl;
#include "app.h"

std::string TAG = "MAIN";

int main(int, char**)
{
    PRINT("HELLO " + TAG);
    PRINT("APP start");
    App app(ImVec2(1280,720),"ImGUI APP", App::BACKEND::SDL3);

    PRINT("Do-While ");
    do {
        app.Begin();{
        }app.Render();
    } while (!app.getIsAppDone());

    PRINT("APP stop");
    return EXIT_SUCCESS;
}




