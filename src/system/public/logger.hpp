#pragma once
#include <QOpenGLFunctions_4_3_Core>
#include <iostream>
#include <cstring>

class Logger
{
    public:
        static void ErrorMessage(const char* message)
        {
            std::cerr << "Error: " << message << std::endl;
        }
        static void WindowErrorCallback(int error_code, const char* description)
        {
            std::cerr << "Error Code: " << error_code << ", Description: " << description << std::endl;
        }
        static void CompileShaderError(QOpenGLFunctions_4_3_Core* gl, unsigned int id, const char* type)
        {
            int success;
            char infoLog[1024];
            if(strcmp(type, "PROGRAM") != 0)
            {
                gl->glGetShaderiv(id, GL_COMPILE_STATUS, &success);
                if(!success)
                {
                    gl->glGetShaderInfoLog(id, 1024, nullptr, infoLog);
                    std::cerr << "Failed to "<< type << " shader compile.\nLog: " << infoLog << std::endl;
                }
            }else
            {
                gl->glGetProgramiv(id, GL_LINK_STATUS, &success);
                if(!success)
                {
                    gl->glGetProgramInfoLog(id, 1021, nullptr, infoLog);
                    std::cerr << "Failed to Program link.\nLog: " << infoLog << std::endl;
                }
            }
        }
};