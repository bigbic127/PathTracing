#include "shader.hpp"
#include <QOpenGLContext>
#include <QOpenGLVersionFunctionsFactory>
#include <glm/gtc/type_ptr.hpp>
#include <fstream>
#include <sstream>
#include "folderPath.hpp"
#include "logger.hpp"

OpenGLShader::OpenGLShader(const std::string& vsPath, const std::string& fsPath)
{
    if(!InitOpenGL()) return;

    unsigned int vID, fID;
    std::string vsSource = LoadShaderSource(vsPath);
    std::string fsSource = LoadShaderSource(fsPath);
    const char* vsCode = vsSource.c_str();
    const char* fsCode = fsSource.c_str();
    vID = gl->glCreateShader(GL_VERTEX_SHADER);
    gl->glShaderSource(vID, 1, &vsCode, nullptr);
    gl->glCompileShader(vID);
    Logger::CompileShaderError(gl, vID, "VERTEX");
    fID = gl->glCreateShader(GL_FRAGMENT_SHADER);
    gl->glShaderSource(fID, 1, &fsCode, nullptr);
    gl->glCompileShader(fID);
    Logger::CompileShaderError(gl, fID, "FRAGMENT");
    programID = gl->glCreateProgram();
    gl->glAttachShader(programID, vID);
    gl->glAttachShader(programID, fID);
    gl->glLinkProgram(programID);
    Logger::CompileShaderError(gl, programID, "PROGRAM");
    gl->glDeleteShader(vID);
    gl->glDeleteShader(fID);
}

OpenGLShader::OpenGLShader(const std::string& csPath)
{
    unsigned cID;
}

bool OpenGLShader::InitOpenGL()
{
    auto* context = QOpenGLContext::currentContext();
    if(!context) return false;
    gl = QOpenGLVersionFunctionsFactory::get<QOpenGLFunctions_4_3_Core>(context);
    return true;
}

const std::string OpenGLShader::LoadShaderSource(const std::string& path)
{
    std::string p = path;
    std::string root = GetExecutableDir();
    p = root+path;
    std::ifstream file(p);
    if(!file.is_open())
        std::cerr << "Failed to open shader file: "<< path << std::endl;
    std::stringstream buffer;
    buffer << file.rdbuf();
    file.close();
    return buffer.str();
    
}

OpenGLShader::~OpenGLShader()
{
    gl->glDeleteProgram(programID);
}

void OpenGLShader::UseProgram()
{
    gl->glUseProgram(programID);
}

void OpenGLShader::EndProgram()
{
    gl->glUseProgram(0);
}

GLint OpenGLShader::GetLocation(const std::string& name) const
{
    return gl->glGetUniformLocation(programID, name.c_str());
}

void OpenGLShader::SetBool(const std::string& name, bool value) const
{
    gl->glUniform1i(GetLocation(name), value);
}

void OpenGLShader::SetFloat(const std::string& name, float value) const
{
    gl->glUniform1f(GetLocation(name), value);
}

void OpenGLShader::SetInt(const std::string& name, int value) const
{
    gl->glUniform1i(GetLocation(name), value);
}

void OpenGLShader::SetDouble(const std::string& name, int value) const
{
    gl->glUniform1d(GetLocation(name), value);
}

void OpenGLShader::SetVector2(const std::string& name, const glm::vec2& value) const
{
    gl->glUniform2fv(GetLocation(name), 1, glm::value_ptr(value));
}

void OpenGLShader::SetVector3(const std::string& name, const glm::vec3& value) const
{
    gl->glUniform3fv(GetLocation(name), 1, glm::value_ptr(value));
}

void OpenGLShader::SetVector4(const std::string& name, const glm::vec4& value) const
{
    gl->glUniform4fv(GetLocation(name), 1, glm::value_ptr(value));
}

void OpenGLShader::SetMatrix4(const std::string& name, const glm::mat4& value) const
{
    gl->glUniformMatrix4fv(GetLocation(name), 1, GL_FALSE, glm::value_ptr(value));
}