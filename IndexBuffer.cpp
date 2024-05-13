#include "IndexBuffer.h"

IndexBuffer::IndexBuffer(Graphics& gfx, const std::vector<unsigned short>& indices)
	: count ( (UINT)indices.size())
{
    //Creating Index Buffer
    D3D11_BUFFER_DESC ibd = {};
    ibd.BindFlags = D3D11_BIND_INDEX_BUFFER;
    ibd.Usage = D3D11_USAGE_DEFAULT;
    ibd.CPUAccessFlags = 0u;
    ibd.MiscFlags = 0u;
    ibd.ByteWidth = sizeof(indices);
    ibd.StructureByteStride = sizeof(unsigned short);

    D3D11_SUBRESOURCE_DATA isd = {};
    isd.pSysMem = &indices;
    GetDevice(gfx)->CreateBuffer(&ibd, &isd, &pIndexBuffer);
}

void IndexBuffer::Bind(Graphics& gfx) noexcept
{
    //Binding Index Buffer into Gfx device
    GetContext(gfx)->IASetIndexBuffer(pIndexBuffer.Get(), DXGI_FORMAT_R16_UINT, 0u);
}

UINT IndexBuffer::GetCount() const noexcept
{
    return count;
}
