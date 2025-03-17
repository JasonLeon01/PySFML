#include <graphics_base.h>

void bind_blend_mode(py::module_ &m) {
    py::class_<sf::BlendMode> blend_mode(m, "BlendMode");

    py::enum_<sf::BlendMode::Factor>(blend_mode, "Factor")
    .value("Zero", sf::BlendMode::Factor::Zero)
    .value("One", sf::BlendMode::Factor::One)
    .value("SrcColor", sf::BlendMode::Factor::SrcColor)
    .value("OneMinusSrcColor", sf::BlendMode::Factor::OneMinusSrcColor)
    .value("DstColor", sf::BlendMode::Factor::DstColor)
    .value("OneMinusDstColor", sf::BlendMode::Factor::OneMinusDstColor)
    .value("SrcAlpha", sf::BlendMode::Factor::SrcAlpha)
    .value("OneMinusSrcAlpha", sf::BlendMode::Factor::OneMinusSrcAlpha)
    .value("DstAlpha", sf::BlendMode::Factor::DstAlpha)
    .value("OneMinusDstAlpha", sf::BlendMode::Factor::OneMinusDstAlpha)
    .export_values();

    py::enum_<sf::BlendMode::Equation>(blend_mode, "Equation")
    .value("Add", sf::BlendMode::Equation::Add)
    .value("Subtract", sf::BlendMode::Equation::Subtract)
    .value("ReverseSubtract", sf::BlendMode::Equation::ReverseSubtract)
    .value("Min", sf::BlendMode::Equation::Min)
    .value("Max", sf::BlendMode::Equation::Max)
    .export_values();

    blend_mode.def(py::init<>())
    .def(py::init<sf::BlendMode::Factor, sf::BlendMode::Factor, sf::BlendMode::Equation>(),
         "Constructor with source and destination factors and blend equation",
         py::arg("sourceFactor"), py::arg("destinationFactor"), py::arg("blendEquation") = sf::BlendMode::Equation::Add)
    .def(py::init<sf::BlendMode::Factor, sf::BlendMode::Factor, sf::BlendMode::Equation,
                  sf::BlendMode::Factor, sf::BlendMode::Factor, sf::BlendMode::Equation>(),
         "Constructor with separate color and alpha factors and blend equations",
         py::arg("colorSourceFactor"), py::arg("colorDestinationFactor"), py::arg("colorBlendEquation"),
         py::arg("alphaSourceFactor"), py::arg("alphaDestinationFactor"), py::arg("alphaBlendEquation"))
    .def_readwrite("color_src_factor", &sf::BlendMode::colorSrcFactor)
    .def_readwrite("color_dst_factor", &sf::BlendMode::colorDstFactor)
    .def_readwrite("color_equation", &sf::BlendMode::colorEquation)
    .def_readwrite("alpha_src_factor", &sf::BlendMode::alphaSrcFactor)
    .def_readwrite("alpha_dst_factor", &sf::BlendMode::alphaDstFactor)
    .def_readwrite("alpha_equation", &sf::BlendMode::alphaEquation);

    m.attr("blend_alpha") = sf::BlendAlpha;
    m.attr("blend_add") = sf::BlendAdd;
    m.attr("blend_multiply") = sf::BlendMultiply;
    m.attr("blend_min") = sf::BlendMin;
    m.attr("blend_max") = sf::BlendMax;
    m.attr("blend_none") = sf::BlendNone;
}

void bind_transform(py::module& m) {
    py::class_<sf::Transform>(m, "Transform")
    .def(py::init<>())
    .def(py::init<float, float, float, float, float, float, float, float, float>())
    .def("get_matrix", &sf::Transform::getMatrix)
    .def("get_inverse", &sf::Transform::getInverse)
    .def("transform_point", &sf::Transform::transformPoint, py::arg("point"))
    .def("transform_rect", &sf::Transform::transformRect, py::arg("rect"))
    .def("combine", &sf::Transform::combine, py::arg("transform"))
    .def("translate", &sf::Transform::translate, py::arg("offset"))
    .def("rotate", static_cast<sf::Transform& (sf::Transform::*)(sf::Angle)>(&sf::Transform::rotate), py::arg("angle"))
    .def("rotate", static_cast<sf::Transform& (sf::Transform::*)(sf::Angle, sf::Vector2f)>(&sf::Transform::rotate), py::arg("angle"), py::arg("center"))
    .def("scale", py::overload_cast<sf::Vector2f>(&sf::Transform::scale), py::arg("factors"))
    .def("scale", py::overload_cast<sf::Vector2f, sf::Vector2f>(&sf::Transform::scale), py::arg("factors"), py::arg("center"))
    .def_static("identity", []() {
       return sf::Transform::Identity;
    })
    .def("__mul__", [] (
        const sf::Transform& left, const sf::Transform& right) {
            return left * right;
        }
    )
    .def("__imul__", [](sf::Transform& left, const sf::Transform& right) {
       return left *= right;
    })
    .def("__eq__", [](const sf::Transform& left, const sf::Transform& right) {
       return left == right;
    })
    .def("__ne__", [](const sf::Transform& left, const sf::Transform& right) {
       return left!= right;
    });
}

void bind_transformable(py::module& m) {
    py::class_<sf::Transformable>(m, "Transformable")
    .def(py::init<>())
    .def("set_position", &sf::Transformable::setPosition, py::arg("position"))
    .def("set_rotation", &sf::Transformable::setRotation, py::arg("angle"))
    .def("set_scale", &sf::Transformable::setScale, py::arg("factors"))
    .def("set_origin", &sf::Transformable::setOrigin, py::arg("origin"))
    .def("get_position", &sf::Transformable::getPosition)
    .def("get_rotation", &sf::Transformable::getRotation)
    .def("get_scale", &sf::Transformable::getScale)
    .def("get_origin", &sf::Transformable::getOrigin)
    .def("move", &sf::Transformable::move, py::arg("offset"))
    .def("rotate", &sf::Transformable::rotate, py::arg("angle"))
    .def("scale", &sf::Transformable::scale, py::arg("factors"))
    .def("get_transform", &sf::Transformable::getTransform)
    .def("get_inverse_transform", &sf::Transformable::getInverseTransform);
}

void bind_vertex(py::module& m) {
    py::class_<sf::Vertex>(m, "Vertex")
    .def(py::init<>())
    .def(py::init<sf::Vector2f, sf::Color, sf::Vector2f>(), py::arg("position"), py::arg("color"), py::arg("texCoords"))
    .def_readwrite("position", &sf::Vertex::position)
    .def_readwrite("color", &sf::Vertex::color)
    .def_readwrite("texCoords", &sf::Vertex::texCoords);

    py::class_<sf::VertexArray, sf::Drawable>(m, "VertexArray")
    .def(py::init<>())
    .def(py::init<sf::PrimitiveType, std::size_t>(), py::arg("type"), py::arg("vertexCount") = 0)
    .def("__getitem__", [](sf::VertexArray &self, std::size_t index) -> sf::Vertex & {
        if (index >= self.getVertexCount()) {
            throw py::index_error("Index out of range");
        }
        return self[index];
    }, py::return_value_policy::reference)
    .def("__setitem__", [](sf::VertexArray &self, std::size_t index, const sf::Vertex &vertex) {
        if (index >= self.getVertexCount()) {
            throw py::index_error("Index out of range");
        }
        self[index] = vertex;
    })
    .def("__len__", &sf::VertexArray::getVertexCount)
    .def("get_vertex_count", &sf::VertexArray::getVertexCount)
    .def("clear", &sf::VertexArray::clear)
    .def("resize", &sf::VertexArray::resize, py::arg("vertexCount"))
    .def("append", &sf::VertexArray::append, py::arg("vertex"))
    .def("set_primitive_type", &sf::VertexArray::setPrimitiveType, py::arg("type"))
    .def("get_primitive_type", &sf::VertexArray::getPrimitiveType)
    .def("get_bounds", &sf::VertexArray::getBounds);

    py::class_<sf::VertexBuffer, sf::Drawable> vertex_buffer(m, "VertexBuffer");

    py::enum_<sf::VertexBuffer::Usage>(vertex_buffer, "Usage")
    .value("Stream", sf::VertexBuffer::Usage::Stream)
    .value("Dynamic", sf::VertexBuffer::Usage::Dynamic)
    .value("Static", sf::VertexBuffer::Usage::Static)
    .export_values();

    vertex_buffer.def(py::init<>())
    .def(py::init<sf::PrimitiveType>())
    .def(py::init<sf::VertexBuffer::Usage>())
    .def(py::init<sf::PrimitiveType, sf::VertexBuffer::Usage>())
    .def("create", &sf::VertexBuffer::create, py::arg("vertexCount"))
    .def("get_vertex_count", &sf::VertexBuffer::getVertexCount)
    .def("update", py::overload_cast<const sf::Vertex*>(&sf::VertexBuffer::update), py::arg("vertices"))
    .def("update", py::overload_cast<const sf::Vertex*, std::size_t, unsigned int>(&sf::VertexBuffer::update), py::arg("vertices"), py::arg("vertexCount"), py::arg("offset"))
    .def("update", py::overload_cast<const sf::VertexBuffer&>(&sf::VertexBuffer::update), py::arg("vertexBuffer"))
    .def("set_primitive_type", &sf::VertexBuffer::setPrimitiveType, py::arg("type"))
    .def("get_primitive_type", &sf::VertexBuffer::getPrimitiveType)
    .def("set_usage", &sf::VertexBuffer::setUsage, py::arg("usage"))
    .def("get_usage", &sf::VertexBuffer::getUsage)
    .def("get_native_handle", &sf::VertexBuffer::getNativeHandle)
    .def_static("bind", &sf::VertexBuffer::bind, py::arg("buffer"))
    .def_static("is_available", &sf::VertexBuffer::isAvailable)
    .def("__copy__", [](const sf::VertexBuffer &self) { return sf::VertexBuffer(self); })
    .def("__deepcopy__", [](const sf::VertexBuffer &self, py::dict) { return sf::VertexBuffer(self); });
}


void bind_shape(py::module_ &m) {
    py::class_<sf::Shape, sf::Transformable, sf::Drawable>(m, "Shape")
    .def("set_texture", &sf::Shape::setTexture, py::arg("texture"), py::arg("resetRect") = false)
    .def("set_texture_rect", &sf::Shape::setTextureRect, py::arg("rect"))
    .def("set_fill_color", &sf::Shape::setFillColor, py::arg("color"))
    .def("set_outline_color", &sf::Shape::setOutlineColor, py::arg("color"))
    .def("set_outline_thickness", &sf::Shape::setOutlineThickness, py::arg("thickness"))
    .def("get_texture", &sf::Shape::getTexture)
    .def("get_texture_rect", &sf::Shape::getTextureRect)
    .def("get_fill_color", &sf::Shape::getFillColor)
    .def("get_outline_color", &sf::Shape::getOutlineColor)
    .def("get_outline_thickness", &sf::Shape::getOutlineThickness)
    .def("get_point_count", &sf::Shape::getPointCount)
    .def("get_point", &sf::Shape::getPoint)
    .def("get_geometric_center", &sf::Shape::getGeometricCenter)
    .def("get_local_bounds", &sf::Shape::getLocalBounds)
    .def("get_global_bounds", &sf::Shape::getGlobalBounds);
}

void bind_color(py::module_ &m) {
    py::class_<sf::Color>(m, "Color")
    .def(py::init<std::uint8_t, std::uint8_t, std::uint8_t, std::uint8_t>(),
         py::arg("red"), py::arg("green"), py::arg("blue"), py::arg("alpha") = 255)
    .def(py::init<std::uint32_t>(), py::arg("color"))
    .def("to_integer", &sf::Color::toInteger)
    .def_readwrite("r", &sf::Color::r)
    .def_readwrite("g", &sf::Color::g)
    .def_readwrite("b", &sf::Color::b)
    .def_readwrite("a", &sf::Color::a)
    .def_static("black", []() { return sf::Color::Black; })
    .def_static("white", []() { return sf::Color::White; })
    .def_static("red", []() { return sf::Color::Red; })
    .def_static("green", []() { return sf::Color::Green; })
    .def_static("blue", []() { return sf::Color::Blue; })
    .def_static("yellow", []() { return sf::Color::Yellow; })
    .def_static("magenta", []() { return sf::Color::Magenta; })
    .def_static("cyan", []() { return sf::Color::Cyan; })
    .def_static("transparent", []() { return sf::Color::Transparent; })
    .def("__eq__", [](const sf::Color& left, const sf::Color& right) {
        return left.r == right.r && left.g == right.g && left.b == right.b && left.a == right.a;
    })
    .def("__ne__", [](const sf::Color& left, const sf::Color& right) {
        return left.r != right.r || left.g != right.g || left.b != right.b || left.a != right.a;
    })
    .def("__add__", [](const sf::Color& left, const sf::Color& right) {
        return sf::Color(left.r + right.r, left.g + right.g, left.b + right.b, left.a + right.a);
    })
    .def("__sub__", [](const sf::Color& left, const sf::Color& right) {
        return sf::Color(left.r - right.r, left.g - right.g, left.b - right.b, left.a - right.a);
    })
    .def("__mul__", [](const sf::Color& left, float right) {
        return sf::Color(static_cast<std::uint8_t>(left.r * right),
                         static_cast<std::uint8_t>(left.g * right),
                         static_cast<std::uint8_t>(left.b * right),
                         static_cast<std::uint8_t>(left.a * right));
    })
    .def("__iadd__", [](sf::Color& left, const sf::Color& right) {
        left.r += right.r;
        left.g += right.g;
        left.b += right.b;
        left.a += right.a;
        return left;
    })
   .def("__isub__", [](sf::Color& left, const sf::Color& right) {
        left.r -= right.r;
        left.g -= right.g;
        left.b -= right.b;
        left.a -= right.a;
        return left;
    })
   .def("__imul__", [](sf::Color& left, float right) {
        left.r = static_cast<std::uint8_t>(left.r * right);
        left.g = static_cast<std::uint8_t>(left.g * right);
        left.b = static_cast<std::uint8_t>(left.b * right);
   });
}

void bind_font(py::module_ &m) {
    py::class_<sf::Font> font(m, "Font");

    py::class_<sf::Font::Info>(font, "Info")
    .def(py::init<>())
    .def_readwrite("family", &sf::Font::Info::family);

    font.def(py::init<>())
    .def(py::init<const void*, std::size_t>(), py::arg("data"), py::arg("sizeInBytes"))
    .def(py::init<sf::InputStream&>(), py::arg("stream"))
    .def(py::init<>([](const std::string &filename) {
        return sf::Font(filename);
    }), py::arg("filename"))

    .def("open_from_file", [](sf::Font &self, const std::string &filename) {
        return self.openFromFile(filename);
    }, py::arg("filename"))
    .def("open_from_memory", &sf::Font::openFromMemory, py::arg("data"), py::arg("sizeInBytes"))
    .def("open_from_stream", &sf::Font::openFromStream, py::arg("stream"))

    .def("get_info", &sf::Font::getInfo)

    .def("get_glyph", [](sf::Font &self, unsigned int codePoint, unsigned int characterSize, bool bold, float outlineThickness) {
        return self.getGlyph(codePoint, characterSize, bold, outlineThickness);
    }, py::arg("codePoint"), py::arg("characterSize"), py::arg("bold"), py::arg("outlineThickness") = 0.0f)
    .def("has_glyph", [](sf::Font &self, unsigned int codePoint) {
        return self.hasGlyph(codePoint);
    }, py::arg("codePoint"))

    .def("get_kerning", &sf::Font::getKerning, py::arg("first"), py::arg("second"), py::arg("characterSize"), py::arg("bold") = false)
    .def("get_line_spacing", &sf::Font::getLineSpacing, py::arg("characterSize"))
    .def("get_underline_position", &sf::Font::getUnderlinePosition, py::arg("characterSize"))
    .def("get_underline_thickness", &sf::Font::getUnderlineThickness, py::arg("characterSize"))

    .def("set_smooth", &sf::Font::setSmooth, py::arg("smooth"))
    .def("is_smooth", &sf::Font::isSmooth)

    .def("get_texture", &sf::Font::getTexture, py::arg("characterSize"));
}

void bind_glyph(py::module_ &m) {
    py::class_<sf::Glyph>(m, "Glyph")
    .def(py::init<>())
    .def_readwrite("advance", &sf::Glyph::advance)
    .def_readwrite("lsb_delta", &sf::Glyph::lsbDelta)
    .def_readwrite("rsb_delta", &sf::Glyph::rsbDelta)
    .def_readwrite("bounds", &sf::Glyph::bounds)
    .def_readwrite("texture_rect", &sf::Glyph::textureRect);
}
