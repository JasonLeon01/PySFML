#include <window.h>

void bind_base_window(py::module_ &m) {
    py::class_<sf::WindowBase>(m, "WindowBase")
    .def(py::init<>())
    .def(py::init<sf::VideoMode, const std::string&, std::uint32_t, sf::State>(), py::arg("mode"), py::arg("title"), py::arg("style") = 7/*sf::Style::Default*/, py::arg("state") = sf::State::Windowed)
    .def(py::init<sf::VideoMode, const std::string&, sf::State>(), py::arg("mode"), py::arg("title"), py::arg("state") = sf::State::Windowed)
    .def("is_open", &sf::WindowBase::isOpen)
    .def("close", &sf::WindowBase::close)
    .def("poll_event", &sf::WindowBase::pollEvent)
    .def("wait_event", &sf::WindowBase::waitEvent)
    .def("get_position", &sf::WindowBase::getPosition)
    .def("set_position", &sf::WindowBase::setPosition)
    .def("get_size", &sf::WindowBase::getSize)
    .def("set_size", &sf::WindowBase::setSize)
    .def("set_minimum_size", &sf::WindowBase::setMinimumSize)
    .def("set_maximum_size", &sf::WindowBase::setMaximumSize)
    .def("set_title", &sf::WindowBase::setTitle)
    .def("set_icon", &sf::WindowBase::setIcon)
    .def("set_visible", &sf::WindowBase::setVisible)
    .def("set_mouse_cursor_visible", &sf::WindowBase::setMouseCursorVisible)
    .def("setMouseCursorGrabbed", &sf::WindowBase::setMouseCursorGrabbed)
    .def("set_mouse_cursor", &sf::WindowBase::setMouseCursor)
    .def("set_key_repeat_enabled", &sf::WindowBase::setKeyRepeatEnabled)
    .def("set_joystick_threshold", &sf::WindowBase::setJoystickThreshold)
    .def("request_focus", &sf::WindowBase::requestFocus)
    .def("has_focus", &sf::WindowBase::hasFocus);
}

void bind_window(py::module_ &m) {
    py::class_<sf::Window, sf::WindowBase>(m, "Window")
    .def(py::init<>())
    .def(py::init<sf::VideoMode, const std::string&, std::uint32_t, sf::State&, const sf::ContextSettings&>(), py::arg("mode"), py::arg("title"), py::arg("style") = 7/*sf::Style::Default*/, py::arg("state") = sf::State::Windowed, py::arg("settings") = sf::ContextSettings())
    .def(py::init<sf::VideoMode, const std::string&, sf::State, const sf::ContextSettings&>(), py::arg("mode"), py::arg("title"), py::arg("state") = sf::State::Windowed, py::arg("settings") = sf::ContextSettings())
    .def("close", &sf::Window::close)
    .def("setVerticalSyncEnabled", &sf::Window::setVerticalSyncEnabled)
    .def("setFramerateLimit", &sf::Window::setFramerateLimit)
    .def("set_active", &sf::Window::setActive)
    .def("display", &sf::Window::display)
    .def("get_settings", &sf::Window::getSettings);
}

void bind_clipboard(py::module &m) {
    py::module_ clipboard = m.def_submodule("Clipboard");

    clipboard.def("get_string", []() {
        sf::String content = sf::Clipboard::getString();
        return std::string(content);
    });
    clipboard.def("set_string", [](const std::string& text) {
        sf::Clipboard::setString(sf::String(text));
    });
}

void bind_joystick(py::module &m) {
    py::module_ joystick = m.def_submodule("Joystick");

    py::enum_<sf::Joystick::Axis>(joystick, "Axis")
    .value("X", sf::Joystick::Axis::X)
    .value("Y", sf::Joystick::Axis::Y)
    .value("Z", sf::Joystick::Axis::Z)
    .value("R", sf::Joystick::Axis::R)
    .value("U", sf::Joystick::Axis::U)
    .value("V", sf::Joystick::Axis::V)
    .value("PovX", sf::Joystick::Axis::PovX)
    .value("PovY", sf::Joystick::Axis::PovY)
    .export_values();

    py::class_<sf::Joystick::Identification>(joystick, "Identification")
    .def(py::init<>())
    .def("name", 
        [](sf::Joystick::Identification& self) -> std::string {
            return self.name.toAnsiString();
        })
    .def("set_name", 
        [](sf::Joystick::Identification& self, const std::string& value) {
            self.name = value;
        })
    .def_readwrite("vendor_id", &sf::Joystick::Identification::vendorId)
    .def_readwrite("product_id", &sf::Joystick::Identification::productId);

    joystick.def("is_connected", &sf::Joystick::isConnected);
    joystick.def("get_button_count", &sf::Joystick::getButtonCount);
    joystick.def("has_axis", &sf::Joystick::hasAxis);
    joystick.def("is_button_pressed", &sf::Joystick::isButtonPressed);
    joystick.def("get_axis_position", &sf::Joystick::getAxisPosition);
    joystick.def("get_identification", &sf::Joystick::getIdentification);
    joystick.def("update", &sf::Joystick::update);
}

void bind_keyboard(py::module_ &m) {
    py::module_ keyboard = m.def_submodule("Keyboard");

    py::enum_<sf::Keyboard::Key>(keyboard, "Key")
    .value("Unknown", sf::Keyboard::Key::Unknown)
    .value("A", sf::Keyboard::Key::A)
    .value("B", sf::Keyboard::Key::B)
    .value("C", sf::Keyboard::Key::C)
    .value("D", sf::Keyboard::Key::D)
    .value("E", sf::Keyboard::Key::E)
    .value("F", sf::Keyboard::Key::F)
    .value("G", sf::Keyboard::Key::G)
    .value("H", sf::Keyboard::Key::H)
    .value("I", sf::Keyboard::Key::I)
    .value("J", sf::Keyboard::Key::J)
    .value("K", sf::Keyboard::Key::K)
    .value("L", sf::Keyboard::Key::L)
    .value("M", sf::Keyboard::Key::M)
    .value("N", sf::Keyboard::Key::N)
    .value("O", sf::Keyboard::Key::O)
    .value("P", sf::Keyboard::Key::P)
    .value("Q", sf::Keyboard::Key::Q)
    .value("R", sf::Keyboard::Key::R)
    .value("S", sf::Keyboard::Key::S)
    .value("T", sf::Keyboard::Key::T)
    .value("U", sf::Keyboard::Key::U)
    .value("V", sf::Keyboard::Key::V)
    .value("W", sf::Keyboard::Key::W)
    .value("X", sf::Keyboard::Key::X)
    .value("Y", sf::Keyboard::Key::Y)
    .value("Z", sf::Keyboard::Key::Z)
    .value("Num0", sf::Keyboard::Key::Num0)
    .value("Num1", sf::Keyboard::Key::Num1)
    .value("Num2", sf::Keyboard::Key::Num2)
    .value("Num3", sf::Keyboard::Key::Num3)
    .value("Num4", sf::Keyboard::Key::Num4)
    .value("Num5", sf::Keyboard::Key::Num5)
    .value("Num6", sf::Keyboard::Key::Num6)
    .value("Num7", sf::Keyboard::Key::Num7)
    .value("Num8", sf::Keyboard::Key::Num8)
    .value("Num9", sf::Keyboard::Key::Num9)
    .value("Escape", sf::Keyboard::Key::Escape)
    .value("LControl", sf::Keyboard::Key::LControl)
    .value("LShift", sf::Keyboard::Key::LShift)
    .value("LAlt", sf::Keyboard::Key::LAlt)
    .value("LSystem", sf::Keyboard::Key::LSystem)
    .value("RControl", sf::Keyboard::Key::RControl)
    .value("RShift", sf::Keyboard::Key::RShift)
    .value("RAlt", sf::Keyboard::Key::RAlt)
    .value("RSystem", sf::Keyboard::Key::RSystem)
    .value("Menu", sf::Keyboard::Key::Menu)
    .value("LBracket", sf::Keyboard::Key::LBracket)
    .value("RBracket", sf::Keyboard::Key::RBracket)
    .value("Semicolon", sf::Keyboard::Key::Semicolon)
    .value("Comma", sf::Keyboard::Key::Comma)
    .value("Period", sf::Keyboard::Key::Period)
    .value("Apostrophe", sf::Keyboard::Key::Apostrophe)
    .value("Slash", sf::Keyboard::Key::Slash)
    .value("Backslash", sf::Keyboard::Key::Backslash)
    .value("Grave", sf::Keyboard::Key::Grave)
    .value("Equal", sf::Keyboard::Key::Equal)
    .value("Hyphen", sf::Keyboard::Key::Hyphen)
    .value("Space", sf::Keyboard::Key::Space)
    .value("Enter", sf::Keyboard::Key::Enter)
    .value("Backspace", sf::Keyboard::Key::Backspace)
    .value("Tab", sf::Keyboard::Key::Tab)
    .value("PageUp", sf::Keyboard::Key::PageUp)
    .value("PageDown", sf::Keyboard::Key::PageDown)
    .value("End", sf::Keyboard::Key::End)
    .value("Home", sf::Keyboard::Key::Home)
    .value("Insert", sf::Keyboard::Key::Insert)
    .value("Delete", sf::Keyboard::Key::Delete)
    .value("Add", sf::Keyboard::Key::Add)
    .value("Subtract", sf::Keyboard::Key::Subtract)
    .value("Multiply", sf::Keyboard::Key::Multiply)
    .value("Divide", sf::Keyboard::Key::Divide)
    .value("Left", sf::Keyboard::Key::Left)
    .value("Right", sf::Keyboard::Key::Right)
    .value("Up", sf::Keyboard::Key::Up)
    .value("Down", sf::Keyboard::Key::Down)
    .value("Numpad0", sf::Keyboard::Key::Numpad0)
    .value("Numpad1", sf::Keyboard::Key::Numpad1)
    .value("Numpad2", sf::Keyboard::Key::Numpad2)
    .value("Numpad3", sf::Keyboard::Key::Numpad3)
    .value("Numpad4", sf::Keyboard::Key::Numpad4)
    .value("Numpad5", sf::Keyboard::Key::Numpad5)
    .value("Numpad6", sf::Keyboard::Key::Numpad6)
    .value("Numpad7", sf::Keyboard::Key::Numpad7)
    .value("Numpad8", sf::Keyboard::Key::Numpad8)
    .value("Numpad9", sf::Keyboard::Key::Numpad9)
    .value("F1", sf::Keyboard::Key::F1)
    .value("F2", sf::Keyboard::Key::F2)
    .value("F3", sf::Keyboard::Key::F3)
    .value("F4", sf::Keyboard::Key::F4)
    .value("F5", sf::Keyboard::Key::F5)
    .value("F6", sf::Keyboard::Key::F6)
    .value("F7", sf::Keyboard::Key::F7)
    .value("F8", sf::Keyboard::Key::F8)
    .value("F9", sf::Keyboard::Key::F9)
    .value("F10", sf::Keyboard::Key::F10)
    .value("F11", sf::Keyboard::Key::F11)
    .value("F12", sf::Keyboard::Key::F12)
    .value("F13", sf::Keyboard::Key::F13)
    .value("F14", sf::Keyboard::Key::F14)
    .value("F15", sf::Keyboard::Key::F15)
    .value("Pause", sf::Keyboard::Key::Pause)
    .export_values();

    // Binding the Scan enum
    py::enum_<sf::Keyboard::Scan>(keyboard, "Scan")
    .value("Unknown", sf::Keyboard::Scan::Unknown)
    .value("A", sf::Keyboard::Scan::A)
    .value("B", sf::Keyboard::Scan::B)
    .value("C", sf::Keyboard::Scan::C)
    .value("D", sf::Keyboard::Scan::D)
    .value("E", sf::Keyboard::Scan::E)
    .value("F", sf::Keyboard::Scan::F)
    .value("G", sf::Keyboard::Scan::G)
    .value("H", sf::Keyboard::Scan::H)
    .value("I", sf::Keyboard::Scan::I)
    .value("J", sf::Keyboard::Scan::J)
    .value("K", sf::Keyboard::Scan::K)
    .value("L", sf::Keyboard::Scan::L)
    .value("M", sf::Keyboard::Scan::M)
    .value("N", sf::Keyboard::Scan::N)
    .value("O", sf::Keyboard::Scan::O)
    .value("P", sf::Keyboard::Scan::P)
    .value("Q", sf::Keyboard::Scan::Q)
    .value("R", sf::Keyboard::Scan::R)
    .value("S", sf::Keyboard::Scan::S)
    .value("T", sf::Keyboard::Scan::T)
    .value("U", sf::Keyboard::Scan::U)
    .value("V", sf::Keyboard::Scan::V)
    .value("W", sf::Keyboard::Scan::W)
    .value("X", sf::Keyboard::Scan::X)
    .value("Y", sf::Keyboard::Scan::Y)
    .value("Z", sf::Keyboard::Scan::Z)
    .value("Num1", sf::Keyboard::Scan::Num1)
    .value("Num2", sf::Keyboard::Scan::Num2)
    .value("Num3", sf::Keyboard::Scan::Num3)
    .value("Num4", sf::Keyboard::Scan::Num4)
    .value("Num5", sf::Keyboard::Scan::Num5)
    .value("Num6", sf::Keyboard::Scan::Num6)
    .value("Num7", sf::Keyboard::Scan::Num7)
    .value("Num8", sf::Keyboard::Scan::Num8)
    .value("Num9", sf::Keyboard::Scan::Num9)
    .value("Num0", sf::Keyboard::Scan::Num0)
    .value("Enter", sf::Keyboard::Scan::Enter)
    .value("Escape", sf::Keyboard::Scan::Escape)
    .value("Backspace", sf::Keyboard::Scan::Backspace)
    .value("Tab", sf::Keyboard::Scan::Tab)
    .value("Space", sf::Keyboard::Scan::Space)
    .value("Hyphen", sf::Keyboard::Scan::Hyphen)
    .value("Equal", sf::Keyboard::Scan::Equal)
    .value("LBracket", sf::Keyboard::Scan::LBracket)
    .value("RBracket", sf::Keyboard::Scan::RBracket)
    .value("Backslash", sf::Keyboard::Scan::Backslash)
    .value("Semicolon", sf::Keyboard::Scan::Semicolon)
    .value("Apostrophe", sf::Keyboard::Scan::Apostrophe)
    .value("Grave", sf::Keyboard::Scan::Grave)
    .value("Comma", sf::Keyboard::Scan::Comma)
    .value("Period", sf::Keyboard::Scan::Period)
    .value("Slash", sf::Keyboard::Scan::Slash)
    .value("F1", sf::Keyboard::Scan::F1)
    .value("F2", sf::Keyboard::Scan::F2)
    .value("F3", sf::Keyboard::Scan::F3)
    .value("F4", sf::Keyboard::Scan::F4)
    .value("F5", sf::Keyboard::Scan::F5)
    .value("F6", sf::Keyboard::Scan::F6)
    .value("F7", sf::Keyboard::Scan::F7)
    .value("F8", sf::Keyboard::Scan::F8)
    .value("F9", sf::Keyboard::Scan::F9)
    .value("F10", sf::Keyboard::Scan::F10)
    .value("F11", sf::Keyboard::Scan::F11)
    .value("F12", sf::Keyboard::Scan::F12)
    .value("F13", sf::Keyboard::Scan::F13)
    .value("F14", sf::Keyboard::Scan::F14)
    .value("F15", sf::Keyboard::Scan::F15)
    .value("F16", sf::Keyboard::Scan::F16)
    .value("F17", sf::Keyboard::Scan::F17)
    .value("F18", sf::Keyboard::Scan::F18)
    .value("F19", sf::Keyboard::Scan::F19)
    .value("F20", sf::Keyboard::Scan::F20)
    .value("F21", sf::Keyboard::Scan::F21)
    .value("F22", sf::Keyboard::Scan::F22)
    .value("F23", sf::Keyboard::Scan::F23)
    .value("F24", sf::Keyboard::Scan::F24)
    .value("CapsLock", sf::Keyboard::Scan::CapsLock)
    .value("PrintScreen", sf::Keyboard::Scan::PrintScreen)
    .value("ScrollLock", sf::Keyboard::Scan::ScrollLock)
    .value("Pause", sf::Keyboard::Scan::Pause)
    .value("Insert", sf::Keyboard::Scan::Insert)
    .value("Home", sf::Keyboard::Scan::Home)
    .value("PageUp", sf::Keyboard::Scan::PageUp)
    .value("Delete", sf::Keyboard::Scan::Delete)
    .value("End", sf::Keyboard::Scan::End)
    .value("PageDown", sf::Keyboard::Scan::PageDown)
    .value("Right", sf::Keyboard::Scan::Right)
    .value("Left", sf::Keyboard::Scan::Left)
    .value("Down", sf::Keyboard::Scan::Down)
    .value("Up", sf::Keyboard::Scan::Up)
    .value("NumLock", sf::Keyboard::Scan::NumLock)
    .value("NumpadDivide", sf::Keyboard::Scan::NumpadDivide)
    .value("NumpadMultiply", sf::Keyboard::Scan::NumpadMultiply)
    .value("NumpadMinus", sf::Keyboard::Scan::NumpadMinus)
    .value("NumpadPlus", sf::Keyboard::Scan::NumpadPlus)
    .value("NumpadEqual", sf::Keyboard::Scan::NumpadEqual)
    .value("NumpadEnter", sf::Keyboard::Scan::NumpadEnter)
    .value("NumpadDecimal", sf::Keyboard::Scan::NumpadDecimal)
    .value("Numpad1", sf::Keyboard::Scan::Numpad1)
    .value("Numpad2", sf::Keyboard::Scan::Numpad2)
    .value("Numpad3", sf::Keyboard::Scan::Numpad3)
    .value("Numpad4", sf::Keyboard::Scan::Numpad4)
    .value("Numpad5", sf::Keyboard::Scan::Numpad5)
    .value("Numpad6", sf::Keyboard::Scan::Numpad6)
    .value("Numpad7", sf::Keyboard::Scan::Numpad7)
    .value("Numpad8", sf::Keyboard::Scan::Numpad8)
    .value("Numpad9", sf::Keyboard::Scan::Numpad9)
    .value("Numpad0", sf::Keyboard::Scan::Numpad0)
    .value("NonUsBackslash", sf::Keyboard::Scan::NonUsBackslash)
    .value("Application", sf::Keyboard::Scan::Application)
    .value("Execute", sf::Keyboard::Scan::Execute)
    .value("ModeChange", sf::Keyboard::Scan::ModeChange)
    .value("Help", sf::Keyboard::Scan::Help)
    .value("Menu", sf::Keyboard::Scan::Menu)
    .value("Select", sf::Keyboard::Scan::Select)
    .value("Redo", sf::Keyboard::Scan::Redo)
    .value("Undo", sf::Keyboard::Scan::Undo)
    .value("Cut", sf::Keyboard::Scan::Cut)
    .value("Copy", sf::Keyboard::Scan::Copy)
    .value("Paste", sf::Keyboard::Scan::Paste)
    .value("VolumeMute", sf::Keyboard::Scan::VolumeMute)
    .value("VolumeUp", sf::Keyboard::Scan::VolumeUp)
    .value("VolumeDown", sf::Keyboard::Scan::VolumeDown)
    .value("MediaPlayPause", sf::Keyboard::Scan::MediaPlayPause)
    .value("MediaStop", sf::Keyboard::Scan::MediaStop)
    .value("MediaNextTrack", sf::Keyboard::Scan::MediaNextTrack)
    .value("MediaPreviousTrack", sf::Keyboard::Scan::MediaPreviousTrack)
    .value("LControl", sf::Keyboard::Scan::LControl)
    .value("LShift", sf::Keyboard::Scan::LShift)
    .value("LAlt", sf::Keyboard::Scan::LAlt)
    .value("LSystem", sf::Keyboard::Scan::LSystem)
    .value("RControl", sf::Keyboard::Scan::RControl)
    .value("RShift", sf::Keyboard::Scan::RShift)
    .value("RAlt", sf::Keyboard::Scan::RAlt)
    .value("RSystem", sf::Keyboard::Scan::RSystem)
    .value("Back", sf::Keyboard::Scan::Back)
    .value("Forward", sf::Keyboard::Scan::Forward)
    .value("Refresh", sf::Keyboard::Scan::Refresh)
    .value("Stop", sf::Keyboard::Scan::Stop)
    .value("Search", sf::Keyboard::Scan::Search)
    .value("Favorites", sf::Keyboard::Scan::Favorites)
    .value("HomePage", sf::Keyboard::Scan::HomePage)
    .value("LaunchApplication1", sf::Keyboard::Scan::LaunchApplication1)
    .value("LaunchApplication2", sf::Keyboard::Scan::LaunchApplication2)
    .value("LaunchMail", sf::Keyboard::Scan::LaunchMail)
    .value("LaunchMediaSelect", sf::Keyboard::Scan::LaunchMediaSelect)
    .export_values();

    // Binding the functions
    keyboard.def("is_key_pressed", [](sf::Keyboard::Key key) {
        return sf::Keyboard::isKeyPressed(key);
    });
    keyboard.def("is_key_pressed", [](sf::Keyboard::Scan scan) {
        return sf::Keyboard::isKeyPressed(scan);
    });
    keyboard.def("localize", &sf::Keyboard::localize);
    keyboard.def("delocalize", &sf::Keyboard::delocalize);
    keyboard.def("get_description", &sf::Keyboard::getDescription);
    keyboard.def("set_virtual_keyboard_visible", &sf::Keyboard::setVirtualKeyboardVisible);
}

void bind_mouse(py::module_ &m) {
    py::module_ mouse = m.def_submodule("Mouse");

    py::enum_<sf::Mouse::Button>(mouse, "Button")
    .value("Left", sf::Mouse::Button::Left)
    .value("Right", sf::Mouse::Button::Right)
    .value("Middle", sf::Mouse::Button::Middle)
    .value("Extra1", sf::Mouse::Button::Extra1)
    .value("Extra2", sf::Mouse::Button::Extra2)
    .export_values();
    
    py::enum_<sf::Mouse::Wheel>(mouse, "Wheel")
    .value("Vertical", sf::Mouse::Wheel::Vertical)
    .value("Horizontal", sf::Mouse::Wheel::Horizontal)
    .export_values();
    
    mouse.def("is_button_pressed", &sf::Mouse::isButtonPressed);
    mouse.def("get_position", []() {
        sf::Vector2i position = sf::Mouse::getPosition();
        return std::make_tuple(position.x, position.y);
    });
    mouse.def("get_position", [](sf::WindowBase& window) {
        sf::Vector2i position = sf::Mouse::getPosition(window);
        return std::make_tuple(position.x, position.y);
    });
    mouse.def("set_position", [](int x, int y) {
        sf::Mouse::setPosition(sf::Vector2i(x, y)); 
    });
    mouse.def("set_position", [](int x, int y, sf::WindowBase& window) {
        sf::Mouse::setPosition(sf::Vector2i(x, y), window); 
    });
}

void bind_sensor(py::module_ &m) {
    py::module_ sensor = m.def_submodule("Sensor");

    py::enum_<sf::Sensor::Type>(sensor, "Type")
    .value("Accelerometer", sf::Sensor::Type::Accelerometer)
    .value("Gyroscope", sf::Sensor::Type::Gyroscope)
    .value("Magnetometer", sf::Sensor::Type::Magnetometer)
    .value("Gravity", sf::Sensor::Type::Gravity)
    .value("UserAcceleration", sf::Sensor::Type::UserAcceleration)
    .value("Orientation", sf::Sensor::Type::Orientation)
    .export_values();
    
    sensor.def("is_available", &sf::Sensor::isAvailable);
    sensor.def("set_enabled", &sf::Sensor::setEnabled);
    sensor.def("get_value", &sf::Sensor::getValue);
}

void bind_touch(py::module_ &m) {
    py::module_ touch = m.def_submodule("Touch");

    touch.def("isDown", &sf::Touch::isDown);
    touch.def("getPosition", [](unsigned int finger) {
        sf::Vector2i position = sf::Touch::getPosition(finger);
        return sf::Vector2i(position.x, position.y);
    });
    touch.def("getPosition", [](unsigned int finger, sf::WindowBase& relativeTo) {
        sf::Vector2i position = sf::Touch::getPosition(finger, relativeTo);
        return sf::Vector2i(position.x, position.y);
    });
}
