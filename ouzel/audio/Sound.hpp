// Copyright (C) 2017 Elviss Strazdins
// This file is part of the Ouzel engine.

#pragma once

#include <cfloat>
#include <memory>
#include "audio/SoundInput.hpp"
#include "math/Vector3.hpp"
#include "scene/Component.hpp"
#include "core/UpdateCallback.hpp"

namespace ouzel
{
    namespace audio
    {
        class Audio;
        class SoundData;
        class Stream;

        class Sound: public SoundInput, public scene::Component
        {
            friend Audio;
        public:
            Sound();
            virtual ~Sound();

            bool init(const std::shared_ptr<SoundData>& newSoundData);

            virtual void draw(const Matrix4& transformMatrix,
                              float opacity,
                              const Matrix4& renderViewProjection,
                              const std::shared_ptr<graphics::Texture>& renderTarget,
                              const Rectangle& renderViewport,
                              bool depthWrite,
                              bool depthTest,
                              bool wireframe,
                              bool scissorTest,
                              const Rectangle& scissorRectangle) override;

            const std::shared_ptr<SoundData>& getSoundData() const { return soundData; }

            const Vector3& getPosition() const { return position; }
            void setPosition(const Vector3& newPosition);

            float getPitch() const { return pitch; }
            void setPitch(float newPitch);

            float getGain() const { return gain; }
            void setGain(float newGain);

            float getRolloffFactor() const { return rolloffFactor; }
            void setRolloffFactor(float newRolloffFactor);

            float getMinDistance() { return minDistance; }
            void setMinDistance(float newMinDistance);

            float getMaxDistance() { return maxDistance; }
            void setMaxDistance(float newMaxDistance);

            bool play(bool repeatSound = false);
            bool pause();
            bool stop();

            virtual AudioDevice::RenderCommand getRenderCommand() override;

        private:
            void update(float delta);

            static bool render(uint32_t frames,
                               uint16_t channels,
                               uint32_t sampleRate,
                               Vector3& sourcePosition,
                               float& sourceRolloffFactor,
                               float& sourceMinDistance,
                               float& sourceMaxDistance,
                               std::vector<float>& result,
                               const std::shared_ptr<SoundData>& soundData,
                               const std::shared_ptr<Stream>& stream,
                               const Vector3& position,
                               float pitch,
                               float gain,
                               float rolloffFactor,
                               float minDistance,
                               float maxDistance);

            UpdateCallback updateCallback;
            std::shared_ptr<SoundData> soundData;
            std::shared_ptr<Stream> stream;

            Vector3 position;
            float pitch = 1.0f;
            float gain = 1.0f;
            float rolloffFactor = 1.0f;
            float minDistance = 1.0f;
            float maxDistance = FLT_MAX;

            uint32_t resetCount = 0;
        };
    } // namespace audio
} // namespace ouzel
