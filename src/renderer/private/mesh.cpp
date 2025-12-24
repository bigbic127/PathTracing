#include "mesh.hpp"
#include <QOpenGLContext>
#include <QOpenGLVersionFunctionsFactory>
#include <QOpenGLFunctions_4_3_Core>

OpenGLMesh::OpenGLMesh(const std::vector<Vertex>& vertices, const std::vector<unsigned int>& indices)
{
    if(!InitOpenGL()) return;

    gl->glGenVertexArrays(1, &VAO);
    gl->glBindVertexArray(VAO);
    gl->glGenBuffers(1, &VBO);
    gl->glBindBuffer(GL_ARRAY_BUFFER, VBO);
    gl->glBufferData(GL_ARRAY_BUFFER, vertices.size()*sizeof(Vertex), vertices.data(), GL_STATIC_DRAW);
    gl->glEnableVertexAttribArray(0);//position
    gl->glEnableVertexAttribArray(1);//normal
    gl->glEnableVertexAttribArray(2);//texcoord;
    gl->glEnableVertexAttribArray(3);//tangent;
    gl->glEnableVertexAttribArray(4);//bitangent;
    gl->glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
    gl->glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, normal));
    gl->glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, texcoord));
    gl->glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, tangent));
    gl->glVertexAttribPointer(4, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, bitangent));
    gl->glGenBuffers(1, &EBO);
    gl->glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    indiceSize = GLsizei(indices.size()*sizeof(unsigned int));
    gl->glBufferData(GL_ELEMENT_ARRAY_BUFFER, indiceSize, indices.data(), GL_STATIC_DRAW);
    gl->glBindVertexArray(0);
}

OpenGLMesh::~OpenGLMesh()
{
    gl->glDeleteVertexArrays(1, &VAO);
    gl->glDeleteBuffers(1, &VBO);
    gl->glDeleteBuffers(1, &EBO);
}

bool OpenGLMesh::InitOpenGL()
{
    auto* context = QOpenGLContext::currentContext();
    if(!context) return false;
    gl = QOpenGLVersionFunctionsFactory::get<QOpenGLFunctions_4_3_Core>(context);
    return true;
}

void OpenGLMesh::Bind()
{
    gl->glBindVertexArray(VAO);
}

void OpenGLMesh::Unbind()
{
    gl->glBindVertexArray(0);
}

void OpenGLMesh::Draw()
{
    gl->glDrawElements(GL_TRIANGLES, indiceSize, GL_UNSIGNED_INT, 0);
    GLenum err = gl->glGetError();
    if (err != GL_NO_ERROR)
        qDebug() << "GL ERROR:" << err;
}