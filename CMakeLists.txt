cmake_minimum_required(VERSION 3.10)

# set the project name and version
project(SimpleGameEngine VERSION 1.0)

# specify the C++ standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

option(BUILD_SHARED_LIBS "Build using shared libraries" ON)

message("PROJECT - CMakeLists ")
message("   - PROJECT BINARY : " ${PROJECT_BINARY_DIR})
message("   - CMAKE PREFIX PATH : " ${CMAKE_CURRENT_SOURCE_DIR})
message("")

message("FIND PACKAGES :")

#set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake-build-debug/")

INCLUDE(FindPkgConfig)

PKG_SEARCH_MODULE(SDL2 REQUIRED sdl2)
PKG_SEARCH_MODULE(SDL2IMAGE REQUIRED SDL2_image>=2.0.0)
PKG_SEARCH_MODULE(SDL2TTF REQUIRED SDL2_ttf>=2.0.0)

#find_package(SDL2 REQUIRED)
find_package(SDL2 REQUIRED)
#find_package(SDL2_image REQUIRED)
message(" > SDL2")
message("   - SDL2_LIBRARIES : ${SDL2_LIBRARIES} --- ${SDL2IMAGE_LIBRARIES} --- ${SDL2TTF_LIBRARIES}")
message("   - SDL2_INCLUDE_DIRS : ${SDL2_INCLUDE_DIRS} --- ${SDL2IMAGE_INCLUDE_DIRS} --- ${SDL2TTF_INCLUDE_DIRS}")

find_package(Lua 5.4 REQUIRED)
message(" > LUA")
message("   - LUA_LIBRARIES : ${LUA_LIBRARIES}")
message("   - LUA_INCLUDE_DIR : ${LUA_INCLUDE_DIR}")
message("")

add_subdirectory(${CMAKE_SOURCE_DIR}/include/sol)
list(APPEND EXTRA_LIBS sol)

add_subdirectory(${CMAKE_SOURCE_DIR}/include/glm)
list(APPEND EXTRA_LIBS glm_static)

include_directories(
        ${PROJECT_SOURCE_DIR}/assets/
        ${PROJECT_SOURCE_DIR}/include/
        ${PROJECT_SOURCE_DIR}/src/
        ${SDL2_INCLUDE_DIRS}
        ${SDL2IMAGE_INCLUDE_DIRS}
        ${SDL2TTF_INCLUDE_DIRS}
        ${LUA_INCLUDE_DIR}
)

file(COPY assets DESTINATION ${CMAKE_BINARY_DIR})
set(BINARY ${CMAKE_PROJECT_NAME})
file(GLOB_RECURSE SOURCES LIST_DIRECTORIES true ./src/*.h ./src/*.cpp)

#file(GLOB_RECURSE REMOVE_SOURCES "./src/main.cpp")
#list(REMOVE_ITEM SOURCES ${REMOVE_SOURCES})

set(SOURCES ${SOURCES})


add_library(SimpleGameEngineLib STATIC ${SOURCES})
target_link_libraries(SimpleGameEngineLib
        ${EXTRA_LIBS}
        ${LUA_LIBRARIES}
        ${SDL2_LIBRARIES}
        ${SDL2IMAGE_LIBRARIES}
        ${SDL2TTF_LIBRARIES}
)

## During development this executable is used for real test.
add_executable(SimpleGameEngine ${SOURCES})
target_link_libraries(SimpleGameEngine
        ${EXTRA_LIBS}
        ${LUA_LIBRARIES}
        ${SDL2_LIBRARIES}
        ${SDL2IMAGE_LIBRARIES}
        ${SDL2TTF_LIBRARIES}
)

add_subdirectory(${PROJECT_SOURCE_DIR}/tests)

