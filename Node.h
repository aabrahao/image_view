#ifndef NODE_H
#define NODE_H

// https://github.com/Abishalini/ROS2QtGui

#include <memory>
#include <rclcpp/rclcpp.hpp>
#include <sensor_msgs/msg/image.hpp>

#include "MainWindow.h"

using std::placeholders::_1;

class Node : public rclcpp::Node {
public:
    using SharedPtr = std::shared_ptr<Node>;
    using ImageMessage = sensor_msgs::msg::Image;
    using ImageSubscription = rclcpp::Subscription<ImageMessage>;
    explicit Node(MainWindow::SharedPtr window);
private:
    void imageCallback(const ImageMessage::SharedPtr msg) const;
    ImageSubscription::SharedPtr m_imageSubscription;
    // MainWindow
    MainWindow::SharedPtr m_window;
};

#endif // NODE_H
