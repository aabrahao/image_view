#include "Node.h"
#include "MainWindow.h"
#include <QApplication>

#define LOG(...) RCLCPP_INFO(rclcpp::get_logger("image_subscriber"), __VA_ARGS__)

Node::Node(MainWindow::SharedPtr window) : rclcpp::Node("image_view"), m_window(window) {
    m_imageSubscription = create_subscription<ImageMessage>("image_raw", 10, std::bind(&Node::imageCallback, this, _1));
}

void Node::imageCallback(const ImageMessage::SharedPtr msg) const { 
    LOG("Received Image: %s %dx%d", msg->encoding.c_str(), msg->width, msg->height);
    if (msg->encoding != "rgb8") {
        LOG("Image encoding not supported!");
        return;
    }
    QImage image(&msg->data[0], msg->width, msg->height, QImage::Format_RGB888);
    m_window->view()->update(image);
}
