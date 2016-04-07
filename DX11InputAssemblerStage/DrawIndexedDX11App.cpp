#include "stdafx.h"
#include "DrawIndexedDX11App.h"


DrawIndexedDX11App::DrawIndexedDX11App(void)
{
}


DrawIndexedDX11App::~DrawIndexedDX11App(void)
{
}


void DrawIndexedDX11App::Clean()
{
  m_pIndexBuffer->Release();
  DX11App::Clean();
}

void DrawIndexedDX11App::RenderFrame()
{
  // clear the back buffer to a deep blue
  float clearColor[4] = {0.0f, 0.2f, 0.4f, 1.0f};
  m_pDeviceContext->ClearRenderTargetView(m_pBackBuffer, clearColor)	;


  UINT elementSize = sizeof(VERTEX);
  UINT offset = 0;
  m_pDeviceContext->IASetVertexBuffers(0, 1, &m_pVertexBuffer, &elementSize, &offset);
  m_pDeviceContext->IASetPrimitiveTopology(D3D10_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

  m_pDeviceContext->DrawIndexed(24, 0, 0);

  // switch the back buffer and the front buffer
  m_pSwapChain->Present(0, 0);
}

void DrawIndexedDX11App::LoadShaders()
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

void DrawIndexedDX11App::CreateVertexBuffer()
{

  D3DXCOLOR nvGreen = D3DXCOLOR(0.46274509803f, 0.72549019607f, 0.0f, 1.0f);
  D3DXCOLOR nvBlack = D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f);
  VERTEX OurVertices[] =
  {
    {-1.0f, 1.0f, 0.0f, nvGreen},
    {0.0f, 1.0f, 0.0f, nvGreen},
    {1.0f, 1.0f, 0.0f, nvGreen},
    {-1.0f, 0.0f, 0.0f, nvGreen},
    {0.0f, 0.0f, 0.0f, nvBlack},
    {1.0f, 0.0f, 0.0f, nvGreen},
    {-1.0f, -1.0f, 0.0f, nvGreen},
    {0.0f, -1.0f, 0.0f, nvGreen},
    {1.0f, -1.0f, 0.0f, nvGreen},

  };

  DWORD indices[] = {
    3, 0, 4,
    4, 0, 1,
    4, 1, 5,
    1, 2, 5,
    6, 3, 7,
    7, 3, 4,
    7, 4, 8,
    8, 4, 5
  };

  D3D11_BUFFER_DESC indexBufferDesc;
  ZeroMemory( &indexBufferDesc, sizeof(indexBufferDesc) );

  indexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
  indexBufferDesc.ByteWidth = sizeof(indices);
  indexBufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
  indexBufferDesc.CPUAccessFlags = 0;
  indexBufferDesc.MiscFlags = 0;

  D3D11_SUBRESOURCE_DATA iinitData;

  iinitData.pSysMem = indices;
  m_pDevice->CreateBuffer(&indexBufferDesc, &iinitData, &m_pIndexBuffer);

  m_pDeviceContext->IASetIndexBuffer( m_pIndexBuffer, DXGI_FORMAT_R32_UINT, 0);

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


