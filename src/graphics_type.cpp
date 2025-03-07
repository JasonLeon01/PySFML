#include <graphics_type.h>

void bind_glsl(py::module_ &m) {
    py::module_ glsl = m.def_submodule("Glsl");
    glsl.attr("Vec2") = m.attr("Vector2f");
    glsl.attr("Vec3") = m.attr("Vector3f");
    glsl.attr("Ivec2") = m.attr("Vector2i");
    glsl.attr("Ivec3") = m.attr("Vector3i");

    py::class_<sf::Glsl::Vec4>(glsl, "Vec4")
    .def(py::init<>())
    .def(py::init<float, float, float, float>(), py::arg("x"), py::arg("y"), py::arg("z"), py::arg("w"))
    .def_readwrite("x", &sf::Glsl::Vec4::x)
    .def_readwrite("y", &sf::Glsl::Vec4::y)
    .def_readwrite("z", &sf::Glsl::Vec4::z)
    .def_readwrite("w", &sf::Glsl::Vec4::w);

    py::class_<sf::Glsl::Ivec4>(glsl, "Ivec4")
    .def(py::init<>())
    .def(py::init<int, int, int, int>(), py::arg("x"), py::arg("y"), py::arg("z"), py::arg("w"))
    .def_readwrite("x", &sf::Glsl::Ivec4::x)
    .def_readwrite("y", &sf::Glsl::Ivec4::y)
    .def_readwrite("z", &sf::Glsl::Ivec4::z)
    .def_readwrite("w", &sf::Glsl::Ivec4::w);

    py::class_<sf::Glsl::Bvec2>(glsl, "Bvec2")
    .def(py::init<>())
    .def(py::init<bool, bool>(), py::arg("x"), py::arg("y"))
    .def_readwrite("x", &sf::Glsl::Bvec2::x)
    .def_readwrite("y", &sf::Glsl::Bvec2::y);

    py::class_<sf::Glsl::Bvec3>(glsl, "Bvec3")
    .def(py::init<>())
    .def(py::init<bool, bool, bool>(), py::arg("x"), py::arg("y"), py::arg("z"))
    .def_readwrite("x", &sf::Glsl::Bvec3::x)
    .def_readwrite("y", &sf::Glsl::Bvec3::y)
    .def_readwrite("z", &sf::Glsl::Bvec3::z);

    py::class_<sf::Glsl::Bvec4>(glsl, "Bvec4")
    .def(py::init<>())
    .def(py::init<bool, bool, bool, bool>(), py::arg("x"), py::arg("y"), py::arg("z"), py::arg("w"))
    .def_readwrite("x", &sf::Glsl::Bvec4::x)
    .def_readwrite("y", &sf::Glsl::Bvec4::y)
    .def_readwrite("z", &sf::Glsl::Bvec4::z)
    .def_readwrite("w", &sf::Glsl::Bvec4::w);

    py::class_<sf::Glsl::Mat3>(glsl, "Mat3")
    .def(py::init<>([](const std::vector<float>& pointer) {
       return sf::Glsl::Mat3(pointer.data());
    }), py::arg("pointer"))
    .def(py::init<const sf::Transform&>(), py::arg("transform"))
    .def_readwrite("array", &sf::Glsl::Mat3::array);

    py::class_<sf::Glsl::Mat4>(glsl, "Mat4")
    .def(py::init<>([](const std::vector<float>& pointer) {
        return sf::Glsl::Mat4(pointer.data());
    }), py::arg("pointer"))
    .def(py::init<const sf::Transform&>(), py::arg("transform"))
    .def_readwrite("array", &sf::Glsl::Mat4::array);
}

void bind_type(py::module_ &m) {
    py::enum_<sf::CoordinateType>(m, "CoordinateType")
    .value("Local", sf::CoordinateType::Normalized)
    .value("Pixels", sf::CoordinateType::Pixels)
    .export_values();

    py::enum_<sf::PrimitiveType>(m, "PrimitiveType")
    .value("Points", sf::PrimitiveType::Points)
    .value("Lines", sf::PrimitiveType::Lines)
    .value("LinesStrip", sf::PrimitiveType::LineStrip)
    .value("Triangles", sf::PrimitiveType::Triangles)
    .value("TrianglesStrip", sf::PrimitiveType::TriangleStrip)
    .value("TrianglesFan", sf::PrimitiveType::TriangleFan)
    .export_values();

    py::class_<sf::Drawable>(m, "Drawable"); // Pure virtual class
}
