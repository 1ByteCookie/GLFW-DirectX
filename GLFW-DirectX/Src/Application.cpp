#include "Application.hpp"

Application::Application(int wWidth, int wHeight)
	:	m_Window(nullptr)
	,	m_WindowHandle(0)
	,	m_WindowWidth(wWidth)
	,	m_WindowHeight(wHeight)
{

	if (!glfwInit())
		OutputDebugString(L"glfwInit error!\n");


	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
	glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);


	m_Window = glfwCreateWindow(m_WindowWidth, m_WindowHeight, "DirectX Demo", nullptr, nullptr);
	if (!m_Window)
		OutputDebugString(L"Window creation failed!\n");


	m_WindowHandle	= glfwGetWin32Window(m_Window);
	m_Graphics		= std::make_unique<Graphics>(m_WindowHandle);

}

Application::~Application()
{

	glfwDestroyWindow(m_Window);
	glfwTerminate();

}
