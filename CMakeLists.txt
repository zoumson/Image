cmake_minimum_required(VERSION 2.8.9)

#set the project name
project (image)

#Set the compiler
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_BUILD_TYPE Release)
set( EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)


#Set ccache (for speeding up)
find_program(CCACHE_FOUND ccache) 
if(CCACHE_FOUND) 
    set_property(GLOBAL PROPERTY RULE_LAUNCH_COMPILE ccache) 
    set_property(GLOBAL PROPERTY RULE_LAUNCH_LINK ccache) 
endif(CCACHE_FOUND) 
set (CMAKE_CXX_FLAGS "-DPCL_ONLY_CORE_POINT_TYPES=ON -DNO_EXPLICIT_INSTANTIATIONS") 

############### Dependencies #######################

#Bring the headers
include_directories(${PROJECT_SOURCE_DIR}/include)

# OpenCV
find_package( OpenCV  REQUIRED )
# header
include_directories( ${OpenCV_INCLUDE_DIRS} )

add_executable( imageBasics ${PROJECT_SOURCE_DIR}/src/imageBasics.cpp )
# add lib
target_link_libraries( imageBasics ${OpenCV_LIBS} )