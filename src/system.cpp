#include <system.h>

void bind_angle(py::module &m) {
    py::class_<sf::Angle>(m, "Angle")
    .def(py::init<>())
    .def_static("degrees", &sf::degrees)
    .def_static("radians", &sf::radians)
    .def("as_degrees", &sf::Angle::asDegrees)
    .def("as_radians", &sf::Angle::asRadians)
    .def("wrap_signed", &sf::Angle::wrapSigned)
    .def("wrap_unsigned", &sf::Angle::wrapUnsigned)
    .def("__repr__", [](const sf::Angle &a) {
        return "<sf.Angle: " + std::to_string(a.asDegrees()) + " degrees>";
    })
    .def("__eq__", [](const sf::Angle &a, const sf::Angle &b) { return a == b; })
    .def("__ne__", [](const sf::Angle &a, const sf::Angle &b) { return a != b; })
    .def("__lt__", [](const sf::Angle &a, const sf::Angle &b) { return a < b; })
    .def("__le__", [](const sf::Angle &a, const sf::Angle &b) { return a <= b; })
    .def("__gt__", [](const sf::Angle &a, const sf::Angle &b) { return a > b; })
    .def("__ge__", [](const sf::Angle &a, const sf::Angle &b) { return a >= b; })
    .def("__add__", [](const sf::Angle &a, const sf::Angle &b) { return a + b; })
    .def("__sub__", [](const sf::Angle &a, const sf::Angle &b) { return a - b; })
    .def("__mul__", [](const sf::Angle &a, float b) { return a * b; })
    .def("__truediv__", [](const sf::Angle &a, float b) { return a / b; })
    .def("__mod__", [](const sf::Angle &a, const sf::Angle &b) { return a % b; })
    .def("__neg__", [](const sf::Angle &a) { return -a; })
    .def("__float__", &sf::Angle::asDegrees);
}

void bind_time(py::module &m) {
    py::class_<sf::Time>(m, "Time")
    .def("as_seconds", &sf::Time::asSeconds)
    .def("as_milliseconds", &sf::Time::asMilliseconds)
    .def("as_microseconds", &sf::Time::asMicroseconds)
    .def("to_duration", &sf::Time::toDuration)
    .def("__repr__", [](const sf::Time &t) {
        return "<sf.Time: " + std::to_string(t.asSeconds()) + " seconds>";
    });
}

void bind_clock(py::module &m) {
    py::class_<sf::Clock>(m, "Clock")
   .def(py::init<>())
   .def("start", &sf::Clock::start)
   .def("stop", &sf::Clock::stop)
   .def("restart", &sf::Clock::restart)
   .def("reset", &sf::Clock::reset)
   .def("get_elapsed_time", &sf::Clock::getElapsedTime)
   .def("__repr__", [](const sf::Clock &c) {
        return "<sf.Clock: " + std::to_string(c.getElapsedTime().asSeconds()) + " seconds>";
    });
}

void bind_input_stream(py::module &m) {
    py::class_<sf::InputStream>(m, "InputStream")
    .def("read", [](sf::InputStream& self, std::size_t count) {
        int64_t* samples = new int64_t[count];
        std::optional<long long unsigned int> readcount = self.read(samples, count);
        py::bytes bytes(reinterpret_cast<char*>(samples), count * sizeof(int64_t));
        delete[] samples;
        return bytes;
    }, "size")
    .def("seek", &sf::InputStream::seek)
    .def("tell", &sf::InputStream::tell)
    .def_property_readonly("size", &sf::InputStream::getSize);

    py::class_<sf::FileInputStream, sf::InputStream>(m, "FileInputStream")
    .def(py::init<>())
    .def("open", &sf::FileInputStream::open);
}
