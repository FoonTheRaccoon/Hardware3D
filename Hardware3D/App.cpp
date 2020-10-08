#include "App.h"

App::App()
    :
    wnd(800, 600, L"Project Raccoon 3D Engine")
{}

int App::Go()
{
    while (true)
    {
        if (const std::optional<int> ecode = Window::ProccessMessages())
        {
            return *ecode;
        }
        DoFrame();
    }
}

void App::DoFrame()
{
    wnd.Gfx().ClearBuffer(0.0f, 0.0f, 0.0f);
    wnd.Gfx().DrawTriangle();
    wnd.Gfx().EndFrame();
}
