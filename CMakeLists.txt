cmake_minimum_required(VERSION 3.10)
project(tcash)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

# Add source file directory
file(GLOB_RECURSE SRC_FILES CONFIGURE_DEPENDS src/*.cpp)

add_executable(tcash ${SRC_FILES})

# Add pugixml include directory so headers are found
target_include_directories(tcash PRIVATE
    ${PROJECT_SOURCE_DIR}/libs/pugixml-1.15/src
    ${PROJECT_SOURCE_DIR}/include
    ${PROJECT_SOURCE_DIR}/include/helper
)

# Link the static pugixml library explicitly by path
target_link_libraries(tcash PRIVATE
    ${PROJECT_SOURCE_DIR}/libs/pugixml-1.15/build/libpugixml.a
)
