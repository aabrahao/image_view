#ifndef NODE_H
#define NODE_H

// https://github.com/Abishalini/ROS2QtGui

#include <memory>
#include <rclcpp/rclcpp.hpp>
#include <sensor_msgs/msg/image.hpp>

#include "MainWindow.h"

class Node : public QObject {
    Q_OBJECT
public:
    Node(int argc, char *argv[], MainWindow *window);
private:
    void imageCallback(const sensor_msgs::msg::Image::SharedPtr msg) const;
    // Members
    rclcpp::Node::SharedPtr m_node;
    rclcpp::Subscription<sensor_msgs::msg::Image>::SharedPtr m_image;
    MainWindow *m_window;
};

#endif // NODE_H
