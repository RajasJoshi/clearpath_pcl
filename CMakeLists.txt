#  Copyright (c) 2022 Jonas Mahler

#  This file is part of clearpath_pcl.

#  clearpath_pcl is free software: you can redistribute it and/or modify it under the terms 
#  of the GNU General Public License as published by the Free Software Foundation, 
#  either version 3 of the License, or (at your option) any later version.

#  clearpath_pcl is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; 
#  without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. 
#  See the GNU General Public License for more details.

#  You should have received a copy of the GNU General Public License along 
#  with clearpath_pcl. If not, see <https://www.gnu.org/licenses/>. 

cmake_minimum_required(VERSION 3.5)
project(clearpath_pcl)

# Default to C99
if(NOT CMAKE_C_STANDARD)
  set(CMAKE_C_STANDARD 99)
endif()

# Default to C++14
if(NOT CMAKE_CXX_STANDARD)
  set(CMAKE_CXX_STANDARD 14)
endif()

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# find dependencies
find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(std_msgs REQUIRED)
find_package(sensor_msgs REQUIRED)
find_package(pcl_conversions REQUIRED)
find_package(PCL 1.10 REQUIRED)

include_directories(${PCL_INCLUDE_DIRS})
link_directories(${PCL_LIBRARY_DIRS})
add_definitions(${PCL_DEFINITIONS})

add_executable(clearpath_pcl_node src/clearpath_pcl_node.cpp)

target_link_libraries( clearpath_pcl_node
  ${Boost_SYSTEM_LIBRARY}
  ${PCL_LIBRARIES}
)

ament_target_dependencies(
  clearpath_pcl_node
  rclcpp std_msgs 
  sensor_msgs
  pcl_conversions
)

install(TARGETS
  clearpath_pcl_node
  DESTINATION lib/${PROJECT_NAME}
)

# Files for testing
install(FILES
  test/cube1_record_1.yaml test/cube1_record_2.yaml test/clearpath_pcl_launch.testing.py 
  DESTINATION lib/${PROJECT_NAME}
)

# Rviz2 config for visualization
install(FILES config/clearpath_pcl.rviz 
  DESTINATION lib/${PROJECT_NAME}
)

if(BUILD_TESTING)
  #find_package(ament_lint_auto REQUIRED)
  #ament_lint_auto_find_test_dependencies()
  find_package(launch_testing_ament_cmake)    
  add_launch_test(test/clearpath_pcl_launch.testing.py)
endif()

ament_package()
