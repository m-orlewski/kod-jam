cmake_minimum_required(VERSION 3.11) # FetchContent is available in 3.11+
project(
	kod-jam
	DESCRIPTION "some game"
	HOMEPAGE_URL "github.com/jaenek/kod-jam"
)

add_library(project_options INTERFACE)
target_compile_features(project_options INTERFACE cxx_std_17)

if (NOT raylib_FOUND)
  include(FetchContent)
  FetchContent_Declare(
    raylib
    URL https://github.com/raysan5/raylib/archive/master.tar.gz
  )

  FetchContent_GetProperties(raylib)
  if (NOT raylib_POPULATED)
    set(FETCHCONTENT_QUIET NO)
    FetchContent_Populate(raylib)

    set(BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
	# set(GRAPHICS="GRAPHICS_API_OPENGL_11")
    add_subdirectory(${raylib_SOURCE_DIR} ${raylib_BINARY_DIR})
  endif()
endif()

if (EMSCRIPTEN)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -s USE_GLFW=3 -s ASSERTIONS=1 -s WASM=1 -s ASYNCIFY --preload-file assets/ --preload-file resources/")
    set(CMAKE_EXECUTABLE_SUFFIX ".html") # This line is used to set your executable to build with the emscripten html template so taht you can directly open it.
endif ()

# This is the main part:
file(GLOB PROJECT_SOURCES
	src/*/*.cpp
	src/main.cpp
)
add_executable(${PROJECT_NAME} ${PROJECT_SOURCES})
target_compile_definitions(${PROJECT_NAME} PRIVATE GLSL_VERSION=100)
target_include_directories(${PROJECT_NAME} PRIVATE ${raylib_SOURCE_DIR}/src)
target_link_libraries(${PROJECT_NAME} PRIVATE project_options raylib)

# copy resources ands assets
file(GLOB ASSETS assets/*.png)
file(COPY ${ASSETS} DESTINATION assets)
file(COPY resources DESTINATION .)