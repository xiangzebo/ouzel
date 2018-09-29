// Copyright 2015-2018 Elviss Strazdins. All rights reserved.

#pragma once

#include "input/InputDevice.hpp"

namespace ouzel
{
    namespace input
    {
        class InputSystemLinux;

        class MouseDeviceLinux: public InputDevice
        {
        public:
            MouseDeviceLinux(InputSystemLinux& initInputSystemLinux,
                             uint32_t initDeviceId):
                InputDevice(initDeviceId),
                inputSystemLinux(initInputSystemLinux)
            {
            }

            virtual ~MouseDeviceLinux() {}

        private:
            InputSystemLinux& inputSystemLinux;
        };
    } // namespace input
} // namespace ouzel