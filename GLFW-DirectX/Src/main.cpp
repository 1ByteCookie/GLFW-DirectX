#include "Application.hpp"

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR pCmdLine, int nCmdShow)
{

	Application* This = new Application(1280, 720);


	while (!glfwWindowShouldClose(This->GetWindow()))
	{

		glfwPollEvents();
		This->Renderer()->ClearColorBuffer(0.25f, 0.0f, 5.0f, 1.0f);

		This->Renderer()->SwapChain()->Present(0, 0);
	
	}

	delete This;
	return 0;

}