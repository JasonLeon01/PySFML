cmake_minimum_required(VERSION 3.8...3.27)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project ("pysf")

set(SFML_DIR ${CMAKE_SOURCE_DIR}/SFML-3.0.0)
set(PYBIND11_DIR ${CMAKE_SOURCE_DIR}/pybind11)

find_package(Python3 3.10.0 EXACT REQUIRED COMPONENTS Interpreter Development)
if(NOT Python3_FOUND)
    message(FATAL_ERROR "Python 3.10.0 not found")
endif()

get_filename_component(PYTHON_DIR "${Python3_EXECUTABLE}" DIRECTORY)

message(STATUS "Python Dir: ${PYTHON_DIR}")
message(STATUS "Python include dirs: ${Python3_INCLUDE_DIRS}")
message(STATUS "Python libraries: ${Python3_LIBRARIES}")

add_subdirectory(${SFML_DIR})
if (CMAKE_SYSTEM_NAME STREQUAL "Windows")
    if (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
        include_directories(${SFML_DIR}/include)
        link_directories(${PYTHON_DIR}/libs)
    endif()
    set(TARGET_SUFFIX ".pyd")
elseif (CMAKE_SYSTEM_NAME STREQUAL "Darwin")
    set(FETCHCONTENT_QUIET OFF)
    set(TARGET_SUFFIX ".so")
else()
    message(FATAL_ERROR "Unsupported platform: ${CMAKE_SYSTEM_NAME}")
endif()

add_subdirectory(${PYBIND11_DIR})
include_directories(${PYTHON_DIR}/include)
include_directories(${CMAKE_SOURCE_DIR}/include)

set(CMAKE_BUILD_TYPE Release)
if (CMAKE_SYSTEM_NAME STREQUAL "Windows" AND MSVC)
    set(CMAKE_CXX_FLAGS_RELEASE "/O2 /DNDEBUG")
else()
    set(CMAKE_CXX_FLAGS_RELEASE "-O3 -DNDEBUG -s -flto")
endif()

add_library(pysf SHARED
                "src/utils.cpp"
                "src/main.cpp"
                "src/system.cpp"
                "src/window_base.cpp"
                "src/window_event.cpp"
                "src/window.cpp"
                "src/graphics_type.cpp"
                "src/graphics_base.cpp"
                "src/graphics_render.cpp"
                "src/graphics_core.cpp"
                "src/audio.cpp"
                "src/network.cpp")

set_target_properties(pysf PROPERTIES
    PREFIX ""
    SUFFIX ${TARGET_SUFFIX}
    LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
)

if(CMAKE_SYSTEM_NAME STREQUAL "Darwin")
    set_target_properties(pysf PROPERTIES
        INSTALL_RPATH "@loader_path"
        BUILD_WITH_INSTALL_RPATH TRUE
        MACOSX_RPATH TRUE
    )
endif()

target_link_libraries(pysf PRIVATE
    sfml-system
    sfml-window
    sfml-graphics
    sfml-audio
    sfml-network
    Python3::Python
    pybind11::module
)

if(CMAKE_SYSTEM_NAME STREQUAL "Windows")
    if (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
        target_link_libraries(pysf PRIVATE
            -Wl,-rpath=${PYTHON_DIR}/libs
        )
        add_custom_command(TARGET pysf POST_BUILD
            COMMAND ${CMAKE_STRIP} --strip-all $<TARGET_FILE:pysf>
        )
    endif()
elseif(CMAKE_SYSTEM_NAME STREQUAL "Darwin")
    add_custom_command(TARGET pysf POST_BUILD
        COMMAND ${CMAKE_STRIP} -x $<TARGET_FILE:pysf>
    )
endif()
