#pragma once

class IMaterial
{
    public:
        virtual ~IMaterial() = default;
        virtual void Bind() = 0;
        virtual void Unbind() = 0;
};

class OpenGLMaterial:protected IMaterial
{
    public:
    private:
};