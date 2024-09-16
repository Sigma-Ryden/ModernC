# base
cmake_minimum_required(VERSION 3.5)

project(ModernCTesting LANGUAGES C)
# ~base

# packages
set(ModernC_DIR ${CMAKE_CURRENT_LIST_DIR}/cmake)
find_package(ModernC REQUIRED)
# ~packages

# test
include_directories(test)

file(GLOB_RECURSE ${PROJECT_NAME}_TEST_SOURCES test/*.c)
file(GLOB_RECURSE ${PROJECT_NAME}_TEST_HEADERS test/*.h) # optionaly

add_executable(${PROJECT_NAME}
    ${${PROJECT_NAME}_TEST_SOURCES}
    ${${PROJECT_NAME}_TEST_HEADERS} # optionaly
    ${Modern_C_HEADER_FILES} # optionaly
)
target_link_libraries(${PROJECT_NAME} ModernC)
# ~test
