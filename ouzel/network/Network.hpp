// Copyright (C) 2017 Elviss Strazdins
// This file is part of the Ouzel engine.

#pragma once

#include <cstdint>
#include <string>

namespace ouzel
{
    namespace network
    {
        class Network
        {
        public:
            Network();
            ~Network();

            bool init();

            bool connect(const std::string& address, uint16_t port);
            bool disconnect();
        };
    } // namespace network
} // namespace ouzel
