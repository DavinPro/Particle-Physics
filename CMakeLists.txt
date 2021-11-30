cmake_minimum_required(VERSION 3.21)

# Default to release builds
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif()

# For generators with multiple configurations (like VS), only allow Debug and Release
if(CMAKE_CONFIGURATION_TYPES)
    set(CMAKE_CONFIGURATION_TYPES "Debug;Release" CACHE STRING "Limited configurations" FORCE)
    mark_as_advanced(CMAKE_CONFIGURATION_TYPES)
endif()

project(ParticlePhysics)

find_package(SFML 2 REQUIRED COMPONENTS graphics system window)
set(SFML_LIBS sfml-graphics sfml-system sfml-window)

file(GLOB SOURCES src/*.cpp)
add_executable(${PROJECT_NAME} ${SOURCES})
target_include_directories(${PROJECT_NAME} PRIVATE "include" "lib")

target_link_libraries(${PROJECT_NAME} ${SFML_LIBS})

set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 17)

if (UNIX)
   target_link_libraries(${PROJECT_NAME} pthread)
endif (UNIX)

# Copy DLLS to target output directory
add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
  COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_RUNTIME_DLLS:${PROJECT_NAME}> $<TARGET_FILE_DIR:${PROJECT_NAME}>
  COMMAND_EXPAND_LISTS
  )
