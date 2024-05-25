cmake_minimum_required(VERSION 3.14 FATAL_ERROR)

project(Cards LANGUAGES CXX)

if(NOT DEFINED ${PLATFORM})
    set(PLATFORM Desktop)
endif()

# --- Import tools ----

include(../cmake/tools.cmake)

# ---- Dependencies ----

include(../cmake/CPM.cmake)

find_package(OpenSSL REQUIRED)

CPMAddPackage(NAME raylib GITHUB_REPOSITORY raysan5/raylib GIT_TAG 5.0 OPTIONS "PLATFORM ${PLATFORM}" "CMAKE_BUILD_TYPE MinSizeRel")
CPMAddPackage(NAME cpp-httplib GITHUB_REPOSITORY yhirose/cpp-httplib GIT_TAG v0.15.3 OPTIONS "HTTPLIB_USE_OPENSSL TRUE")
CPMAddPackage(
  NAME nlohmann_json
  GIT_REPOSITORY https://github.com/nlohmann/json
  GIT_TAG v3.11.2  # You can specify the version you need
)
CPMAddPackage(
  NAME spdlog
  GIT_REPOSITORY https://github.com/gabime/spdlog.git
  GIT_TAG v1.14.1 # Specify the version you want to use
)
# ---- Create standalone executable ----

file(GLOB sources CONFIGURE_DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/source/**/*.cpp ${CMAKE_CURRENT_SOURCE_DIR}/source/*.cpp)

add_executable(${PROJECT_NAME} ${sources})
target_link_libraries(${PROJECT_NAME} PRIVATE raylib httplib::httplib nlohmann_json::nlohmann_json OpenSSL::SSL OpenSSL::Crypto spdlog)

target_include_directories(
  ${PROJECT_NAME} PUBLIC $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
                         $<INSTALL_INTERFACE:include/${PROJECT_NAME}-${PROJECT_VERSION}>
)

file(CREATE_LINK ${CMAKE_CURRENT_SOURCE_DIR}/assets ${CMAKE_CURRENT_BINARY_DIR}/assets SYMBOLIC)

# Find and copy OpenSSL DLLs dynamically
if (WIN32)
    # Define the directory where OpenSSL DLLs are located
    set(OPENSSL_BIN_DIR "${OPENSSL_ROOT_DIR}/bin")

    # Find all DLL files in the OpenSSL bin directory
    file(GLOB OPENSSL_DLLS "${OPENSSL_BIN_DIR}/*.dll")

    # Copy each DLL to the runtime output directory
    foreach(OPENSSL_DLL ${OPENSSL_DLLS})
        add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy_if_different
            ${OPENSSL_DLL}
            $<TARGET_FILE_DIR:${PROJECT_NAME}>)
    endforeach()
endif()
