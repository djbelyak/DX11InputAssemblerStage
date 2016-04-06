#include "stdafx.h"
#include "DX11App.h"


DX11App::DX11App():
	m_nHeight(600),
	m_nWidth(800)
{
}


DX11App::~DX11App(void)
{
	Clean();

	delete m_pSwapChain;
	delete m_pDevice;
	delete m_pDeviceContext;
}

void DX11App::Init(HWND* in_Wnd)
{

	HRESULT hr = S_OK;

	DXGI_SWAP_CHAIN_DESC scd;
	SecureZeroMemory(&scd, sizeof(DXGI_SWAP_CHAIN_DESC));

	scd.BufferCount = 1;                                    
	scd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;     
	scd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;      
	scd.OutputWindow = *in_Wnd;                                
	scd.SampleDesc.Count = 4;                               
	scd.Windowed = TRUE;                               //Windows is temp

	// create a device, device context and swap chain using the information in the scd struct
	hr = D3D11CreateDeviceAndSwapChain(NULL,
		D3D_DRIVER_TYPE_HARDWARE,
		NULL,
		NULL,
		NULL,
		NULL,
		D3D11_SDK_VERSION,
		&scd,
		&m_pSwapChain,
		&m_pDevice,
		NULL,
		&m_pDeviceContext);

	InitBackBuffer();
	SetViewPort();
}

void DX11App::Clean()
{
	m_pSwapChain->Release();
	m_pBackBuffer->Release();
	m_pDevice->Release();
	m_pDeviceContext->Release();
}

void DX11App::RenderFrame()
{
	// clear the back buffer to a deep blue
	float clearColor[4] = {0.0f, 0.2f, 0.4f, 1.0f};
	m_pDeviceContext->ClearRenderTargetView(m_pBackBuffer, clearColor)	;

	// do 3D rendering on the back buffer here

	// switch the back buffer and the front buffer
	m_pSwapChain->Present(0, 0);
}

void DX11App::InitBackBuffer(){	// get the address of the back buffer
	ID3D11Texture2D *pBackBuffer;
	m_pSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&pBackBuffer);

	// use the back buffer address to create the render target
	m_pDevice->CreateRenderTargetView(pBackBuffer, NULL, &m_pBackBuffer);
	pBackBuffer->Release();

	// set the render target as the back buffer
	m_pDeviceContext->OMSetRenderTargets(1, &m_pBackBuffer, NULL);}void DX11App::SetViewPort(){	D3D11_VIEWPORT viewport;
	ZeroMemory(&viewport, sizeof(D3D11_VIEWPORT));

	viewport.TopLeftX = 0;
	viewport.TopLeftY = 0;
	viewport.Width = m_nWidth;
	viewport.Height = m_nHeight;

	m_pDeviceContext->RSSetViewports(1, &viewport);}


