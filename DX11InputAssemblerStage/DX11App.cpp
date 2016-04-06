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

void DX11App::RenderFrame()
{
	// clear the back buffer to a deep blue
	float clearColor[4] = {0.0f, 0.2f, 0.4f, 1.0f};
	m_pDeviceContext->ClearRenderTargetView(m_pBackBuffer, clearColor)	;

	
	UINT elementSize = sizeof(VERTEX);
	UINT offset = 0;
	m_pDeviceContext->IASetVertexBuffers(0, 1, &m_pVertexBuffer, &elementSize, &offset);
	m_pDeviceContext->IASetPrimitiveTopology(D3D10_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	m_pDeviceContext->Draw(12,0);




	// switch the back buffer and the front buffer
	m_pSwapChain->Present(0, 0);
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

void DX11App::LoadShaders()
{
	ID3D10Blob *VS, *PS;
	D3DX11CompileFromFile(L"Shader.shader", 0, 0, "VShader", "vs_4_0", 0, 0, 0, &VS, 0, 0);
	D3DX11CompileFromFile(L"Shader.shader", 0, 0, "PShader", "ps_4_0", 0, 0, 0, &PS, 0, 0);

	m_pDevice->CreateVertexShader(VS->GetBufferPointer(), VS->GetBufferSize(), NULL, &m_pVS);
	m_pDevice->CreatePixelShader(PS->GetBufferPointer(), PS->GetBufferSize(), NULL, &m_pPS);

	m_pDeviceContext->VSSetShader(m_pVS, 0, 0);
	m_pDeviceContext->PSSetShader(m_pPS, 0, 0);

	D3D11_INPUT_ELEMENT_DESC ied[] = 
	{
		{"POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0},
		{"COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0},
	};

	m_pDevice->CreateInputLayout(ied, 2, VS->GetBufferPointer(), VS->GetBufferSize(), &m_pLayout);
	m_pDeviceContext->IASetInputLayout(m_pLayout);
}

void DX11App::CreateVertexBuffer()
{
	VERTEX OurVertices[] =
	{
		{-1.0f, -1.0f, 0.0f, D3DXCOLOR(0.0f, 0.0f, 1.0f, 1.0f)},
		{-0.5f, 0.0f, 0.0f, D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f)},
		{0.0f, -1.0f, 0.0f, D3DXCOLOR(0.0f, 1.0f, 0.0f, 1.0f)},
		{0.0f, -1.0f, 0.0f, D3DXCOLOR(0.0f, 0.0f, 1.0f, 1.0f)},
		{0.5f, 0.0f, 0.0f, D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f)},
		{1.0f, -1.0f, 0.0f, D3DXCOLOR(0.0f, 1.0f, 0.0f, 1.0f)},
		{-1.0f, 0.0f, 0.0f, D3DXCOLOR(0.0f, 0.0f, 1.0f, 1.0f)},
		{-0.5f, 1.0f, 0.0f, D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f)},
		{0.0f, 0.0f, 0.0f, D3DXCOLOR(0.0f, 1.0f, 0.0f, 1.0f)},
		{0.0f, 0.0f, 0.0f, D3DXCOLOR(0.0f, 0.0f, 1.0f, 1.0f)},
		{0.5f, 1.0f, 0.0f, D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f)},
		{1.0f, 0.0f, 0.0f, D3DXCOLOR(0.0f, 1.0f, 0.0f, 1.0f)},
	};

	D3D11_BUFFER_DESC bd;
	ZeroMemory(&bd, sizeof(bd));

	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = sizeof(OurVertices);
	bd.BindFlags        = D3D11_BIND_VERTEX_BUFFER;
	bd.CPUAccessFlags   = 0;
	bd.MiscFlags        = 0;


	D3D11_SUBRESOURCE_DATA InitData;
	InitData.pSysMem = OurVertices;
	InitData.SysMemPitch = 0;
	InitData.SysMemSlicePitch = 0;

	HRESULT hr = S_OK;
	hr = m_pDevice->CreateBuffer(&bd, &InitData, &m_pVertexBuffer);

}




