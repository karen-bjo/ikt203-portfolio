# CMakeList.txt : Top-level CMake project file, do global configuration
# and include sub-projects here.
#
cmake_minimum_required (VERSION 3.20)

# Enable Hot Reload for MSVC compilers if supported.
if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

project ("Portfolio")

# Add shared libraries (available to all assignments) FIRST
add_subdirectory(DataStructures)   # header-only DS target
add_subdirectory(SharedLib)        # I/O helpers

# Include sub-projects.

# Tell CMake to find and include the first exercise project.
add_subdirectory(Assignment-01)
add_subdirectory(Assignment-02)
add_subdirectory(Assignment-03)
add_subdirectory(Assignment-04)
