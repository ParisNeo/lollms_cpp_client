cmake_minimum_required(VERSION 3.12)
project(LollmsClientLib)  # Change the project name to indicate it's a library

# Include ExternalProject module
include(ExternalProject)

# Set up the external project
ExternalProject_Add(
    socketio-client-cpp
    PREFIX ${CMAKE_BINARY_DIR}/external
    GIT_REPOSITORY https://github.com/socketio/socket.io-client-cpp.git
    GIT_TAG master # You can change this to a specific release/tag if needed
    CMAKE_ARGS -DCMAKE_INSTALL_PREFIX=<INSTALL_DIR> -DSIO_DISABLE_LOGGING=ON -DBUILD_SHARED_LIBS=OFF  # Build socketio-client-cpp as a static library
)

# Add your project's library here
add_library(LollmsClientLib src/LollmsClient.cpp src/ASCIIColors.cpp)

# Include the socket.io-client-cpp header files
target_include_directories(LollmsClientLib PUBLIC

    ${CMAKE_BINARY_DIR}/external/include
    ${CMAKE_BINARY_DIR}/external/include/socket.io-client-cpp
    ${CMAKE_SOURCE_DIR}/inc 
)

# This is required for googletest
find_package(sioclient)

# Link your project with the socket.io-client-cpp library
target_include_directories(LollmsClientLib PRIVATE ${CMAKE_BINARY_DIR}/external/include)
target_link_directories(LollmsClientLib PRIVATE ${CMAKE_BINARY_DIR}/external/lib)
target_link_libraries(LollmsClientLib PRIVATE sioclient)
