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

void bind_blend_mode(py::module_& m);
void bind_transform(py::module& m);
void bind_transformable(py::module& m);
void bind_vertex(py::module& m);
void bind_shape(py::module_ &m);
void bind_color(py::module_& m);
void bind_font(py::module_& m);
void bind_glyph(py::module_& m);
