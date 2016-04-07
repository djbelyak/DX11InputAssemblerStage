#pragma once
#include "dx11app.h"
class DrawDX11App :
  public DX11App
{
public:
  DrawDX11App(void);
  ~DrawDX11App(void);

  void RenderFrame();

protected:
  void LoadShaders();
  void CreateVertexBuffer();
};

