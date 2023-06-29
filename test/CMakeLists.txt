

file(GLOB HEADERS "${CMAKE_CURRENT_LIST_DIR}/*.h")
file(GLOB SOURCES "${CMAKE_CURRENT_LIST_DIR}/*.cpp")

add_executable(Google_Tests_run ${SOURCES})
target_link_libraries(Google_Tests_run gtest gtest_main)
target_compile_definitions(Google_Tests_run PRIVATE GRENDER_DEBUG_BUILD)