#include "window.hpp"

#include <QMenuBar>
#include <QToolBar>
#include <QStatusBar>
#include <QVBoxLayout>
#include <QTabWidget>
#include <QSplitter>

OpenGLWidget::OpenGLWidget(QWidget* parent):QOpenGLWidget(parent)
{    
}

void OpenGLWidget::initializeGL()
{
    initializeOpenGLFunctions();
    glEnable(GL_DEPTH_TEST);
}
void OpenGLWidget::resizeGL(int w, int h)
{
    glViewport(0, 0, w, h);
}

void OpenGLWidget::paintGL()
{
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
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