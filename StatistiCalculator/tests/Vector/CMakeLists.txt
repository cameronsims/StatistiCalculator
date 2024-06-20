project(StatistiCalculator_Vector)

# Add source to this project's executable.
add_executable(StatistiCalculator_Vector "${TEST_VECTOR_DIRECTORY}/main.cpp" "${SRC_DIRECTORY}/structures/Exception.cpp" "${INC_DIRECTORY}/structures/Vector.h" "${INC_DIRECTORY}/structures/Exception.h")

# Include Files
target_include_directories(StatistiCalculator_Vector PUBLIC "${INC_DIRECTORY}")