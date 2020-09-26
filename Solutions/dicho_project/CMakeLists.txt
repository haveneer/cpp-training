cmake_minimum_required(VERSION 3.12)
# bypass common config this directory is used as subdirectory
if (NOT CPP_TRAINING_SOURCE_DIR)
    # if not added as add_subdirectory from main code directory
    project(dicho)
    set(CMAKE_CXX_STANDARD 11)

    # to enable shared lib in WIN32
    # cf    https://github.com/google/googletest/tree/master/googletest#incorporating-into-an-existing-cmake-project
    #   and https://stackoverflow.com/questions/12540970/how-to-make-gtest-build-mdd-instead-of-mtd-by-default-using-cmake
    set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
    add_subdirectory(third_party/googletest)
    include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})
    include(CTest)
endif ()

add_executable(dicho main.cpp f.cpp f.hpp dicho.cpp dicho.hpp)
add_test(NAME DichoMain COMMAND dicho)

add_executable(dicho_tests dicho_tests.cpp f.cpp f.hpp dicho.cpp dicho.hpp)
target_link_libraries(dicho_tests PUBLIC gtest gtest_main)
target_include_directories(dicho_tests PUBLIC ${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})
add_test(NAME DichoTest COMMAND dicho_tests)
set_property(TEST DichoTest PROPERTY LABELS "GTest")

