cmake_minimum_required(VERSION 3.12)

project(Object VERSION 0.0.3)

option(BUILD_EXAMPLES "Build examples" OFF)

if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

if (MSVC)
  add_compile_options(/Zc:preprocessor)
endif()

add_subdirectory("Object")

if (BUILD_EXAMPLES)
  add_subdirectory("Examples")
endif()