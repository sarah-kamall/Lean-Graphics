cmake_minimum_required(VERSION 3.10.0)
project(tut2 VERSION 0.1.0 LANGUAGES C CXX)

add_executable(tut_3 main.cpp glad/src/glad.c)
target_link_libraries(tut_3 glfw)
include_directories(
    glad/include
)
include(CTest)
enable_testing()

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG ${PROJECT_SOURCE_DIR}/bin)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE ${PROJECT_SOURCE_DIR}/bin)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)


