#include "Graphics.hpp"

Graphics::Graphics(HWND Handle)
	:	m_SwapChain(nullptr)
	,	m_Device(nullptr)
	,	m_Context(nullptr)
	,	m_RenderTarget(nullptr)
{

	DXGI_SWAP_CHAIN_DESC scDescriptor = { };
	scDescriptor.BufferDesc.Width					= NULL;
	scDescriptor.BufferDesc.Height					= NULL;
	scDescriptor.BufferDesc.RefreshRate.Numerator	= 60;
	scDescriptor.BufferDesc.RefreshRate.Denominator	= 1;
	scDescriptor.BufferDesc.Format					= DXGI_FORMAT_R16G16B16A16_FLOAT;
	scDescriptor.SampleDesc.Count					= 1;
	scDescriptor.SampleDesc.Quality					= 0;
	scDescriptor.BufferUsage						= DXGI_USAGE_RENDER_TARGET_OUTPUT;
	scDescriptor.BufferCount						= 2;
	scDescriptor.OutputWindow						= Handle;
	scDescriptor.Windowed							= TRUE;
	scDescriptor.SwapEffect							= DXGI_SWAP_EFFECT_DISCARD;

	D3D11CreateDeviceAndSwapChain(NULL,
								  D3D_DRIVER_TYPE_HARDWARE,
								  NULL,
								  D3D11_CREATE_DEVICE_DEBUG | D3D11_CREATE_DEVICE_SINGLETHREADED,
								  NULL,
								  NULL,
								  D3D11_SDK_VERSION,
								  &scDescriptor,
								  &m_SwapChain,
								  &m_Device,
								  NULL,
								  &m_Context);

	ID3D11Resource* BackBuffer;
	m_SwapChain->GetBuffer(0, __uuidof(ID3D11Resource), reinterpret_cast<void**>(&BackBuffer));
	m_Device->CreateRenderTargetView(BackBuffer, NULL, &m_RenderTarget);

	BackBuffer->Release();

}

Graphics::~Graphics()
{

	if (m_SwapChain) { m_SwapChain->Release(); }
	if (m_Device) { m_Device->Release(); }
	if (m_Context) { m_Context->Release(); }
	if (m_RenderTarget) { m_RenderTarget->Release(); }

}

void Graphics::ClearColorBuffer(float R, float G, float B, float A)
{

	float RGBA[] = { R,G,B,A };
	m_Context->ClearRenderTargetView(m_RenderTarget, RGBA);

}
