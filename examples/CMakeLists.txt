cmake_minimum_required(VERSION 3.12)
project(chatApp)

# Find the lollmsClientLib package
find_package(LollmsClientLib REQUIRED)

add_executable(chatApp main.cpp)

# Link your application with the lollmsClientLib library
target_link_libraries(chatApp PRIVATE LollmsClientLib)