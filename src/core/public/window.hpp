#pragma once
#include <QMainWindow>
#include <QOpenGLWidget>
#include <QOpenGLFunctions_4_3_Core>

class OpenGLWidget:public QOpenGLWidget, protected QOpenGLFunctions_4_3_Core
{
    Q_OBJECT
    public:
        explicit OpenGLWidget(QWidget* parent = nullptr);
    protected:
        void initializeGL() override;
        void resizeGL(int w, int h) override;
        void paintGL() override;
};

class Window:public QMainWindow
{
    Q_OBJECT
    public:
        explicit Window(QWidget* parent = nullptr);
        void CreateWidget();
    private:
        OpenGLWidget* openGLWidget;
        int width = 1280, height = 720;
};