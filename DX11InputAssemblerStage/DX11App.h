#pragma once
#include "stdafx.h"

class DX11App
{
public:
	DX11App();
	virtual ~DX11App(void);

	void Init(HWND in_Wnd);
	void Clean();

protected:
	HWND m_WindwowsHandler;

	IDXGISwapChain* m_pSwapChain;            
	ID3D11Device* m_pDevice;                     
	ID3D11DeviceContext* m_pDeviceContext;           
};

