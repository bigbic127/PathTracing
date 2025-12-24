#include "window.hpp"
#include <iostream>
#include <QMenuBar>
#include <QToolBar>
#include <QStatusBar>
#include <QVBoxLayout>
#include <QTabWidget>
#include <QSplitter>
#include "glm/gtc/matrix_transform.hpp"
#include <memory>

OpenGLWidget::OpenGLWidget(QWidget* parent):QOpenGLWidget(parent)
{
    QSurfaceFormat format;
    format.setVersion(4, 3);
    format.setProfile(QSurfaceFormat::CoreProfile);
    format.setDepthBufferSize(24);
    format.setStencilBufferSize(8);
    setFormat(format);
}

void OpenGLWidget::initializeGL()
{
    initializeOpenGLFunctions();
    glEnable(GL_DEPTH_TEST);
    const std::string vsPath = "/Shader/vertex/standard.vs";
    const std::string fsPath = "/Shader/fragment/standard.fs";
    cube = std::make_unique<OpenGLQaudMesh>();
    shader = std::make_unique<OpenGLShader>(vsPath, fsPath);
}
void OpenGLWidget::resizeGL(int w, int h)
{
    //qreal retinaScale = devicePixelRatio();
    glViewport(0, 0, w, h);
}

void OpenGLWidget::paintGL()
{
    glClearColor(0.0f, 1.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

    shader->UseProgram();
    glm::mat4 model(1.0f);
    glm::mat4 view(1.0f);
    glm::mat4 persective(1.0f);
    view = glm::lookAt(glm::vec3(0.0f, 0.0f, -3.0f), glm::vec3(0.0f), glm::vec3(0.0f,1.0f,0.0f));
    persective = glm::perspective(45.0f, float(width())/height(), 0.01f, 100.0f);
    shader->SetMatrix4("mModel", model);
    shader->SetMatrix4("mView", view);
    shader->SetMatrix4("mProjection", persective);
    cube->Bind();
    cube->Draw();
    cube->Unbind();
    shader->EndProgram();    
}

Window::Window(QWidget* parent):QMainWindow(parent)
{
    CreateWidget();
}

void Window::CreateWidget()
{
    QMenuBar* menubar = new QMenuBar(this);
    QMenu* menu = menubar->addMenu("&File");
    setMenuBar(menubar);

    QToolBar* toolbar = new QToolBar(this);
    addToolBar(Qt::TopToolBarArea, toolbar);

    QStatusBar* statusbar = new QStatusBar(this);
    setStatusBar(statusbar);

    QSplitter* splitter = new QSplitter(Qt::Horizontal, this);
    openGLWidget = new OpenGLWidget(splitter);
    QTabWidget* tabWidget = new QTabWidget(splitter);
    splitter->addWidget(openGLWidget);
    splitter->addWidget(tabWidget);
    splitter->setSizes({1000, 280});
    setCentralWidget(splitter);

    QWidget* matWidget = new QWidget(this);
    tabWidget->addTab(matWidget, "Material Properties");

    setWindowTitle("OpenGL PathTracing Test");
    resize(width, height);
}