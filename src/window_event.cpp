#include <window_event.h>

void bind_event(py::module_ &m) {
    py::class_<sf::Event> event(m, "Event");

    py::class_<sf::Event::Closed>(event, "Closed")
    .def(py::init<>());

    py::class_<sf::Event::Resized>(event, "Resized")
    .def(py::init<>())
    .def_readonly("size", &sf::Event::Resized::size);

    py::class_<sf::Event::FocusLost>(event, "FocusLost")
    .def(py::init<>());

    py::class_<sf::Event::FocusGained>(event, "FocusGained")
    .def(py::init<>());

    py::class_<sf::Event::TextEntered>(event, "TextEntered")
    .def(py::init<>())
    .def_readonly("unicode", &sf::Event::TextEntered::unicode);

    py::class_<sf::Event::KeyPressed>(event, "KeyPressed")
    .def(py::init<>())
    .def_readonly("code", &sf::Event::KeyPressed::code)
    .def_readonly("scancode", &sf::Event::KeyPressed::scancode)
    .def_readonly("alt", &sf::Event::KeyPressed::alt)
    .def_readonly("control", &sf::Event::KeyPressed::control)
    .def_readonly("shift", &sf::Event::KeyPressed::shift)
    .def_readonly("system", &sf::Event::KeyPressed::system);

    py::class_<sf::Event::KeyReleased>(event, "KeyReleased")
    .def(py::init<>())
    .def_readonly("code", &sf::Event::KeyReleased::code)
    .def_readonly("scancode", &sf::Event::KeyReleased::scancode)
    .def_readonly("alt", &sf::Event::KeyReleased::alt)
    .def_readonly("control", &sf::Event::KeyReleased::control)
    .def_readonly("shift", &sf::Event::KeyReleased::shift)
    .def_readonly("system", &sf::Event::KeyReleased::system);

    py::class_<sf::Event::MouseWheelScrolled>(event, "MouseWheelScrolled")
    .def(py::init<>())
    .def_readonly("wheel", &sf::Event::MouseWheelScrolled::wheel)
    .def_readonly("delta", &sf::Event::MouseWheelScrolled::delta)
    .def_readonly("position", &sf::Event::MouseWheelScrolled::position);

    py::class_<sf::Event::MouseButtonPressed>(event, "MouseButtonPressed")
    .def(py::init<>())
    .def_readonly("button", &sf::Event::MouseButtonPressed::button)
    .def_readonly("position", &sf::Event::MouseButtonPressed::position);

    py::class_<sf::Event::MouseButtonReleased>(event, "MouseButtonReleased")
    .def(py::init<>())
    .def_readonly("button", &sf::Event::MouseButtonReleased::button)
    .def_readonly("position", &sf::Event::MouseButtonReleased::position);

    py::class_<sf::Event::MouseMoved>(event, "MouseMoved")
    .def(py::init<>())
    .def_readonly("position", &sf::Event::MouseMoved::position);

    py::class_<sf::Event::MouseMovedRaw>(event, "MouseMovedRaw")
    .def(py::init<>())
    .def_readonly("delta", &sf::Event::MouseMovedRaw::delta);

    py::class_<sf::Event::MouseEntered>(event, "MouseEntered")
    .def(py::init<>());

    py::class_<sf::Event::MouseLeft>(event, "MouseLeft")
    .def(py::init<>());

    py::class_<sf::Event::JoystickButtonPressed>(event, "JoystickButtonPressed")
    .def(py::init<>())
    .def_readonly("joystickId", &sf::Event::JoystickButtonPressed::joystickId)
    .def_readonly("button", &sf::Event::JoystickButtonPressed::button);

    py::class_<sf::Event::JoystickButtonReleased>(event, "JoystickButtonReleased")
    .def(py::init<>())
    .def_readonly("joystickId", &sf::Event::JoystickButtonReleased::joystickId)
    .def_readonly("button", &sf::Event::JoystickButtonReleased::button);

    py::class_<sf::Event::JoystickMoved>(event, "JoystickMoved")
    .def(py::init<>())
    .def_readonly("joystickId", &sf::Event::JoystickMoved::joystickId)
    .def_readonly("axis", &sf::Event::JoystickMoved::axis)
    .def_readonly("position", &sf::Event::JoystickMoved::position);

    py::class_<sf::Event::JoystickConnected>(event, "JoystickConnected")
    .def(py::init<>())
    .def_readonly("joystickId", &sf::Event::JoystickConnected::joystickId);

    py::class_<sf::Event::JoystickDisconnected>(event, "JoystickDisconnected")
    .def(py::init<>())
    .def_readonly("joystickId", &sf::Event::JoystickDisconnected::joystickId);

    py::class_<sf::Event::TouchBegan>(event, "TouchBegan")
    .def(py::init<>())
    .def_readonly("finger", &sf::Event::TouchBegan::finger)
    .def_readonly("position", &sf::Event::TouchBegan::position);

    py::class_<sf::Event::TouchMoved>(event, "TouchMoved")
    .def(py::init<>())
    .def_readonly("finger", &sf::Event::TouchMoved::finger)
    .def_readonly("position", &sf::Event::TouchMoved::position);

    py::class_<sf::Event::TouchEnded>(event, "TouchEnded")
    .def(py::init<>())
    .def_readonly("finger", &sf::Event::TouchEnded::finger)
    .def_readonly("position", &sf::Event::TouchEnded::position);

    py::class_<sf::Event::SensorChanged>(event, "SensorChanged")
    .def(py::init<>())
    .def_readonly("type", &sf::Event::SensorChanged::type)
    .def_readonly("value", &sf::Event::SensorChanged::value);

    event.def(py::init([](sf::Event::Closed &closed) { return sf::Event(closed); }))
    .def(py::init([](sf::Event::Resized &resized) { return sf::Event(resized); }))
    .def(py::init([](sf::Event::FocusLost &focusLost) { return sf::Event(focusLost); }))
    .def(py::init([](sf::Event::FocusGained &focusGained) { return sf::Event(focusGained); }))
    .def(py::init([](sf::Event::TextEntered &textEntered) { return sf::Event(textEntered); }))
    .def(py::init([](sf::Event::KeyPressed &keyPressed) { return sf::Event(keyPressed); }))
    .def(py::init([](sf::Event::KeyReleased &keyReleased) { return sf::Event(keyReleased); }))
    .def(py::init([](sf::Event::MouseWheelScrolled &mouseWheelScrolled) { return sf::Event(mouseWheelScrolled); }))
    .def(py::init([](sf::Event::MouseButtonPressed &mouseButtonPressed) { return sf::Event(mouseButtonPressed); }))
    .def(py::init([](sf::Event::MouseButtonReleased &mouseButtonReleased) { return sf::Event(mouseButtonReleased); }))
    .def(py::init([](sf::Event::MouseMoved &mouseMoved) { return sf::Event(mouseMoved); }))
    .def(py::init([](sf::Event::MouseMovedRaw &mouseMovedRaw) { return sf::Event(mouseMovedRaw); }))
    .def(py::init([](sf::Event::MouseEntered &mouseEntered) { return sf::Event(mouseEntered); }))
    .def(py::init([](sf::Event::MouseLeft &mouseLeft) { return sf::Event(mouseLeft); }))
    .def(py::init([](sf::Event::JoystickButtonPressed &joystickButtonPressed) { return sf::Event(joystickButtonPressed); }))
    .def(py::init([](sf::Event::JoystickButtonReleased &joystickButtonReleased) { return sf::Event(joystickButtonReleased); }))
    .def(py::init([](sf::Event::JoystickMoved &joystickMoved) { return sf::Event(joystickMoved); }))
    .def(py::init([](sf::Event::JoystickConnected &joystickConnected) { return sf::Event(joystickConnected); }))
    .def(py::init([](sf::Event::JoystickDisconnected &joystickDisconnected) { return sf::Event(joystickDisconnected); }))
    .def(py::init([](sf::Event::TouchBegan &touchBegan) { return sf::Event(touchBegan); }))
    .def(py::init([](sf::Event::TouchMoved &touchMoved) { return sf::Event(touchMoved); }))
    .def(py::init([](sf::Event::TouchEnded &touchEnded) { return sf::Event(touchEnded); }))
    .def(py::init([](sf::Event::SensorChanged &sensorChanged) { return sf::Event(sensorChanged); }))
    .def("isClosed", [](sf::Event& event) { return event.is<sf::Event::Closed>(); })
    .def("isResized", [](sf::Event& event) { return event.is<sf::Event::Resized>(); })
    .def("isFocusLost", [](sf::Event& event) { return event.is<sf::Event::FocusLost>(); })
    .def("isFocusGained", [](sf::Event& event) { return event.is<sf::Event::FocusGained>(); })
    .def("isTextEntered", [](sf::Event& event) { return event.is<sf::Event::TextEntered>(); })
    .def("isKeyPressed", [](sf::Event& event) { return event.is<sf::Event::KeyPressed>(); })
    .def("isKeyReleased", [](sf::Event& event) { return event.is<sf::Event::KeyReleased>(); })
    .def("isMouseWheelScrolled", [](sf::Event& event) { return event.is<sf::Event::MouseWheelScrolled>(); })
    .def("isMouseButtonPressed", [](sf::Event& event) { return event.is<sf::Event::MouseButtonPressed>(); })
    .def("isMouseButtonReleased", [](sf::Event& event) { return event.is<sf::Event::MouseButtonReleased>(); })
    .def("isMouseMoved", [](sf::Event& event) { return event.is<sf::Event::MouseMoved>(); })
    .def("isMouseMovedRaw", [](sf::Event& event) { return event.is<sf::Event::MouseMovedRaw>(); })
    .def("isMouseEntered", [](sf::Event& event) { return event.is<sf::Event::MouseEntered>(); })
    .def("isMouseLeft", [](sf::Event& event) { return event.is<sf::Event::MouseLeft>(); })
    .def("isJoystickButtonPressed", [](sf::Event& event) { return event.is<sf::Event::JoystickButtonPressed>(); })
    .def("isJoystickButtonReleased", [](sf::Event& event) { return event.is<sf::Event::JoystickButtonReleased>(); })
    .def("isJoystickMoved", [](sf::Event& event) { return event.is<sf::Event::JoystickMoved>(); })
    .def("isJoystickConnected", [](sf::Event& event) { return event.is<sf::Event::JoystickConnected>(); })
    .def("isJoystickDisconnected", [](sf::Event& event) { return event.is<sf::Event::JoystickDisconnected>(); })
    .def("isTouchBegan", [](sf::Event& event) { return event.is<sf::Event::TouchBegan>(); })
    .def("isTouchMoved", [](sf::Event& event) { return event.is<sf::Event::TouchMoved>(); })
    .def("isTouchEnded", [](sf::Event& event) { return event.is<sf::Event::TouchEnded>(); })
    .def("isSensorChanged", [](sf::Event& event) { return event.is<sf::Event::SensorChanged>(); })
    .def("getIfClosed", [](sf::Event& event) { return event.getIf<sf::Event::Closed>(); })
    .def("getIfResized", [](sf::Event& event) { return event.getIf<sf::Event::Resized>(); })
    .def("getIfFocused", [](sf::Event& event) { return event.getIf<sf::Event::FocusLost>(); })
    .def("getIfFocused", [](sf::Event& event) { return event.getIf<sf::Event::FocusGained>(); })
    .def("getIfTextEntered", [](sf::Event& event) { return event.getIf<sf::Event::TextEntered>(); })
    .def("getIfKeyPressed", [](sf::Event& event) { return event.getIf<sf::Event::KeyPressed>(); })
    .def("getIfKeyReleased", [](sf::Event& event) { return event.getIf<sf::Event::KeyReleased>(); })
    .def("getIfMouseWheelScrolled", [](sf::Event& event) { return event.getIf<sf::Event::MouseWheelScrolled>(); })
    .def("getIfMouseButtonPressed", [](sf::Event& event) { return event.getIf<sf::Event::MouseButtonPressed>(); })
    .def("getIfMouseButtonReleased", [](sf::Event& event) { return event.getIf<sf::Event::MouseButtonReleased>(); })
    .def("getIfMouseMoved", [](sf::Event& event) { return event.getIf<sf::Event::MouseMoved>(); })
    .def("getIfMouseMovedRaw", [](sf::Event& event) { return event.getIf<sf::Event::MouseMovedRaw>(); })
    .def("getIfMouseEntered", [](sf::Event& event) { return event.getIf<sf::Event::MouseEntered>(); })
    .def("getIfMouseLeft", [](sf::Event& event) { return event.getIf<sf::Event::MouseLeft>(); })
    .def("getIfJoystickButtonPressed", [](sf::Event& event) { return event.getIf<sf::Event::JoystickButtonPressed>(); })
    .def("getIfJoystickButtonReleased", [](sf::Event& event) { return event.getIf<sf::Event::JoystickButtonReleased>(); })
    .def("getIfJoystickMoved", [](sf::Event& event) { return event.getIf<sf::Event::JoystickMoved>(); })
    .def("getIfJoystickConnected", [](sf::Event& event) { return event.getIf<sf::Event::JoystickConnected>(); })
    .def("getIfJoystickDisconnected", [](sf::Event& event) { return event.getIf<sf::Event::JoystickDisconnected>(); })
    .def("getIfTouchBegan", [](sf::Event& event) { return event.getIf<sf::Event::TouchBegan>(); })
    .def("getIfTouchMoved", [](sf::Event& event) { return event.getIf<sf::Event::TouchMoved>(); })
    .def("getIfTouchEnded", [](sf::Event& event) { return event.getIf<sf::Event::TouchEnded>(); })
    .def("getIfSensorChanged", [](sf::Event& event) { return event.getIf<sf::Event::SensorChanged>(); });
}
