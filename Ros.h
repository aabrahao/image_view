#ifndef NODE_H
#define NODE_H

#include <QObject>
#include <memory>
#include <rclcpp/rclcpp.hpp>
#include <sensor_msgs/msg/image.hpp>

#define LOG(...) RCLCPP_INFO(rclcpp::get_logger("image_subscriber"), __VA_ARGS__)

class Ros : public QObject {
    Q_OBJECT
public:
    static Ros *instance(void) { return s_self; }
    static void quit(void) { s_self->shutdown(); }
    Ros(int argc, char *argv[], const std::string &node_name);
    ~Ros();
    // Execute ROS
    void spin(void);
    void spinOnBackground(void);
    void shutdown(void);
    // No
    rclcpp::Node::SharedPtr node(void) { return m_node; }
protected:
    void imageCallback(const sensor_msgs::msg::Image::SharedPtr msg) const;
private:
    rclcpp::executors::StaticSingleThreadedExecutor::SharedPtr m_executor;
    rclcpp::Node::SharedPtr m_node;
    // Publishers and subiscribers
    rclcpp::Subscription<sensor_msgs::msg::Image>::SharedPtr m_image;
    // Instance
    static Ros *s_self;
};

#endif // NODE_H
