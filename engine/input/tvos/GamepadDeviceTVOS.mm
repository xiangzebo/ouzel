// Copyright 2015-2020 Elviss Strazdins. All rights reserved.

#include "GamepadDeviceTVOS.hpp"
#include "InputSystemTVOS.hpp"

namespace ouzel::input::tvos
{
    GamepadDevice::GamepadDevice(InputSystem& initInputSystem,
                                 DeviceId initId,
                                 GCControllerPtr initController):
        input::GamepadDevice(initInputSystem, initId),
        controller(initController)
    {
        if (controller.extendedGamepad)
        {
            // left thumbstick
            controller.extendedGamepad.leftThumbstick.up.valueChangedHandler = ^(GCControllerButtonInput*, float value, BOOL pressed) {
                handleButtonValueChange(Gamepad::Button::leftThumbUp, pressed, value);
            };
            controller.extendedGamepad.leftThumbstick.down.valueChangedHandler = ^(GCControllerButtonInput*, float value, BOOL pressed) {
                handleButtonValueChange(Gamepad::Button::leftThumbDown, pressed, value);
            };
            controller.extendedGamepad.leftThumbstick.left.valueChangedHandler = ^(GCControllerButtonInput*, float value, BOOL pressed) {
                handleButtonValueChange(Gamepad::Button::leftThumbLeft, pressed, value);
            };
            controller.extendedGamepad.leftThumbstick.right.valueChangedHandler = ^(GCControllerButtonInput*, float value, BOOL pressed) {
                handleButtonValueChange(Gamepad::Button::leftThumbRight, pressed, value);
            };

            // right thumbstick
            controller.extendedGamepad.rightThumbstick.up.valueChangedHandler = ^(GCControllerButtonInput*, float value, BOOL pressed) {
                handleButtonValueChange(Gamepad::Button::rightThumbUp, pressed, value);
            };
            controller.extendedGamepad.rightThumbstick.down.valueChangedHandler = ^(GCControllerButtonInput*, float value, BOOL pressed) {
                handleButtonValueChange(Gamepad::Button::rightThumbDown, pressed, value);
            };
            controller.extendedGamepad.rightThumbstick.left.valueChangedHandler = ^(GCControllerButtonInput*, float value, BOOL pressed) {
                handleButtonValueChange(Gamepad::Button::rightThumbLeft, pressed, value);
            };
            controller.extendedGamepad.rightThumbstick.right.valueChangedHandler = ^(GCControllerButtonInput*, float value, BOOL pressed) {
                handleButtonValueChange(Gamepad::Button::rightThumbRight, pressed, value);
            };

            // D-pad
            controller.extendedGamepad.dpad.up.valueChangedHandler = ^(GCControllerButtonInput*, float value, BOOL pressed) {
                handleButtonValueChange(Gamepad::Button::dPadUp, pressed, value);
            };
            controller.extendedGamepad.dpad.down.valueChangedHandler = ^(GCControllerButtonInput*, float value, BOOL pressed) {
                handleButtonValueChange(Gamepad::Button::dPadDown, pressed, value);
            };
            controller.extendedGamepad.dpad.left.valueChangedHandler = ^(GCControllerButtonInput*, float value, BOOL pressed) {
                handleButtonValueChange(Gamepad::Button::dPadLeft, pressed, value);
            };
            controller.extendedGamepad.dpad.right.valueChangedHandler = ^(GCControllerButtonInput*, float value, BOOL pressed) {
                handleButtonValueChange(Gamepad::Button::dPadRight, pressed, value);
            };

            // buttons
            controller.extendedGamepad.buttonA.valueChangedHandler = ^(GCControllerButtonInput*, float value, BOOL pressed) {
                handleButtonValueChange(Gamepad::Button::faceBottom, pressed, value);
            };
            controller.extendedGamepad.buttonB.valueChangedHandler = ^(GCControllerButtonInput*, float value, BOOL pressed) {
                handleButtonValueChange(Gamepad::Button::faceRight, pressed, value);
            };
            controller.extendedGamepad.buttonX.valueChangedHandler = ^(GCControllerButtonInput*, float value, BOOL pressed) {
                handleButtonValueChange(Gamepad::Button::faceLeft, pressed, value);
            };
            controller.extendedGamepad.buttonY.valueChangedHandler = ^(GCControllerButtonInput*, float value, BOOL pressed) {
                handleButtonValueChange(Gamepad::Button::faceTop, pressed, value);
            };

            // triggers and shoulders
            controller.extendedGamepad.leftShoulder.valueChangedHandler = ^(GCControllerButtonInput*, float value, BOOL pressed) {
                handleButtonValueChange(Gamepad::Button::leftShoulder, pressed, value);
            };
            controller.extendedGamepad.leftTrigger.valueChangedHandler = ^(GCControllerButtonInput*, float value, BOOL pressed) {
                handleButtonValueChange(Gamepad::Button::leftTrigger, pressed, value);
            };
            controller.extendedGamepad.rightShoulder.valueChangedHandler = ^(GCControllerButtonInput*, float value, BOOL pressed) {
                handleButtonValueChange(Gamepad::Button::rightShoulder, pressed, value);
            };
            controller.extendedGamepad.rightTrigger.valueChangedHandler = ^(GCControllerButtonInput*, float value, BOOL pressed) {
                handleButtonValueChange(Gamepad::Button::rightTrigger, pressed, value);
            };

        }
        else if (controller.gamepad)
        {
            // D-pad
            controller.gamepad.dpad.up.valueChangedHandler = ^(GCControllerButtonInput*, float value, BOOL pressed) {
                handleButtonValueChange(Gamepad::Button::dPadUp, pressed, value);
            };
            controller.gamepad.dpad.down.valueChangedHandler = ^(GCControllerButtonInput*, float value, BOOL pressed) {
                handleButtonValueChange(Gamepad::Button::dPadDown, pressed, value);
            };
            controller.gamepad.dpad.left.valueChangedHandler = ^(GCControllerButtonInput*, float value, BOOL pressed) {
                handleButtonValueChange(Gamepad::Button::dPadLeft, pressed, value);
            };
            controller.gamepad.dpad.right.valueChangedHandler = ^(GCControllerButtonInput*, float value, BOOL pressed) {
                handleButtonValueChange(Gamepad::Button::dPadRight, pressed, value);
            };

            // buttons
            controller.gamepad.buttonA.valueChangedHandler = ^(GCControllerButtonInput*, float value, BOOL pressed) {
                handleButtonValueChange(Gamepad::Button::faceBottom, pressed, value);
            };
            controller.gamepad.buttonB.valueChangedHandler = ^(GCControllerButtonInput*, float value, BOOL pressed) {
                handleButtonValueChange(Gamepad::Button::faceRight, pressed, value);
            };
            controller.gamepad.buttonX.valueChangedHandler = ^(GCControllerButtonInput*, float value, BOOL pressed) {
                handleButtonValueChange(Gamepad::Button::faceLeft, pressed, value);
            };
            controller.gamepad.buttonY.valueChangedHandler = ^(GCControllerButtonInput*, float value, BOOL pressed) {
                handleButtonValueChange(Gamepad::Button::faceTop, pressed, value);
            };
        }
        else if (controller.microGamepad)
        {
            // D-pad
            controller.microGamepad.dpad.up.valueChangedHandler = ^(GCControllerButtonInput*, float value, BOOL pressed) {
                handleButtonValueChange(Gamepad::Button::dPadUp, pressed, value);
            };
            controller.microGamepad.dpad.down.valueChangedHandler = ^(GCControllerButtonInput*, float value, BOOL pressed) {
                handleButtonValueChange(Gamepad::Button::dPadDown, pressed, value);
            };
            controller.microGamepad.dpad.left.valueChangedHandler = ^(GCControllerButtonInput*, float value, BOOL pressed) {
                handleButtonValueChange(Gamepad::Button::dPadLeft, pressed, value);
            };
            controller.microGamepad.dpad.right.valueChangedHandler = ^(GCControllerButtonInput*, float value, BOOL pressed) {
                handleButtonValueChange(Gamepad::Button::dPadRight, pressed, value);
            };

            // buttons
            controller.microGamepad.buttonA.valueChangedHandler = ^(GCControllerButtonInput*, float value, BOOL pressed) {
                handleButtonValueChange(Gamepad::Button::faceBottom, pressed, value);
            };
            controller.microGamepad.buttonX.valueChangedHandler = ^(GCControllerButtonInput*, float value, BOOL pressed) {
                handleButtonValueChange(Gamepad::Button::faceLeft, pressed, value);
            };
        }

        controller.controllerPausedHandler = ^(GCController*) {
            handleButtonValueChange(Gamepad::Button::pause, true, 1.0F);
            handleButtonValueChange(Gamepad::Button::pause, false, 0.0F);
        };

        if (controller.vendorName)
            name = [controller.vendorName cStringUsingEncoding:NSASCIIStringEncoding];

        attached = (controller.isAttachedToDevice == YES);
    }

    void GamepadDevice::setAbsoluteDpadValues(bool absoluteDpadValues)
    {
        controller.microGamepad.reportsAbsoluteDpadValues = absoluteDpadValues ? YES : NO;
    }

    bool GamepadDevice::isAbsoluteDpadValues() const
    {
        return controller.microGamepad.reportsAbsoluteDpadValues == YES;
    }

    std::int32_t GamepadDevice::getPlayerIndex() const
    {
        return static_cast<std::int32_t>(controller.playerIndex);
    }

    void GamepadDevice::setPlayerIndex(std::int32_t playerIndex)
    {
        switch (playerIndex)
        {
            case 0:
                controller.playerIndex = GCControllerPlayerIndex1;
                break;
            case 1:
                controller.playerIndex = GCControllerPlayerIndex2;
                break;
            case 2:
                controller.playerIndex = GCControllerPlayerIndex3;
                break;
            case 3:
                controller.playerIndex = GCControllerPlayerIndex4;
                break;
            default:
                controller.playerIndex = GCControllerPlayerIndexUnset;
                break;
        }
    }
}
