#include "Application.hpp"

#include <d3dcompiler.h>

struct Vertex
{
	DirectX::XMFLOAT2 Position;
	DirectX::XMFLOAT3 Color;
};

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


	m_ViewportDescriptor = {};
	m_ViewportDescriptor.Width		= m_WindowWidth;
	m_ViewportDescriptor.Height		= m_WindowHeight;
	m_ViewportDescriptor.MaxDepth	= 0;
	m_ViewportDescriptor.MinDepth	= 0;
	m_ViewportDescriptor.TopLeftX	= 0;
	m_ViewportDescriptor.TopLeftY	= 0;


	m_WindowHandle	= glfwGetWin32Window(m_Window);
	m_Graphics		= std::make_unique<Graphics>(m_WindowHandle);

}

Application::~Application()
{

	{
		m_Triangle.VertexBuffer->Release();
		m_Triangle.IndexBuffer->Release();
		m_Triangle.VertexShader->Release();
		m_Triangle.PixelShader->Release();
		m_Triangle.InputLayout->Release();
	}

	glfwDestroyWindow(m_Window);
	glfwTerminate();

}

void Application::InitTriangle()
{

	Vertex VertexBuffer[] =
	{
		DirectX::XMFLOAT2(-0.5f, -0.5f), DirectX::XMFLOAT3(1.0f, 0.0f, 0.0f),
		DirectX::XMFLOAT2( 0.0f,  0.5f), DirectX::XMFLOAT3(0.0f, 1.0f, 0.0f),
		DirectX::XMFLOAT2( 0.5f, -0.5f), DirectX::XMFLOAT3(0.0f, 0.0f, 1.0f)
	};

	uint32_t IndexBuffer[] =
	{
		0, 1, 2
	};

	
	// Vertex buffer creation
	D3D11_BUFFER_DESC vbDescriptor = { };
	vbDescriptor.ByteWidth				= sizeof(VertexBuffer);
	vbDescriptor.Usage					= D3D11_USAGE_DEFAULT;
	vbDescriptor.BindFlags				= D3D11_BIND_VERTEX_BUFFER;
	vbDescriptor.CPUAccessFlags			= 0;
	vbDescriptor.MiscFlags				= 0;
	vbDescriptor.StructureByteStride	= sizeof(Vertex);

	D3D11_SUBRESOURCE_DATA vbResource = { };
	vbResource.pSysMem				= VertexBuffer;
	vbResource.SysMemPitch			= 0;
	vbResource.SysMemSlicePitch		= 0;
	
	m_Graphics->Device()->CreateBuffer(&vbDescriptor, &vbResource,  &m_Triangle.VertexBuffer);


	// Index buffer creation
	D3D11_BUFFER_DESC ibDescriptor = { };
	ibDescriptor.ByteWidth				= sizeof(IndexBuffer);
	ibDescriptor.Usage					= D3D11_USAGE_DEFAULT;
	ibDescriptor.BindFlags				= D3D11_BIND_INDEX_BUFFER;
	ibDescriptor.CPUAccessFlags			= 0;
	ibDescriptor.MiscFlags				= 0;
	ibDescriptor.StructureByteStride	= sizeof(uint32_t);

	D3D11_SUBRESOURCE_DATA ibResource = { };
	ibResource.pSysMem				= IndexBuffer;
	ibResource.SysMemPitch			= 0;
	ibResource.SysMemSlicePitch		= 0;

	m_Graphics->Device()->CreateBuffer(&ibDescriptor, &ibResource, &m_Triangle.IndexBuffer);


	{
		// Shader creation
		ID3DBlob* vsBlob;
		D3DReadFileToBlob(L"ShaderBin/VertexShader.cso", &vsBlob);
		m_Graphics->Device()->CreateVertexShader(vsBlob->GetBufferPointer(),
												 vsBlob->GetBufferSize(),
												 NULL,
												 &m_Triangle.VertexShader);

		ID3DBlob* psBlob;
		D3DReadFileToBlob(L"ShaderBin/PixelShader.cso", &psBlob);
		m_Graphics->Device()->CreatePixelShader(psBlob->GetBufferPointer(),
												psBlob->GetBufferSize(),
												NULL,
												&m_Triangle.PixelShader);


		// Input layout creation
		D3D11_INPUT_ELEMENT_DESC PositionElement = { };
		PositionElement.SemanticName			= "POSITION";
		PositionElement.SemanticIndex			= 0;
		PositionElement.Format					= DXGI_FORMAT_R32G32_FLOAT;
		PositionElement.InputSlot				= 0;
		PositionElement.AlignedByteOffset		= offsetof(Vertex, Vertex::Position);
		PositionElement.InputSlotClass			= D3D11_INPUT_PER_VERTEX_DATA;
		PositionElement.InstanceDataStepRate	= 0;

		D3D11_INPUT_ELEMENT_DESC ColorElement = { };
		ColorElement.SemanticName				= "COLOR";
		ColorElement.SemanticIndex				= 0;
		ColorElement.Format						= DXGI_FORMAT_R32G32B32_FLOAT;
		ColorElement.InputSlot					= 0;
		ColorElement.AlignedByteOffset			= offsetof(Vertex, Vertex::Color);
		ColorElement.InputSlotClass				= D3D11_INPUT_PER_VERTEX_DATA;
		ColorElement.InstanceDataStepRate		= 0;

		D3D11_INPUT_ELEMENT_DESC Layout[] = { PositionElement, ColorElement };
		m_Graphics->Device()->CreateInputLayout(Layout,
												2,
												vsBlob->GetBufferPointer(),
												vsBlob->GetBufferSize(),
												&m_Triangle.InputLayout);
		

		vsBlob->Release();
		psBlob->Release();
	}

}

void Application::DrawTriangle()
{

	UINT Stride = sizeof(Vertex);
	UINT Offset = 0;
	m_Graphics->Context()->IASetVertexBuffers(0,
											  1,
											  &m_Triangle.VertexBuffer,
											  &Stride,
											  &Offset);


	m_Graphics->Context()->IASetIndexBuffer(m_Triangle.IndexBuffer, DXGI_FORMAT_R32_UINT, 0);

	m_Graphics->Context()->IASetInputLayout(m_Triangle.InputLayout);
	m_Graphics->Context()->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);


	m_Graphics->Context()->VSSetShader(m_Triangle.VertexShader, NULL, 0);
	m_Graphics->Context()->PSSetShader(m_Triangle.PixelShader, NULL, 0);


	ID3D11RenderTargetView* RenderTarget =  m_Graphics->GetRenderTarget();
	m_Graphics->Context()->OMSetRenderTargets(1, &RenderTarget, NULL);
	m_Graphics->Context()->RSSetViewports(1, &m_ViewportDescriptor);


	m_Graphics->Context()->DrawIndexed(3, 0, 0);

}
