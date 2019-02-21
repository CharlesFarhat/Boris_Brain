cmake_minimum_required(VERSION 3.5)
# Project
set(PROJECT Boris_System_Brain)
project(${PROJECT})
SET(CMAKE_BUILD_TYPE Release) # Release, RelWithDebInfo
SET(CMAKE_VERBOSE_MAKEFILE OFF)
SET(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${PROJECT_SOURCE_DIR}/CMakeModules/")

# Versions
set(VERSION_MAJOR 0)
set(VERSION_MINOR 1)
set(VERSION_PATCH 1)


# Add plain cmake packages
FIND_PACKAGE(OpenCV REQUIRED)
FIND_PACKAGE(Eigen REQUIRED)
find_package(SuiteParse REQUIRED)
FIND_PACKAGE(Boost REQUIRED COMPONENTS thread system)
find_package(Pangolin 0.2 QUIET)
find_package(Glog REQUIRED)

# Boris_Utils used to get some maths and mainly technical stuff
FIND_PACKAGE(Boris_Utils REQUIRED)

message(STATUS "Boris utils found and ready to go !")
message(STATUS "All default dependencies ready to go !")


# Include dirs
INCLUDE_DIRECTORIES(
        ${Eigen_INCLUDE_DIRS}
        ${OpenCV_INCLUDE_DIRS}
        ${Boost_INCLUDE_DIRS}
        ${Glog_INCLUDE_DIRS}
        ${Pangolin_INCLUDE_DIRS}

        ${PROJECT_SOURCE_DIR}/src
        ${PROJECT_SOURCE_DIR}/src/EnvProcessing/VisualOdometry/include
        ${Boris_Utils_INCLUDE_DIRS}
)
include_directories( ${CSPARSE_INCLUDE_DIR} ${CHOLMOD_INCLUDE_DIR})

# Set link libraries
LIST(APPEND LINK_LIBS_EXTERNAL
        ${Boris_Utils_LIBRARIES}
        ${OpenCV_LIBS}
        ${Boost_LIBRARIES}
        ${GLOG_LIBRARY}
        ${Pangolin_LIBRARIES}
        )


# setup params for the build
SET(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/Bin)
SET(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/lib)

# add all coponments and ceate all libraries
add_subdirectory(src/EnvProcessing/VisualOdometry)


#Create Boris library
#add_library(Boris_System_Brain SHARED )
#target_link_libraries(Boris_System_Brain ${LINK_LIBS_EXTERNAL})
#set(BOOST_THREAD_LIBRARY boost_thread)



##########################################################################################
# PROGRAMS
##########################################################################################
ADD_EXECUTABLE(BorisBrain src/Boris_Brain.cpp src/EnvProcessing/VisualOdometry/VO_Pipeline_Live.cpp)
TARGET_LINK_LIBRARIES(BorisBrain Boris_System_Brain)