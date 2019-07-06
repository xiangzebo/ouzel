// Copyright 2015-2019 Elviss Strazdins. All rights reserved.

#ifndef OUZEL_GRAPHICS_D3D11BUFFER_HPP
#define OUZEL_GRAPHICS_D3D11BUFFER_HPP

#include "core/Setup.h"

#if OUZEL_COMPILE_DIRECT3D11

#include <d3d11.h>
#include "graphics/direct3d11/D3D11RenderResource.hpp"
#include "graphics/BufferType.hpp"

namespace ouzel
{
    namespace graphics
    {
        namespace d3d11
        {
            class RenderDevice;

            class Buffer final: public RenderResource
            {
            public:
                Buffer(RenderDevice& initRenderDevice,
                       BufferType initType,
                       uint32_t initFlags,
                       const std::vector<uint8_t>& data,
                       uint32_t initSize);
                ~Buffer();

                void setData(const std::vector<uint8_t>& data);

                inline auto getFlags() const { return flags; }
                inline auto getType() const { return type; }
                inline auto getSize() const { return size; }

                inline auto getBuffer() const { return buffer; }

            private:
                void createBuffer(UINT newSize, const std::vector<uint8_t>& data);

                BufferType type;
                uint32_t flags = 0;

                ID3D11Buffer* buffer = nullptr;
                UINT size = 0;
            };
        } // namespace d3d11
    } // namespace graphics
} // namespace ouzel

#endif

#endif // OUZEL_GRAPHICS_D3D11BUFFER_HPP
