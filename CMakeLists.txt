cmake_minimum_required(VERSION 3.16)
project(rbOP_vision)

set(CMAKE_CXX_STANDARD 17)



include_directories(SDK)
add_subdirectory(SDK)

find_package(OpenCV REQUIRED)
find_package(OpenVINO REQUIRED)


add_executable(rbOPVision rbOPVision.cpp)

target_include_directories(rbOPVision PRIVATE SDK)
# target_include_directories(rbOPVision PUBLIC ${rclcpp_INCLUDE_DIRS})
include_directories(${OpenCV_INCLUDE_DIRS})
# target_link_libraries(rbOPVision PRIVATE
#                                 SDK
#                                 ${OpenCV_LIBS}
#                                 # ${rclcpp_LIBRARIES}
#                                 )


target_link_libraries(rbOPVision PRIVATE
    SDK
    ${OpenCV_LIBS}
    ${OpenVINO_LIBS}  # 添加OpenVINO链接
)
# ament_target_dependencies(rbOPVision 
#     # SDK
#    rclcpp
#    sensor_msgs
#    cv_bridge
#    image_transport  
# )

# ament_package()