cmake_minimum_required(VERSION 3.10)
project(addon)

set(CMAKE_CXX_STANDARD 14)

include_directories(${CMAKE_JS_INC})
file(GLOB SOURCE_FILES "src/*.cpp" "src/*.h")

add_library(${PROJECT_NAME} SHARED ${SOURCE_FILES})
set_target_properties(${PROJECT_NAME} PROPERTIES PREFIX "" SUFFIX ".node")
target_link_libraries(${PROJECT_NAME} ${CMAKE_JS_LIB})

# macOS-specific framework
find_library(APPLICATION_SERVICES_FRAMEWORK ApplicationServices)
message(STATUS "ApplicationServices found at: ${APPLICATION_SERVICES_FRAMEWORK}")
target_link_libraries(${PROJECT_NAME} ${APPLICATION_SERVICES_FRAMEWORK})
