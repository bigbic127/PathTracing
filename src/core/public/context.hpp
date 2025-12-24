#pragma once
#include <QOpenGLFunctions_4_3_Core>

class Context
{
    public:
        static Context* GetContext(){return instance;}
    private:
        static Context* instance;
};