#pragma once

class IRenderer
{
    public:
        virtual ~IRenderer() = default;
        virtual void Update() = 0;
        virtual void Draw() = 0;
};


class OpenGLRenderer:protected IRenderer
{
    public:
        OpenGLRenderer();
        ~OpenGLRenderer();
};