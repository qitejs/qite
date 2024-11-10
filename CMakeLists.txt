cmake_minimum_required(VERSION 3.11)

# Set the project name
project(qite VERSION 1.0 LANGUAGES CXX)

# Set the C++ standard
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Enable optimizations
if(CMAKE_BUILD_TYPE STREQUAL "Release")
    message(STATUS "Building in Release mode")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3")  # Use -O3 for maximum optimization
else()
    message(STATUS "Building in Debug mode")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g")   # Use -g for debug information
endif()

# Specify the source directory
set(SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/src")

# Find all .cpp files in the source directory and its subdirectories
file(GLOB_RECURSE SOURCES "${SOURCE_DIR}/*.cpp")

# Add the executable target
add_executable(${PROJECT_NAME} ${SOURCES})

# CPack configuration for packaging
set(CPACK_GENERATOR "ZIP;TGZ")  # Specify the package formats
set(CPACK_PACKAGE_NAME "Qite")   # Name of the package
set(CPACK_PACKAGE_VERSION "${PROJECT_VERSION}")  # Use project version
set(CPACK_PACKAGE_DESCRIPTION "A JavaScript execution engine.")  # Package description
set(CPACK_PACKAGE_CONTACT "Qite Contributors And Owners")  # Package owners
set(CPACK_PACKAGE_LICENSE "GPL-3.0")  # Specify the license
set(CPACK_PACKAGE_VENDOR "Qite")  # Vendor name

include(CPack)  # Include CPack for packaging
