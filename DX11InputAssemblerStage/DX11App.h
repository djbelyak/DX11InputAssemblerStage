#pragma once
#include "stdafx.h"

class DX11App
{
public:
	DX11App();
	virtual ~DX11App(void);

	void Init(HWND* in_Wnd);
	void RenderFrame();
	void Clean();

protected:
	void InitBackBuffer();
	void SetViewPort();

protected:
	HWND m_WindwowsHandler;

	IDXGISwapChain* m_pSwapChain;            
	ID3D11Device* m_pDevice;                     
	ID3D11DeviceContext* m_pDeviceContext; 
	ID3D11RenderTargetView* m_pBackBuffer;

	size_t m_nWidth;
	size_t m_nHeight;
};

