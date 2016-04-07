#pragma once
#include "dx11app.h"
class DrawInstancedDX11App :
  public DX11App
{
public:
  DrawInstancedDX11App(void);
  ~DrawInstancedDX11App(void);

  void RenderFrame();
  void Clean();


protected:
  void LoadShaders();
  void CreateVertexBuffer();

  ID3D11Buffer* m_pInstanceBuffer;
};

