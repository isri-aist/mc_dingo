cmake_minimum_required(VERSION 3.22)

set(CXX_DISABLE_WERROR 1)
set(CMAKE_CXX_STANDARD 17)

set(PROJECT_NAME mc_dingo)
set(PROJECT_DESCRIPTION "dingo robot module for mc_rtc")

project(
  ${PROJECT_NAME}
  LANGUAGES CXX
  VERSION 1.0.0)
include(CTest)
enable_testing()

find_package(mc_rtc REQUIRED)
find_description_package(dingo_description REQUIRED)

file(GLOB_RECURSE DINGO_XACRO_FILES "${DINGO_DESCRIPTION_PATH}/urdf/*.xacro")

find_program(XACRO xacro REQUIRED)
set(DINGO_URDF_DIR "${CMAKE_INSTALL_PREFIX}/share/mc_dingo/urdf")
set(GENERATED_DINGO_URDF "${CMAKE_BINARY_DIR}/urdf/dingo.urdf")
set(xacro_IN "${DINGO_DESCRIPTION_PATH}/urdf/dingo.urdf.xacro")
message(STATUS "Generating URDF at ${urdf_OUT} from ${xacro_IN}")

add_custom_command(
  OUTPUT ${GENERATED_DINGO_URDF}
  COMMAND ${XACRO} ${xacro_IN} -o ${GENERATED_DINGO_URDF}
  DEPENDS ${xacro_SRC}
  COMMENT "Generate ${GENERATED_DINGO_URDF}")

add_custom_target(generate-dingo-urdf ALL DEPENDS ${GENERATED_DINGO_URDF})
install(FILES ${GENERATED_DINGO_URDF} DESTINATION ${DINGO_URDF_DIR})

add_subdirectory(src)

if(BUILD_TESTING)
  add_subdirectory(tests)
endif()
