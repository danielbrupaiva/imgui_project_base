#include "global.hpp"
#include "app.hpp"
#include "database.hpp"
#include "filelogger.hpp"

const std::string TAG = "MAIN";

int main(int, char**)
{
    PRINT("HELLO " + TAG);
    PRINT("APP start");    

    App app{ImVec2(1280,720),"ImGUI APP", App::BACKEND::SDL3};
    //Start backend
    Database db{"localhost","5432","imgui","1234","project"};

    PRINT("Do-While ");
    do {//IMGUI code
        app.begin();{
        }app.render();
    } while (!app.get_is_app_done());

    PRINT("APP stop");
    return EXIT_SUCCESS;
}

