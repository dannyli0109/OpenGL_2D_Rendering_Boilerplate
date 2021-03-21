#include "ImGuiContainer.h"
#include "Window.h"

ImGuiContainer::~ImGuiContainer()
{
    Destroy();
}

void ImGuiContainer::Init()
{
    Window* window = Window::GetInstance();
    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;

    // Setup Dear ImGui style
    ImGui::StyleColorsDark();
    //ImGui::StyleColorsClassic();

    // Setup Platform/Renderer backends
    //ImGui_ImplGlfw_InitForOpenGL(window->Get(), true);
    ImGui_ImplOpenGL3_Init("#version 410");
}

void ImGuiContainer::Destroy()
{
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
}

void ImGuiContainer::Begin()
{
    Window* window = Window::GetInstance();
    ImGuiIO& io = ImGui::GetIO();
    glm::vec2 windowSize = window->GetSize();
    io.DisplaySize = ImVec2(windowSize.x, windowSize.y);
    ImGui_ImplOpenGL3_NewFrame();
    ImGui::NewFrame();
    // Make window dockable
    ImGui::DockSpaceOverViewport(ImGui::GetMainViewport(), ImGuiDockNodeFlags_PassthruCentralNode);
}

void ImGuiContainer::End()
{
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    ImGui::EndFrame();
}
