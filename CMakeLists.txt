cmake_minimum_required (VERSION 3.8)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project ("pysf")

set(SFML_DIR ${CMAKE_SOURCE_DIR}/SFML-3.0.0)
set(PYBIND11_DIR ${CMAKE_SOURCE_DIR}/pybind11)

find_package(Python3 3.9.0 EXACT REQUIRED COMPONENTS Interpreter Development)
if(NOT Python3_FOUND)
    message(FATAL_ERROR "Python 3.9.0 not found")
endif()

get_filename_component(PYTHON_DIR "${Python3_EXECUTABLE}" DIRECTORY)
set(PYTHON_EXECUTABLE ${Python3_EXECUTABLE})

message(STATUS "Python Dir: ${PYTHON_DIR}")
message(STATUS "Using Python: ${PYTHON_EXECUTABLE}")
message(STATUS "Python include dirs: ${Python3_INCLUDE_DIRS}")
message(STATUS "Python libraries: ${Python3_LIBRARIES}")

include_directories(${SFML_DIR}/include)
link_directories(${SFML_DIR}/lib)
add_subdirectory(${PYBIND11_DIR})
include_directories(${PYTHON_DIR}/include)
link_directories(${PYTHON_DIR}/libs)
include_directories(${CMAKE_SOURCE_DIR}/include)

set(CMAKE_BUILD_TYPE Release)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
set(CMAKE_CXX_FLAGS_RELEASE "-O3 -DNDEBUG -s -flto")
set(CMAKE_EXE_LINKER_FLAGS "-flto")

add_library(pysf SHARED
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

if(CMAKE_SYSTEM_NAME STREQUAL "Windows")
    set(TARGET_SUFFIX ".pyd")
else()
    message(FATAL_ERROR "Unsupported platform: ${CMAKE_SYSTEM_NAME}")
endif()

set_target_properties(pysf PROPERTIES
    PREFIX ""
    SUFFIX ${TARGET_SUFFIX}
    LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
)

target_link_libraries(pysf
    sfml-system
    sfml-window
    sfml-graphics
    sfml-audio
    sfml-network
    "${PYTHON_DIR}/libpython39.a"
    pybind11::module
    -Wl,-rpath=${PYTHON_DIR}/libs
)

add_custom_command(TARGET pysf POST_BUILD
    COMMAND ${CMAKE_STRIP} --strip-all $<TARGET_FILE:pysf>
)
