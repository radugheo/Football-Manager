cmake_minimum_required(VERSION 3.15)

# NOTE: update executable name in .github/workflows/cmake.yml when changing executable name in this file
# for now, the project name is used as the executable name
project(oop)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

###############################################################################

# external dependencies
#include(FetchContent)
#
#FetchContent_Declare(
#        SomeLib
#        GIT_REPOSITORY https://github.com/<SomeUser>/<SomeLib>.git
#        GIT_TAG        <some_git_hash> # <which tag/branch @ <some_date>>
#)
#
#FetchContent_MakeAvailable(SomeLib)

include(FetchContent)

FetchContent_Declare(
        SFML
        GIT_REPOSITORY https://github.com/SFML/SFML.git
        GIT_TAG        2888d9c56eba4dedb93a84a3c57957e4a907d428 # master as of 2021-11-18
)

FetchContent_MakeAvailable(SFML)

###############################################################################

# NOTE: update executable name in .github/workflows/cmake.yml when changing name here
add_executable(${PROJECT_NAME} main.cpp sources/Player.cpp headers/Player.h sources/Team.cpp headers/Team.h sources/Game.cpp headers/Game.h sources/Transfer.cpp headers/Transfer.h sources/LoanTransfer.cpp headers/LoanTransfer.h sources/League.cpp headers/League.h sources/GameEngine.cpp headers/GameEngine.h sources/Menu.cpp headers/Menu.h sources/Button.cpp headers/Button.h sources/ListObject.cpp headers/ListObject.h)

#set(SFML_STATIC_LIBRARIES TRUE)
#set(SFML_DIR C:/SFML/lib/cmake/SFML)
#find_package(SFML COMPONENTS system window graphics audio network REQUIRED)
#include_directories(C:/SFML/include)
#target_link_libraries(${PROJECT_NAME} sfml-system sfml-window sfml-graphics sfml-audio)

###############################################################################

# custom compiler flags
message("Compiler: ${CMAKE_CXX_COMPILER_ID} version ${CMAKE_CXX_COMPILER_VERSION}")
if(MSVC)
    target_compile_options(${PROJECT_NAME} PRIVATE /W4 /WX /wd4244 /wd5999 /wd4267 /permissive-)
else()
    target_compile_options(${PROJECT_NAME} PRIVATE -Wall -Wextra -pedantic -Werror)

    if("${CMAKE_CXX_COMPILER_ID}" MATCHES "GNU")
    elseif("${CMAKE_CXX_COMPILER_ID}" MATCHES "Clang")
        target_compile_options(${PROJECT_NAME} PRIVATE -stdlib=libc++)
        target_link_options(${PROJECT_NAME} PRIVATE -stdlib=libc++)
    endif()
endif()

###############################################################################

# sanitizers
# should disable them when releasing executables
if(APPLE)
    # if("${CMAKE_CXX_COMPILER_ID}" MATCHES "Clang")
    # first check Apple since Apple is also a kind of Unix
    target_compile_options(${PROJECT_NAME} PRIVATE -fsanitize=address,undefined)
    target_link_options(${PROJECT_NAME} PRIVATE -fsanitize=address,undefined)
    # endif()
elseif(UNIX)
    if("${CMAKE_CXX_COMPILER_ID}" MATCHES "GNU")
        # we cannot mix sanitizers with Valgrind
    elseif("${CMAKE_CXX_COMPILER_ID}" MATCHES "Clang")
        if("${CMAKE_CXX_COMPILER_VERSION}" MATCHES "12.")
            # check leaks on Linux since macOS does not support the leaks sanitizer yet
            # leaks sanitizer is enabled by default on Linux, so we do not need to enable it explicitly
            target_compile_options(${PROJECT_NAME} PRIVATE -fsanitize=address,undefined)
            target_link_options(${PROJECT_NAME} PRIVATE -fsanitize=address,undefined)
        else()
            target_compile_options(${PROJECT_NAME} PRIVATE -fsanitize=memory,undefined -fsanitize-memory-track-origins)
            target_link_options(${PROJECT_NAME} PRIVATE -fsanitize=memory,undefined -fsanitize-memory-track-origins -Wl,-rpath,tools/llvm-project/build/lib)
        endif()
    endif()
endif()

###############################################################################

# use SYSTEM so clang-tidy does not report warnings from these directories
#target_include_directories(${PROJECT_NAME} SYSTEM PRIVATE ${<SomeLib>_SOURCE_DIR}/include)
#target_link_directories(${PROJECT_NAME} PRIVATE ${<SomeLib>_BINARY_DIR}/lib)
#target_link_libraries(${PROJECT_NAME} <SomeLib>)

function(sfml_set_custom_stdlib target)
    if(APPLE)
    elseif(UNIX)
        if("${CMAKE_CXX_COMPILER_ID}" MATCHES "Clang")
            target_compile_options(${target} PRIVATE "-stdlib=libc++")
            target_link_libraries(${target} PRIVATE "-stdlib=libc++")
        endif()
    endif()
endfunction()

FetchContent_MakeAvailable(SFML)

sfml_set_custom_stdlib(sfml-system)
sfml_set_custom_stdlib(sfml-window)
sfml_set_custom_stdlib(sfml-graphics)

###############################################################################

target_include_directories(${PROJECT_NAME} SYSTEM PRIVATE ${SFML_SOURCE_DIR}/include)
target_link_directories(${PROJECT_NAME} PRIVATE ${SFML_BINARY_DIR}/lib)
target_link_libraries(${PROJECT_NAME} sfml-graphics sfml-window sfml-system)
###############################################################################

target_include_directories(${PROJECT_NAME} SYSTEM PRIVATE ext/random/include)

# copy binaries to bin folder; these are uploaded as artifacts on each release
# install(DIRECTORY some_dir1 some_dir2 DESTINATION bin)
# install(FILES some_file1.txt some_file2.md DESTINATION bin)

install(TARGETS ${PROJECT_NAME} DESTINATION bin)
install(DIRECTORY resources DESTINATION bin)