# ---- Options ----
option(ENABLE_TEST_COVERAGE "Enable test coverage" OFF)

cmake_minimum_required(VERSION 3.14)

project(ECGen VERSION 1.0)
include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

# ---- Add source files ----

# Note: globbing sources is considered bad practice as CMake's generators may
# not detect new files automatically. Keep that in mind when changing files, or
# explicitly mention them here.
file(
  GLOB_RECURSE
  headers
  CONFIGURE_DEPENDS
  "${CMAKE_CURRENT_SOURCE_DIR}/include/*.h ${CMAKE_CURRENT_SOURCE_DIR}/include/*.hpp"
)
file(GLOB_RECURSE sources CONFIGURE_DEPENDS
     "${CMAKE_CURRENT_SOURCE_DIR}/source/*.cpp")

# ---- Create library ----

# Note: for header-only libraries change all PUBLIC flags to INTERFACE and
# create an interface target: add_library(${PROJECT_NAME} INTERFACE)
add_library(${PROJECT_NAME} ${headers} ${sources})

set_target_properties(${PROJECT_NAME} PROPERTIES CXX_STANDARD 20)

# being a cross-platform target, we enforce standards conformance on MSVC
target_compile_options(${PROJECT_NAME}
                       PUBLIC "$<$<COMPILE_LANG_AND_ID:CXX,MSVC>:/permissive->")

# Link dependencies
target_link_libraries(${PROJECT_NAME} PRIVATE ${CONAN_LIBS})

target_include_directories(
  ${PROJECT_NAME}
  PUBLIC $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
         $<INSTALL_INTERFACE:include/${PROJECT_NAME}-${PROJECT_VERSION}>)

# Link dependencies
# ---- Create test ----

add_executable(${PROJECT_NAME}Tests ${headers} ${sources})
set_target_properties(${PROJECT_NAME}Tests PROPERTIES CXX_STANDARD 20)
target_link_libraries(${PROJECT_NAME}Tests ${CONAN_LIBS})
target_include_directories(
  ${PROJECT_NAME}Tests
  PUBLIC $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
         $<INSTALL_INTERFACE:include/${PROJECT_NAME}-${PROJECT_VERSION}>)

# ---- Add ${PROJECT_NAME}Tests ----

enable_testing()

# Note: doctest and similar testing frameworks can automatically configure CMake
# tests. For other testing frameworks add the tests target instead:
# add_test(NAME ecgenTests COMMAND ${PROJECT_NAME}Tests)

string(TOLOWER ${PROJECT_NAME} PROJECT_FILE_NAME)
add_test(NAME ${PROJECT_FILE_NAME}Tests COMMAND ${PROJECT_NAME}Tests)

# ---- code coverage ----

if(ENABLE_TEST_COVERAGE)
  target_compile_options(${PROJECT_NAME}Tests PUBLIC -O0 -g -fprofile-arcs
                                                -ftest-coverage)
  target_link_options(${PROJECT_NAME}Tests PUBLIC -fprofile-arcs -ftest-coverage)
endif()
