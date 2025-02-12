#include <pybind11/pybind11.h>
#include <pybind11/pytypes.h>
#include <pybind11/stl.h>
#include <filesystem>
#include <optional>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

namespace py = pybind11;

#ifdef _WIN32
#  define SFML_API __declspec(dllexport)
#else
#  define SFML_API
#endif

void bind_render_states(py::module_& m);
void bind_render_target(py::module_& m);
void bind_render_texture(py::module_& m);
void bind_render_window(py::module_& m);
void bind_shader(py::module_& m);
