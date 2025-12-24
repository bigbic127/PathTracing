#pragma once
#include <glm/glm.hpp>
#include <QOpenGLFunctions_4_3_Core>
#include <vector>

struct Vertex
{
    glm::vec3 position;
    glm::vec3 normal;
    glm::vec2 texcoord;
    glm::vec3 tangent;
    glm::vec3 bitangent;
};

class IMesh
{
    public:
        virtual ~IMesh() = default;
        virtual void Bind() = 0;
        virtual void Unbind() = 0;
        virtual void Draw() = 0;
};

class OpenGLMesh:protected IMesh
{
    public:
        OpenGLMesh(const std::vector<Vertex>& vertices, const std::vector<unsigned int>& indices);
        ~OpenGLMesh();
        bool InitOpenGL();
        void Bind() override;
        void Unbind() override;
        void Draw() override;
    private:
        unsigned int VAO, VBO, EBO;
        GLsizei indiceSize;
        QOpenGLFunctions_4_3_Core* gl;
};