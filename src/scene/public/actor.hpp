#pragma once
#include <memory>
#include <vector>
#include <string>
#include "component.hpp"

class Actor
{
    public:
        Actor(const std::string& name="Actor"):name(name){}
        template<typename T, typename... Args>
        T* AddComponent(Args&&... args);
        template<typename T>
        T* GetComponent();
        template<typename T>
        std::vector<T*> GetComponents();
        void Update();
        void Draw();
    private:
        std::string name;
        std::vector<std::unique_ptr<IComponent>> components;
};

template<typename T, typename... Args>
T* Actor::AddComponent(Args&&... args)
{
    auto component = std::make_unique<T>(std::forward<Args>(args)...);
    T* ptr = component.get();
    components.push_back(std::move(component));
    return ptr;
}

template<typename T>
T* Actor::GetComponent()
{
    for(auto& component:components)
    {
        if(auto casted = dynamic_cast<T*>(component.get()))
            return casted;
    }
    return nullptr;
}

template<typename T>
std::vector<T*> Actor::GetComponents()
{
    std::vector<T*> result;
    for(auto& component:components)
    {
        if(auto casted = dynamic_cast<T*>(component.get()))
            result.push_back(casted);
    }
    return result;
}
