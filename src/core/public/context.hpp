#pragma once

class Context
{
    public:
        static Context* GetContext(){return instance;}
    private:
        static Context* instance;
};