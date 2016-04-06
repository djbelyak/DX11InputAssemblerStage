#include "stdafx.h"
#include "DX11App.h"


DX11App::DX11App()
{
	m_pSwapChain = NULL;
	m_pDevice = NULL;
	m_pDeviceContext = NULL;
}


DX11App::~DX11App(void)
{
	Clean();

	delete m_pSwapChain;
	delete m_pDevice;
	delete m_pDeviceContext;
}

void DX11App::Init(HWND in_Wnd)
{

	 DXGI_SWAP_CHAIN_DESC scd;

    // clear out the struct for use
    ZeroMemory(&scd, sizeof(DXGI_SWAP_CHAIN_DESC));

    // fill the swap chain description struct
    scd.BufferCount = 1;                                    
    scd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;     
    scd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;      
		scd.OutputWindow = m_WindwowsHandler;                                
    scd.SampleDesc.Count = 4;                               
    scd.Windowed = TRUE;                               //Windows is temp

    // create a device, device context and swap chain using the information in the scd struct
    D3D11CreateDeviceAndSwapChain(NULL,
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
}

void DX11App::Clean()
{
	m_pSwapChain->Release();
	m_pDevice->Release();
	m_pDeviceContext->Release();
}

