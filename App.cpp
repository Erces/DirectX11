#include "App.h"
#include <chrono>

App::App() 
	:
	wnd(800,600,"Erzi Engine")
{}

//Same as Unity Start
int App::Start()
{
	while (true)
	{
		if (const auto ecode = Window::ProccessMessages())
		{
			return *ecode;
		}
		Update();
	}
}  

//Same as Unity Update
void App::Update()
{
	const float c = sin(timer.Peek() / 2.0f + 0.5f);

	wnd.Gfx().ClearBuffer(c, c, 1.0f);
	wnd.Gfx().DrawTestTriangle(timer.Peek(), wnd.mouse.GetPosX() / 400.0f -1.0f,-wnd.mouse.GetPosY() / 300.0f +1.0f);
	wnd.Gfx().EndFrame();
}
