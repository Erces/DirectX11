#include "VertexShader.h"
#include "GraphicsThrowMacros.h"
VertexShader::VertexShader(Graphics& gfx, const std::wstring& path)
{
	INFOMAN(gfx);
	
	GFX_THROW_INFO(D3DReadFileToBlob(L"VertexShader.cso", &pBytecodeBlob));
	GFX_THROW_INFO(GetDevice(gfx)->CreateVertexShader(pBytecodeBlob->GetBufferPointer(), pBytecodeBlob->GetBufferSize(), nullptr, &pVertexShader));
}

void VertexShader::Bind(Graphics& gfx) noexcept
{
	
	GetContext(gfx)->VSSetShader(pVertexShader.Get(), 0, 0);
}

ID3DBlob* VertexShader::GetByteCode() const noexcept
{
	return pBytecodeBlob.Get();
}


