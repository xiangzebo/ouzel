// Copyright 2015-2018 Elviss Strazdins. All rights reserved.

#ifndef LOADERTTF_HPP
#define LOADERTTF_HPP

#include "assets/Loader.hpp"

namespace ouzel
{
    namespace assets
    {
        class LoaderTTF final: public Loader
        {
        public:
            static const uint32_t TYPE = Loader::FONT;

            explicit LoaderTTF(Cache& initCache);
            bool loadAsset(Bundle& bundle, const std::string& filename, const std::vector<uint8_t>& data, bool mipmaps = true) override;
        };
    } // namespace assets
} // namespace ouzel

#endif // LOADERTTF_HPP
