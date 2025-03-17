#include <window_base.h>

void bind_enum(py::module_ &m) {
    py::module_ style = m.def_submodule("Style");

    style.attr("Empty") = py::int_(static_cast<int>(sf::Style::None)); // attr name cannot be none.
    style.attr("Titlebar") = py::int_(static_cast<int>(sf::Style::Titlebar));
    style.attr("Resize") = py::int_(static_cast<int>(sf::Style::Resize));
    style.attr("Close") = py::int_(static_cast<int>(sf::Style::Close));
    style.attr("Default") = py::int_(static_cast<int>(sf::Style::Default));

    py::enum_<sf::State>(m, "State")
    .value("Windowed", sf::State::Windowed)
    .value("Fullscreen", sf::State::Fullscreen);
}

void bind_context(py::module_ &m) {
    py::class_<sf::ContextSettings> context_settings(m, "ContextSettings");

    context_settings.def(py::init<>())
    .def_readwrite("depthBits", &sf::ContextSettings::depthBits)
    .def_readwrite("stencilBits", &sf::ContextSettings::stencilBits)
    .def_readwrite("antiAliasingLevel", &sf::ContextSettings::antiAliasingLevel)
    .def_readwrite("majorVersion", &sf::ContextSettings::majorVersion)
    .def_readwrite("minorVersion", &sf::ContextSettings::minorVersion)
    .def_readwrite("attributeFlags", &sf::ContextSettings::attributeFlags)
    .def_readwrite("sRgbCapable", &sf::ContextSettings::sRgbCapable);

    py::class_<sf::Context>(m, "Context")
    .def(py::init<>())
    .def(py::init<const sf::ContextSettings&, sf::Vector2u>(), py::arg("settings"), py::arg("size"))
    .def("set_active", &sf::Context::setActive, py::arg("active"))
    .def("get_settings", &sf::Context::getSettings);

    py::enum_<sf::ContextSettings::Attribute>(context_settings, "Attribute")
    .value("Default", sf::ContextSettings::Default)
    .value("Core", sf::ContextSettings::Core)
    .value("Debug", sf::ContextSettings::Debug)
    .export_values();

}

void bind_cursor(py::module_ &m) {
    py::class_<sf::Cursor> cursor(m, "Cursor");

    py::enum_<sf::Cursor::Type>(cursor, "Type")
    .value("Arrow", sf::Cursor::Type::Arrow)
    .value("ArrowWait", sf::Cursor::Type::ArrowWait)
    .value("Wait", sf::Cursor::Type::Wait)
    .value("Text", sf::Cursor::Type::Text)
    .value("Hand", sf::Cursor::Type::Hand)
    .value("SizeHorizontal", sf::Cursor::Type::SizeHorizontal)
    .value("SizeVertical", sf::Cursor::Type::SizeVertical)
    .value("SizeTopLeftBottomRight", sf::Cursor::Type::SizeTopLeftBottomRight)
    .value("SizeBottomLeftTopRight", sf::Cursor::Type::SizeBottomLeftTopRight)
    .value("SizeLeft", sf::Cursor::Type::SizeLeft)
    .value("SizeRight", sf::Cursor::Type::SizeRight)
    .value("SizeTop", sf::Cursor::Type::SizeTop)
    .value("SizeBottom", sf::Cursor::Type::SizeBottom)
    .value("SizeTopLeft", sf::Cursor::Type::SizeTopLeft)
    .value("SizeTopRight", sf::Cursor::Type::SizeTopRight)
    .value("SizeBottomLeft", sf::Cursor::Type::SizeBottomLeft)
    .value("SizeBottomRight", sf::Cursor::Type::SizeBottomRight)
    .value("SizeAll", sf::Cursor::Type::SizeAll)
    .value("Cross", sf::Cursor::Type::Cross)
    .value("Help", sf::Cursor::Type::Help)
    .value("NotAllowed", sf::Cursor::Type::NotAllowed)
    .export_values();

    cursor.def(py::init<sf::Cursor::Type>(), py::arg("type"))
    .def(py::init<const std::uint8_t*, sf::Vector2u, sf::Vector2u>(), py::arg("pixels"), py::arg("size"), py::arg("hotSpot"))
    .def_static("createFromPixels", &sf::Cursor::createFromPixels, py::arg("pixels"), py::arg("size"), py::arg("hotSpot"))
    .def_static("createFromSystem", &sf::Cursor::createFromSystem, py::arg("type"));
}

void bind_video_mode(py::module_ &m) {
    py::class_<sf::VideoMode>(m, "VideoMode")
    .def(py::init<>())
    .def(py::init<sf::Vector2u, unsigned int>(), py::arg("size"), py::arg("bitsPerPixel") = 32)
    .def_property("size", [](sf::VideoMode &vm) { return vm.size; }, [](sf::VideoMode &vm, sf::Vector2u size) { vm.size = size; })
    .def_property("bits_per_pixel", [](sf::VideoMode &vm) { return vm.bitsPerPixel; }, [](sf::VideoMode &vm, unsigned int bitsPerPixel) { vm.bitsPerPixel = bitsPerPixel; })
    .def_static("get_desktop_mode", &sf::VideoMode::getDesktopMode)
    .def_static("get_fullscreen_modes", &sf::VideoMode::getFullscreenModes)
    .def("is_valid", &sf::VideoMode::isValid);
}
