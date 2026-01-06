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
