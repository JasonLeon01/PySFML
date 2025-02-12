#include <pybind11/pybind11.h>
#include <pybind11/pytypes.h>
#include <pybind11/stl.h>
#include <filesystem>
#include <optional>
#include <SFML/System.hpp>

namespace py = pybind11;

#ifdef _WIN32
#  define SFML_API __declspec(dllexport)
#else
#  define SFML_API
#endif

void bind_angle(py::module_& m);
void bind_time(py::module_& m);
void bind_clock(py::module_& m);

template <typename T>
void bind_vector2(py::module &m, const std::string &name) {
    py::class_<sf::Vector2<T>>(m, name.c_str())
    .def(py::init<>())
    .def(py::init<T, T>())
    .def(py::init([](py::tuple vec2) {
        auto [x1, x2] = vec2.cast<std::tuple<T, T>>();
        return sf::Vector2<T>(x1, x2);
    }), py::arg("tuple"))
    .def("__add__", [](sf::Vector2<T> left, sf::Vector2<T> right) {
        left += right;
        return left;
    })
    .def("__sub__", [](sf::Vector2<T> left, sf::Vector2<T> right) {
        left -= right;
        return left;
    })
    .def("__mul__", [](sf::Vector2<T> left, T right) {
        left.x *= right;
        left.y *= right;
        return left; 
    })
    .def("__truediv__", [](sf::Vector2<T> left, T right) {
        left.x /= right;
        left.y /= right;
        return left;
    })
    .def("__eq__", [](sf::Vector2<T> left, sf::Vector2<T> right) {
        return left.x == right.x && left.y == right.y;
    })
    .def("__ne__", [](sf::Vector2<T> left, sf::Vector2<T> right) {
        return left.x != right.x || left.y != right.y;
    })
    .def("__repr__", [](const sf::Vector2<T> &v) {
        return "<sf.Vector2: (" + std::to_string(v.x) + ", " + std::to_string(v.y) + ")>"; 
    })
    .def_readwrite("x", &sf::Vector2<T>::x)
    .def_readwrite("y", &sf::Vector2<T>::y);
}

template <typename T>
void bind_vector3(py::module &m, const std::string &name) {
    py::class_<sf::Vector3<T>>(m, name.c_str())
   .def(py::init<>())
   .def(py::init<T, T, T>())
   .def(py::init([](py::tuple vec3) {
        auto [x1, x2, x3] = vec3.cast<std::tuple<T, T, T>>();
        return sf::Vector3<T>(x1, x2, x3);
    }), py::arg("tuple"))
    .def("__add__", [](sf::Vector3<T> left, sf::Vector3<T> right) {
        left += right;
        return left;
    })
    .def("__sub__", [](sf::Vector3<T> left, sf::Vector3<T> right) {
        left -= right;
        return left;
    })
   .def("__mul__", [](sf::Vector3<T> left, T right) {
        left.x *= right;
        left.y *= right;
        left.z *= right;
        return left;
    })
    .def("__truediv__", [](sf::Vector3<T> left, T right) {
        left.x /= right;
        left.y /= right;
        left.z /= right;
        return left;
    })
    .def("__eq__", [](sf::Vector3<T> left, sf::Vector3<T> right) {
        return left.x == right.x && left.y == right.y && left.z == right.z;
    })
    .def("__ne__", [](sf::Vector3<T> left, sf::Vector3<T> right) {
        return left.x!= right.x || left.y!= right.y || left.z!= right.z;
    })
    .def("__repr__", [](const sf::Vector3<T> &v) {
        return "<sf.Vector3: (" + std::to_string(v.x) + ", " + std::to_string(v.y) + ", " + std::to_string(v.z) + ")>";
    })
    .def_readwrite("x", &sf::Vector3<T>::x)
    .def_readwrite("y", &sf::Vector3<T>::y)
    .def_readwrite("z", &sf::Vector3<T>::z);
}

void bind_input_stream(py::module_& m);
