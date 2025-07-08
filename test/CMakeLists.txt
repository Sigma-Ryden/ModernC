# [[Root]]
project(ModernCTesting)


# [[Binaries]]
file(GLOB_RECURSE PROJECT_TEST_SOURCES "${CMAKE_CURRENT_LIST_DIR}/*.c" "${CMAKE_CURRENT_LIST_DIR}/*.h")
add_executable("${PROJECT_NAME}" ${PROJECT_TEST_SOURCES})


# [[Dependencies]]
target_link_libraries("${PROJECT_NAME}" PRIVATE ModernC)
target_include_directories("${PROJECT_NAME}" PRIVATE "${CMAKE_CURRENT_LIST_DIR}")