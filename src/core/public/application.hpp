#pragma once
#include <QApplication>
#include "window.hpp"

class Application:public QApplication
{
    Q_OBJECT
    public:
        explicit Application(int argc, char* argv[]);
        Window& GetWindow(){return window;}
    private:
        Window window;
};