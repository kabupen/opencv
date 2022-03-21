cmake_minimum_required(VERSION 3.1)
project (test1)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall")

find_package(OpenCV REQUIRED)
include_directories( ${OpenCV_INCLUDE_DIRS} )

add_executable(main main.cpp)
target_link_libraries(main ${OpenCV_LIBS})

add_executable(main_procrustes main_procrustes.cpp)
target_link_libraries(main_procrustes ${OpenCV_LIBS})

add_executable(mat test/mat.cpp)
target_link_libraries(mat ${OpenCV_LIBS})

add_executable(test test.cpp)
target_link_libraries(test ${OpenCV_LIBS})
