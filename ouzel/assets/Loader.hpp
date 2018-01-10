// Copyright (C) 2017 Elviss Strazdins
// This file is part of the Ouzel engine.

#pragma once

#include <string>
#include <vector>
#include "utils/Noncopyable.hpp"

namespace ouzel
{
    namespace assets
    {
        class Cache;

        class Loader: public Noncopyable
        {
            friend Cache;
        public:
            enum Type
            {
                NONE,
                BMF,
                COLLADA,
                IMAGE,
                MTL,
                OBJ,
                PARTICLE_SYSTEM,
                SPRITE,
                TTF,
                VORBIS,
                WAVE
            };

            Loader(uint32_t initType, const std::vector<std::string>& initExtensions);
            virtual ~Loader();

            inline uint32_t getType() const { return type; }

            virtual bool loadAsset(const std::string& filename, const std::vector<uint8_t>& data, bool mipmaps = true) = 0;

        protected:
            uint32_t type = Type::NONE;
            Cache* cache = nullptr;
            std::vector<std::string> extensions;
        };
    } // namespace assets
} // namespace ouzel
