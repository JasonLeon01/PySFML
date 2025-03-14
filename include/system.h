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
    .def(py::init([](int x, int y) {
        return sf::Vector2<T>(x, y);
    }), py::arg("x"), py::arg("y"))
    .def(py::init([](float x, float y) {
        return sf::Vector2<T>(x, y);
    }), py::arg("x"), py::arg("y"))
    .def(py::init([](unsigned int x, unsigned int y) {
        return sf::Vector2<T>(x, y);
    }), py::arg("x"), py::arg("y"))
    .def(py::init([](py::tuple vec2) {
        auto [x1, x2] = vec2.cast<std::tuple<T, T>>();
        return sf::Vector2<T>(x1, x2);
    }), py::arg("tuple"))
    .def("to_int", [](sf::Vector2<T> vec2) {
        return sf::Vector2<int>(vec2.x, vec2.y);
    })
    .def("to_float", [](sf::Vector2<T> vec2) {
        return sf::Vector2<float>(vec2.x, vec2.y);
    })
    .def("to_uint", [](sf::Vector2<T> vec2) {
        return sf::Vector2<unsigned int>(vec2.x, vec2.y);
    })
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
    .def("__iadd__", [](sf::Vector2<T> &left, sf::Vector2<T> right) -> sf::Vector2<T>& {
        left += right;
        return left;
    })
    .def("__isub__", [](sf::Vector2<T> &left, sf::Vector2<T> right) -> sf::Vector2<T>& {
        left -= right;
        return left;
    })
    .def("__imul__", [](sf::Vector2<T> &left, T right) -> sf::Vector2<T>& {
        left.x *= right;
        left.y *= right;
        return left;
    })
    .def("__itruediv__", [](sf::Vector2<T> &left, T right) -> sf::Vector2<T>& {
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
    .def_property("x",
        [](const sf::Vector2<T> &v) { return v.x; },
        [](sf::Vector2<T> &v, T value) { v.x = value; }
        , py::return_value_policy::reference)
    .def_property("y",
        [](const sf::Vector2<T> &v) { return v.y; },
        [](sf::Vector2<T> &v, T value) { v.y = value; }
        , py::return_value_policy::reference);
}

template <typename T>
void bind_vector3(py::module &m, const std::string &name) {
    py::class_<sf::Vector3<T>>(m, name.c_str())
   .def(py::init<>())
   .def(py::init([](int x, int y, int z) {
        return sf::Vector3<T>(x, y, z);
    }), py::arg("x"), py::arg("y"), py::arg("z"))
    .def(py::init([](float x, float y, float z) {
        return sf::Vector3<T>(x, y, z);
    }), py::arg("x"), py::arg("y"), py::arg("z"))
    .def(py::init([](unsigned int x, unsigned int y, unsigned int z) {
        return sf::Vector3<T>(x, y, z);
    }), py::arg("x"), py::arg("y"), py::arg("z"))
    .def(py::init([](py::tuple vec3) {
        auto [x1, x2, x3] = vec3.cast<std::tuple<T, T, T>>();
        return sf::Vector3<T>(x1, x2, x3);
    }), py::arg("tuple"))
    .def("to_int", [](sf::Vector3<T> vec3) {
        return sf::Vector3<int>(vec3.x, vec3.y, vec3.z);
    })
    .def("to_float", [](sf::Vector3<T> vec3) {
        return sf::Vector3<float>(vec3.x, vec3.y, vec3.z);
    })
    .def("to_uint", [](sf::Vector3<T> vec3) {
        return sf::Vector3<unsigned int>(vec3.x, vec3.y, vec3.z);
    })
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
    .def("__iadd__", [](sf::Vector3<T> &left, sf::Vector3<T> right) -> sf::Vector3<T>& {
        left += right;
        return left;
    })
    .def("__isub__", [](sf::Vector3<T> &left, sf::Vector3<T> right) -> sf::Vector3<T>& {
        left -= right;
        return left;
    })
    .def("__imul__", [](sf::Vector3<T> &left, T right) -> sf::Vector3<T>& {
        left.x *= right;
        left.y *= right;
        left.z *= right;
        return left;
    })
    .def("__itruediv__", [](sf::Vector3<T> &left, T right) -> sf::Vector3<T>& {
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
    .def_property("x",
        [](const sf::Vector3<T> &v) { return v.x; },
        [](sf::Vector3<T> &v, T value) { v.x = value; }
        , py::return_value_policy::reference)
    .def_property("y",
        [](const sf::Vector3<T> &v) { return v.y; },
        [](sf::Vector3<T> &v, T value) { v.y = value; }
        , py::return_value_policy::reference)
    .def_property("z",
        [](const sf::Vector3<T> &v) { return v.z; },
        [](sf::Vector3<T> &v, T value) { v.z = value; }
        , py::return_value_policy::reference);
}

void bind_input_stream(py::module_& m);
