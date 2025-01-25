cmake_minimum_required(VERSION 3.10)
project(AgenceVoyageIHM)

# Définir la norme C++ utilisée
set(CMAKE_CXX_STANDARD 20)

# Trouver wxWidgets
find_package(wxWidgets REQUIRED COMPONENTS core base)

# Inclure les macros wxWidgets
include(${wxWidgets_USE_FILE})

# Trouver le connecteur MySQL pour C++
find_library(MYSQL_LIB mysqlcppconn REQUIRED)

# Définir le chemin pour cpprestsdk
set(cpprest_DIR "/usr/lib/x86_64-linux-gnu/cmake/cpprestsdk")

# Trouver cpprestsdk (Casablanca)
find_package(cpprestsdk REQUIRED)

include_directories(${CMAKE_SOURCE_DIR}/include)

add_definitions(-DPROJECT_ROOT_DIR="${CMAKE_SOURCE_DIR}")


# Définir les fichiers sources
set(SOURCES 
    src/main.cpp 
    src/Client.cpp 
    src/Trek.cpp
    src/Reservation.cpp
    src/Client/ClientEditDialog.cpp
    src/ButtonCellRenderer.cpp
    src/db_setup.cpp)

# Inclure les répertoires des fichiers d'en-tête
include_directories(src)

# Ajouter l'exécutable
add_executable(wxApp ${SOURCES})

# Lier les bibliothèques nécessaires
target_link_libraries(wxApp 
    ${wxWidgets_LIBRARIES} 
    ${MYSQL_LIB} 
    cpprest 
    ssl 
    crypto)
