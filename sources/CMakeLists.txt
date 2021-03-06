cmake_minimum_required(VERSION 3.13)

project(cppmathlib VERSION 0.1.0 LANGUAGES CXX)

include(FetchContent)


# define build types and configurations
# --------------------------------------- #
if (CMAKE_CONFIGURATION_TYPES)
    if (NOT "Test" IN_LIST CMAKE_CONFIGURATION_TYPES)
        list(APPEND CMAKE_CONFIGURATION_TYPES Test)
    endif()
else()
    set(allowableBuildTypes Debug Test Release)
    set_property(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS "${allowableBuildTypes}")
    if (NOT CMAKE_BUILD_TYPE)
        set(CMAKE_BUILD_TYPE Release CACHE STRING "" FORCE)
    elseif(NOT CMAKE_BUILD_TYPE IN_LIST allowableBuildTypes)
        message(FATAL_ERROR "Invalid build type ${CMAKE_BUILD_TYPE}") 
    endif()
endif()

set(CMAKE_TEST_POSTFIX _tests)

set(CMAKE_CXX_FLAGS "-Wall -Wextra")
set(CMAKE_CXX_FLAGS_RELEASE "-O3")

# use c++17
# --------------------------------------- #
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# libraries
# --------------------------------------- #
add_library(tao src/linalg/dyn/Mat.cpp src/linalg/dyn/Col.cpp src/linalg/dyn/Row.cpp src/geometry/geometry.cpp)
target_include_directories(tao PUBLIC include)

# executables
# --------------------------------------- #

# test definitions
# use googletest framework
# --------------------------------------- #
FetchContent_Declare(googletest
    GIT_REPOSITORY  https://github.com/google/googletest.git
    GIT_TAG         2fe3bd994b3189899d93f1d5a881e725e046fdc2 # 1.8.1
)
FetchContent_GetProperties(googletest)
if (NOT googletest_POPULATED)
    FetchContent_Populate(googletest)
    add_subdirectory(${googletest_SOURCE_DIR} ${googletest_BINARY_DIR})
endif()

include(GoogleTest)

set(test_sources ${test_sources}
    tests/main.cpp
    tests/mat_tests.cpp
    tests/col_tests.cpp
    tests/row_tests.cpp
    tests/comp_mat_tests.cpp
    tests/comp_dyn_mat_tests.cpp
    tests/linalg_operations_tests.cpp
)

add_executable(taomaintest ${test_sources})
target_link_libraries(taomaintest PRIVATE gtest PRIVATE tao)
target_include_directories(taomaintest PRIVATE include)

gtest_discover_tests(taomaintest)

enable_testing()
