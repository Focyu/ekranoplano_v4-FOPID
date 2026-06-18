cmake_minimum_required(VERSION 3.5)
project(fopid_control_v4)
set(CMAKE_VERBOSE_MAKEFILE ON)
# Set CMAKE_BUILD_TYPE
set(CMAKE_BUILD_TYPE Debug)
set(MW_TOP_LEVEL_PROJECT_NAME ${PROJECT_NAME})
# Default to C99
if(NOT CMAKE_C_STANDARD)
  set(CMAKE_C_STANDARD 99)
endif()
# Default to C++17
if(NOT CMAKE_CXX_STANDARD)
  set(CMAKE_CXX_STANDARD 17)
endif()
if(ALIAS_ROS2_TF2)
  add_definitions(-Dtf2=ros2_tf2)
  add_definitions(-Dtf2_ros=ros2_tf2_ros)
  add_definitions(-Dmessage_filters=ros2_message_filters)
endif()
# Check the ROS 2 distribution and define a macro
if("$ENV{ROS_DISTRO}" STREQUAL "humble")
    message(STATUS "Building for ROS 2 Humble")
    add_definitions(-DROS2_DISTRO_HUMBLE)
elseif("$ENV{ROS_DISTRO}" STREQUAL "jazzy")
    message(STATUS "Building for ROS 2 Jazzy")
    add_definitions(-DROS2_DISTRO_JAZZY)
else()
    message(WARNING "ROS 2 distribution $ENV{ROS_DISTRO} is not recommended for this MATLAB version. Use 'ROS 2 Jazzy' for this MATLAB version.")
    message(WARNING "Building for ROS 2 Jazzy")
    add_definitions(-DROS2_DISTRO_JAZZY)
endif()
# find dependencies
find_package(ament_cmake REQUIRED)
find_package(ament_cmake_ros REQUIRED)
find_package( gazebo_msgs REQUIRED)
find_package( geometry_msgs REQUIRED)
find_package( nav_msgs REQUIRED)
find_package( rclcpp REQUIRED)
find_package( rosgraph_msgs REQUIRED)
find_package( sensor_msgs REQUIRED)
find_package( std_msgs REQUIRED)
# Add package include directories
include_directories("${CMAKE_CURRENT_SOURCE_DIR}/include/fopid_control_v4")
set (CMAKE_SKIP_BUILD_RPATH false)
set (CMAKE_BUILD_WITH_INSTALL_RPATH true)
set (CMAKE_INSTALL_RPATH "${CMAKE_INSTALL_PREFIX}/lib")
set (CMAKE_INSTALL_RPATH_USE_LINK_PATH TRUE)
# Node
add_executable(FOpid_control_V4 
src/FOpid_control_V4.cpp
src/FOpid_control_V4_data.cpp
src/main.cpp
src/ros2nodeinterface.cpp
src/rtGetInf.cpp
src/rtGetNaN.cpp
src/rt_nonfinite.cpp
src/slros2_initialize.cpp
src/slros2_multi_threaded_executor.cpp
)
if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
target_compile_options(FOpid_control_V4 PUBLIC 
  $<$<OR:$<COMPILE_LANGUAGE:CXX>,$<COMPILE_LANGUAGE:C>>:
  -Wall -Wextra -Wpedantic
  >)
endif()
target_compile_options(FOpid_control_V4 PRIVATE
  $<$<OR:$<COMPILE_LANGUAGE:CXX>,$<COMPILE_LANGUAGE:C>>:
  -DMODEL=FOpid_control_V4
  -DNUMST=2
  -DNCSTATES=32
  -DHAVESTDIO
  -DMODEL_HAS_DYNAMICALLY_LOADED_SFCNS=0
  -DCLASSIC_INTERFACE=0
  -DALLOCATIONFCN=0
  -DTID01EQ=1
  -DONESTEPFCN=1
  -DTERMFCN=1
  -DMULTI_INSTANCE_CODE=1
  -DINTEGER_CODE=0
  -DMT=0
  -DROS2_PROJECT
  -DSTACK_SIZE=64
  -D__MW_TARGET_USE_HARDWARE_RESOURCES_H__
  -DRT
  -DMW_SOCKETCAN_NUM_INTERFACES=1
  -DMW_SOCKETCAN_IF_NAME0=can0
  -DMW_SOCKETCAN_IF_REAL0=1
  -DMW_SOCKETCAN_IF_SPEED0=500000
  -DMW_SOCKETCAN_IF_QUEUE0=65536
  -DMW_SOCKETCAN_IF_NAME1=can1
  -DMW_SOCKETCAN_IF_REAL1=1
  -DMW_SOCKETCAN_IF_SPEED1=500000
  -DMW_SOCKETCAN_IF_QUEUE1=65536
  -DMW_SOCKETCAN_IF_NAME2=can2
  -DMW_SOCKETCAN_IF_REAL2=1
  -DMW_SOCKETCAN_IF_SPEED2=500000
  -DMW_SOCKETCAN_IF_QUEUE2=65536
  -DMW_SOCKETCAN_IF_NAME3=can3
  -DMW_SOCKETCAN_IF_REAL3=1
  -DMW_SOCKETCAN_IF_SPEED3=500000
  -DMW_SOCKETCAN_IF_QUEUE3=65536
  -DMW_SOCKETCAN_IF_NAME4=can4
  -DMW_SOCKETCAN_IF_REAL4=1
  -DMW_SOCKETCAN_IF_SPEED4=500000
  -DMW_SOCKETCAN_IF_QUEUE4=65536
  -DMW_CAN_ALLOWALLMSGS=1
  -fpermissive  >
  )
ament_target_dependencies(
  FOpid_control_V4
  "gazebo_msgs"
  "geometry_msgs"
  "nav_msgs"
  "rclcpp"
  "rosgraph_msgs"
  "sensor_msgs"
  "std_msgs"
)
target_include_directories(FOpid_control_V4 PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  $<INSTALL_INTERFACE:include>)
target_link_libraries(FOpid_control_V4 
    "/usr/local/MATLAB/R2026a/sys/os/glnxa64/orig/libstdc++.so.6"
	${CMAKE_DL_LIBS}
    )
install(TARGETS FOpid_control_V4
  EXPORT export_${PROJECT_NAME}
  DESTINATION lib/${PROJECT_NAME})
ament_export_include_directories(
  include
)
foreach(file_i ${CUDA_BINS})
add_custom_command(
                   TARGET FOpid_control_V4
                   POST_BUILD
                   COMMAND ${CMAKE_COMMAND}
                   ARGS -E copy ${PROJECT_SOURCE_DIR}/src/${file_i} ${CMAKE_INSTALL_PREFIX}/FOpid_control_V4_ert_rtw/${file_i}
				   )
add_custom_command(
                   TARGET FOpid_control_V4
                   POST_BUILD
                   COMMAND ${CMAKE_COMMAND}
                   ARGS -E copy ${PROJECT_SOURCE_DIR}/src/${file_i} ${CMAKE_INSTALL_PREFIX}/codegen/exe/FOpid_control_V4/${file_i}
				   )				   
endforeach(file_i)
ament_package()
# Generated on Thu Jun 18 08:14:32 2026
