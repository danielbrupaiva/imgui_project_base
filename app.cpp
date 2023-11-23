#include "app.hpp"

App::App(ImVec2 _size, std::string _title, BACKEND _backend) :
    m_size(_size),
    m_title(_title),
    m_backend(_backend)
{
    setup_backend(m_backend);
    load_texture_from_file("./resources/logo.png",
                           &m_SDL_logo_texture, m_logo_size.x, m_logo_size.y, m_SDL_renderer);
}

App::~App()
{
    //Imgui cleanup
    ImGui_ImplSDLRenderer3_Shutdown();
    ImGui_ImplSDL3_Shutdown();
    ImGui::DestroyContext();
    //SDL cleanup
    IMG_Quit();
    SDL_DestroyTexture(m_SDL_logo_texture);
    SDL_DestroyRenderer(m_SDL_renderer);
    SDL_DestroyWindow(m_SDL_window);
    SDL_Quit();
}

bool App::setup_backend(BACKEND _backend)
{

    // Setup SDL
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
    {
        printf("Error: %s\n", SDL_GetError());
        return EXIT_FAILURE;
    }
    // Enable native IME.
    SDL_SetHint(SDL_HINT_IME_SHOW_UI, "1");    
    // Create window with SDL_Renderer graphics context
    m_SDL_window_flags = (SDL_WindowFlags)( SDL_WINDOW_OPENGL
                                            | SDL_WINDOW_ALWAYS_ON_TOP
                                            //| SDL_WINDOW_FULLSCREEN_DESKTOP
                                            | SDL_WINDOW_BORDERLESS
                                            );
    m_SDL_window = SDL_CreateWindow(m_title.c_str(), m_size.x, m_size.y, m_SDL_window_flags);
    if (m_SDL_window == nullptr)
    {
        printf("Error: SDL_CreateWindow(): %s\n", SDL_GetError());
        return EXIT_FAILURE;
    }
    m_SDL_renderer = SDL_CreateRenderer(m_SDL_window, NULL, SDL_RENDERER_PRESENTVSYNC | SDL_RENDERER_ACCELERATED);
    if (m_SDL_renderer == nullptr)
    {
        SDL_Log("Error creating SDL_Renderer!");
        return EXIT_FAILURE;
    }
    SDL_SetWindowPosition(m_SDL_window, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED);
    SDL_ShowWindow(m_SDL_window);


    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& m_io = ImGui::GetIO(); (void)m_io;
    m_io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
    m_io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls

    // Setup Dear ImGui style
    ImGui::StyleColorsDark();
    //ImGui::StyleColorsLight();

    // Setup Platform/Renderer backends
    ImGui_ImplSDL3_InitForSDLRenderer(m_SDL_window, m_SDL_renderer);
    ImGui_ImplSDLRenderer3_Init(m_SDL_renderer);

    return EXIT_SUCCESS;
}
void App::event_handler()
{
    SDL_Event event;
    while (SDL_PollEvent(&event))
    {
        ImGui_ImplSDL3_ProcessEvent(&event);
        if (event.type == SDL_EVENT_QUIT)
            m_is_app_done = true;
        if (event.type == SDL_EVENT_WINDOW_CLOSE_REQUESTED && event.window.windowID == SDL_GetWindowID(m_SDL_window))
            m_is_app_done = true;
    }
    mouse_handler(100.0);
}
void App::begin()
{
    event_handler();
    // Start the Dear ImGui frame
    ImGui_ImplSDLRenderer3_NewFrame();
    ImGui_ImplSDL3_NewFrame();
    ImGui::NewFrame();
    set_app_style();

}
void App::render()
{
    m_fsm[m_current_state].pfHandler(this);   
    // Rendering
    ImGui::Render();
    ImGuiIO& m_io = ImGui::GetIO(); (void)m_io;
    // Setup area to render
    //SDL_RenderSetScale(m_SDL_renderer, m_io.DisplayFramebufferScale.x, m_io.DisplayFramebufferScale.y);
    SDL_SetRenderDrawColor(m_SDL_renderer, (Uint8)(m_clear_color.x * 255), (Uint8)(m_clear_color.y * 255), (Uint8)(m_clear_color.z * 255), (Uint8)(m_clear_color.w * 255));
    SDL_RenderClear(m_SDL_renderer);
    // Texture in order to apply
    //SDL_Rect rectangle = {(1280-1089)/2,0,1089,720};
    //SDL_RenderCopy(m_SDL_renderer,m_SDL_logoTexture,NULL,&rectangle);
    // Apply render
    ImGui_ImplSDLRenderer3_RenderDrawData(ImGui::GetDrawData());
    SDL_RenderPresent(m_SDL_renderer);
}
bool App::load_texture_from_file(const char *_filename, SDL_Texture **_texture_ptr, float &_width, float &_height, SDL_Renderer *_renderer)
{
    int _flags = IMG_INIT_PNG | IMG_INIT_JPG ;
    int _initStatus = IMG_Init(_flags);
    if((_initStatus & _flags) != _flags){
        std::cout << "SDL2_Image format not available" << std::endl;
        return EXIT_FAILURE;
    }
    SDL_Surface* _surface = IMG_Load(_filename);
    if (_surface == nullptr) {
        fprintf(stderr, "Failed to create SDL surface: %s\n", SDL_GetError());
        return EXIT_FAILURE;
    }
    *_texture_ptr = SDL_CreateTextureFromSurface(_renderer, _surface);
    if ((*_texture_ptr) == nullptr) {
        fprintf(stderr, "Failed to create SDL texture: %s\n", SDL_GetError());
        return EXIT_FAILURE;
    }
    SDL_DestroySurface(_surface);
    return EXIT_SUCCESS;
}
void screen1_render(App* app)
{
    const char* name = "SCREEN 1";
    ImVec2 position = ImVec2(0,0);
    ImVec2 size = ImVec2(1280, 720);
    ImGuiWindowFlags flags = ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoBackground | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoMove;
    ImGui::SetNextWindowPos(position);
    ImGui::SetNextWindowSize(size, ImGuiCond_Always);

    if(ImGui::Begin(name, NULL, flags)){
        //ImGui::Image((void*)app->m_SDL_logoTexture, ImgSize);
        ImVec2 ImgSize = ImVec2(1089, 720);
        ImGui::SetCursorPos(ImVec2((size.x-ImgSize.x)/2,0) );
        ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(app->m_clear_color));
        ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(app->m_clear_color));
        ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(app->m_clear_color));
        if(ImGui::ImageButton((void*)app->m_SDL_logo_texture, ImgSize)){
            app->m_current_state = FSM::SCREEN2;
        }
        ImGui::PopStyleColor(3);
    }ImGui::End();
}
void screen2_render(App* app)
{
    const std::string name = "LOGIN";
    ImVec2 position = ImVec2(0,0);
    ImVec2 size = ImVec2(1280, 720);
    ImGuiWindowFlags flags = ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoMove;


    ImGui::SetNextWindowPos(position);
    ImGui::SetNextWindowSize(size, ImGuiCond_Always);

    static User _inputUser;

    if(ImGui::Begin(name.c_str(), NULL, flags)){

        ImGui::Text("Username:");
        ImGui::InputTextWithHint("##username","Username", &_inputUser.name, ImGuiInputTextFlags_CharsUppercase | ImGuiInputTextFlags_CharsNoBlank);

        ImGui::Text("Password:");
        static bool _isViewPass = false;
        ImGui::InputTextWithHint("##password:","Password", &_inputUser.password, _isViewPass ? ImGuiInputTextFlags_None : ImGuiInputTextFlags_Password);
        ImGui::SameLine();
        if(ImGui::Button(_isViewPass ? "Hide" : "View")){
            _isViewPass = !_isViewPass;
        }
        static bool _isLogged = false;
        if(ImGui::Button(_isLogged ? "Logout":"Login")){
            _isLogged = ! _isLogged;
        }
        ImGui::SameLine();
        if(ImGui::Button("Logout")){

        }
        ImGui::SameLine();
        if(ImGui::Button("Users")){

        }
        //CRUD - Create, Read, Update, Delete.
        ImGui::SeparatorText("CRUD");
        if(ImGui::Button("Create")){

        }
        ImGui::SameLine();
        if(ImGui::Button("Read")){

        }
        ImGui::SameLine();
        if(ImGui::Button("Update")){

        }
        ImGui::SameLine();
        if(ImGui::Button("Delete")){

        }

    }ImGui::End();


}
void screen3_render(App* app)
{
    const std::string name = "HOME";
    ImVec2 position = ImVec2(0,0);
    ImVec2 size = ImVec2(1280, 720);
    ImGuiWindowFlags flags = ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoMove;
    ImGui::SetNextWindowPos(position);
    ImGui::SetNextWindowSize(size, ImGuiCond_Always);
    if(ImGui::Begin(name.c_str(), NULL, flags)){        
    }ImGui::End();
}
void screen4_render(App* app)
{
    const std::string name = "RECIPIES";
    ImVec2 position = ImVec2(0,0);
    ImVec2 size = ImVec2(1280, 720);
    ImGuiWindowFlags flags = ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoMove;
    ImGui::SetNextWindowPos(position);
    ImGui::SetNextWindowSize(size, ImGuiCond_Always);

    if(ImGui::Begin(name.c_str(), NULL, flags)){

    }ImGui::End();
}
void screen5_render(App* app)
{
    const std::string name = "SETUP";
    ImVec2 position = ImVec2(0,0);
    ImVec2 size = ImVec2(1280, 720);
    ImGuiWindowFlags flags = ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoMove;
    ImGui::SetNextWindowPos(position);
    ImGui::SetNextWindowSize(size, ImGuiCond_Always);

    if(ImGui::Begin(name.c_str(), NULL, flags)){

    }ImGui::End();
}
void App::draw_grid(float scale, const ImVec4& color, bool filled)
{
    const ImU32 color_int = ImColor(color);

    ImVec2 top_left;
    ImVec2 bottom_right;
    ImDrawList* draw = ImGui::GetBackgroundDrawList();

    int cell_size =  std::gcd( static_cast<int>(m_size.x), static_cast<int>(m_size.y)) / (scale <= 0.0f ? 0.0f : scale);

    for (int col = 0; col < m_size.y / 8; ++col)
    {
        for (int row = 0; row < m_size.x / 8; ++row)
        {
            top_left = ImVec2(row * cell_size, col * cell_size);
            bottom_right = ImVec2((row + 1) * cell_size, (col + 1) * cell_size);
            if (filled)
                draw->AddRectFilled(top_left, bottom_right, color_int);
            else
                draw->AddRect(top_left, bottom_right, color_int);
        }
    }
}
void App::mouse_handler(float threshold){
    
    uint8_t index = m_current_state;
    ImGuiIO& io = ImGui::GetIO();
    if ( ImGui::IsMouseClicked(ImGuiMouseButton_Left)){
        PRINT("Clicked");
        m_is_drag_state=true;
    }
    if( m_is_drag_state && io.MouseDelta.x > 0 && ImGui::IsMouseDragging(ImGuiMouseButton_Left, threshold)){
        PRINT("Swipe Left");
        index == 0 ? index = 4 : index--;
        m_current_state = static_cast<FSM::systemState_t>(index);
        PRINT("Screen: " + std::to_string( m_current_state + 1 ));
        m_is_drag_state=false;
    }
    if( m_is_drag_state && io.MouseDelta.x < 0 && ImGui::IsMouseDragging(ImGuiMouseButton_Left, threshold)){
        PRINT("Swipe Right");
        index == 4 ? index = 0 : index++;
        m_current_state = static_cast<FSM::systemState_t>(index);
        PRINT("Screen: " + std::to_string( m_current_state + 1 ));
        m_is_drag_state=false;
    }
    if ( ImGui::IsMouseReleased(ImGuiMouseButton_Left)){
        PRINT("Released");
        m_is_drag_state=true;
    }
}

void App::set_app_style()
{
    ImGuiStyle& style = ImGui::GetStyle();
    //ImGui::SeparatorText("Rounding");
    //ImGui::SliderFloat("WindowRounding", &style.WindowRounding, 0.0f, 12.0f, "%.0f");
    style.WindowRounding = 5.0f;
    style.WindowTitleAlign = ImVec2(0.5f, 0.5f);
    style.SeparatorTextAlign = ImVec2(0.5f, 0.5f);
}


void App::debug_screen(App* app){

    const char* name = "Debug";
    //ImVec2 position = ImVec2(0,0);
    //ImVec2 size = ImVec2(1280, 720);
    ImGuiWindowFlags _flags = ImGuiWindowFlags_AlwaysAutoResize;
    //ImGui::SetNextWindowPos(position);
    //ImGui::SetNextWindowSize(size, ImGuiCond_Always);

    //ImGui::ShowDemoWindow();
    //ImVec2 size = ImVec2(1089, 720);
    //ImGui::Image((void*)app->m_SDL_logoTexture, size);

    if( ImGui::Begin(name,NULL, _flags) ){
        ImGuiIO& io = ImGui::GetIO();
        // Basic info
        ImGui::SeparatorText("Basic info");
        ImGui::Text("Dear ImGui %s", ImGui::GetVersion());
        ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / io.Framerate, io.Framerate);
        ImGui::Text("%d vertices, %d indices (%d triangles)", io.MetricsRenderVertices, io.MetricsRenderIndices, io.MetricsRenderIndices / 3);
        ImGui::Text("%d visible windows, %d active allocations", io.MetricsRenderWindows, io.MetricsActiveWindows);
        //Screen selector
        ImGui::SeparatorText("Screen selector");
        if (ImGui::Button("Screen1")){
            app->m_current_state = FSM::SCREEN1;
            PRINT("FSM::SCREEN1");
        }
        ImGui::SameLine();
        if (ImGui::Button("Screen2")){
            app->m_current_state = FSM::SCREEN2;
            PRINT("FSM::SCREEN2");
        }
        ImGui::SameLine();
        if (ImGui::Button("Screen3")){
            app->m_current_state = FSM::SCREEN3;
            PRINT("FSM::SCREEN3");
        }
        ImGui::SameLine();
        if (ImGui::Button("Screen4")){
            app->m_current_state = FSM::SCREEN4;
            PRINT("FSM::SCREEN4");
        }
        ImGui::SameLine();
        if (ImGui::Button("Screen5")){
            app->m_current_state = FSM::SCREEN5;
            PRINT("FSM::SCREEN5");
        }
        // Mouse info
        ImGui::SeparatorText("Mouse info");
        if (ImGui::IsMousePosValid())
            ImGui::Text("Mouse pos: (%g, %g)", io.MousePos.x, io.MousePos.y);

        else
            ImGui::Text("Mouse pos: <INVALID>");
        ImGui::Text("Mouse delta: (%g, %g)", io.MouseDelta.x, io.MouseDelta.y);
        ImGui::Text("Mouse down:");

        for (int i = 0; i < IM_ARRAYSIZE(io.MouseDown); i++){
            if (ImGui::IsMouseDown(i)) {
                ImGui::SameLine();
                ImGui::Text("b%d (%.02f secs)", i, io.MouseDownDuration[i]);
            }
        }
        //Mouse SwapView
        struct funcs { static bool IsLegacyNativeDupe(ImGuiKey key) { return key < 512 && ImGui::GetIO().KeyMap[key] != -1; } }; // Hide Native<>ImGuiKey duplicates when both exists in the array
        ImGuiKey start_key = (ImGuiKey)0;
        ImGui::Text("Keys down:");         for (ImGuiKey key = start_key; key < ImGuiKey_NamedKey_END; key = (ImGuiKey)(key + 1)) { if (funcs::IsLegacyNativeDupe(key) || !ImGui::IsKeyDown(key)) continue; ImGui::SameLine(); ImGui::Text((key < ImGuiKey_NamedKey_BEGIN) ? "\"%s\"" : "\"%s\" %d", ImGui::GetKeyName(key), key); }
        
        if( m_is_drag_state && ImGui::IsMouseDragging(ImGuiMouseButton_Left, 50.0f) && io.MouseDelta.x < 0 ){
            PRINT("Swipe Left");
            m_is_drag_state = false;
        }else if(m_is_drag_state && ImGui::IsMouseDragging(ImGuiMouseButton_Left, 50.0f) && io.MouseDelta.x > 0 ){
            PRINT("Swipe Right");
            m_is_drag_state = false;
        }
        m_is_drag_state = ImGui::IsMouseReleased(ImGuiMouseButton_Left);

        if (ImGui::Button("EXIT!!!"))
            app->set_app_done(true);

    }ImGui::End();
}
