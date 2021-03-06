// Copyright 2015-2020 Elviss Strazdins. All rights reserved.

#ifndef OUZEL_GRAPHICS_IMAGEDATA_HPP
#define OUZEL_GRAPHICS_IMAGEDATA_HPP

#include <cstdint>
#include <vector>
#include "PixelFormat.hpp"
#include "../math/Size.hpp"

namespace ouzel::graphics
{
    class Image final
    {
    public:
        Image() = default;

        Image(PixelFormat initPixelFormat,
              const Size2U& initSize,
              const std::vector<std::uint8_t>& initData):
            pixelFormat(initPixelFormat), size(initSize), data(initData)
        {
        }

        auto getPixelFormat() const noexcept { return pixelFormat; }
        auto& getSize() const noexcept { return size; }
        auto& getData() const noexcept { return data; }

    private:
        PixelFormat pixelFormat = PixelFormat::rgba8UnsignedNorm;
        Size2U size;
        std::vector<std::uint8_t> data;
    };
}

#endif // OUZEL_GRAPHICS_IMAGEDATA_HPP
