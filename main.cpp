#include <QApplication>
#include "MainWindow.h"
#include "Node.h"

int main(int argc, char *argv[]) {
    QApplication application(argc, argv);
    MainWindow window;
    window.show();
    Node node(argc, argv, &window);
    return application.exec();
}
