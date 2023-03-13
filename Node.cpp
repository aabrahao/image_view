#include "Node.h"
#include <thread>

#define LOG(...) RCLCPP_INFO(rclcpp::get_logger("image_subscriber"), __VA_ARGS__)

Node::Node(int argc, char *argv[], MainWindow *window) 
: m_window(window) {
    // Initilize ROS
    rclcpp::init(argc, argv);
    // Create ROS executer and node
    auto executor = rclcpp::executors::StaticSingleThreadedExecutor::make_shared();
    m_node = rclcpp::Node::make_shared("image_view"); 
    executor->add_node(m_node);
    // Add ROS publisher and subscribers
    m_image = m_node->create_subscription<sensor_msgs::msg::Image>("image_raw",
                                                        rclcpp::SystemDefaultsQoS(),
                                                        std::bind(&Node::imageCallback, this, std::placeholders::_1));
    // Spin ROS
    std::thread thread(std::bind(&rclcpp::executors::StaticSingleThreadedExecutor::spin, executor));
    thread.detach();
}

void Node::imageCallback(const sensor_msgs::msg::Image::SharedPtr msg) const { 
    LOG("Received Image: %s %dx%d", msg->encoding.c_str(), msg->width, msg->height);
    if (msg->encoding != "rgb8") {
        LOG("Image encoding not supported!");
        return;
    }
    QImage image(&msg->data[0], msg->width, msg->height, QImage::Format_RGB888);
    m_window->view()->update(image);
}
