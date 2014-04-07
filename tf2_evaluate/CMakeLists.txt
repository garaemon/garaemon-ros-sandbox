cmake_minimum_required(VERSION 2.8.3)
project(tf2_evaluate)

find_package(catkin REQUIRED COMPONENTS
  tf
  tf2
  tf2_ros
)
catkin_package(
 CATKIN_DEPENDS tf tf2 tf2_ros
)

include_directories(
  ${catkin_INCLUDE_DIRS}
)

add_executable(tf2_echo src/tf2_echo.cpp)
target_link_libraries(tf2_echo ${catkin_LIBRARIES})

add_executable(tf2_publish src/tf2_publish.cpp)
target_link_libraries(tf2_publish ${catkin_LIBRARIES})

add_executable(tf2_lookup_bench src/tf2_lookup_bench.cpp)
target_link_libraries(tf2_lookup_bench ${catkin_LIBRARIES})

add_executable(tf_lookup_bench src/tf_lookup_bench.cpp)
target_link_libraries(tf_lookup_bench ${catkin_LIBRARIES})

install(TARGETS tf2_echo tf2_publish tf2_lookup_bench tf_lookup_bench
  ARCHIVE DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
  LIBRARY DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
  RUNTIME DESTINATION ${CATKIN_PACKAGE_BIN_DESTINATION}
)

install(DIRECTORY launch scripts
  DESTINATION ${CATKIN_PACKAGE_SHARE_DESTINATION}
)

