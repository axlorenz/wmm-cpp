# 1. Minimale CMake-Version festlegen
cmake_minimum_required(VERSION 3.20)

# 2. Name des Projekts und unterstützte Programmiersprachen
project(wmm VERSION 0.1.0 LANGUAGES CXX)

# 3. Add static library wmm
add_library(wmm STATIC 
    src/magnetic_field.cpp
    src/wmm_model.cpp
)

# 4. Make target c++20
target_compile_features(wmm PUBLIC cxx_std_20)

# 5. Include directories
target_include_directories(wmm
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include
    PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src
)

# 6. add cli-executable
add_executable(wmm_cli examples/wmm_cli.cpp)

# 7. link executable against lib
target_link_libraries(wmm_cli PRIVATE wmm)

# 8. disable extensions
set_target_properties(wmm PROPERTIES CXX_EXTENSIONS OFF)

include(CTest)

if(BUILD_TESTING)

    find_package(GTest CONFIG REQUIRED)

    add_executable(wmm_tests
        tests/wmm_tests.cpp
    )

    target_link_libraries(wmm_tests
        PRIVATE
        wmm
        GTest::gtest_main
    )

    target_include_directories(wmm_tests
    PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src
)

    include(GoogleTest)
    gtest_discover_tests(wmm_tests)
endif()
