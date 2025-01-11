cmake_minimum_required(VERSION 3.10)
project(AgenceVoyageIHM)

set(CMAKE_CXX_STANDARD 20)

# Find wxWidgets
find_package(wxWidgets REQUIRED COMPONENTS core base)

# Include wxWidgets macros
include(${wxWidgets_USE_FILE})

# Find MySQL Connector
find_library(MYSQL_LIB mysqlcppconn REQUIRED)

# Source files
set(SOURCES 
    src/main.cpp 
    src/Client.cpp 
    src/Trek.cpp
    src/Reservation.cpp
    src/Client/ClientEditDialog.cpp
    src/db_setup.cpp)

# Include directories
include_directories(src)

# Add executable
add_executable(wxApp ${SOURCES})

# Link libraries
target_link_libraries(wxApp ${wxWidgets_LIBRARIES} ${MYSQL_LIB})
