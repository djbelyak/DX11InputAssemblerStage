#pragma once
#include "dx11app.h"
class DrawIndexedDX11App :
  public DX11App
{
public:
  DrawIndexedDX11App(void);
  ~DrawIndexedDX11App(void);

  void Init(HWND* in_Wnd);
  void RenderFrame();
  void Clean();


protected:
  void LoadShaders();
  void CreateVertexBuffer();

  ID3D11Buffer* m_pIndexBuffer;
};

