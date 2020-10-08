#pragma once
#include "Window.h"

class App
{
public:
	App(float width, float height, const wchar_t* name);
	int Go();
private:
	void DoFrame();
private:
	const float width;
	const float height;
	Window wnd;
};

