#include <pybind11/pybind11.h>
#include <pybind11/pytypes.h>
#include <pybind11/stl.h>
#include <filesystem>
#include <optional>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>

namespace py = pybind11;

#ifdef _WIN32
#  define SFML_API __declspec(dllexport)
#else
#  define SFML_API
#endif

void bind_enum(py::module_ &m);
void bind_context(py::module_& m);
void bind_cursor(py::module_& m);
void bind_event(py::module_& m);
void bind_video_mode(py::module_& m);
