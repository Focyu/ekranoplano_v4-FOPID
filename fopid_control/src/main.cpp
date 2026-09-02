
//
// File main.cpp
//
// Code generated for Simulink model 'FOpid_control'.
//
// Model version                  : 13.62
// Simulink Coder version         : 26.1 (R2026a) 20-Nov-2025
// C/C++ source code generated on : Tue Sep 01 18:34:35 2026
//
#include "ros2nodeinterface.h"
#include <cstdlib>
rclcpp::Node::SharedPtr SLROSNodePtr;
namespace ros2 {
namespace matlab {
  std::shared_ptr<ros2::matlab::NodeInterface> gMatlabNodeIntr;
  std::shared_ptr<ros2::matlab::NodeInterface> getNodeInterface() {
    return gMatlabNodeIntr;
  }
  char* getEnvironmentVariable(const char* varName) {
    try{
		return getenv(varName);
    }catch(...){
        return nullptr;
    }
  }
} //namespace matlab
} //namespace ros2
int main(int argc, char* argv[]) {
#ifdef MW_DEBUG_LOG
  #ifdef ROS2_DISTRO_JAZZY //jazzy
   RCLCPP_INFO(rclcpp::get_logger("global_logger"),"This application is built for ROS 2 Jazzy");
  #elif defined(ROS2_DISTRO_HUMBLE) //humble
   RCLCPP_INFO(rclcpp::get_logger("global_logger"),"This application is built for ROS 2 Humble");
  #endif
  // This is added to debug the issues and test in BAT.
  auto val = ros2::matlab::getEnvironmentVariable("RMW_IMPLEMENTATION");
  if(val){
      RCLCPP_INFO(rclcpp::get_logger("global_logger"), "RMW_IMPLEMENTATION is set to %s",val);
  }else{
      RCLCPP_INFO(rclcpp::get_logger("global_logger"), "RMW_IMPLEMENTATION is NOT set");
  }
  val = ros2::matlab::getEnvironmentVariable("ROS_DISABLE_LOANED_MESSAGES");
  if(val){
      RCLCPP_INFO(rclcpp::get_logger("global_logger"), "ROS_DISABLE_LOANED_MESSAGES is set to %s",val);
  }else{
      RCLCPP_INFO(rclcpp::get_logger("global_logger"), "ROS_DISABLE_LOANED_MESSAGES is NOT set");
  }
#endif
    ros2::matlab::gMatlabNodeIntr = std::make_shared<ros2::matlab::NodeInterface>();
    ros2::matlab::gMatlabNodeIntr->initialize(argc, argv);
    auto ret = ros2::matlab::gMatlabNodeIntr->run();
    ros2::matlab::gMatlabNodeIntr->terminate();
    ros2::matlab::gMatlabNodeIntr.reset();
    return ret;
}
