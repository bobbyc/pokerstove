cmake_minimum_required(VERSION 2.8)

PROJECT(peval-c)

find_package (Threads)

# build the test
file(GLOB test_sources *.test.cpp)
add_executable(${PROJECT_NAME}_tests ${test_sources})
target_link_libraries(${PROJECT_NAME}_tests ${PROJECT_NAME}-s gtest gtest_main ${CMAKE_THREAD_LIBS_INIT})

# build the library sources from all sources, removing the test sources
file(GLOB lib_sources *.cpp)
foreach(source_file ${test_sources})
  list(REMOVE_ITEM lib_sources ${source_file})
endforeach()

# peval library
add_library( ${PROJECT_NAME}-s STATIC ${lib_sources})
TARGET_LINK_LIBRARIES( ${PROJECT_NAME}-s peval penum)

add_library( ${PROJECT_NAME} SHARED ${lib_sources})
TARGET_LINK_LIBRARIES( ${PROJECT_NAME} peval penum)

add_test(TestCPeval ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${PROJECT_NAME}_tests)
