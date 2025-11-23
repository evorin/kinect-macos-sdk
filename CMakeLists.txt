cmake_minimum_required(VERSION 3.15)
project(KinectMacOSSDK VERSION 1.0.0 LANGUAGES C CXX)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Set C standard
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

# Output directories
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

# Find required packages
find_package(PkgConfig REQUIRED)

# Find libfreenect
pkg_check_modules(FREENECT REQUIRED libfreenect)

# Include directories
include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${CMAKE_CURRENT_SOURCE_DIR}/src
    ${FREENECT_INCLUDE_DIRS}
)

# Source files
set(SOURCES
    src/kinect_interface.cpp
    src/main.cpp
)

# Header files
set(HEADERS
    src/kinect_interface.h
    src/algorithm_interface.h
    include/custom_algorithm.h
)

# Create executable
add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS})

# Link libraries
target_link_libraries(${PROJECT_NAME}
    ${FREENECT_LIBRARIES}
    pthread
)

# Add compile options
target_compile_options(${PROJECT_NAME} PRIVATE
    -Wall
    -Wextra
    -Wpedantic
)

# macOS specific settings
if(APPLE)
    target_compile_definitions(${PROJECT_NAME} PRIVATE MACOS_BUILD)
    find_library(COREFOUNDATION_LIBRARY CoreFoundation)
    find_library(IOKIT_LIBRARY IOKit)
    target_link_libraries(${PROJECT_NAME}
        ${COREFOUNDATION_LIBRARY}
        ${IOKIT_LIBRARY}
    )
endif()

# Installation rules
install(TARGETS ${PROJECT_NAME}
    RUNTIME DESTINATION bin
)

install(FILES ${HEADERS}
    DESTINATION include/kinect-sdk
)

# Print configuration summary
message(STATUS "")
message(STATUS "========================================")
message(STATUS "Kinect macOS SDK Configuration Summary")
message(STATUS "========================================")
message(STATUS "Version: ${PROJECT_VERSION}")
message(STATUS "C++ Standard: ${CMAKE_CXX_STANDARD}")
message(STATUS "Build Type: ${CMAKE_BUILD_TYPE}")
message(STATUS "libfreenect found: ${FREENECT_FOUND}")
message(STATUS "libfreenect libraries: ${FREENECT_LIBRARIES}")
message(STATUS "Install prefix: ${CMAKE_INSTALL_PREFIX}")
message(STATUS "========================================")
message(STATUS "")
