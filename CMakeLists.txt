# CMakeList.txt : CMake project for StatistiCalculator, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

project(StatistiCalculator)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED True)




#######################################################################




# Directories
set(MAIN_DIRECTORY "${PROJECT_SOURCE_DIR}/StatistiCalculator")
set(SRC_DIRECTORY  "${MAIN_DIRECTORY}/src")
set(INC_DIRECTORY  "${MAIN_DIRECTORY}/include")
set(TEST_DIRECTORY "${MAIN_DIRECTORY}/tests")
set(LIBRARY_DIRECTORY "${PROJECT_SOURCE_DIR}/lib")

file(GLOB_RECURSE SRC_FILES "${SRC_DIRECTORY}/*.cpp")   # Raw CPP Implementation Files
file(GLOB_RECURSE INC_FILES "${INC_DIRECTORY}/*.h")     # Raw CPP Header Files







#######################################################################





# Terminal Directory ##################################################

set(TERMINAL_DIRECTORY "${PROJECT_SOURCE_DIR}/Terminal")
include("${TERMINAL_DIRECTORY}/CMakeLists.txt")





# GUI Directory #######################################################

#set(GUI_DIRECTORY "${PROJECT_SOURCE_DIR}/SC_GUI")
#include("${GUI_DIRECTORY}/CMakeLists.txt")






# Add Tests ###########################################################

include("${TEST_DIRECTORY}/CMakeLists.txt")







# Add source to this project's executable.
add_executable(StatistiCalculator ${SRC_FILES} ${INC_FILES})


# Include Files
target_include_directories(StatistiCalculator PUBLIC ${INC_DIRECTORY} ${INC_FILES})
