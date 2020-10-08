#include "App.h"

App::App(float width, float height, const wchar_t* name)
    :
    wnd(width, height, name),
    width(width), height(height)
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
    wnd.Gfx().DrawTriangle(-globalTimer.TimeSinceStart(), 0.0f, 0.0f);
    wnd.Gfx().DrawTriangle(globalTimer.TimeSinceStart(), wnd.mouse.GetPosX() / (width / 2.0f) - 1.0f, -wnd.mouse.GetPosY() / (height / 2.0f) + 1.0f);
    wnd.Gfx().EndFrame();
}
