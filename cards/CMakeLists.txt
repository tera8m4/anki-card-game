cmake_minimum_required(VERSION 3.14 FATAL_ERROR)

project(Cards LANGUAGES CXX)

if(NOT DEFINED ${PLATFORM})
    set(PLATFORM Desktop)
endif()

# --- Import tools ----

include(../cmake/tools.cmake)

# ---- Dependencies ----

include(../cmake/CPM.cmake)

CPMAddPackage(NAME raylib GITHUB_REPOSITORY raysan5/raylib GIT_TAG 5.0 OPTIONS "PLATFORM ${PLATFORM}" "CMAKE_BUILD_TYPE MinSizeRel")

# ---- Create standalone executable ----

file(GLOB sources CONFIGURE_DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/source/**/*.cpp ${CMAKE_CURRENT_SOURCE_DIR}/source/*.cpp)

add_executable(${PROJECT_NAME} ${sources})
target_link_libraries(${PROJECT_NAME} raylib)

target_include_directories(
  ${PROJECT_NAME} PUBLIC $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
                         $<INSTALL_INTERFACE:include/${PROJECT_NAME}-${PROJECT_VERSION}>
)

file(CREATE_LINK ${CMAKE_CURRENT_SOURCE_DIR}/assets ${CMAKE_CURRENT_BINARY_DIR}/assets SYMBOLIC)
