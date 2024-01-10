cmake_minimum_required(VERSION 3.0)
project(TraceExample)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Find MPI
find_package(MPI REQUIRED)

# Include spdlog (assuming it's installed system-wide)
find_package(spdlog REQUIRED)

# Include directories
include_directories(${MPI_INCLUDE_PATH})

# Define the executable
add_executable(TraceExample main.cpp Tracer.h)

# Link MPI and spdlog
target_link_libraries(TraceExample ${MPI_LIBRARIES} spdlog::spdlog)
