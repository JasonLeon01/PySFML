cmake_minimum_required (VERSION 3.8)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project ("pysf")

set(SFML_DIR ${CMAKE_SOURCE_DIR}/SFML-3.0.0)
set(PYBIND11_DIR ${CMAKE_SOURCE_DIR}/pybind11-master)

if(CMAKE_SYSTEM_NAME STREQUAL "Windows")
    set(PYTHON_DIR "path/to/python")
    set(PYTHON_EXECUTABLE "${PYTHON_DIR}/python.exe")
elseif(CMAKE_SYSTEM_NAME STREQUAL "Linux")
    set(PYTHON_DIR "/usr")
    set(PYTHON_EXECUTABLE "/usr/bin/python3.9")
elseif(CMAKE_SYSTEM_NAME STREQUAL "Darwin")
    set(PYTHON_DIR "/usr/local")
    set(PYTHON_EXECUTABLE "/usr/bin/python3.9")
else()
    message(FATAL_ERROR "Unsupported platform: ${CMAKE_SYSTEM_NAME}")
endif()

execute_process(
    COMMAND ${PYTHON_EXECUTABLE} --version
    OUTPUT_VARIABLE PYTHON_VERSION_OUTPUT
    ERROR_VARIABLE PYTHON_VERSION_OUTPUT
    RESULT_VARIABLE PYTHON_VERSION_RESULT
)

if(NOT PYTHON_VERSION_RESULT EQUAL 0 OR NOT PYTHON_VERSION_OUTPUT MATCHES "Python 3.9.0")
    message(FATAL_ERROR "Python version must be 3.9.0. Found: ${PYTHON_VERSION_OUTPUT}")
endif()

message(STATUS "Using Python: ${PYTHON_EXECUTABLE}, Version: ${PYTHON_VERSION_OUTPUT}")

include_directories(${SFML_DIR}/include)
link_directories(${SFML_DIR}/lib)
add_subdirectory(${PYBIND11_DIR})
include_directories(${PYTHON_DIR}/include)
link_directories(${PYTHON_DIR}/libs)
include_directories(${CMAKE_SOURCE_DIR}/include)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
set(CMAKE_CXX_FLAGS_RELEASE "-O3 -DNDEBUG -s -flto")
set(CMAKE_EXE_LINKER_FLAGS "-flto")

add_library(pysf SHARED
                "src/main.cpp"
                "src/system.cpp"
                "src/window_base.cpp"
                "src/window.cpp"
                "src/graphics_type.cpp"
                "src/graphics_base.cpp"
                "src/graphics_render.cpp"
                "src/graphics_core.cpp"
                "src/audio.cpp"
                "src/network.cpp")

if(CMAKE_SYSTEM_NAME STREQUAL "Windows")
    set(TARGET_SUFFIX ".pyd")
elseif(CMAKE_SYSTEM_NAME STREQUAL "Linux")
    set(TARGET_SUFFIX ".so")
elseif(CMAKE_SYSTEM_NAME STREQUAL "Darwin")
    set(TARGET_SUFFIX ".so")
else()
    message(FATAL_ERROR "Unsupported platform: ${CMAKE_SYSTEM_NAME}")
endif()

set_target_properties(pysf PROPERTIES
    PREFIX ""
    SUFFIX ${TARGET_SUFFIX}
    LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
)

if(CMAKE_SYSTEM_NAME STREQUAL "Windows")
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
else()
    target_link_libraries(pysf
        sfml-system
        sfml-window
        sfml-graphics
        sfml-audio
        sfml-network
        pybind11::module
        -Wl,-rpath=${PYTHON_DIR}/libs
    )
endif()


add_custom_command(TARGET pysf POST_BUILD
    COMMAND ${CMAKE_STRIP} --strip-all $<TARGET_FILE:pysf>
)
