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

void bind_base_window(py::module_& m);
void bind_window(py::module_& m);
void bind_clipboard(py::module_& m);
void bind_joystick(py::module_& m);
void bind_keyboard(py::module_& m);
void bind_mouse(py::module_& m);
void bind_sensor(py::module_& m);
void bind_touch(py::module_& m);