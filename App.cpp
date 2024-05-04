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
	
	const float t = timer.Peek();
	std::ostringstream oss;
	oss << "Time elapsed: " << std::setprecision(1) << std::fixed << t;
	wnd.SetTitle(oss.str());
}
