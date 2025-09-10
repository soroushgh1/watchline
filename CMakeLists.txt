cmake_minimum_required(VERSION 3.16)
project(App LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(MAIN_FILE ${CMAKE_SOURCE_DIR}/main.cpp)

file(GLOB_RECURSE SRC_FILES CONFIGURE_DEPENDS ${CMAKE_SOURCE_DIR}/src/*.cpp)

find_package(PkgConfig REQUIRED)
pkg_check_modules(GTKMM REQUIRED gtkmm-4.0)
pkg_check_modules(LIBADWAITA REQUIRED libadwaita-1)

include_directories(${CMAKE_SOURCE_DIR}/src/external)

include_directories(
  ${GTKMM_INCLUDE_DIRS}
  ${LIBADWAITA_INCLUDE_DIRS}
)

link_directories(
  ${GTKMM_LIBRARY_DIRS}
  ${LIBADWAITA_LIBRARY_DIRS}
)

add_executable(App ${SRC_FILES} ${MAIN_FILE})

target_link_libraries(App
  ${GTKMM_LIBRARIES}
  ${LIBADWAITA_LIBRARIES}
)
