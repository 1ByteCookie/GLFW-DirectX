#pragma once

#include <Windows.h>
#include <d3d11.h>

class Graphics
{

public:

	Graphics(HWND Handle);
	~Graphics();

	inline IDXGISwapChain* SwapChain() { return m_SwapChain; }
	inline ID3D11Device* Device() { return m_Device; }
	inline ID3D11DeviceContext* Context() { return m_Context; }
	
	inline ID3D11RenderTargetView* GetRenderTarget() { return m_RenderTarget; }

	void ClearColorBuffer(float R, float G, float B, float A);


private:

	IDXGISwapChain*			m_SwapChain;
	ID3D11Device*			m_Device;
	ID3D11DeviceContext*	m_Context;
	ID3D11RenderTargetView* m_RenderTarget;

};