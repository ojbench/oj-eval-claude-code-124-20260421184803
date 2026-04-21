cmake_minimum_required(VERSION 3.10)
project(problem_124_code CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Optimize for speed
if (NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Release)
endif()

add_executable(code code.cpp)

# Place the executable at project root so the judge can find 'code'
set_target_properties(code PROPERTIES
  RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}"
)

target_compile_options(code PRIVATE -O2 -pipe -DNDEBUG)
