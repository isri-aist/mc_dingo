# Here we find a typical ROS description package, this set the DINGO_DESCRIPTION_PATH CMake variable
find_description_package(dingo_description)
if(EXISTS "${DINGO_DESCRIPTION_PATH}/share/dingo_description")
  set(DINGO_DESCRIPTION_PATH "${DINGO_DESCRIPTION_PATH}/share/dingo_description")
endif()

# Generate the robot module C++ code using this value
configure_file(dingo.in.cpp "${CMAKE_CURRENT_BINARY_DIR}/dingo.cpp")

set(dingo_SRC
  "${CMAKE_CURRENT_BINARY_DIR}/dingo.cpp"
)
set(dingo_HDR
  dingo.h
)

add_robot(dingo ${dingo_SRC} ${dingo_HDR})
target_include_directories(dingo PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}")
