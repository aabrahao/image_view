#include <QApplication>
#include "MainWindow.h"
#include "Node.h"

int main(int argc, char *argv[]) {
    // Qt
    QApplication application(argc, argv);
    auto window = std::make_shared<MainWindow>();
    application.processEvents();
    window->show();
    // Ros
    rclcpp::init(argc, argv);
    auto node = std::make_shared<Node>(window);    
    rclcpp::executors::MultiThreadedExecutor executer;
    executer.add_node(node);
    // Qt and ROS Spin...
    while (rclcpp::ok()) {
        application.processEvents();
        executer.spin_some();
    }
    // ROS Shutdown
    executer.remove_node(node);
    rclcpp::shutdown();
    return 0;
}
