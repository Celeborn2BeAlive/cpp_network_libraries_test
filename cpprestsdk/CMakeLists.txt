cmake_minimum_required(VERSION 3.13)

project(cpprestsdk_test)

find_package(cpprestsdk CONFIG REQUIRED)

add_executable(cpprestsdk_test main.cpp)
target_link_libraries(cpprestsdk_test PRIVATE cpprestsdk::cpprest)

install(TARGETS cpprestsdk_test DESTINATION .)