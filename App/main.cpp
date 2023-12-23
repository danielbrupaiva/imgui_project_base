#include "user.hpp"
#include "app.hpp"
#include "database.hpp"
#include "filelogger.hpp"

static const std::string TAG = "MAIN";

int main(int, char **)
{
    PRINT(TAG);

    Application::UI app{ImVec2(1280, 720), "ImGUI APP", Application::UI::BACKEND::SDL3};
    // Start backend
    Core::Database& db = Core::Database::Instance("localhost", "5432", "imgui", "1234", "project");
    bool show_demo_window = true;
    PRINT("Do-While ");
    do
    { // IMGUI code
        app.begin();
        {
            Global::StateMachine[static_cast<int>(Global::current_state)].pfHandler(app);
            ImGui::ShowDemoWindow(&show_demo_window);
        }
        app.render();

    } while (!app.get_is_app_done());

    PRINT("APP stop");
    return EXIT_SUCCESS;
}
