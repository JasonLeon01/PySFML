#include <graphics_core.h>

void bind_texture(py::module& m) {
    py::class_<sf::Texture>(m, "Texture")
    .def(py::init<>())
    .def(py::init([](const std::string& filename, bool s_rgb, const sf::IntRect& area) {
        sf::Texture texture(filename, s_rgb, area);
        return texture;
    }), py::arg("filename"), py::arg("s_rgb") = false, py::arg("area") = sf::IntRect{})
    .def(py::init<const void*, std::size_t, bool>(), py::arg("data"), py::arg("size"), py::arg("s_rgb") = false)
    .def(py::init<const void*, std::size_t, bool, const sf::IntRect&>(), py::arg("data"), py::arg("size"), py::arg("s_rgb") = false, py::arg("area"))
    .def(py::init<sf::InputStream&, bool>(), py::arg("stream"), py::arg("s_rgb") = false)
    .def(py::init<sf::InputStream&, bool, const sf::IntRect&>(), py::arg("stream"), py::arg("s_rgb") = false, py::arg("area"))
    .def(py::init<const sf::Image&, bool>(), py::arg("image"), py::arg("s_rgb") = false)
    .def(py::init<const sf::Image&, bool, const sf::IntRect&>(), py::arg("image"), py::arg("s_rgb") = false, py::arg("area"))
    .def(py::init<sf::Vector2u, bool>(), py::arg("size"), py::arg("s_rgb") = false)
    .def("resize", &sf::Texture::resize, py::arg("size"), py::arg("s_rgb") = false)
    .def("load_from_file", [](sf::Texture& self, const std::string& filename, bool s_rgb, const sf::IntRect& area) {
       return self.loadFromFile(filename, s_rgb, area);
    }, py::arg("filename"), py::arg("s_rgb") = false, py::arg("area") = sf::IntRect{})
    .def("load_from_memory", &sf::Texture::loadFromMemory, py::arg("data"), py::arg("size"), py::arg("s_rgb") = false, py::arg("area") = sf::IntRect{})
    .def("load_from_stream", &sf::Texture::loadFromStream, py::arg("stream"), py::arg("s_rgb") = false, py::arg("area") = sf::IntRect{})
    .def("load_from_image", &sf::Texture::loadFromImage, py::arg("image"), py::arg("s_rgb") = false, py::arg("area") = sf::IntRect{})
    .def("get_size", &sf::Texture::getSize)
    .def("copy_to_image", &sf::Texture::copyToImage)
    .def("update", py::overload_cast<const std::uint8_t*>(&sf::Texture::update), py::arg("pixels"))
    .def("update", py::overload_cast<const std::uint8_t*, sf::Vector2u, sf::Vector2u>(&sf::Texture::update), py::arg("pixels"), py::arg("size"), py::arg("position"))
    .def("update", py::overload_cast<const sf::Texture&>(&sf::Texture::update), py::arg("texture"))
    .def("update", py::overload_cast<const sf::Texture&, sf::Vector2u>(&sf::Texture::update), py::arg("texture"), py::arg("position"))
    .def("update", py::overload_cast<const sf::Image&>(&sf::Texture::update), py::arg("image"))
    .def("update", py::overload_cast<const sf::Image&, sf::Vector2u>(&sf::Texture::update), py::arg("image"), py::arg("position"))
    .def("update", py::overload_cast<const sf::Window&>(&sf::Texture::update), py::arg("window"))
    .def("update", py::overload_cast<const sf::Window&, sf::Vector2u>(&sf::Texture::update), py::arg("window"), py::arg("position"))
    .def("set_smooth", &sf::Texture::setSmooth, py::arg("smooth"))
    .def("is_smooth", &sf::Texture::isSmooth)
    .def("is_srgb", &sf::Texture::isSrgb)
    .def("set_repeated", &sf::Texture::setRepeated, py::arg("repeat"))
    .def("is_repeated", &sf::Texture::isRepeated)
    .def("generate_mipmap", &sf::Texture::generateMipmap)
    .def("swap", &sf::Texture::swap, py::arg("right"))
    .def("get_native_handle", &sf::Texture::getNativeHandle)
    .def_static("bind", &sf::Texture::bind, py::arg("texture"), py::arg("coordinate_type") = sf::CoordinateType::Normalized)
    .def_static("get_maximum_size", &sf::Texture::getMaximumSize);
}

void bind_sprite(py::module& m) {
    py::class_<sf::Sprite, sf::Transformable, sf::Drawable>(m, "Sprite", py::dynamic_attr())
    .def(py::init<const sf::Texture&>(), py::arg("texture"))
    .def(py::init<const sf::Texture&, const sf::IntRect&>(), py::arg("texture"), py::arg("rectangle"))
    .def("set_texture", [](sf::Sprite& self, const sf::Texture& texture, bool resetRect) {
       self.setTexture(texture, resetRect);
    }, py::arg("texture"), py::arg("resetRect") = false)
    .def("set_texture_rect", &sf::Sprite::setTextureRect, py::arg("rectangle"))
    .def("set_color", &sf::Sprite::setColor, py::arg("color"))
    .def("get_texture", &sf::Sprite::getTexture)
    .def("get_texture_rect", &sf::Sprite::getTextureRect)
    .def("get_color", &sf::Sprite::getColor)
    .def("get_local_bounds", &sf::Sprite::getLocalBounds)
    .def("get_global_bounds", &sf::Sprite::getGlobalBounds);
}

void bind_stencil_mode(py::module& m) {
    py::enum_<sf::StencilComparison>(m, "StencilComparison")
    .value("Never", sf::StencilComparison::Never)
    .value("Less", sf::StencilComparison::Less)
    .value("LessEqual", sf::StencilComparison::LessEqual)
    .value("Greater", sf::StencilComparison::Greater)
    .value("GreaterEqual", sf::StencilComparison::GreaterEqual)
    .value("Equal", sf::StencilComparison::Equal)
    .value("NotEqual", sf::StencilComparison::NotEqual)
    .value("Always", sf::StencilComparison::Always)
    .export_values();

    py::enum_<sf::StencilUpdateOperation>(m, "StencilUpdateOperation")
    .value("Keep", sf::StencilUpdateOperation::Keep)
    .value("Zero", sf::StencilUpdateOperation::Zero)
    .value("Replace", sf::StencilUpdateOperation::Replace)
    .value("Increment", sf::StencilUpdateOperation::Increment)
    .value("Decrement", sf::StencilUpdateOperation::Decrement)
    .value("Invert", sf::StencilUpdateOperation::Invert)
    .export_values();

    py::class_<sf::StencilValue>(m, "StencilValue")
    .def(py::init<int>())
    .def_readwrite("value", &sf::StencilValue::value);

    py::class_<sf::StencilMode>(m, "StencilMode")
    .def(py::init<>())
    .def_readwrite("stencil_comparison", &sf::StencilMode::stencilComparison)
    .def_readwrite("stencil_update_operation", &sf::StencilMode::stencilUpdateOperation)
    .def_readwrite("stencil_reference", &sf::StencilMode::stencilReference)
    .def_readwrite("stencil_mask", &sf::StencilMode::stencilMask)
    .def_readwrite("stencil_only", &sf::StencilMode::stencilOnly)
    .def("__eq__", [](const sf::StencilMode& left, const sf::StencilMode& right) {
       return left == right;
    })
    .def("__ne__", [](const sf::StencilMode& left, const sf::StencilMode& right) {
       return left != right;
    });
}

void bind_text(py::module& m) {
    py::class_<sf::Text, sf::Transformable, sf::Drawable> text(m, "Text");
    py::enum_<sf::Text::Style>(text, "Style")
    .value("Regular", sf::Text::Regular)
    .value("Bold", sf::Text::Bold)
    .value("Italic", sf::Text::Italic)
    .value("Underlined", sf::Text::Underlined)
    .value("StrikeThrough", sf::Text::StrikeThrough);

    text.def(py::init<const sf::Font&, std::string, unsigned int>(),
         py::arg("font"), py::arg("string") = "", py::arg("character_size") = 30)
    .def("set_string", [](sf::Text& self, const std::string& string) {
        self.setString(sf::String::fromUtf8(string.begin(), string.end()));
    }, py::arg("string"))
    .def("set_font", [](sf::Text& self, const sf::Font& font) {
       self.setFont(font);
    }, py::arg("font"))
    .def("set_character_size", &sf::Text::setCharacterSize, py::arg("size"))
    .def("set_line_spacing", &sf::Text::setLineSpacing, py::arg("factor"))
    .def("set_letter_spacing", &sf::Text::setLetterSpacing, py::arg("factor"))
    .def("set_style", &sf::Text::setStyle, py::arg("style"))
    .def("set_fill_color", &sf::Text::setFillColor, py::arg("color"))
    .def("set_outline_color", &sf::Text::setOutlineColor, py::arg("color"))
    .def("set_outline_thickness", &sf::Text::setOutlineThickness, py::arg("thickness"))
    .def("get_string", [](sf::Text& self) {
        return self.getString().toUtf8();
    })
    .def("get_font", &sf::Text::getFont)
    .def("get_character_size", &sf::Text::getCharacterSize)
    .def("get_letter_spacing", &sf::Text::getLetterSpacing)
    .def("get_line_spacing", &sf::Text::getLineSpacing)
    .def("get_style", &sf::Text::getStyle)
    .def("get_fill_color", &sf::Text::getFillColor)
    .def("get_outline_color", &sf::Text::getOutlineColor)
    .def("get_outline_thickness", &sf::Text::getOutlineThickness)
    .def("find_character_pos", &sf::Text::findCharacterPos, py::arg("index"))
    .def("get_local_bounds", &sf::Text::getLocalBounds)
    .def("get_global_bounds", &sf::Text::getGlobalBounds);
}

void bind_view(py::module& m) {
    py::class_<sf::View>(m, "View")
    .def(py::init<>())
    .def(py::init<const sf::FloatRect&>(), py::arg("rectangle"))
    .def(py::init<sf::Vector2f, sf::Vector2f>(), py::arg("center"), py::arg("size"))
    .def("set_center", &sf::View::setCenter, py::arg("center"))
    .def("set_size", &sf::View::setSize, py::arg("size"))
    .def("set_rotation", &sf::View::setRotation, py::arg("angle"))
    .def("set_viewport", &sf::View::setViewport, py::arg("rectangle"))
    .def("set_scissor", &sf::View::setScissor, py::arg("rectangle"))
    .def("get_center", &sf::View::getCenter)
    .def("get_size", &sf::View::getSize)
    .def("get_rotation", &sf::View::getRotation)
    .def("get_viewport", &sf::View::getViewport)
    .def("get_scissor", &sf::View::getScissor)
    .def("move", &sf::View::move, py::arg("offset"))
    .def("rotate", &sf::View::rotate, py::arg("angle"))
    .def("zoom", &sf::View::zoom, py::arg("factor"))
    .def("get_transform", &sf::View::getTransform)
    .def("get_inverse_transform", &sf::View::getInverseTransform);
}
