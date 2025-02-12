#include <pybind11/pybind11.h>
#include <pybind11/pytypes.h>
#include <pybind11/stl.h>
#include <filesystem>
#include <optional>
#include <SFML/System.hpp>
#include <SFML/Audio.hpp>

namespace py = pybind11;

#ifdef _WIN32
#  define SFML_API __declspec(dllexport)
#else
#  define SFML_API
#endif

void bind_sound_channel(py::module& m);
void bind_listener(py::module& m);
void bind_sound_source(py::module& m);
void bind_sound_stream(py::module& m);
void bind_sound_buffer(py::module& m);
void bind_playback_device(py::module& m);
void bind_music(py::module& m);
void bind_sound(py::module& m);
void bind_sound_recorder(py::module& m);
void bind_sound_buffer_recorder(py::module& m);
void bind_input_sound_file(py::module& m);
void bind_output_sound_file(py::module& m);
