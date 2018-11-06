// Copyright 2015-2018 Elviss Strazdins. All rights reserved.

#ifndef FONT_HPP
#define FONT_HPP

#include <cstdint>
#include <string>
#include <map>
#include <memory>
#include <unordered_map>
#include <vector>
#include "math/Color.hpp"
#include "graphics/Texture.hpp"
#include "graphics/Vertex.hpp"

namespace ouzel
{
    class Font
    {
    public:
        Font() = default;
        virtual ~Font();

        Font(const Font&) = delete;
        Font& operator=(const Font&) = delete;

        Font(Font&&) = delete;
        Font& operator=(Font&&) = delete;

        virtual void getVertices(const std::string& text,
                                 Color color,
                                 float fontSize,
                                 const Vector2& anchor,
                                 std::vector<uint16_t>& indices,
                                 std::vector<graphics::Vertex>& vertices,
                                 std::shared_ptr<graphics::Texture>& texture) = 0;
    };
}

#endif // FONT_HPP
