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

void bind_type(py::module_ &m);

template <typename T>
void bind_rect(py::module_ &m, const std::string &class_name) {
    py::class_<sf::Rect<T>>(m, class_name.c_str())
    .def(py::init<>())
    .def(py::init<sf::Vector2<T>, sf::Vector2<T>>(), py::arg("position"), py::arg("size"))
    .def("contains", &sf::Rect<T>::contains, py::arg("point"))
    .def("find_intersection", &sf::Rect<T>::findIntersection, py::arg("rectangle"))
    .def("get_center", &sf::Rect<T>::getCenter)
    .def_readwrite("position", &sf::Rect<T>::position)
    .def_readwrite("size", &sf::Rect<T>::size);
}

void bind_blend_mode(py::module_& m);
void bind_transform(py::module& m);
void bind_transformable(py::module& m);
void bind_vertex(py::module& m);
void bind_shape(py::module_ &m);
void bind_color(py::module_& m);
void bind_font(py::module_& m);
void bind_glyph(py::module_& m);
void bind_image(py::module_& m);
