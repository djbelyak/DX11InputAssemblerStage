#pragma once
#include "stdafx.h"

struct VERTEX
{
	FLOAT X, Y, Z;     
	D3DXCOLOR Color;   
};

enum eAppType {
  Draw,
  DrawInstanced,
  DrawIndexed,
  DrawIndexedInstanced,
  DrawAuto
};

eAppType GetAppType(LPWSTR* argList);

class DX11App
{
public:
  static DX11App* MakeDX11App(eAppType in_type);
	DX11App();
	virtual ~DX11App(void);

	void Init(HWND* in_Wnd);
	virtual void RenderFrame() = 0;
	void Clean();

	size_t GetWidth() const {return m_nWidth;}
	size_t GetHeight() const {return m_nHeight;}

protected:
	void InitBackBuffer();
	void SetViewPort();
	virtual void LoadShaders() = 0;
	virtual void CreateVertexBuffer() = 0;


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

