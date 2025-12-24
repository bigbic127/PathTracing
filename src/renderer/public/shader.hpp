#pragma once
#include <glm/glm.hpp>
#include <QOpenGLFunctions_4_3_Core>
#include <string>

class IShader
{
    public:
        virtual ~IShader() = default;
        virtual void UseProgram() = 0;
        virtual void EndProgram() = 0;
};

class OpenGLShader:protected IShader
{
    public:
        OpenGLShader(const std::string& vsPath, const std::string& fsPath);
        OpenGLShader(const std::string& csPath);
        ~OpenGLShader();
        bool InitOpenGL();
        void UseProgram() override;
        void EndProgram() override;
        void SetBool(const std::string& name, bool value) const;
        void SetInt(const std::string& name, int value) const;
        void SetFloat(const std::string& name, float value) const;
        void SetDouble(const std::string& name, int value) const;
        void SetVector2(const std::string& name, const glm::vec2& value) const;
        void SetVector3(const std::string& name, const glm::vec3& value) const;
        void SetVector4(const std::string& name, const glm::vec4& value) const;
        void SetMatrix4(const std::string& name, const glm::mat4& value) const;
        GLint GetLocation(const std::string& name) const;
        unsigned int GetProgramID() const {return programID;}
    private:
        const std::string LoadShaderSource(const std::string& path); 
        unsigned int programID;
        QOpenGLFunctions_4_3_Core* gl;
};