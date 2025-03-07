#include <graphics_render.h>

void bind_image(py::module_ &m) {
    py::class_<sf::Image>(m, "Image")
    .def(py::init<>())
    .def(py::init<sf::Vector2u, sf::Color>(), py::arg("size"), py::arg("color") = sf::Color::Black)
    .def(py::init<sf::Vector2u, const uint8_t*>(), py::arg("size"), py::arg("pixels"))
    .def(py::init<const void*, std::size_t>(), py::arg("data"), py::arg("size"))
    .def(py::init<sf::InputStream&>(), py::arg("stream"))
    .def("resize", (void (sf::Image::*)(sf::Vector2u, sf::Color)) &sf::Image::resize, py::arg("size"), py::arg("color") = sf::Color::Black)
    .def("resize", (void (sf::Image::*)(sf::Vector2u, const uint8_t*)) &sf::Image::resize, py::arg("size"), py::arg("pixels"))
    .def("load_from_file", [](sf::Image &self, const std::string &filename) {
        return self.loadFromFile(filename);
    }, py::arg("filename"))
    .def("load_from_memory", &sf::Image::loadFromMemory, py::arg("data"), py::arg("size"))
    .def("load_from_stream", &sf::Image::loadFromStream, py::arg("stream"))
    .def("save_to_file", &sf::Image::saveToFile, py::arg("filename"))
    .def("save_to_memory", &sf::Image::saveToMemory, py::arg("format"))
    .def("get_size", &sf::Image::getSize)
    .def("create_mask_from_color", &sf::Image::createMaskFromColor, py::arg("color"), py::arg("alpha") = 0)
    .def("copy", &sf::Image::copy, py::arg("source"), py::arg("dest"), py::arg("source_rect") = sf::IntRect(), py::arg("apply_alpha") = false)
    .def("set_pixel", &sf::Image::setPixel, py::arg("coords"), py::arg("color"))
    .def("get_pixel", &sf::Image::getPixel, py::arg("coords"))
    .def("get_pixels_ptr", &sf::Image::getPixelsPtr)
    .def("flip_horizontally", &sf::Image::flipHorizontally)
    .def("flip_vertically", &sf::Image::flipVertically);
}

void bind_convex_shape(py::module_ &m) {
    py::class_<sf::ConvexShape, sf::Shape>(m, "ConvexShape")
    .def(py::init<std::size_t>(), py::arg("pointCount") = 0)
    .def("set_point_count", &sf::ConvexShape::setPointCount, py::arg("count"))
    .def("get_point_count", &sf::ConvexShape::getPointCount)
    .def("set_point", &sf::ConvexShape::setPoint, py::arg("index"), py::arg("point"))
    .def("get_point", &sf::ConvexShape::getPoint, py::arg("index"));
}

void bind_circle_shape(py::module_ &m) {
    py::class_<sf::CircleShape, sf::Shape>(m, "CircleShape")
    .def(py::init<float, std::size_t>(), py::arg("radius") = 0, py::arg("point_count") = 30)
    .def("set_radius", &sf::CircleShape::setRadius, py::arg("radius"))
    .def("get_radius", &sf::CircleShape::getRadius)
    .def("set_point_count", &sf::CircleShape::setPointCount, py::arg("count"))
    .def("get_point_count", &sf::CircleShape::getPointCount)
    .def("get_point", &sf::CircleShape::getPoint, py::arg("index"))
    .def("get_geometric_center", &sf::CircleShape::getGeometricCenter);
}

void bind_rectangle_shape(py::module_ &m) {
    py::class_<sf::RectangleShape, sf::Shape>(m, "RectangleShape")
    .def(py::init<sf::Vector2f>(), py::arg("size") = sf::Vector2f{})
    .def("set_size", &sf::RectangleShape::setSize, py::arg("size"))
    .def("get_size", &sf::RectangleShape::getSize)
    .def("get_point_count", &sf::RectangleShape::getPointCount)
    .def("get_point", &sf::RectangleShape::getPoint, py::arg("index"))
    .def("get_geometric_center", &sf::RectangleShape::getGeometricCenter);
}

void bind_render_states(py::module_ &m) {
    py::class_<sf::RenderStates>(m, "RenderStates")
    .def(py::init<>())
    .def(py::init<const sf::BlendMode&>(), py::arg("blend_mode"))
    .def(py::init<const sf::StencilMode&>(), py::arg("stencil_mode"))
    .def(py::init<const sf::Transform&>(), py::arg("transform"))
    .def(py::init<const sf::Texture*>(), py::arg("texture"))
    .def(py::init<const sf::Shader*>(), py::arg("shader"))
    .def(py::init<const sf::BlendMode&, const sf::StencilMode&, const sf::Transform&,
                  sf::CoordinateType, const sf::Texture*, const sf::Shader*>(),
          py::arg("blend_mode"), py::arg("stencil_mode"), py::arg("transform"),
          py::arg("coordinate_type"), py::arg("texture"), py::arg("shader"))
    .def_readwrite("blend_mode", &sf::RenderStates::blendMode)
    .def_readwrite("stencil_mode", &sf::RenderStates::stencilMode)
    .def_readwrite("transform", &sf::RenderStates::transform)
    .def_readwrite("coordinate_type", &sf::RenderStates::coordinateType)
    .def_readwrite("texture", &sf::RenderStates::texture)
    .def_readwrite("shader", &sf::RenderStates::shader)
    .def_static("default", []() {
        return sf::RenderStates::Default;
    });
}

void bind_render_target(py::module_ &m) {
    py::class_<sf::RenderTarget>(m, "RenderTarget")
    .def("clear", static_cast<void(sf::RenderTarget::*)(sf::Color)>(&sf::RenderTarget::clear), py::arg("color") = sf::Color::Black)
    .def("clear", static_cast<void(sf::RenderTarget::*)(sf::Color, sf::StencilValue)>(&sf::RenderTarget::clear), py::arg("color"), py::arg("stencilValue"))
    .def("clear_stencil", &sf::RenderTarget::clearStencil, py::arg("stencilValue"))
    .def("set_view", &sf::RenderTarget::setView, py::arg("view"))
    .def("get_view", &sf::RenderTarget::getView)
    .def("get_default_view", &sf::RenderTarget::getDefaultView)
    .def("get_viewport", &sf::RenderTarget::getViewport, py::arg("view"))
    .def("get_scissor", &sf::RenderTarget::getScissor, py::arg("view"))
    .def("map_pixel_to_coords", static_cast<sf::Vector2f(sf::RenderTarget::*)(sf::Vector2i) const>(&sf::RenderTarget::mapPixelToCoords), py::arg("point"))
    .def("map_coords_to_pixel", static_cast<sf::Vector2i(sf::RenderTarget::*)(sf::Vector2f) const>(&sf::RenderTarget::mapCoordsToPixel), py::arg("point"))
    .def("draw", [](sf::RenderTarget& self, const sf::Drawable& drawable, const sf::RenderStates& states) {
        self.draw(drawable, states);
    }, py::arg("drawable"), py::arg("states") = sf::RenderStates::Default)
    .def("draw", [](sf::RenderTarget& self, const sf::Vertex* vertices, std::size_t vertexCount, sf::PrimitiveType type, const sf::RenderStates& states) {
        self.draw(vertices, vertexCount, type, states);
    }, py::arg("vertices"), py::arg("vertexCount"), py::arg("type"), py::arg("states") = sf::RenderStates::Default)
    .def("draw", [](sf::RenderTarget& self, const sf::VertexBuffer& buffer, const sf::RenderStates& states) {
        self.draw(buffer, states);
    }, py::arg("buffer"), py::arg("states") = sf::RenderStates::Default)
    .def("draw", [](sf::RenderTarget& self, const sf::VertexBuffer& buffer, std::size_t first, std::size_t count, const sf::RenderStates& states) {
        self.draw(buffer, first, count, states);
    }, py::arg("buffer"), py::arg("first"), py::arg("count"), py::arg("states") = sf::RenderStates::Default)
    .def("get_size", &sf::RenderTarget::getSize)
    .def("is_srgb", &sf::RenderTarget::isSrgb)
    .def("set_active", &sf::RenderTarget::setActive, py::arg("active") = true)
    .def("push_gl_states", &sf::RenderTarget::pushGLStates)
    .def("pop_gl_states", &sf::RenderTarget::popGLStates)
    .def("reset_gl_states", &sf::RenderTarget::resetGLStates);
}

void bind_render_texture(py::module_ &m) {
    py::class_<sf::RenderTexture, sf::RenderTarget>(m, "RenderTexture")
    .def(py::init<>())
    .def(py::init<sf::Vector2u, const sf::ContextSettings&>(), py::arg("size"), py::arg("settings") = sf::ContextSettings())
    .def("resize", &sf::RenderTexture::resize)
    .def("set_smooth", &sf::RenderTexture::setSmooth, py::arg("smooth"))
    .def("is_smooth", &sf::RenderTexture::isSmooth)
    .def("set_repeated", &sf::RenderTexture::setRepeated, py::arg("repeated"))
    .def("is_repeated", &sf::RenderTexture::isRepeated)
    .def("generate_mipmap", &sf::RenderTexture::generateMipmap)
    .def("set_active", &sf::RenderTexture::setActive, py::arg("active") = true)
    .def("display", &sf::RenderTexture::display)
    .def("get_size", &sf::RenderTexture::getSize)
    .def("is_srgb", &sf::RenderTexture::isSrgb)
    .def("get_texture", &sf::RenderTexture::getTexture, py::return_value_policy::reference_internal)
    .def_static("get_maximum_anti_aliasing_level", []() {
        return sf::RenderTexture::getMaximumAntiAliasingLevel();
    });
}

void bind_render_window(py::module_ &m) {
    py::class_<sf::RenderWindow, sf::Window, sf::RenderTarget>(m, "RenderWindow")
    .def(py::init<>())
    .def(py::init<sf::VideoMode, const std::string&, std::uint32_t, sf::State, const sf::ContextSettings&>(), py::arg("mode"), py::arg("title"), py::arg("style") = 7/*sf::Style::Default*/, py::arg("state") = sf::State::Windowed, py::arg("contextSettings") = sf::ContextSettings())
    .def(py::init<sf::VideoMode, const std::string&, sf::State, const sf::ContextSettings&>(), py::arg("mode"), py::arg("title"), py::arg("state"), py::arg("contextSettings") = sf::ContextSettings())
    .def("get_size", &sf::RenderWindow::getSize)
    .def("set_icon", [](sf::RenderWindow& self, const sf::Image& image) {
        self.setIcon(image);
    }, py::arg("image"))
    .def("set_icon", [](sf::RenderWindow& self, sf::Vector2<unsigned int>& size, const std::uint8_t* pixels) {
        self.setIcon(size, pixels);
    }, py::arg("size"), py::arg("pixels"))
    .def("is_srgb", &sf::RenderWindow::isSrgb)
    .def("set_active", &sf::RenderWindow::setActive, py::arg("active") = true);
}

void bind_shader(py::module& m) {
    py::class_<sf::Shader> shader(m, "Shader");

    py::enum_<sf::Shader::Type>(shader, "Type")
    .value("Vertex", sf::Shader::Type::Vertex)
    .value("Geometry", sf::Shader::Type::Geometry)
    .value("Fragment", sf::Shader::Type::Fragment)
    .export_values();

    shader.def(py::init<>())
    .def(py::init([](const std::string& filename, sf::Shader::Type type) {
        return std::make_unique<sf::Shader>(std::filesystem::path(filename), type);
    }), py::arg("filename"), py::arg("type"))
    .def(py::init([](const std::string& vertexShaderFilename, const std::string& fragmentShaderFilename) {
        return std::make_unique<sf::Shader>(std::filesystem::path(vertexShaderFilename), std::filesystem::path(fragmentShaderFilename));
    }), py::arg("vertexShaderFilename"), py::arg("fragmentShaderFilename"))
    .def(py::init([](const std::string& vertexShaderFilename, const std::string& geometryShaderFilename, const std::string& fragmentShaderFilename) {
        return std::make_unique<sf::Shader>(std::filesystem::path(vertexShaderFilename), std::filesystem::path(geometryShaderFilename), std::filesystem::path(fragmentShaderFilename));
    }), py::arg("vertexShaderFilename"), py::arg("geometryShaderFilename"), py::arg("fragmentShaderFilename"))
    .def("load_from_file", [](sf::Shader& self, const std::string& filename, sf::Shader::Type type) {
        return self.loadFromFile(filename, type);
    }, py::arg("filename"), py::arg("type"))
    .def("load_from_file", [](sf::Shader& self, const std::string& vertex, const std::string& fragment) {
        return self.loadFromMemory(vertex, fragment);
    }, py::arg("vertex"), py::arg("fragment"))
    .def("load_from_file", [](sf::Shader& self, const std::string& vertex, const std::string& geometry, const std::string& fragment) {
        return self.loadFromMemory(vertex, geometry, fragment);
    }, py::arg("vertex"), py::arg("geometry"), py::arg("fragment"))
    .def("load_from_memory", [](sf::Shader& self, const std::string& source, sf::Shader::Type type) {
        return self.loadFromMemory(source, type);
    }, py::arg("source"), py::arg("type"))
    .def("load_from_memory", [](sf::Shader& self, const std::string& vertex, const std::string& fragment) {
        return self.loadFromMemory(vertex, fragment);
    }, py::arg("vertex"), py::arg("fragment"))
    .def("load_from_memory", [](sf::Shader& self, const std::string& vertex, const std::string& geometry, const std::string& fragment) {
        return self.loadFromMemory(vertex, geometry, fragment);
    }, py::arg("vertex"), py::arg("geometry"), py::arg("fragment"))
    .def("set_uniform", [](sf::Shader& self, const std::string& name, float x) {
        self.setUniform(name, x);
    }, py::arg("name"), py::arg("x"))
    .def("set_uniform", [](sf::Shader& self, const std::string& name, const sf::Glsl::Vec2& vector) {
        self.setUniform(name, vector);
    }, py::arg("name"), py::arg("vector"))
    .def("set_uniform", [](sf::Shader& self, const std::string& name, const sf::Glsl::Vec3& vector) {
        self.setUniform(name, vector);
    }, py::arg("name"), py::arg("vector"))
    .def("set_uniform", [](sf::Shader& self, const std::string& name, const sf::Glsl::Vec4& vector) {
        self.setUniform(name, vector);
    }, py::arg("name"), py::arg("vector"))
    .def("set_uniform", [](sf::Shader& self, const std::string& name, int x) {
        self.setUniform(name, x);
    }, py::arg("name"), py::arg("x"))
    .def("set_uniform", [](sf::Shader& self, const std::string& name, const sf::Glsl::Ivec2& vector) {
        self.setUniform(name, vector);
    }, py::arg("name"), py::arg("vector"))
    .def("set_uniform", [](sf::Shader& self, const std::string& name, const sf::Glsl::Ivec3& vector) {
        self.setUniform(name, vector);
    }, py::arg("name"), py::arg("vector"))
    .def("set_uniform", [](sf::Shader& self, const std::string& name, const sf::Glsl::Ivec4& vector) {
        self.setUniform(name, vector);
    }, py::arg("name"), py::arg("vector"))
    .def("set_uniform", [](sf::Shader& self, const std::string& name, bool x) {
        self.setUniform(name, x);
    }, py::arg("name"), py::arg("x"))
    .def("set_uniform", [](sf::Shader& self, const std::string& name, const sf::Glsl::Bvec2& vector) {
        self.setUniform(name, vector);
    }, py::arg("name"), py::arg("vector"))
    .def("set_uniform", [](sf::Shader& self, const std::string& name, const sf::Glsl::Bvec3& vector) {
        self.setUniform(name, vector);
    }, py::arg("name"), py::arg("vector"))
    .def("set_uniform", [](sf::Shader& self, const std::string& name, const sf::Glsl::Bvec4& vector) {
        self.setUniform(name, vector);
    }, py::arg("name"), py::arg("vector"))
    .def("set_uniform", [](sf::Shader& self, const std::string& name, const sf::Glsl::Mat3& matrix) {
        self.setUniform(name, matrix);
    }, py::arg("name"), py::arg("matrix"))
    .def("set_uniform", [](sf::Shader& self, const std::string& name, const sf::Glsl::Mat4& matrix) {
        self.setUniform(name, matrix);
    }, py::arg("name"), py::arg("matrix"))
    .def("set_uniform", [](sf::Shader& self, const std::string& name, const sf::Texture& texture) {
        self.setUniform(name, texture);
    }, py::arg("name"), py::arg("texture"))
    .def("set_uniform_array", [](sf::Shader& self, const std::string& name, const float* values, std::size_t count) {
        self.setUniformArray(name, values, count);
    }, py::arg("name"), py::arg("values"), py::arg("count"))
    .def("set_uniform_array", [](sf::Shader& self, const std::string& name, const sf::Glsl::Vec2* values, std::size_t count) {
        self.setUniformArray(name, values, count);
    }, py::arg("name"), py::arg("values"), py::arg("count"))
    .def("set_uniform_array", [](sf::Shader& self, const std::string& name, const sf::Glsl::Vec3* values, std::size_t count) {
        self.setUniformArray(name, values, count);
    }, py::arg("name"), py::arg("values"), py::arg("count"))
    .def("set_uniform_array", [](sf::Shader& self, const std::string& name, const sf::Glsl::Vec4* values, std::size_t count) {
        self.setUniformArray(name, values, count);
    }, py::arg("name"), py::arg("values"), py::arg("count"))
    .def("set_uniform_array", [](sf::Shader& self, const std::string& name, const sf::Glsl::Mat3* matrixArray, std::size_t count) {
        self.setUniformArray(name, matrixArray, count);
    }, py::arg("name"), py::arg("matrixArray"), py::arg("count"))
    .def("set_uniform_array", [](sf::Shader& self, const std::string& name, const sf::Glsl::Mat4* matrixArray, std::size_t count) {
        self.setUniformArray(name, matrixArray, count);
    }, py::arg("name"), py::arg("matrixArray"), py::arg("count"))
    .def("get_native_handle", &sf::Shader::getNativeHandle)
    .def_static("bind", &sf::Shader::bind, py::arg("shader"))
    .def_static("is_available", &sf::Shader::isAvailable)
    .def_static("is_geometry_available", &sf::Shader::isGeometryAvailable);
}
