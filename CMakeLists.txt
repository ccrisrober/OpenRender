cmake_minimum_required(VERSION 2.8)
project(opengl-template)

option(GLFW_BUILD_DOCS OFF)
option(GLFW_BUILD_EXAMPLES OFF)
option(GLFW_BUILD_TESTS OFF)
add_subdirectory(lib/glfw)

option(ASSIMP_BUILD_ASSIMP_TOOLS OFF)
option(ASSIMP_BUILD_SAMPLES OFF)
option(ASSIMP_BUILD_TESTS OFF)
add_subdirectory(lib/assimp)

list(APPEND CMAKE_CXX_FLAGS "-std=c++11")
add_definitions(-Wall)

add_definitions(-DGLEW_STATIC)
option(glew-cmake_BUILD_SHARED "" OFF)
add_subdirectory(lib/glew)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W4")

include_directories(
	lib/assimp/include/
	lib/glfw/include/
	lib/glm/
	lib/glew/include/
	lib/glew/src/)

file(GLOB PROJECT_HEADERS 
	src/*.h
	src/**/*.h
)
file(GLOB PROJECT_SOURCES 
	src/*.cpp
	src/**/*.cpp
)
file(GLOB PROJECT_SOIL
	src/SOIL/*.h
	src/SOIL/*.c
)
file(GLOB PROJECT_SHADERS 
	shaders/*.vert
	shaders/*.frag
	shaders/*.geom
	shaders/*.comp
	shaders/*.tcs
	shaders/*.tes

	shaders/**/*.vert
	shaders/**/*.frag
	shaders/**/*.geom
	shaders/**/*.comp
	shaders/**/*.tcs
	shaders/**/*.tes
)
file(GLOB PROJECT_CONFIGS 
	CMakeList.txt 
	.gitattributes 
	.gitignore 
	.gitmodules
)

source_group("Headers" FILES ${PROJECT_HEADERS}) 
source_group("Shaders" FILES ${PROJECT_SHADERS})
source_group("Sources" FILES ${PROJECT_SOURCES})
source_group("SOIL" FILES ${PROJECT_SOIL})

add_definitions(-DGLFW_INCLUDE_NONE
                -DPROJECT_SOURCE_DIR=\"${PROJECT_SOURCE_DIR}\")
add_executable(${PROJECT_NAME} ${PROJECT_SOURCES} ${PROJECT_HEADERS}
                               ${PROJECT_SHADERS} ${PROJECT_SOIL})
target_link_libraries(${PROJECT_NAME} assimp glfw ${GLFW_LIBRARIES} libglew_static)
set_target_properties(${PROJECT_NAME} PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/${PROJECT_NAME})