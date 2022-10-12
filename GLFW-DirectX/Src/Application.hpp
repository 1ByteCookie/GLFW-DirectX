#pragma once

#define GLFW_EXPOSE_NATIVE_WIN32
#define GLFW_NATIVE_INCLUDE_NONE

#include <Windows.h>
#include <GLFW/glfw3.h>
#include <GLFW/glfw3native.h>


class Application
{

public:
	
	Application(int wWidth, int wHeight);
	~Application();

	inline GLFWwindow* GetWindow() const { return m_Window; }

private:

	GLFWwindow* m_Window;
	HWND		m_WindowHandle;

	int			m_WindowWidth;
	int			m_WindowHeight;

};