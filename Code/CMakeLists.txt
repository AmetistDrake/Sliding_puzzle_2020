cmake_minimum_required(VERSION 3.17)
project(pot_HF)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Werror -Wextra -pedantic") # -Werror

add_executable(pot_HF main.cpp woodpecker.hpp State.hpp Node.hpp Solver.hpp)