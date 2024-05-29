# CMakeList.txt : CMake project for ElectronLink Package, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

project ("ElectronLink")

include_directories("../xlang/Api")

FILE(GLOB API_SRC "../xlang/Api/value.cpp")
FILE(GLOB Main_SRC "main.cpp")
If (WIN32)
FILE(GLOB Hardware_SRC "smbus_windows.cpp")
else()
FILE(GLOB Hardware_SRC "smbus_linux.cpp")
endif()

add_library(${PROJECT_NAME} 
	SHARED
	${API_SRC}
	${Main_SRC}
	${Hardware_SRC}
)

