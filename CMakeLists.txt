# CMakeLists.txt : CMake project for ElectronLink Package, include source and define
# project specific logic here.

cmake_minimum_required (VERSION 3.8)

project ("ElectronLink")

# Function to search for the xlang/api directory
function(find_xlang_api_dir)
    set(XLANG_API_DIR "" CACHE INTERNAL "Path to xlang/Api")

    # Check if xlang/api exists in the specified path
    function(check_dir path)
        if (IS_DIRECTORY "${path}/xlang/Api")
            set(XLANG_API_DIR "${path}/xlang/api" CACHE INTERNAL "Path to xlang/Api" FORCE)
        endif()
    endfunction()

    # Check the parent directory
    get_filename_component(PARENT_DIR ${CMAKE_SOURCE_DIR} DIRECTORY)
    check_dir(${PARENT_DIR})

    # Check the immediate subdirectories of the parent directory
    file(GLOB PARENT_SUBDIRS LIST_DIRECTORIES true "${PARENT_DIR}/*")
    foreach(subdir ${PARENT_SUBDIRS})
        check_dir(${subdir})
    endforeach()

    if (XLANG_API_DIR STREQUAL "")
        message(FATAL_ERROR "Could not find xlang/api directory")
    else()
        message(STATUS "Found xlang/api directory at ${XLANG_API_DIR}")
    endif()
endfunction()

# Call the function to find the xlang/api directory
find_xlang_api_dir()

# Include the xlang/api directory
include_directories(${XLANG_API_DIR})

# Find source files
FILE(GLOB API_SRC "${XLANG_API_DIR}/value.cpp")
FILE(GLOB Main_SRC "main.cpp")

if (WIN32)
    FILE(GLOB Hardware_SRC "smbus_windows.cpp")
else()
    FILE(GLOB Hardware_SRC "smbus_linux.cpp")
endif()

# Add the library target
add_library(${PROJECT_NAME} 
    SHARED
    ${API_SRC}
    ${Main_SRC}
    ${Hardware_SRC}
)
