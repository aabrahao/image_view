cmake_minimum_required(VERSION 3.8)
project(image_view)

# Qt6 moc
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

# C++
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Compiler
add_compile_options(-Wall -Wextra -Wpedantic -Wunused-parameter)

# ROS dependencies
find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(std_msgs REQUIRED)
find_package(sensor_msgs REQUIRED)

# Qt6 dependencies
find_package(QT NAMES Qt6 REQUIRED COMPONENTS Widgets)
find_package(Qt6 REQUIRED COMPONENTS Widgets)

# Executable
add_executable(${PROJECT_NAME}
      main.cpp
      Ros.cpp
      Ros.h
      ImageView.cpp
      ImageView.h
      MainWindow.cpp
      MainWindow.h)

# ROS
ament_target_dependencies(${PROJECT_NAME}
      rclcpp 
      std_msgs 
      sensor_msgs)

# Qt6
target_link_libraries(${PROJECT_NAME} Qt6::Widgets)

install(TARGETS ${PROJECT_NAME}
      DESTINATION lib/${PROJECT_NAME})

ament_package()
