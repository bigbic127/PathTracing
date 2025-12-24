#pragma once
#include <vector>
#include <memory>
#include "actor.hpp"

class World
{
    public:
        Actor* CreateActor(const std::string& name = "Actor");
        const std::vector<std::unique_ptr<Actor>>& GetActors()const{return actors;}
        void SetCurrentCamera(Actor* camera){currentCamera = camera;}
        void SetCurrentLight(Actor* light){currentLight = light;}
        void Update();
    private:
        std::vector<std::unique_ptr<Actor>> actors;
        Actor* currentCamera;
        Actor* currentLight;
        static float deletaTime;
        float lastTime = 0.0f;
};