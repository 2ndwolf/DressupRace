set(GENERATOR_NAME "MinGW Makefiles")
cmake_minimum_required(VERSION 3.17)
set(PROJ_NAME "MTR2_aslib")

set(MINGW_PATH "D:/MinGW/GCC12.2_64/bin")
set(CMAKE_C_COMPILER   "${MINGW_PATH}/gcc.exe")
set(CMAKE_CXX_COMPILER "${MINGW_PATH}/g++.exe")

SET(CMAKE_CXX_FLAGS_RELEASE "-fkeep-inline-functions")
SET(CMAKE_C_FLAGS_RELEASE "-fkeep-inline-functions")
# SET(CMAKE_CXX_FLAGS_DEBUG "-fkeep-inline-functions")
# SET(CMAKE_C_FLAGS_RELEASE "-O0")

project(MTR2_aslib VERSION 1.2.0.0)
message(STATUS "---- ${CMAKE_BUILD_TYPE}")


set(STATIC_BUILD FALSE)

set(CMAKE_CXX_STANDARD 20)

if(CMAKE_SIZEOF_VOID_P EQUAL 4)
		set(architecture i686-w64)
elseif(CMAKE_SIZEOF_VOID_P EQUAL 8)
		set(architecture x86_64)
# if not compiling, just use the x86_64 includes
# else()
# 	set(sdl_p_folder x86_64-w64-mingw32)	
endif()

configure_file(
	${PROJECT_SOURCE_DIR}/metadata.txt
	${PROJECT_BINARY_DIR}/versioninfo.rc
)
configure_file(
	${PROJECT_SOURCE_DIR}/run.txt
	${PROJECT_BINARY_DIR}/run.bat
)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin${CMAKE_BUILD_TYPE}_${architecture})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin${CMAKE_BUILD_TYPE}_${architecture})
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin${CMAKE_BUILD_TYPE}_${architecture})

include_directories(
		${PROJECT_SOURCE_DIR}/include
		${PROJECT_SOURCE_DIR}/dependencies
		${PROJECT_SOURCE_DIR}/dependencies/MultiThread_Renderer2/include
		${PROJECT_SOURCE_DIR}/dependencies/MultiThread_Renderer2/include/components
		${PROJECT_SOURCE_DIR}/dependencies/AISAF/include
		# ${PROJECT_SOURCE_DIR}/dependencies/MultiThread_Renderer2/dependencies/
)

file(GLOB SOURCES        ${PROJECT_SOURCE_DIR}/src/*.cpp    )
file(GLOB NESTEDSOURCES  ${PROJECT_SOURCE_DIR}/src/*/*.cpp  )
file(GLOB NESTEDSOURCES2 ${PROJECT_SOURCE_DIR}/src/*/*/*.cpp)
file(GLOB HEADERS        ${PROJECT_SOURCE_DIR}/include/*.h  )
set (EXEINFO             ${PROJECT_SOURCE_DIR}/versioninfo.o)

set(CMAKE_CXX_STANDARD_LIBRARIES "-static ${CMAKE_CXX_STANDARD_LIBRARIES}")

set(MTR_SUBDIRECTORY "${PROJECT_SOURCE_DIR}/dependencies/MultiThread_Renderer2")
add_subdirectory("${MTR_SUBDIRECTORY}")
set(AISAF_SUBDIRECTORY "${PROJECT_SOURCE_DIR}/dependencies/AISAF")
add_subdirectory("${AISAF_SUBDIRECTORY}")

add_executable(${PROJ_NAME} ${SOURCES} ${NESTEDSOURCES} ${NESTEDSOURCES2} ${HEADERS} ${EXEINFO})
add_dependencies(${PROJ_NAME} MTR AISAF)


target_link_libraries(${PROJ_NAME} MTR AISAF)


# execute_process(COMMAND ${CMAKE_COMMAND} -E make_directory "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/assets/")
execute_process(COMMAND ${CMAKE_COMMAND} -E copy_directory "${PROJECT_SOURCE_DIR}/assets/" "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/assets/")

add_custom_command(TARGET ${PROJECT_NAME} PRE_BUILD
  COMMAND windres versioninfo.rc -o versioninfo.o
	VERBATIM)

