#include "Graphics.h"
#include <d3dcompiler.h>
#include <xutility>
#include <cmath>
namespace wrl = Microsoft::WRL;
#pragma comment(lib,"d3d11.lib")
#pragma comment(lib,"D3DCompiler.lib")
Graphics::Graphics(HWND hWnd)
{
	DXGI_SWAP_CHAIN_DESC sd = {};
	sd.BufferDesc.Width = 0;
	sd.BufferDesc.Height = 0;
	//RGBA
	sd.BufferDesc.Format = DXGI_FORMAT_B8G8R8A8_UNORM;
	//Refresh Rate
	sd.BufferDesc.RefreshRate.Numerator = 0;
	sd.BufferDesc.RefreshRate.Denominator = 0;
	//Scaling
	sd.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
	sd.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;

	//Antialising
	sd.SampleDesc.Count = 1;
	sd.SampleDesc.Quality = 0;
	//Render pipeline
	sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	sd.BufferCount = 1;
	sd.OutputWindow = hWnd;
	sd.Windowed = TRUE;
	sd.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
	sd.Flags = 0;


	D3D11CreateDeviceAndSwapChain
	(
		nullptr,
		D3D_DRIVER_TYPE_HARDWARE,
		nullptr,
		0,
		nullptr,
		0,
		D3D11_SDK_VERSION,
		&sd,
		&pSwap,
		&pDevice,
		nullptr,
		&pContext
	);
	
	wrl::ComPtr<ID3D11Resource> pBackBuffer;
	//ID3D11Resource* pBackBuffer = nullptr;;
	pSwap->GetBuffer(0, __uuidof(ID3D11Resource),&pBackBuffer);
	pDevice->CreateRenderTargetView(
		pBackBuffer.Get(),
		nullptr,
		&pTarget
	);
	pBackBuffer->Release();
}



void Graphics::EndFrame()
{
	pSwap->Present(1u, 0u);
}

void Graphics::ClearBuffer(float red, float green, float blue) noexcept
{
	const float color[] = { red,green,blue,1.0f };
	pContext->ClearRenderTargetView(pTarget.Get(), color);
}

void Graphics::DrawTestTriangle(float angle)
{
    namespace wrl = Microsoft::WRL;
    struct Vertex
    {
        struct
        {
            float x;
            float y;
        } pos;
        struct
        {
            unsigned char r;
            unsigned char g;
            unsigned char b;
            unsigned char a;
        } color;
       
    };
    const Vertex vertices[] =
    {
        {0.0f,0.5f,255,0,0,0},
        {0.5f,-0.5f,0,255,0,0},
        {-0.5f,-0.5f,0,0,255,0},
        {-0.3f,0.3f,0,0,255,0},
        {0.3f,0.3f,0,0,255,0},
        {0.0f,-0.8f,0,0,255,0},
    };
     
    //[!][!][!][!][!][!][!][!][!][!][!][!]**VERTEX BUFFER**[!][!][!][!][!][!][!][!][!][!][!][!]
    wrl::ComPtr<ID3D11Buffer> pVertexBuffer;
    D3D11_BUFFER_DESC bd = {};
    bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
    bd.Usage = D3D11_USAGE_DEFAULT;
    bd.CPUAccessFlags = 0u;
    bd.MiscFlags = 0u;
    bd.ByteWidth = sizeof(vertices);
    bd.StructureByteStride = sizeof(Vertex);

    D3D11_SUBRESOURCE_DATA sd = {};
    sd.pSysMem = &vertices;

    //vertex buffer
    pDevice->CreateBuffer(&bd, &sd, &pVertexBuffer);
    const UINT stride = sizeof(Vertex);
    const UINT offset = 0u;
    pContext->IASetVertexBuffers(0u, 1u, pVertexBuffer.GetAddressOf(), &stride, &offset);
    //[!][!][!][!][!][!][!][!][!][!][!][!]**VERTEX BUFFER END**[!][!][!][!][!][!][!][!][!][!][!][!]




    //[!][!][!][!][!][!][!][!][!][!][!][!]**INDEX BUFFER**[!][!][!][!][!][!][!][!][!][!][!][!]
    const unsigned short indices[] =
    {
        0,1,2,
        0,2,3,
        0,4,1,
        2,1,5
    };
    wrl::ComPtr<ID3D11Buffer> pIndexBuffer;
    D3D11_BUFFER_DESC ibd = {};
    ibd.BindFlags = D3D11_BIND_INDEX_BUFFER;
    ibd.Usage = D3D11_USAGE_DEFAULT;
    ibd.CPUAccessFlags = 0u;
    ibd.MiscFlags = 0u;
    ibd.ByteWidth = sizeof(indices);
    ibd.StructureByteStride = sizeof(unsigned short);

    D3D11_SUBRESOURCE_DATA isd = {};
    isd.pSysMem = &indices;
    pDevice->CreateBuffer(&ibd, &isd, &pIndexBuffer);

    //bind index buffer
    pContext->IASetIndexBuffer(pIndexBuffer.Get(), DXGI_FORMAT_R16_UINT, 0u);
    //[!][!][!][!][!][!][!][!][!][!][!][!]**INDEX BUFFER END**[!][!][!][!][!][!][!][!][!][!][!][!]


    //[!][!][!][!][!][!][!][!][!][!][!][!]**CONSTANT BUFFER**[!][!][!][!][!][!][!][!][!][!][!][!]
    struct ConstantBuffer
    {
        struct
        {
            float element[4][4];
        }transformation;
    };
    const ConstantBuffer cb =
    {
        {
            (3.0f / 4.0f) * std::cos(angle), std::sin(angle), 0.0f,   0.0f,
            (3.0f / 4.0f) * -std::sin(angle),std::cos(angle), 0.0f,   0.0f,
            0.0f,            0.0f,            1.0f,   0.0f,
            0.0f,            0.0f,            0.0f,   1.0f,
        }   
    };
    wrl::ComPtr<ID3D11Buffer> pConstantBuffer;
    D3D11_BUFFER_DESC cbd = {};
    cbd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
    cbd.Usage = D3D11_USAGE_DYNAMIC;
    cbd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
    cbd.MiscFlags = 0u;
    cbd.ByteWidth = sizeof(cb);
    cbd.StructureByteStride = 0u;
    D3D11_SUBRESOURCE_DATA csd = {};
    csd.pSysMem = &cb;
    pDevice->CreateBuffer(&cbd, &csd, &pConstantBuffer);
    pContext->VSSetConstantBuffers(0u, 1u, pConstantBuffer.GetAddressOf());
    //[!][!][!][!][!][!][!][!][!][!][!][!]**CONSTANT BUFFER END**[!][!][!][!][!][!][!][!][!][!][!][!]

    //pixel shader
    wrl::ComPtr<ID3D11PixelShader> pPixelShader;
    wrl::ComPtr<ID3DBlob> pPixelShaderBlob;
    D3DReadFileToBlob(L"PixelShader.cso", &pPixelShaderBlob);
    pDevice->CreatePixelShader(pPixelShaderBlob->GetBufferPointer(), pPixelShaderBlob->GetBufferSize(), nullptr, &pPixelShader);
    //binding pixel shader
    pContext->PSSetShader(pPixelShader.Get(), nullptr, 0u);


    //vertex shader
    wrl::ComPtr<ID3D11VertexShader> pVertexShader;
    wrl::ComPtr<ID3DBlob> pVertexShaderBlob;
    D3DReadFileToBlob(L"VertexShader.cso", &pVertexShaderBlob);
    pDevice->CreateVertexShader(pVertexShaderBlob->GetBufferPointer(), pVertexShaderBlob->GetBufferSize(), nullptr, &pVertexShader);
    //binding vertex shader
    pContext->VSSetShader(pVertexShader.Get(), 0, 0);


    //creating input layout
    wrl::ComPtr<ID3D11InputLayout> pInputLayout;
    const D3D11_INPUT_ELEMENT_DESC ied[] =
    {
        {"POSITION",0,DXGI_FORMAT_R32G32_FLOAT,0,0,D3D11_INPUT_PER_VERTEX_DATA,0},
        {"COLOR",0,DXGI_FORMAT_R8G8B8A8_UNORM,0,8u,D3D11_INPUT_PER_VERTEX_DATA,0},

    };
    pDevice->CreateInputLayout(
        ied, (UINT)std::size(ied),
        pVertexShaderBlob->GetBufferPointer(),
        pVertexShaderBlob->GetBufferSize(),
        &pInputLayout
    );

    //binding input layout
    pContext->IASetInputLayout(pInputLayout.Get());

    //render target
    pContext->OMSetRenderTargets(1u, pTarget.GetAddressOf(), nullptr);

    pContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY::D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

    //viewport
    D3D11_VIEWPORT vp;
    vp.Width = 800;
    vp.Height = 600;
    vp.MinDepth = 0;
    vp.MaxDepth = 1;
    vp.TopLeftX = 0;
    vp.TopLeftY = 0;
    pContext->RSSetViewports(1u, &vp);

    //drawing
    pContext->DrawIndexed((UINT)std::size(indices),0u, 0u);
}
