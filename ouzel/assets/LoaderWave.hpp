// Copyright 2015-2018 Elviss Strazdins. All rights reserved.

#ifndef LOADERWAVE_HPP
#define LOADERWAVE_HPP

#include "assets/Loader.hpp"

namespace ouzel
{
    namespace assets
    {
        class LoaderWave final: public Loader
        {
        public:
            static const uint32_t TYPE = Loader::SOUND;

            explicit LoaderWave(Cache& initCache);
            bool loadAsset(Bundle& bundle, const std::string& filename, const std::vector<uint8_t>& data, bool mipmaps = true) override;
        };
    } // namespace assets
} // namespace ouzel

#endif // LOADERWAVE_HPP
