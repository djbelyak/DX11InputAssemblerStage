#include "stdafx.h"
#include "DrawInstancedDX11App.h"


DrawInstancedDX11App::DrawInstancedDX11App(void)
{
}


DrawInstancedDX11App::~DrawInstancedDX11App(void)
{
}

void DrawInstancedDX11App::Clean()
{
  m_pInstanceBuffer->Release();
  DX11App::Clean();
}

void DrawInstancedDX11App::RenderFrame()
{
  // clear the back buffer to a deep blue
  float clearColor[4] = {0.0f, 0.2f, 0.4f, 1.0f};
  m_pDeviceContext->ClearRenderTargetView(m_pBackBuffer, clearColor)	;


  UINT strides[] = 
  {
      sizeof(VERTEX),
      sizeof(D3DXVECTOR3)
  };
  UINT offset[] = {0, 0};
  ID3D11Buffer* bufferPointers[] = 
  {
    m_pVertexBuffer,
    m_pInstanceBuffer,
  };
  m_pDeviceContext->IASetVertexBuffers(0, 2, bufferPointers, strides, offset);
  m_pDeviceContext->IASetPrimitiveTopology(D3D10_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

  m_pDeviceContext->DrawInstanced(3, 2, 0, 0);

  // switch the back buffer and the front buffer
  m_pSwapChain->Present(0, 0);
}

void DrawInstancedDX11App::LoadShaders()
{
  ID3D10Blob *VS, *PS;
  D3DX11CompileFromFile(L"InstanceShader.shader", 0, 0, "VShader", "vs_4_0", 0, 0, 0, &VS, 0, 0);
  D3DX11CompileFromFile(L"InstanceShader.shader", 0, 0, "PShader", "ps_4_0", 0, 0, 0, &PS, 0, 0);

  m_pDevice->CreateVertexShader(VS->GetBufferPointer(), VS->GetBufferSize(), NULL, &m_pVS);
  m_pDevice->CreatePixelShader(PS->GetBufferPointer(), PS->GetBufferSize(), NULL, &m_pPS);

  m_pDeviceContext->VSSetShader(m_pVS, 0, 0);
  m_pDeviceContext->PSSetShader(m_pPS, 0, 0);

  D3D11_INPUT_ELEMENT_DESC ied[] = 
  {
    {"POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0},
    {"COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0},
    {"INSTANCEPOS", 0, DXGI_FORMAT_R32G32B32_FLOAT, 1, 0, D3D11_INPUT_PER_INSTANCE_DATA, 0}
  };

  m_pDevice->CreateInputLayout(ied, 2, VS->GetBufferPointer(), VS->GetBufferSize(), &m_pLayout);
  m_pDeviceContext->IASetInputLayout(m_pLayout);
}

void DrawInstancedDX11App::CreateVertexBuffer()
{

  D3DXCOLOR nvGreen = D3DXCOLOR(0.46274509803f, 0.72549019607f, 0.0f, 1.0f);
  D3DXCOLOR nvBlack = D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f);
  VERTEX OurVertices[] =
  {
    {-1.0f, -1.0f, 0.0f, nvGreen},
    {-1.0f, 0.0f, 0.0f, nvGreen},
    {0.0f, -1.0f, 0.0f, nvGreen},
    {0.0f, 0.0f, 0.0f, nvBlack},
    /*
    {-1.0f, 1.0f, 0.0f, nvGreen},
    {0.0f, 1.0f, 0.0f, nvGreen},
    {1.0f, 1.0f, 0.0f, nvGreen},
    {1.0f, 0.0f, 0.0f, nvGreen},
    {1.0f, -1.0f, 0.0f, nvGreen},
    */
  };
  D3DXVECTOR3 OurInstances[] = 
  {
    D3DXVECTOR3(1.0f, 1.0f, 0.0f),
    D3DXVECTOR3(0.0f, 0.0f, 0.0f),
  };

  D3D11_BUFFER_DESC instancebufferDesc;
  ZeroMemory(&instancebufferDesc, sizeof(instancebufferDesc));
  instancebufferDesc.Usage = D3D11_USAGE_DEFAULT;
  instancebufferDesc.ByteWidth = sizeof(OurInstances);
  instancebufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
  instancebufferDesc.CPUAccessFlags = 0;
  instancebufferDesc.MiscFlags = 0;

  D3D11_SUBRESOURCE_DATA instanceData;
  instanceData.pSysMem = &OurInstances[0];
  instanceData.SysMemPitch = 0;
  instanceData.SysMemSlicePitch = 0;

  m_pDevice->CreateBuffer(&instancebufferDesc, &instanceData, &m_pInstanceBuffer);


  D3D11_BUFFER_DESC vertexBufferDesc;
  ZeroMemory(&vertexBufferDesc, sizeof(vertexBufferDesc));

  vertexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
  vertexBufferDesc.ByteWidth = sizeof(OurVertices);
  vertexBufferDesc.BindFlags        = D3D11_BIND_VERTEX_BUFFER;
  vertexBufferDesc.CPUAccessFlags   = 0;
  vertexBufferDesc.MiscFlags        = 0;


  D3D11_SUBRESOURCE_DATA InitData;
  InitData.pSysMem = &OurVertices[0];
  InitData.SysMemPitch = 0;
  InitData.SysMemSlicePitch = 0;

  HRESULT hr = S_OK;
  hr = m_pDevice->CreateBuffer(&vertexBufferDesc, &InitData, &m_pVertexBuffer);

}



