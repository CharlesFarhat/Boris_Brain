SET(OpenCV_QT_Support FALSE)

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

# Compilation Flags
add_definitions("-DENABLE_SSE")
set(CMAKE_CXX_FLAGS
        "${SSE_FLAGS} -O3 -g -std=c++11 -march=native"
        #   "${SSE_FLAGS} -O3 -g -std=c++0x -fno-omit-frame-pointer"
        )
if (MSVC)
    set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /EHsc")
endif (MSVC)

IF (OpenCV_QT_Support)
#Qt shit !
set(CMAKE_AUTOMOC ON)
find_package(Qt5 COMPONENTS
        Core
        REQUIRED)
message(STATUS "Qt Found !")
## End of those shit
ENDIF()


# Add plain cmake packages
FIND_PACKAGE(OpenCV REQUIRED)
FIND_PACKAGE(Eigen REQUIRED)
find_package(SuiteParse REQUIRED)
FIND_PACKAGE(Boost REQUIRED COMPONENTS thread system)
find_package(Pangolin 0.2 QUIET)
FIND_PACKAGE(yaml-cpp REQUIRED)
# Boris_Utils used to get some maths and mainly technical stuff
FIND_PACKAGE(Boris_Utils REQUIRED)

message(STATUS "Boris utils found and ready to go !")
message(STATUS "All default dependencies ready to go !")


# Include dirs
INCLUDE_DIRECTORIES(
        ${PROJECT_SOURCE_DIR}/src
        ${Eigen_INCLUDE_DIRS}
        ${OpenCV_INCLUDE_DIRS}
        ${PROJECT_SOURCE_DIR}/ThirdParty/Sophus
        ${Boost_INCLUDE_DIRS}
        ${Boris_Utils_INCLUDE_DIRS}
        ${YAML_CPP_INCLUDEDIR}
        ${PROJECT_SOURCE_DIR}/ThirdParty/sse2neon
)

# Set sourcefiles
LIST(APPEND SOURCEFILES
        src/EnvProcessing/VisualOdometry/FullSystem/FullSystem.cpp
        src/EnvProcessing/VisualOdometry/FullSystem/FullSystemOptimize.cpp
        src/EnvProcessing/VisualOdometry/FullSystem/FullSystemOptPoint.cpp
        src/EnvProcessing/VisualOdometry/FullSystem/FullSystemDebugStuff.cpp
        src/EnvProcessing/VisualOdometry/FullSystem/FullSystemMarginalize.cpp
        src/EnvProcessing/VisualOdometry/FullSystem/Residuals.cpp
        src/EnvProcessing/VisualOdometry/FullSystem/CoarseTracker.cpp
        src/EnvProcessing/VisualOdometry/FullSystem/CoarseInitializer.cpp
        src/EnvProcessing/VisualOdometry/FullSystem/ImmaturePoint.cpp
        src/EnvProcessing/VisualOdometry/FullSystem/HessianBlocks.cpp
        src/EnvProcessing/VisualOdometry/FullSystem/PixelSelector2.cpp
        src/EnvProcessing/VisualOdometry/OptimizationBackend/EnergyFunctional.cpp
        src/EnvProcessing/VisualOdometry/OptimizationBackend/AccumulatedTopHessian.cpp
        src/EnvProcessing/VisualOdometry/OptimizationBackend/AccumulatedSCHessian.cpp
        src/EnvProcessing/VisualOdometry/OptimizationBackend/EnergyFunctionalStructs.cpp
        src/utils/settings.cpp
        src/utils/Undistort.cpp
        src/utils/globalCalib.cpp
        src/utils/videoStream.cpp
        src/EnvProcessing/IOWrapper/OpenCV/ImageDisplay_OpenCV.cpp
        src/EnvProcessing/IOWrapper/OpenCV/ImageRW_OpenCV.cpp
        )


# Set link libraries
LIST(APPEND LINK_LIBS
        ${Boris_Utils_LIBRARIES}
        ${OpenCV_LIBS}
        ${Boost_LIBRARIES}
        ${YAML_CPP_LIBRARIES}
        )

# decide if we have pangolin
if (Pangolin_FOUND)
    message("--- found PANGOLIN, compiling dso_pangolin library.")
    include_directories( ${Pangolin_INCLUDE_DIRS} )
    LIST(APPEND SOURCEFILES
            src/EnvProcessing/IOWrapper/Pangolin/KeyFrameDisplay.cpp
            src/EnvProcessing/IOWrapper/Pangolin/PangolinDSOViewer.cpp)
        LIST(APPEND LINK_LIBS
                ${Pangolin_LIBRARIES})
    set(HAS_PANGOLIN 1)
else ()
    message("--- could not find PANGOLIN, not compiling dso_pangolin library.")
    message("    this means there will be no 3D display / GUI available for dso_dataset.")
    set(HAS_PANGOLIN 0)
endif ()

#Create Boris library
include_directories( ${CSPARSE_INCLUDE_DIR} ${CHOLMOD_INCLUDE_DIR})
ADD_LIBRARY(Boris_System_Brain SHARED ${SOURCEFILES})
TARGET_LINK_LIBRARIES(Boris_System_Brain ${LINK_LIBS})

set(BOOST_THREAD_LIBRARY boost_thread)

SET(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/Bin)
SET(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/lib)


##########################################################################################
# PROGRAMS
##########################################################################################

ADD_EXECUTABLE(BorisBrain src/Boris_Brain.cpp src/EnvProcessing/VisualOdometry/VO_Pipeline_Live.cpp)
TARGET_LINK_LIBRARIES(BorisBrain Boris_System_Brain)