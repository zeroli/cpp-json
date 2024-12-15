cmake_minimum_required(VERSION 3.18)

project(json_ut CXX)

add_executable(${PROJECT_NAME}
    main.cc
    json_test.cc
)

target_include_directories(${PROJECT_NAME} PUBLIC "../src")
target_link_libraries(${PROJECT_NAME} cpp-json)
target_link_libraries(${PROJECT_NAME} gtest)
