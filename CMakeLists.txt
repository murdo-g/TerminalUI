cmake_minimum_required(VERSION 3.11)

# Project name
project(TerminalUI)

string(TOLOWER ${PROJECT_NAME} LIB_NAME)

# Generate compile_commands.json for clangd
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Request C++ 11 standard features
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Make sure the compiler looks here for source files
include_directories(/usr/local/include)
link_directories(/usr/local/lib)

# --- Fetch FTXUI --------------------------------------------------------------
include(FetchContent)
 
set(FETCHCONTENT_UPDATES_DISCONNECTED TRUE)
FetchContent_Declare(ftxui
    GIT_REPOSITORY https://github.com/ArthurSonzogni/ftxui
    # Specify a GIT_TAG here.
)
 
FetchContent_GetProperties(ftxui)
if(NOT ftxui_POPULATED)
    FetchContent_Populate(ftxui)
    add_subdirectory(${ftxui_SOURCE_DIR} ${ftxui_BINARY_DIR} EXCLUDE_FROM_ALL)
endif()
 
# ------------------------------------------------------------------------------


### SOURCE CODE ###

# Get a list of source files
file(GLOB SRCS ${PROJECT_SOURCE_DIR}/src/*.cpp)

# Library of all source code
add_library(${LIB_NAME} ${SRCS})

# Put compiled library in bin
set_target_properties(${LIB_NAME} PROPERTIES ARCHIVE_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin)

# Include the include/ directory for downstream projects
include_directories(${PROJECT_SOURCE_DIR}/include)

target_link_libraries(${LIB_NAME} 
    ftxui::screen
    ftxui::dom
    ftxui::component)

set_target_properties(${LIB_NAME} PROPERTIES CXX_STANDARD 17)


### UNIT TESTING ###

# Enable `make test` command
enable_testing()

# Enable test output on failure
set(CTEST_OUTPUT_ON_FAILURE TRUE)

# Make sure the compiler looks in the src directory
include_directories(${PROJECT_SOURCE_DIR}/src)
include_directories(${PROJECT_SOURCE_DIR}/test/framework)
include_directories(ftxui)

# Include test files
file(GLOB TEST_SRCS ${PROJECT_SOURCE_DIR}/test/*.cpp)
# Run through each test file
foreach(testSrc ${TEST_SRCS})
    # Get extension-less file name
    get_filename_component(testName ${testSrc} NAME_WE)
    # Add target
    add_executable(${testName} ${testSrc})
    # Link to source code
    target_link_libraries(${testName} 
        ${LIB_NAME}
        ftxui::screen
        ftxui::dom
        ftxui::component
        )
    # Put test executables in their own directory
    set_target_properties(${testName} PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/test/bin)

    set_target_properties(${testName} PROPERTIES CXX_STANDARD 17)
    # Add test to CTest execution
    add_test(
        NAME ${testName}
        WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}/test/bin
        COMMAND ${testName}
    )
endforeach(testSrc)

# project(terminalui-demo
#   LANGUAGES CXX
#   VERSION 1.0.0
# )

# add_executable(terminalui-demo example/demo.cpp)
 
# target_link_libraries(terminalui-demo
#     PUBLIC
#     ${LIB_NAME}
#     PRIVATE ftxui::screen
#     PRIVATE ftxui::dom
#     PRIVATE ftxui::component # Not needed for this example.
# )
 
# # C++17 is used. We requires fold expressions at least.
# set_target_properties(terminalui-demo PROPERTIES CXX_STANDARD 17)

add_executable(lubadh_interface example/lubadh_demo.cpp)
 
target_link_libraries(lubadh_interface
    PUBLIC
    ${LIB_NAME}
    PRIVATE ftxui::screen
    PRIVATE ftxui::dom
    PRIVATE ftxui::component # Not needed for this example.
)
 
# C++17 is used. We requires fold expressions at least.
set_target_properties(lubadh_interface PROPERTIES CXX_STANDARD 17)
