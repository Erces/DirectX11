#pragma once
#include "Window.h"
#include "ErziTimer.h"
class App
{
public:
	App();

	int Start();
	~App();
private:
	void Update();
private:
	Window wnd;
	ErziTimer timer;
	std::vector<std::unique_ptr<class Box>> boxes;
};

