# CMakeList.txt : CMake project for StatistiCalculator, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

project(StatistiCalculator)
project(StatistiCalculator_Terminal)
project(StatistiCalculator_GUI)

#######################################################################

# Directories
set(MAIN_DIRECTORY "${PROJECT_SOURCE_DIR}/StatistiCalculator")
set(SRC_DIRECTORY  "${MAIN_DIRECTORY}/src")
set(INC_DIRECTORY  "${MAIN_DIRECTORY}/include")
set(TEST_DIRECTORY "${MAIN_DIRECTORY}/tests")

file(GLOB_RECURSE SRC_FILES "${SRC_DIRECTORY}/*.cpp")   # Raw CPP Implementation Files
file(GLOB_RECURSE INC_FILES "${INC_DIRECTORY}/*.h")     # Raw CPP Header Files


# Terminal

set(TERMINAL_DIRECTORY "${PROJECT_SOURCE_DIR}/Terminal")
set(TERMINAL_SRC_DIRECTORY "${TERMINAL_DIRECTORY}/src")
set(TERMINAL_INC_DIRECTORY "${TERMINAL_DIRECTORY}/include")

file(GLOB_RECURSE SRC_TERMINAL_FILES "${TERMINAL_SRC_DIRECTORY}/*.cpp")   # Terminal CPP Implementation Files
file(GLOB_RECURSE INC_TERMINAL_FILES "${TERMINAL_INC_DIRECTORY}/*.h")     # Terminal CPP Header Files

#######################################################################




# Add Tests ###########################################################

include("${TEST_DIRECTORY}/CMakeLists.txt")

#######################################################################

# Add source to this project's executable.
add_executable(StatistiCalculator ${SRC_FILES} ${INC_FILES})
add_executable(StatistiCalculator_Terminal ${SRC_FILES} ${INC_FILES} ${SRC_TERMINAL_FILES} ${INC_TERMINAL_FILES})


# Include Files
target_include_directories(StatistiCalculator PUBLIC ${INC_DIRECTORY} ${INC_FILES})
target_include_directories(StatistiCalculator_Terminal PUBLIC ${INC_DIRECTORY} ${INC_FILES} ${TERMINAL_INC_DIRECTORY} ${INC_TERMINAL_FILES})

