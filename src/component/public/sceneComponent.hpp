#pragma once
#include "component.hpp"
#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>

struct Transform
{
    glm::vec3 position{0.0f};
    glm::vec3 rotation{0.0f};
    glm::vec3 scale{1.0f};
};

class SceneComponent:protected IComponent
{
    public:
        void SetTransform(Transform transform){this->transform = transform;}
        void SetPosition(glm::vec3 position){transform.position = position;}
        void SetRotation(glm::vec3 rotation){transform.rotation = rotation;}
        void SetScale(glm::vec3 scale){transform.scale = scale;}
        glm::mat4 GetMatrix4x4();
        void Update() override;
    protected:
        glm::quat ToQuaternion();
    private:
        Transform transform;

};
