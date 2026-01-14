#pragma once
#include <QMainWindow>
#include <QOpenGLWidget>
#include <QOpenGLFunctions_4_3_Core>
#include "standardMesh.hpp"
#include "shader.hpp"
#include <memory>

class OpenGLRenderer;

class OpenGLWidget:public QOpenGLWidget, protected QOpenGLFunctions_4_3_Core
{
    Q_OBJECT
    public:
        explicit OpenGLWidget(QWidget* parent = nullptr);
    protected:
        void initializeGL() override;
        void resizeGL(int w, int h) override;
        void paintGL() override;
    private:
        unsigned int vao;
        GLsizei indiceSize;
        std::unique_ptr<OpenGLMesh> cube;
        std::unique_ptr<OpenGLShader> shader;
};

class Window:public QMainWindow
{
    Q_OBJECT
    public:
        explicit Window(QWidget* parent = nullptr);
        void CreateWidget();
        OpenGLWidget* GetOpenGLWidget(){return openGLWidget;}
    private:
        OpenGLWidget* openGLWidget;
        OpenGLRenderer* openGLRenderer;
        int width = 1280, height = 720;
};