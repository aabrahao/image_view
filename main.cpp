#include <QApplication>
#include "MainWindow.h"
#include "Ros.h"

int main(int argc, char *argv[]) {
    QApplication application(argc, argv);
    MainWindow window;
    window.show();
    Ros ros(argc, argv, "image_view");
    ros.spinOnBackground();
    return application.exec();
}
