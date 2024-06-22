project(StatistiCalculator_GUI)

set(GUI_DIRECTORY "${PROJECT_SOURCE_DIR}/SC_GUI")
set(GUI_SRC_DIRECTORY "${GUI_DIRECTORY}/src")
set(GUI_INC_DIRECTORY "${GUI_DIRECTORY}/include")

file(GLOB_RECURSE GUI_SRC_FILES "${GUI_SRC_DIRECTORY}/*.cpp")
file(GLOB_RECURSE GUI_INC_FILES "${GUI_INC_DIRECTORY}/*.h")

# Add source to this project's executable.
add_executable(StatistiCalculator_GUI WIN32 ${SRC_FILES}     ${INC_FILES}
                                            ${GUI_SRC_FILES} ${GUI_INC_FILES})


# Include Files
target_include_directories(StatistiCalculator_GUI PUBLIC ${INC_DIRECTORY} ${INC_FILES}
                                                         ${GUI_INC_DIRECTORY} ${GUI_INC_FILES})
