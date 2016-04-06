#pragma once
#include "stdafx.h"

struct VERTEX
{
	FLOAT X, Y, Z;     
	D3DXCOLOR Color;   
};

class DX11App
{
public:
	DX11App();
	virtual ~DX11App(void);

	void Init(HWND* in_Wnd);
	void RenderFrame();
	void Clean();

	size_t GetWidth() const {return m_nWidth;}
	size_t GetHeight() const {return m_nHeight;}

protected:
	void InitBackBuffer();
	void SetViewPort();
	void LoadShaders();
	void CreateVertexBuffer();


protected:
	HWND m_WindwowsHandler;

	IDXGISwapChain* m_pSwapChain;            
	ID3D11Device* m_pDevice;                     
	ID3D11DeviceContext* m_pDeviceContext; 
	ID3D11RenderTargetView* m_pBackBuffer;

	ID3D11VertexShader* m_pVS;    
	ID3D11PixelShader* m_pPS;     

	ID3D11Buffer* m_pVertexBuffer;

	ID3D11InputLayout* m_pLayout;

	size_t m_nWidth;
	size_t m_nHeight;
};

