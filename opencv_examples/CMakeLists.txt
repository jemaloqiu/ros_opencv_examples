cmake_minimum_required(VERSION 2.8.3)
project(opencv_examples)

find_package(catkin REQUIRED sensor_msgs image_geometry cv_bridge roscpp std_msgs image_transport)
find_package(PCL REQUIRED QUIET COMPONENTS common)
find_package(Boost REQUIRED COMPONENTS thread)
#find_package(Qt4 REQUIRED COMPONENTS QtCore QtGui QtOpenGL)
#include(${QT_USE_FILE})
include_directories(${CMAKE_CURRENT_BINARY_DIR})

find_package(OpenCV REQUIRED)

## Specify additional locations of header files
include_directories(include
  ${catkin_INCLUDE_DIRS}
)

catkin_package(
  INCLUDE_DIRS include
  LIBRARIES ${PROJECT_NAME}
  CATKIN_DEPENDS roscpp rospy python_qt_binding #  DEPENDS system_lib
)

#find_package(cvBlob REQUIRED)

add_executable(opencv_ros_learn_mat examples/learn_mat.cpp)
target_link_libraries(opencv_ros_learn_mat ${OpenCV_LIBS} ${ROS_LIBRARIES} ${catkin_LIBRARIES})

add_executable(opencv_ros_load_image examples/load_image.cpp)
target_link_libraries(opencv_ros_load_image ${OpenCV_LIBS} ${ROS_LIBRARIES} ${catkin_LIBRARIES})

add_executable(opencv_ros_reduce_color examples/reduce_color.cpp)
target_link_libraries(opencv_ros_reduce_color ${OpenCV_LIBS} ${ROS_LIBRARIES} ${catkin_LIBRARIES})

add_executable(opencv_ros_image_mask examples/image_mask.cpp)
target_link_libraries(opencv_ros_image_mask ${OpenCV_LIBS} ${ROS_LIBRARIES} ${catkin_LIBRARIES})

add_executable(opencv_ros_combine_images examples/combine_images.cpp)
target_link_libraries(opencv_ros_combine_images ${OpenCV_LIBS} ${ROS_LIBRARIES} ${catkin_LIBRARIES})

add_executable(opencv_ros_filter_image examples/filter_image.cpp)
target_link_libraries(opencv_ros_filter_image ${OpenCV_LIBS} ${ROS_LIBRARIES} ${catkin_LIBRARIES})

add_executable(opencv_ros_contour_sobel examples/contour_sobel.cpp)
target_link_libraries(opencv_ros_contour_sobel ${OpenCV_LIBS} ${ROS_LIBRARIES} ${catkin_LIBRARIES})

add_executable(opencv_ros_laplace_op examples/laplace_op.cpp)
target_link_libraries(opencv_ros_laplace_op ${OpenCV_LIBS} ${ROS_LIBRARIES} ${catkin_LIBRARIES})

add_executable(opencv_ros_contour_canny examples/contour_canny.cpp)
target_link_libraries(opencv_ros_contour_canny ${OpenCV_LIBS} ${ROS_LIBRARIES} ${catkin_LIBRARIES})

add_executable(opencv_ros_hough_trans examples/hough_trans.cpp)
target_link_libraries(opencv_ros_hough_trans ${OpenCV_LIBS} ${ROS_LIBRARIES} ${catkin_LIBRARIES})

add_executable(opencv_ros_histogram_cmp examples/histogram_cmp.cpp)
target_link_libraries(opencv_ros_histogram_cmp ${OpenCV_LIBS} ${ROS_LIBRARIES} ${catkin_LIBRARIES})
