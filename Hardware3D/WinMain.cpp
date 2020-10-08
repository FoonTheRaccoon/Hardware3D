#include "App.h"

int CALLBACK WinMain(
	HINSTANCE hInstance,
	HINSTANCE hPrevInstance, 
	LPSTR lpCmdLine, 
	int nCmdShow)
{
	try
	{
		return App{ 800.0f, 600.0f, L"Project Raccoon 3D Engine" }.Go();
	}
	catch (const RacException& e)
	{
		const auto what = N2W(e.what());
		const auto type = N2W(e.GetType());
		MessageBoxW(nullptr, what, type, MB_OK | MB_ICONEXCLAMATION);
		delete what, type;
	}
	catch (const std::exception& e)
	{
		const auto what = N2W(e.what());
		MessageBoxW(nullptr, what, L"Standard Exception", MB_OK | MB_ICONEXCLAMATION);
		delete what;
	}
	catch (...)
	{
		MessageBoxW(nullptr, L"No details available", L"Unknown Exception", MB_OK | MB_ICONEXCLAMATION);
	}
	return -1;
}