cmake_minimum_required(VERSION 3.22)

set(CXX_DISABLE_WERROR 1)
set(CMAKE_CXX_STANDARD 17)

set(PROJECT_NAME mc_dingo)
set(PROJECT_DESCRIPTION "dingo robot module for mc_rtc")

project(${PROJECT_NAME} LANGUAGES CXX VERSION 1.0.0)
include(CTest)
enable_testing()

find_package(mc_rtc REQUIRED)
find_description_package(dingo_description REQUIRED)

set(PACKAGE_NAME "dingo_description")
message(STATUS "Found package ${DINGO_DESCRIPTION_PATH}")

set(DATA_INSTALL_FOLDER "${CMAKE_INSTALL_PREFIX}/share/${PROJECT_NAME}")

file(GLOB_RECURSE xacro_SRC "${DINGO_DESCRIPTION_PATH}/urdf/*.xacro")

find_program(XACRO xacro REQUIRED)
set(urdf_OUT "${CMAKE_CURRENT_SOURCE_DIR}/urdf/dingo.urdf")
set(xacro_IN ${DINGO_DESCRIPTION_PATH}/urdf/dingo.urdf.xacro)
message(STATUS "Generating URDF at ${urdf_OUT} from ${xacro_IN}")
add_custom_command(
  OUTPUT ${urdf_OUT}
  COMMAND 
    ${XACRO} ${xacro_IN} -o ${urdf_OUT}
  DEPENDS ${xacro_SRC}
COMMENT "Generate ${urdf_OUT}")

add_custom_target(generate-dingo-urdf ALL DEPENDS ${urdf_OUT})
install(FILES "${urdf_OUT}" DESTINATION ${DATA_INSTALL_FOLDER}/urdf/)

add_subdirectory(src)

install(DIRECTORY convex DESTINATION ${DATA_INSTALL_FOLDER}/mc_dingo)
install(DIRECTORY rsdf DESTINATION ${DATA_INSTALL_FOLDER}/mc_dingo)
install(DIRECTORY urdf DESTINATION ${DATA_INSTALL_FOLDER}/mc_dingo)

if(BUILD_TESTING)
  add_subdirectory(tests)
endif()
