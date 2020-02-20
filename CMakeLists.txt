# @file CMakeLists.txt
# 
# CMake files for read experiments

cmake_minimum_required(VERSION 3.10)

# project info
project(Callbacks)

# C++11 standard
set(CMAKE_CXX_STANDARD 17)

# Assume each .cpp file is a separate application
file(GLOB APPLICATIONS "*.cpp")

# Generate executable for each application
foreach(APP ${APPLICATIONS})

    # Use basename (no path, no extension) of .cpp file for application name
    get_filename_component(APPBASENAME "${APP}" NAME_WLE)

    # Application is based on .cpp file only
    add_executable(${APPBASENAME} ${APPBASENAME}.cpp)

endforeach()

# create a run command that times each application
add_custom_target(run DEPENDS run-cmd)
add_custom_command(OUTPUT run-cmd COMMAND date)
set_source_files_properties(run-cmd PROPERTIES SYMBOLIC "true")

# add each application
foreach(APP ${APPLICATIONS})
    get_filename_component(APPBASENAME "${APP}" NAME_WLE)
    add_custom_command(OUTPUT run-cmd APPEND
        # applications called with file both on stdin and command line
        COMMAND echo ${APPBASENAME}
        COMMAND time ./${APPBASENAME}
    )
endforeach()