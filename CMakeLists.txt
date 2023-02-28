cmake_minimum_required(VERSION 3.0.2)
project(StereoImgLoader)

add_compile_options(-std=c++14)

### Find catkin macros and libraries
find_package(catkin REQUIRED COMPONENTS
  cv_bridge
  image_transport
  roscpp
  sensor_msgs
  std_msgs
)
include_directories(${catkin_INCLUDE_DIRS})
message(STATUS "catkin include -- ${catkin_INCLUDE_DIRS}")

### OPENCV
find_package(OpenCV REQUIRED)
message(STATUS "OpenCV Version -- ${OpenCV_VERSION}")
message(STATUS "OpenCV include -- ${OpenCV_INCLUDE_DIRS}")
# message(STATUS "OpenCV libraries -- ${OpenCV_LIBS}") # Too Long to show all opencv libs
include_directories(${OpenCV_INCLUDE_DIRS})

### Eigen3
find_package(Eigen3 REQUIRED)
message(STATUS "Eigen Version -- ${EIGEN3_VERSION_STRING}")
message(STATUS "Eigen include -- ${EIGEN3_INCLUDE_DIR}")
include_directories(${EIGEN3_INCLUDE_DIR})

###########
## Build ##
###########

catkin_package()
include_directories(${catkin_INCLUDE_DIRS})

add_executable(${PROJECT_NAME} stereo_img_publisher_node.cpp)
target_include_directories(${PROJECT_NAME}
PUBLIC "${CMAKE_HOME_DIRECTORY}/include")

set_target_properties(${PROJECT_NAME} PROPERTIES
OUTPUT_NAME stereo_img_publisher
PREFIX "")

## Add cmake target dependencies of the executable
## same as for the library above
add_dependencies(${PROJECT_NAME} ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS})

## Specify libraries to link a library or executable target against
target_link_libraries(${PROJECT_NAME}
  ${catkin_LIBRARIES}
  ${OpenCV_LIBS}
)

#############
## Install ##
#############

# all install targets should use catkin DESTINATION variables
# See http://ros.org/doc/api/catkin/html/adv_user_guide/variables.html

## Mark executable scripts (Python etc.) for installation
## in contrast to setup.py, you can choose the destination
# catkin_install_python(PROGRAMS
#   scripts/my_python_script
#   DESTINATION ${CATKIN_PACKAGE_BIN_DESTINATION}
# )

## Mark executables for installation
## See http://docs.ros.org/melodic/api/catkin/html/howto/format1/building_executables.html
# install(TARGETS ${PROJECT_NAME}_node
#   RUNTIME DESTINATION ${CATKIN_PACKAGE_BIN_DESTINATION}
# )

## Mark libraries for installation
## See http://docs.ros.org/melodic/api/catkin/html/howto/format1/building_libraries.html
# install(TARGETS ${PROJECT_NAME}
#   ARCHIVE DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
#   LIBRARY DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
#   RUNTIME DESTINATION ${CATKIN_GLOBAL_BIN_DESTINATION}
# )

## Mark cpp header files for installation
# install(DIRECTORY include/${PROJECT_NAME}/
#   DESTINATION ${CATKIN_PACKAGE_INCLUDE_DESTINATION}
#   FILES_MATCHING PATTERN "*.h"
#   PATTERN ".svn" EXCLUDE
# )

## Mark other files for installation (e.g. launch and bag files, etc.)
# install(FILES
#   # myfile1
#   # myfile2
#   DESTINATION ${CATKIN_PACKAGE_SHARE_DESTINATION}
# )
