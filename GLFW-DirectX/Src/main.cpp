#include "Application.hpp"

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR pCmdLine, int nCmdShow)
{

	Application* This = new Application(1280, 720);

	while (!glfwWindowShouldClose(This->GetWindow()))
	{
		glfwPollEvents();

	}

	delete This;
	return 0;

}