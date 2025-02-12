cmake_minimum_required (VERSION 3.8)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project ("pysf")

set(SFML_DIR ${CMAKE_SOURCE_DIR}/SFML-3.0.0)
set(PYBIND11_DIR ${CMAKE_SOURCE_DIR}/pybind11-master)
set(PYTHON_DIR "path/to/python")
set(PYTHON_EXECUTABLE "${PYTHON_DIR}/python.exe")

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
                "src/graphics_base.cpp" 
                "src/graphics_render.cpp" 
                "src/graphics_core.cpp" 
                "src/audio.cpp" 
                "src/network.cpp")

set_target_properties(pysf PROPERTIES 
    PREFIX ""
    SUFFIX ".pyd"
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