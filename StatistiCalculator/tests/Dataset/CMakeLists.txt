project(StatistiCalculator_Dataset)

# Add source to this project's executable.
add_executable(StatistiCalculator_Dataset "${TEST_DATASET_DIRECTORY}/main.cpp" ${SRC_FILES} ${INC_FILES})

# Include Files
target_include_directories(StatistiCalculator_Dataset PUBLIC ${INC_DIRECTORY} ${INC_FILES})