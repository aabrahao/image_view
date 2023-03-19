#include <QApplication>
#include "MainWindow.h"
#include "Ros.h"

MainWindow *MainWindow::s_self = nullptr;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent) {
    resize(640, 480);
    m_view = new ImageView;
    setCentralWidget(m_view);
    if (s_self) {
        LOG("Ops, only one instance of 'MainWindow' can be created!");
        QApplication::quit();
    }
    else {
        s_self = this; 
        LOG("MainWindow created...");
    }
}

MainWindow::~MainWindow() {
    LOG("MainWindow destroyed!");    
}
