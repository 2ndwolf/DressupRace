set(GENERATOR_NAME "MinGW Makefiles")
cmake_minimum_required(VERSION 3.17)
set(PROJ_NAME "MTR2_aslib")

set(CMAKE_C_COMPILER "D:/MinGW/GCC12.2_64/bin/gcc.exe")
set(CMAKE_CXX_COMPILER "D:/MinGW/GCC12.2_64/bin/g++.exe")
project(${PROJ_NAME})

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

include_directories(
		${PROJECT_SOURCE_DIR}/include
		${PROJECT_SOURCE_DIR}/dependencies
		${PROJECT_SOURCE_DIR}/dependencies/MultiThread_Renderer2/include
		# ${PROJECT_SOURCE_DIR}/dependencies/MultiThread_Renderer2/dependencies/
)

file(GLOB SOURCES ${PROJECT_SOURCE_DIR}/src/*.cpp)
file(GLOB NESTEDSOURCES ${PROJECT_SOURCE_DIR}/src/*/*.cpp)
file(GLOB NESTEDSOURCES2 ${PROJECT_SOURCE_DIR}/src/*/*/*.cpp)
file(GLOB HEADERS ${PROJECT_SOURCE_DIR}/include/*.h)

set(CMAKE_CXX_STANDARD_LIBRARIES "-static ${CMAKE_CXX_STANDARD_LIBRARIES}")


add_subdirectory(${PROJECT_SOURCE_DIR}/dependencies/MultiThread_Renderer2)
add_executable(${PROJ_NAME} ${SOURCES} ${NESTEDSOURCES} ${NESTEDSOURCES2} ${HEADERS})
add_dependencies(${PROJ_NAME} MTR)

target_link_libraries(${PROJ_NAME} MTR)