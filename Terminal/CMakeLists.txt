project(StatistiCalculator_Terminal)

# Terminal

set(TERMINAL_SRC_DIRECTORY "${TERMINAL_DIRECTORY}/src")
set(TERMINAL_INC_DIRECTORY "${TERMINAL_DIRECTORY}/include")

file(GLOB_RECURSE SRC_TERMINAL_FILES "${TERMINAL_SRC_DIRECTORY}/*.cpp")   # Terminal CPP Implementation Files
file(GLOB_RECURSE INC_TERMINAL_FILES "${TERMINAL_INC_DIRECTORY}/*.h")     # Terminal CPP Header Files

add_executable(StatistiCalculator_Terminal ${SRC_FILES} ${INC_FILES} ${SRC_TERMINAL_FILES} ${INC_TERMINAL_FILES})
target_include_directories(StatistiCalculator_Terminal PUBLIC ${INC_DIRECTORY} ${INC_FILES} ${TERMINAL_INC_DIRECTORY} ${INC_TERMINAL_FILES})
