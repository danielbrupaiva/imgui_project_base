#include "user.hpp"
#include "app.hpp"
#include "database.hpp"
#include "filelogger.hpp"

static const std::string TAG = "MAIN";

int main(int, char **)
{
    PRINT("HELLO " + TAG);
    PRINT("APP start");

    Application::UI app{ImVec2(1280, 720), "ImGUI APP", Application::UI::BACKEND::SDL3};
    // Start backend
    Core::Database& db = Core::Database::Instance("localhost", "5432", "imgui", "1234", "project");

    PRINT("Do-While ");
    do
    { // IMGUI code
        app.begin();
        {
            Global::StateMachine[static_cast<int>(Global::current_state)].pfHandler(app);
        }
        app.render();

    } while (!app.get_is_app_done());

    PRINT("APP stop");
    return EXIT_SUCCESS;
}
