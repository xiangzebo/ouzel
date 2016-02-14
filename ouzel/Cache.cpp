// Copyright (C) 2016 Elviss Strazdins
// This file is part of the Ouzel engine.

#include <rapidjson/rapidjson.h>
#include <rapidjson/filereadstream.h>
#include <rapidjson/document.h>
#include "Cache.h"
#include "Engine.h"
#include "Renderer.h"
#include "Texture.h"
#include "Shader.h"
#include "File.h"
#include "ParticleDefinition.h"
#include "Utils.h"

namespace ouzel
{
    Cache::Cache()
    {
        
    }
    
    Cache::~Cache()
    {
        
    }
    
    void Cache::preloadTexture(const std::string& filename, bool dynamic)
    {
        std::unordered_map<std::string, TexturePtr>::const_iterator i = _textures.find(filename);
        
        if (i == _textures.end())
        {
            TexturePtr texture = Engine::getInstance()->getRenderer()->loadTextureFromFile(filename, dynamic);
            
            if (texture)
            {
                _textures[filename] = texture;
            }
        }
    }
    
    TexturePtr Cache::getTexture(const std::string& filename) const
    {
        TexturePtr result;
        
        std::unordered_map<std::string, TexturePtr>::const_iterator i = _textures.find(filename);
        
        if (i != _textures.end())
        {
            return i->second;
        }
        else
        {
            result = Engine::getInstance()->getRenderer()->loadTextureFromFile(filename);
            
            if (result)
            {
                _textures[filename] = result;
            }
        }
        
        return result;
    }
    
    void Cache::setTexture(const std::string& filename, const TexturePtr& texture)
    {
        _textures[filename] = texture;
    }
    
    void Cache::releaseTextures()
    {
        _textures.clear();
    }
    
    ShaderPtr Cache::getShader(const std::string& shaderName) const
    {
        std::unordered_map<std::string, ShaderPtr>::const_iterator i = _shaders.find(shaderName);
        
        if (i != _shaders.end())
        {
            return i->second;
        }
        else
        {
            return nullptr;
        }
    }
    
    void Cache::setShader(const std::string& shaderName, const ShaderPtr& shader)
    {
        _shaders[shaderName] = shader;
    }
    
    void Cache::preloadParticleDefinition(const std::string& filename)
    {
        std::unordered_map<std::string, ParticleDefinitionPtr>::const_iterator i = _particleDefinitions.find(filename);
        
        if (i == _particleDefinitions.end())
        {
            ParticleDefinitionPtr result = loadParticleDefinition(filename);
            
            if (result)
            {
                _particleDefinitions[filename] = result;
            }
        }
    }
    
    ParticleDefinitionPtr Cache::getParticleDefinition(const std::string& filename) const
    {
        ParticleDefinitionPtr result;
        
        std::unordered_map<std::string, ParticleDefinitionPtr>::const_iterator i = _particleDefinitions.find(filename);
        
        if (i != _particleDefinitions.end())
        {
            return i->second;
        }
        else
        {
            result = loadParticleDefinition(filename);
            
            if (result)
            {
                _particleDefinitions[filename] = result;
            }
        }
        
        return result;
    }
    
    ParticleDefinitionPtr Cache::loadParticleDefinition(const std::string& filename) const
    {
        ParticleDefinitionPtr result = std::make_shared<ParticleDefinition>();
        
        File file(filename, File::Mode::READ, false);
        
        if (file)
        {
            rapidjson::FileReadStream is(file.getFile().get(), TEMP_BUFFER, sizeof(TEMP_BUFFER));
            
            rapidjson::Document document;
            document.ParseStream<0>(is);
            
            if (document.HasParseError())
            {
                return ParticleDefinitionPtr();
            }
            
            if (document.HasMember("blendFuncSource")) result->blendFuncSource = document["blendFuncSource"].GetInt();
            if (document.HasMember("blendFuncDestination")) result->blendFuncDestination = document["blendFuncDestination"].GetInt();
            
            
            if (document.HasMember("emitterType"))
            {
                uint32_t emitterType = document["emitterType"].GetInt();
                
                switch (emitterType)
                {
                    case 0: result->emitterType = ParticleDefinition::EmitterType::GRAVITY; break;
                    case 1: result->emitterType = ParticleDefinition::EmitterType::RADIUS; break;
                }
            }
            
            if (document.HasMember("maxParticles")) result->maxParticles = document["maxParticles"].GetInt();
            
            if (document.HasMember("duration")) result->duration = static_cast<float>(document["duration"].GetDouble());
            if (document.HasMember("particleLifespan")) result->particleLifespan = static_cast<float>(document["particleLifespan"].GetDouble());
            if (document.HasMember("particleLifespanVariance")) result->particleLifespanVariance = static_cast<float>(document["particleLifespanVariance"].GetDouble());
            
            if (document.HasMember("speed")) result->speed = static_cast<float>(document["speed"].GetDouble());
            if (document.HasMember("speedVariance")) result->speedVariance = static_cast<float>(document["speedVariance"].GetDouble());
            
            if (document.HasMember("absolutePosition")) result->absolutePosition = document["absolutePosition"].GetBool();
            
            if (document.HasMember("yCoordFlipped")) result->yCoordFlipped = (document["yCoordFlipped"].GetInt() == 1);
            
            if (document.HasMember("sourcePositionx")) result->sourcePosition.x = static_cast<float>(document["sourcePositionx"].GetDouble());
            if (document.HasMember("sourcePositiony")) result->sourcePosition.y = static_cast<float>(document["sourcePositiony"].GetDouble());
            if (document.HasMember("sourcePositionVariancex")) result->sourcePositionVariance.x = static_cast<float>(document["sourcePositionVariancex"].GetDouble());
            if (document.HasMember("sourcePositionVariancey")) result->sourcePositionVariance.y = static_cast<float>(document["sourcePositionVariancey"].GetDouble());
            
            if (document.HasMember("startParticleSize")) result->startParticleSize = static_cast<float>(document["startParticleSize"].GetDouble());
            if (document.HasMember("startParticleSizeVariance")) result->startParticleSizeVariance = static_cast<float>(document["startParticleSizeVariance"].GetDouble());
            if (document.HasMember("finishParticleSize")) result->finishParticleSize = static_cast<float>(document["finishParticleSize"].GetDouble());
            if (document.HasMember("finishParticleSizeVariance")) result->finishParticleSizeVariance = static_cast<float>(document["finishParticleSizeVariance"].GetDouble());
            if (document.HasMember("angle")) result->angle = static_cast<float>(document["angle"].GetDouble());
            if (document.HasMember("angleVariance")) result->angleVariance = static_cast<float>(document["angleVariance"].GetDouble());
            if (document.HasMember("rotationStart")) result->startRotation = static_cast<float>(document["rotationStart"].GetDouble());
            if (document.HasMember("rotationStartVariance")) result->startRotationVariance = static_cast<float>(document["rotationStartVariance"].GetDouble());
            if (document.HasMember("rotationEnd")) result->finishRotation = static_cast<float>(document["rotationEnd"].GetDouble());
            if (document.HasMember("rotationEndVariance")) result->finishRotationVariance = static_cast<float>(document["rotationEndVariance"].GetDouble());
            if (document.HasMember("rotatePerSecond")) result->rotatePerSecond = static_cast<float>(document["rotatePerSecond"].GetDouble());
            if (document.HasMember("rotatePerSecondVariance")) result->rotatePerSecondVariance = static_cast<float>(document["rotatePerSecondVariance"].GetDouble());
            if (document.HasMember("minRadius")) result->minRadius = static_cast<float>(document["minRadius"].GetDouble());
            if (document.HasMember("minRadiusVariance")) result->minRadiusVariance = static_cast<float>(document["minRadiusVariance"].GetDouble());
            if (document.HasMember("maxRadius")) result->maxRadius = static_cast<float>(document["maxRadius"].GetDouble());
            if (document.HasMember("maxRadiusVariance")) result->maxRadiusVariance = static_cast<float>(document["maxRadiusVariance"].GetDouble());
            
            if (document.HasMember("radialAcceleration")) result->radialAcceleration = static_cast<float>(document["radialAcceleration"].GetDouble());
            if (document.HasMember("radialAccelVariance")) result->radialAccelVariance = static_cast<float>(document["radialAccelVariance"].GetDouble());
            if (document.HasMember("tangentialAcceleration")) result->tangentialAcceleration = static_cast<float>(document["tangentialAcceleration"].GetDouble());
            if (document.HasMember("tangentialAccelVariance")) result->tangentialAccelVariance = static_cast<float>(document["tangentialAccelVariance"].GetDouble());
            
            if (document.HasMember("rotationIsDir")) result->rotationIsDir = static_cast<float>(document["rotationIsDir"].GetBool());
            
            if (document.HasMember("gravityx")) result->gravity.x = static_cast<float>(document["gravityx"].GetDouble());
            if (document.HasMember("gravityy")) result->gravity.y = static_cast<float>(document["gravityy"].GetDouble());
            
            if (document.HasMember("startColorRed")) result->startColorRed = static_cast<float>(document["startColorRed"].GetDouble());
            if (document.HasMember("startColorGreen")) result->startColorGreen = static_cast<float>(document["startColorGreen"].GetDouble());
            if (document.HasMember("startColorBlue")) result->startColorBlue = static_cast<float>(document["startColorBlue"].GetDouble());
            if (document.HasMember("startColorAlpha")) result->startColorAlpha = static_cast<float>(document["startColorAlpha"].GetDouble());
            
            if (document.HasMember("startColorVarianceRed")) result->startColorRedVariance = static_cast<float>(document["startColorVarianceRed"].GetDouble());
            if (document.HasMember("startColorVarianceGreen")) result->startColorGreenVariance = static_cast<float>(document["startColorVarianceGreen"].GetDouble());
            if (document.HasMember("startColorVarianceBlue")) result->startColorBlueVariance = static_cast<float>(document["startColorVarianceBlue"].GetDouble());
            if (document.HasMember("startColorVarianceAlpha")) result->startColorAlphaVariance = static_cast<float>(document["startColorVarianceAlpha"].GetDouble());
            
            if (document.HasMember("finishColorRed")) result->finishColorRed = static_cast<float>(document["finishColorRed"].GetDouble());
            if (document.HasMember("finishColorGreen")) result->finishColorGreen = static_cast<float>(document["finishColorGreen"].GetDouble());
            if (document.HasMember("finishColorBlue")) result->finishColorBlue = static_cast<float>(document["finishColorBlue"].GetDouble());
            if (document.HasMember("finishColorAlpha")) result->finishColorAlpha = static_cast<float>(document["finishColorAlpha"].GetDouble());
            
            if (document.HasMember("finishColorVarianceRed")) result->finishColorRedVariance = static_cast<float>(document["finishColorVarianceRed"].GetDouble());
            if (document.HasMember("finishColorVarianceGreen")) result->finishColorGreenVariance = static_cast<float>(document["finishColorVarianceGreen"].GetDouble());
            if (document.HasMember("finishColorVarianceBlue")) result->finishColorBlueVariance = static_cast<float>(document["finishColorVarianceBlue"].GetDouble());
            if (document.HasMember("finishColorVarianceAlpha")) result->finishColorAlphaVariance = static_cast<float>(document["finishColorVarianceAlpha"].GetDouble());
            
            if (document.HasMember("textureFileName")) result->textureFilename = document["textureFileName"].GetString();
        }
        else
        {
            return ParticleDefinitionPtr();
        }
        
        result->emissionRate = static_cast<float>(result->maxParticles) / result->particleLifespan;
        
        return result;
    }
}
