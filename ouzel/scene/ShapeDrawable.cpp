// Copyright (C) 2016 Elviss Strazdins
// This file is part of the Ouzel engine.

#include "ShapeDrawable.h"
#include "core/CompileConfig.h"
#include "core/Engine.h"
#include "graphics/Renderer.h"
#include "graphics/MeshBuffer.h"
#include "graphics/IndexBuffer.h"
#include "graphics/VertexBuffer.h"
#include "core/Cache.h"
#include "Layer.h"
#include "Camera.h"
#include "math/MathUtils.h"
#include "utils/Utils.h"

namespace ouzel
{
    namespace scene
    {
        ShapeDrawable::ShapeDrawable()
        {
            shader = sharedEngine->getCache()->getShader(graphics::SHADER_COLOR);
            blendState = sharedEngine->getCache()->getBlendState(graphics::BLEND_ALPHA);

            indexBuffer = sharedEngine->getRenderer()->createIndexBuffer();
            indexBuffer->init();
            indexBuffer->setIndexSize(sizeof(uint16_t));

            vertexBuffer = sharedEngine->getRenderer()->createVertexBuffer();
            vertexBuffer->init();
            vertexBuffer->setVertexAttributes(ouzel::graphics::VertexPC::ATTRIBUTES);

            meshBuffer = sharedEngine->getRenderer()->createMeshBuffer();
            meshBuffer->init(indexBuffer, vertexBuffer);
        }

        void ShapeDrawable::draw(const Matrix4& transformMatrix,
                                 const Color& drawColor,
                                 scene::Camera* camera)
        {
            Component::draw(transformMatrix, drawColor, camera);

            if (dirty)
            {
                indexBuffer->setData(indices.data(), static_cast<uint32_t>(indices.size()));
                vertexBuffer->setData(vertices.data(), static_cast<uint32_t>(vertices.size()));
                dirty = false;
            }

            Matrix4 modelViewProj = camera->getRenderViewProjection() * transformMatrix;
            float colorVector[] = {drawColor.normR(), drawColor.normG(), drawColor.normB(), drawColor.normA()};

            for (const DrawCommand& drawCommand : drawCommands)
            {
                std::vector<std::vector<float>> pixelShaderConstants(1);
                pixelShaderConstants[0] = {std::begin(colorVector), std::end(colorVector)};

                std::vector<std::vector<float>> vertexShaderConstants(1);
                vertexShaderConstants[0] = {std::begin(modelViewProj.m), std::end(modelViewProj.m)};

                sharedEngine->getRenderer()->addDrawCommand(std::vector<graphics::TexturePtr>(),
                                                            shader,
                                                            pixelShaderConstants,
                                                            vertexShaderConstants,
                                                            blendState,
                                                            meshBuffer,
                                                            drawCommand.indexCount,
                                                            drawCommand.mode,
                                                            drawCommand.startIndex,
                                                            camera->getRenderTarget(),
                                                            camera->getRenderViewport(),
                                                            camera->getDepthWrite(),
                                                            camera->getDepthTest());
            }
        }

        void ShapeDrawable::drawWireframe(const Matrix4& transformMatrix,
                                          const Color& drawColor,
                                          scene::Camera* camera)
        {
            Component::drawWireframe(transformMatrix, drawColor, camera);

            if (dirty)
            {
                indexBuffer->setData(indices.data(), static_cast<uint32_t>(indices.size()));
                vertexBuffer->setData(vertices.data(), static_cast<uint32_t>(vertices.size()));
                dirty = false;
            }

            Matrix4 modelViewProj = camera->getRenderViewProjection() * transformMatrix;
            float colorVector[] = {drawColor.normR(), drawColor.normG(), drawColor.normB(), drawColor.normA()};

            for (const DrawCommand& drawCommand : drawCommands)
            {
                std::vector<std::vector<float>> pixelShaderConstants(1);
                pixelShaderConstants[0] = {std::begin(colorVector), std::end(colorVector)};

                std::vector<std::vector<float>> vertexShaderConstants(1);
                vertexShaderConstants[0] = {std::begin(modelViewProj.m), std::end(modelViewProj.m)};

                sharedEngine->getRenderer()->addDrawCommand(std::vector<graphics::TexturePtr>(),
                                                            shader,
                                                            pixelShaderConstants,
                                                            vertexShaderConstants,
                                                            blendState,
                                                            meshBuffer,
                                                            drawCommand.indexCount,
                                                            drawCommand.mode,
                                                            drawCommand.startIndex,
                                                            camera->getRenderTarget(),
                                                            camera->getRenderViewport(),
                                                            camera->getDepthWrite(),
                                                            camera->getDepthTest(),
                                                            true);
            }
        }

        void ShapeDrawable::clear()
        {
            boundingBox = AABB2();

            drawCommands.clear();
            indices.clear();
            vertices.clear();

            dirty = true;
        }

        void ShapeDrawable::point(const Vector2& position, const Color& color)
        {
            DrawCommand command;

            command.mode = graphics::Renderer::DrawMode::POINT_LIST;
            command.indexCount = 1;
            command.startIndex = static_cast<uint32_t>(indices.size());

            uint16_t startVertex = static_cast<uint16_t>(vertices.size());

            indices.push_back(startVertex);
            vertices.push_back(graphics::VertexPC(Vector3(position), color));

            drawCommands.push_back(command);

            boundingBox.insertPoint(position);

            dirty = true;
        }

        void ShapeDrawable::line(const Vector2& start, const Vector2& finish, const Color& color)
        {
            DrawCommand command;

            command.mode = graphics::Renderer::DrawMode::LINE_STRIP;
            command.indexCount = 2;
            command.startIndex = static_cast<uint32_t>(indices.size());

            uint16_t startVertex = static_cast<uint16_t>(vertices.size());

            indices.push_back(startVertex);
            vertices.push_back(graphics::VertexPC(Vector3(start), color));

            indices.push_back(startVertex + 1);
            vertices.push_back(graphics::VertexPC(Vector3(finish), color));

            drawCommands.push_back(command);

            boundingBox.insertPoint(start);
            boundingBox.insertPoint(finish);

            dirty = true;
        }

        void ShapeDrawable::circle(const Vector2& position, float radius, const Color& color, bool fill, uint32_t segments)
        {
            if (segments < 3)
            {
                return;
            }

            DrawCommand command;
            command.indexCount = 0;
            command.startIndex = static_cast<uint32_t>(indices.size());

            uint16_t startVertex = static_cast<uint16_t>(vertices.size());

            if (fill)
            {
                vertices.push_back(graphics::VertexPC(Vector3(position), color)); // center
            }

            for (uint32_t i = 0; i <= segments; ++i)
            {
                vertices.push_back(graphics::VertexPC(Vector3((position.v[0] + radius * cosf(i * TAU / static_cast<float>(segments))),
                                                              (position.v[1] + radius * sinf(i * TAU / static_cast<float>(segments))),
                                                              0.0f), color));
            }

            if (fill)
            {
                command.mode = graphics::Renderer::DrawMode::TRIANGLE_STRIP;

                for (uint16_t i = 0; i < segments; ++i)
                {
                    indices.push_back(startVertex + i + 1);
                    ++command.indexCount;

                    indices.push_back(startVertex); // center
                    ++command.indexCount;
                }

                indices.push_back(startVertex + 1);
                ++command.indexCount;
            }
            else
            {
                command.mode = graphics::Renderer::DrawMode::LINE_STRIP;

                for (uint16_t i = 0; i < segments; ++i)
                {
                    indices.push_back(startVertex + i);
                    ++command.indexCount;
                }

                indices.push_back(startVertex);
                ++command.indexCount;
            }

            drawCommands.push_back(command);

            boundingBox.insertPoint(Vector2(position.v[0] - radius, position.v[1] - radius));
            boundingBox.insertPoint(Vector2(position.v[0] + radius, position.v[1] + radius));

            dirty = true;
        }

        void ShapeDrawable::rectangle(const Rectangle& rectangle, const Color& color, bool fill)
        {
            DrawCommand command;
            command.startIndex = static_cast<uint32_t>(indices.size());

            uint16_t startVertex = static_cast<uint16_t>(vertices.size());

            vertices.push_back(graphics::VertexPC(Vector3(rectangle.left(), rectangle.bottom(), 0.0f), color));
            vertices.push_back(graphics::VertexPC(Vector3(rectangle.right(), rectangle.bottom(), 0.0f), color));
            vertices.push_back(graphics::VertexPC(Vector3(rectangle.left(), rectangle.top(), 0.0f), color));
            vertices.push_back(graphics::VertexPC(Vector3(rectangle.right(), rectangle.top(), 0.0f), color));

            if (fill)
            {
                command.mode = graphics::Renderer::DrawMode::TRIANGLE_LIST;
                command.indexCount = 6;

                indices.push_back(startVertex + 0);
                indices.push_back(startVertex + 1);
                indices.push_back(startVertex + 2);
                indices.push_back(startVertex + 1);
                indices.push_back(startVertex + 3);
                indices.push_back(startVertex + 2);
            }
            else
            {
                command.mode = graphics::Renderer::DrawMode::LINE_STRIP;
                command.indexCount = 5;
                indices.push_back(startVertex + 0);
                indices.push_back(startVertex + 1);
                indices.push_back(startVertex + 3);
                indices.push_back(startVertex + 2);
                indices.push_back(startVertex + 0);
            }

            drawCommands.push_back(command);

            boundingBox.insertPoint(rectangle.bottomLeft());
            boundingBox.insertPoint(rectangle.topRight());

            dirty = true;
        }

        void ShapeDrawable::triangle(const Vector2 (&positions)[3], const Color& color, bool fill)
        {
            DrawCommand command;
            command.indexCount = 3;
            command.startIndex = static_cast<uint32_t>(indices.size());

            uint16_t startVertex = static_cast<uint16_t>(vertices.size());

            for (uint16_t i = 0; i < 3; ++i)
            {
                indices.push_back(startVertex + i);
                vertices.push_back(graphics::VertexPC(positions[i], color));
                boundingBox.insertPoint(positions[i]);
            }

            if (fill)
            {
                command.mode = graphics::Renderer::DrawMode::TRIANGLE_LIST;
            }
            else
            {
                command.mode = graphics::Renderer::DrawMode::LINE_STRIP;
                indices.push_back(startVertex);
                ++command.indexCount;
            }

            drawCommands.push_back(command);

            dirty = true;
        }

        void ShapeDrawable::polygon(const std::vector<Vector2>& edges, const Color& color, bool fill)
        {
            if (edges.size() < 3) return;

            DrawCommand command;
            command.startIndex = static_cast<uint32_t>(indices.size());

            uint16_t startVertex = static_cast<uint16_t>(vertices.size());

            for (uint16_t i = 0; i < edges.size(); ++i)
            {
                vertices.push_back(graphics::VertexPC(edges[i], color));
                boundingBox.insertPoint(edges[i]);
            }

            if (fill)
            {
                command.mode = graphics::Renderer::DrawMode::TRIANGLE_LIST;
                command.indexCount = static_cast<uint32_t>(edges.size() - 2) * 3;

                for (uint16_t i = 1; i < edges.size() - 1; ++i)
                {
                    indices.push_back(startVertex);
                    indices.push_back(startVertex + i);
                    indices.push_back(startVertex + i + 1);
                }
            }
            else
            {
                command.mode = graphics::Renderer::DrawMode::LINE_STRIP;
                command.indexCount = static_cast<uint32_t>(edges.size()) + 1;

                for (uint16_t i = 0; i < edges.size(); ++i)
                {
                    indices.push_back(startVertex + i);
                }

                indices.push_back(startVertex);
            }

            drawCommands.push_back(command);
            
            dirty = true;
        }

    } // namespace scene
} // namespace ouzel
