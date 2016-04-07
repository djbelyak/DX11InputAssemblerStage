#include "stdafx.h"
#include "DrawDX11App.h"
#include "DX11App.h"




DX11App::DX11App():
	m_nHeight(1200),
	m_nWidth(1920)
{
}




DX11App::~DX11App(void)
{
	Clean();

	delete m_pSwapChain;
	delete m_pDevice;
	delete m_pDeviceContext;
}

DX11App* DX11App::MakeDX11App(eAppType in_type)
{
  return new DrawDX11App();
}

void DX11App::Init(HWND* in_Wnd)
{

	HRESULT hr = S_OK;

	DXGI_SWAP_CHAIN_DESC scd;
	SecureZeroMemory(&scd, sizeof(DXGI_SWAP_CHAIN_DESC));

	scd.BufferCount = 1;                                    
	scd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	scd.BufferDesc.Height = GetHeight();
	scd.BufferDesc.Width = GetWidth();
	scd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;      
	scd.OutputWindow = *in_Wnd;                                
	scd.SampleDesc.Count = 1;
	scd.Windowed = TRUE;                               
	scd.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;

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
	
	LoadShaders();

	CreateVertexBuffer();	
}

void DX11App::Clean()
{
	m_pSwapChain->SetFullscreenState(false, NULL);


	m_pVS->Release();
	m_pPS->Release();
	m_pSwapChain->Release();
	m_pBackBuffer->Release();
	m_pDevice->Release();
	m_pDeviceContext->Release();
}

void DX11App::InitBackBuffer()
{
	// get the address of the back buffer
	ID3D11Texture2D *pBackBuffer;
	m_pSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&pBackBuffer);

	// use the back buffer address to create the render target
	m_pDevice->CreateRenderTargetView(pBackBuffer, NULL, &m_pBackBuffer);
	pBackBuffer->Release();

	// set the render target as the back buffer
	m_pDeviceContext->OMSetRenderTargets(1, &m_pBackBuffer, NULL);
}

void DX11App::SetViewPort()
{
	D3D11_VIEWPORT viewport;
	ZeroMemory(&viewport, sizeof(D3D11_VIEWPORT));

	viewport.TopLeftX = 0;
	viewport.TopLeftY = 0;
	viewport.Width = GetWidth();
	viewport.Height = GetHeight();

	m_pDeviceContext->RSSetViewports(1, &viewport);
}

eAppType GetAppType(LPWSTR* argList)
{
  if (wcscmp(*argList, L"DrawInstanced") == 0)
    return DrawInstanced;
  if (wcscmp(*argList, L"DrawIndexed") == 0)
    return DrawIndexed;
  if (wcscmp(*argList, L"DrawIndexedInstanced") == 0)
    return DrawIndexedInstanced;
  if (wcscmp(*argList, L"DrawAuto") == 0)
    return DrawAuto;
  return Draw;
}