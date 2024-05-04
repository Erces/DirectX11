#pragma once
#include "Window.h"
#include "ErziTimer.h"
class App
{
public:
	App();

	int Start();
private:
	void Update();
private:
	Window wnd;
	ErziTimer timer;
};

