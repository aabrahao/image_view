#include "Ros.h"
#include <thread>
#include <signal.h>

#include "MainWindow.h"

void kill(int /*sig*/) {
    MainWindow::instance()->close();
}

Ros *Ros::s_self = nullptr;

Ros::Ros(int argc, char *argv[], const std::string &node_name) {
    // Initilize ROS
    rclcpp::init(argc, argv);
    // Create ROS executer and node
    m_executor = rclcpp::executors::StaticSingleThreadedExecutor::make_shared();
    m_node = rclcpp::Node::make_shared(node_name);
    m_executor->add_node(m_node);
    // Add ROS publisher and subscribers
    m_image = m_node->create_subscription<sensor_msgs::msg::Image>("image_raw",
                                                        rclcpp::SystemDefaultsQoS(),
                                                        std::bind(&Ros::imageCallback, this, std::placeholders::_1));
    if (s_self) {
        LOG("Ops, only one instance of 'Ros' can be created!");
        MainWindow::instance()->close();
    }
    else {
        s_self = this; 
        LOG("Ros created...");
    }
    signal(SIGINT, kill);
}

Ros::~Ros() {
    shutdown();
}

void Ros::spin(void) {
    m_executor->spin();
}

void Ros::spinOnBackground(void) {
    std::thread thread(std::bind(&rclcpp::executors::StaticSingleThreadedExecutor::spin, m_executor));
    thread.detach();
}

void Ros::shutdown(void) {
    m_executor->cancel();
    rclcpp::shutdown(); 
    LOG("ROS shutdown!");
}

void Ros::imageCallback(const sensor_msgs::msg::Image::SharedPtr msg) const { 
    LOG("Received Image: %s %dx%d", msg->encoding.c_str(), msg->width, msg->height);
    if (msg->encoding != "rgb8") {
        LOG("Image encoding not supported!");
        return;
    }
    QImage image(&msg->data[0], msg->width, msg->height, QImage::Format_RGB888);
    MainWindow::instance()->view()->update(image);
}
