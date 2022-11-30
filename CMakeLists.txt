set(GENERATOR_NAME "MinGW Makefiles")
cmake_minimum_required(VERSION 3.17)
set(PROJ_NAME "MTR2_aslib")

set(CMAKE_C_COMPILER "D:/MinGW/GCC12.2_64/bin/gcc.exe")
set(CMAKE_CXX_COMPILER "D:/MinGW/GCC12.2_64/bin/g++.exe")

SET(CMAKE_CXX_FLAGS_RELEASE "-O0")
SET(CMAKE_C_FLAGS_RELEASE "-O0")

# set(CMAKE_BUILD_TYPE Release)

project(${PROJ_NAME})

set(STATIC_BUILD FALSE)

set(CMAKE_CXX_STANDARD 20)

if(CMAKE_SIZEOF_VOID_P EQUAL 4)
		set(architecture i686-w64)
elseif(CMAKE_SIZEOF_VOID_P EQUAL 8)
		set(architecture x86_64)
endif()

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin${CMAKE_BUILD_TYPE}_${architecture})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin${CMAKE_BUILD_TYPE}_${architecture})
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin${CMAKE_BUILD_TYPE}_${architecture})

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

set(MTR_SUBDIRECTORY "${PROJECT_SOURCE_DIR}/dependencies/MultiThread_Renderer2")
add_subdirectory("${MTR_SUBDIRECTORY}")

add_executable(${PROJ_NAME} ${SOURCES} ${NESTEDSOURCES} ${NESTEDSOURCES2} ${HEADERS})
add_dependencies(${PROJ_NAME} MTR)


target_link_libraries(${PROJ_NAME} MTR)


# execute_process(COMMAND ${CMAKE_COMMAND} -E make_directory "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/assets/")
execute_process(COMMAND ${CMAKE_COMMAND} -E copy_directory "${PROJECT_SOURCE_DIR}/assets/" "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/assets/")