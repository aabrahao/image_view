#include "MainWindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent) {
    resize(500, 500);
    m_view = new ImageView;
    setCentralWidget(m_view);
}

MainWindow::~MainWindow() {

}

