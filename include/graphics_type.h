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

void bind_glsl(py::module_ &m);
void bind_type(py::module_ &m);

template <typename T>
void bind_rect(py::module_ &m, const std::string &class_name) {
    py::class_<sf::Rect<T>>(m, class_name.c_str())
    .def(py::init<>())
    .def(py::init<sf::Vector2<T>, sf::Vector2<T>>(), py::arg("position"), py::arg("size"))
    .def(py::init([](py::tuple rect) {
        auto [x, y, w, h] = rect.cast<std::tuple<T, T, T, T>>();
        return sf::Rect<T>(sf::Vector2<T>(x, y), sf::Vector2<T>(w, h));
    }), py::arg("tuple"))
    .def("to_int", [](sf::Rect<T> rect) {
        return sf::Rect<int>(sf::Vector2<int>(rect.position.x, rect.position.y), sf::Vector2<int>(rect.size.x, rect.size.y));
    })
    .def("to_float", [](sf::Rect<T> rect) {
        return sf::Rect<float>(sf::Vector2<float>(rect.position.x, rect.position.y), sf::Vector2<float>(rect.size.x, rect.size.y));
    })
    .def("left", [](sf::Rect<T> &rect) { return rect.position.x; })
    .def("top", [](sf::Rect<T> &rect) { return rect.position.y; })
    .def("right", [](sf::Rect<T> &rect) { return rect.position.x + rect.size.x; })
    .def("bottom", [](sf::Rect<T> &rect) { return rect.position.y + rect.size.y; })
    .def("width", [](sf::Rect<T> &rect) { return rect.size.x; })
    .def("height", [](sf::Rect<T> &rect) { return rect.size.y; })
    .def("contains", &sf::Rect<T>::contains, py::arg("point"))
    .def("find_intersection", &sf::Rect<T>::findIntersection, py::arg("rectangle"))
    .def("get_center", &sf::Rect<T>::getCenter)
    .def("__repr__", [](const sf::Rect<T> &r) {
        return "<sf.Rect: (" + std::to_string(r.position.x) + ", " + std::to_string(r.position.y) + ", " + std::to_string(r.size.x) + ", " + std::to_string(r.size.y) + ")>";
    })
    .def_readwrite("position", &sf::Rect<T>::position)
    .def_readwrite("size", &sf::Rect<T>::size);
}

