#include <iostream>
#include "application.hpp"
#include <QGuiApplication>
#include <QSurfaceFormat>
#include <QScreen>
#include "standardMesh.hpp"
#include <memory>
#include "context.hpp"

Application::Application(int argc, char* argv[]):QApplication(argc, argv)
{
}

int main(int argc, char* argv[])
{
    Application app(argc, argv);

    Window& window = app.GetWindow();
    QList<QScreen*> screens = QGuiApplication::screens();
    if(!screens.isEmpty())
    {
        QScreen* display1 = screens[0];
        QRect geometry = display1->geometry();
        QSize size = window.size();
        QPoint pos = geometry.center() - QPoint(size.width()/2, size.height()/2);
        window.move(pos);
    }
    window.showMaximized();
    return app.exec();
}