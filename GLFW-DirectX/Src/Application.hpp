#pragma once

#define GLFW_EXPOSE_NATIVE_WIN32
#define GLFW_NATIVE_INCLUDE_NONE

#include <Windows.h>
#include <GLFW/glfw3.h>
#include <GLFW/glfw3native.h>
#include <memory>

#include "Graphics.hpp"

class Application
{

public:
	
	Application(int wWidth, int wHeight);
	~Application();

	inline GLFWwindow* GetWindow() const { return m_Window; }
	inline Graphics* Renderer() const { return m_Graphics.get(); }

private:

	GLFWwindow*					m_Window;
	HWND						m_WindowHandle;
	std::unique_ptr<Graphics>	m_Graphics;

	int							m_WindowWidth;
	int							m_WindowHeight;

};