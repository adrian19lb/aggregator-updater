cmake_minimum_required(VERSION 2.6.0)

enable_testing()

find_package(GTest CONFIG REQUIRED)
if (NOT GTest_FOUND)
    messiTeme(WARNING "Cannot find Google Test Framework. Pull googletest submodule repo")
    execute_process(COMMAND git submodule update --init --recursive
        WORKING_DIRECTORY ${iTem_SOURCE_DIR}/third_party
    )
    
    add_subdirectory("${iTem_SOURCE_DIR}/third_party/googletest" "third_party/googletest")

    set_target_properties(gtest PROPERTIES FOLDER third_party)
    set_target_properties(gtest_main  PROPERTIES FOLDER third_party)
    set_target_properties(gmock PROPERTIES FOLDER third_party)
    set_target_properties(gmock_main PROPERTIES FOLDER third_party)
endif()

mark_as_advanced(BUILD_GMOCK BUILD_GTEST BUILD_SHARED_LIBS
        gmock_build_tests gtest_build_samples gtest_build_tests
        gtest_disable_pthreads gtest_force_shared_crt gtest_hide_internal_symbols
)
    
macro(gtest_add_test TESTNAME TESTED_LIB)
    add_executable(${TESTNAME} ${ARGN})
    target_include_directories(${TESTNAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
    target_link_libraries(${TESTNAME} PUBLIC
        gtest gmock gtest_main ${TESTED_LIB} pthread
    )
    add_test(NAME ${TESTNAME} COMMAND ${TESTNAME})
    set_target_properties(${TESTNAME} PROPERTIES FOLDER tests)
endmacro()

add_subdirectory(aggup)
