
cmake_minimum_required(VERSION 3.18)

set( CMAKE_CXX_STANDARD_REQUIRED ON )  
set( CMAKE_CXX_COMPILER g++ )

project( simple_md VERSION 0.1.0 LANGUAGES CXX )

file( GLOB_RECURSE SRC_FILES src/*.cpp )

add_executable( ${PROJECT_NAME} ${SRC_FILES})
target_include_directories( ${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include )
target_link_libraries(${PROJECT_NAME} PRIVATE m)

set( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}" )
