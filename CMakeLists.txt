cmake_minimum_required(VERSION 3.5)

set(CXX_DISABLE_WERROR 1)
set(CMAKE_CXX_STANDARD 11)

set(PROJECT_NAME mc_dingo)
set(PROJECT_DESCRIPTION "Dingo robot module for mc_rtc")

project(${PROJECT_NAME} LANGUAGES CXX VERSION 1.0.0)
include(CTest)
enable_testing()

find_package(mc_rtc REQUIRED)
find_description_package(dingo_description REQUIRED)

set(PACKAGE_NAME "dingo_description")

message(STATUS "dingo_description path ${dingo_description_DIR}")
if("${dingo_description_INSTALL_PREFIX}" STREQUAL "")
  if("${dingo_description_SOURCE_PREFIX}" STREQUAL "")
    if("${dingo_description_DIR}" STREQUAL "")
      message(
        FATAL_ERROR
          "dingo_description does not provide SOURCE_PREFIX or INSTALL_PREFIX")
    else()
      set(dingo_description_PREFIX "${dingo_description_DIR}/..")
    endif()
  else()
    set(dingo_description_PREFIX "${dingo_description_SOURCE_PREFIX}")
  endif()
else()
  set(dingo_description_PREFIX
      "${dingo_description_INSTALL_PREFIX}/share/dingo_description")
endif()

set(DATA_INSTALL_FOLDER "${CMAKE_INSTALL_PREFIX}/share/${PROJECT_NAME}")

file(GLOB_RECURSE xacro_SRC "${ur_description_PREFIX}/urdf/*.xacro")

find_program(XACRO xacro REQUIRED)
set(urdf_OUT "${CMAKE_CURRENT_SOURCE_DIR}/urdf/dingo.urdf")
message(STATUS "Prefix path: ${dingo_description_PREFIX}")
set(xacro_IN ${dingo_description_PREFIX}/urdf/dingo.urdf.xacro)

add_custom_command(
  OUTPUT ${urdf_OUT}
  COMMAND 
    ${XACRO} ${xacro_IN} name:=dingo -o ${urdf_OUT}
  DEPENDS ${xacro_SRC}
COMMENT "Generate ${urdf_OUT}")

add_subdirectory(src)

install(DIRECTORY convex DESTINATION ${CMAKE_INSTALL_DATADIR}/mc_dingo)
install(DIRECTORY rsdf DESTINATION ${CMAKE_INSTALL_DATADIR}/mc_dingo)
install(DIRECTORY urdf DESTINATION ${CMAKE_INSTALL_DATADIR}/mc_dingo)

if(BUILD_TESTING)
  add_subdirectory(tests)
endif()
