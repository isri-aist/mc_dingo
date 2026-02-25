# Here we find a typical ROS description package, this set the
# DINGO_DESCRIPTION_PATH CMake variable
find_description_package(dingo_description)
if(EXISTS "${DINGO_DESCRIPTION_PATH}/share/dingo_description")
  set(DINGO_DESCRIPTION_PATH
      "${DINGO_DESCRIPTION_PATH}/share/dingo_description")
endif()

configure_file(config.in.h
               "${CMAKE_CURRENT_BINARY_DIR}/include/mc_dingo/config.h")

set(dingo_SRC dingo.cpp)
set(dingo_HDR dingo.h)

add_robot(dingo ${dingo_SRC} ${dingo_HDR})
target_include_directories(
  dingo PUBLIC $<INSTALL_INTERFACE:include>
               $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}/include>)

target_include_directories(
  dingo PRIVATE $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>)

install(FILES ${dingo_HDR}
              "${CMAKE_CURRENT_BINARY_DIR}/include/mc_dingo/config.h"
        DESTINATION include/mc_dingo)
