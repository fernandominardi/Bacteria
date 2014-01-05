cmake_minimum_required(VERSION 2.6)

project(Bacteria)
#include custom CMake Modules
SET(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake/modules)


#include libxml2
find_package(LibXml2 REQUIRED)
include_directories(${LIBXML2_INCLUDE_DIR})
#inlclude allegro
FIND_PACKAGE(Allegro REQUIRED)
    
    
include_directories(${ALLEGRO_INCLUDE_DIRS} ${ALLEGRO_INCLUDE_DIR})
 
#add the executable
add_executable(Bacteria main.c)
#linker options
target_link_libraries(Bacteria ${LIBXML2_LIBRARIES} ${ALLEGRO_LIBRARIES})
