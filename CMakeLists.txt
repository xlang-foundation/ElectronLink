# CMakeList.txt : CMake project for ElectronLink Package, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

project ("ElectronLink")

include_directories("../xlang/Api")

FILE(GLOB API_SRC "../xlang/Api/value.cpp")
FILE(GLOB Main_SRC "*.cpp")

add_library(${PROJECT_NAME} 
	SHARED
	${API_SRC}
	${Main_SRC}
)

