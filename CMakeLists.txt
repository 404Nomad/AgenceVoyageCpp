cmake_minimum_required(VERSION 3.10)
project(AgenceVoyageIHM)

set(CMAKE_CXX_STANDARD 20)

find_package(wxWidgets REQUIRED COMPONENTS core base)

include(${wxWidgets_USE_FILE})

add_executable(wxApp main.cpp)
target_link_libraries(wxApp ${wxWidgets_LIBRARIES})