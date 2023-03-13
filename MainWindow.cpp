#include "MainWindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent) {
    resize(640, 480);
    m_view = new ImageView;
    setCentralWidget(m_view);
}

MainWindow::~MainWindow() {

}

