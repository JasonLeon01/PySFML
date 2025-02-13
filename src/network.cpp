#include <network.h>

void bind_ftp(py::module &m) {
    py::enum_<sf::Ftp::Response::Status>(m, "FtpResponseStatus")
    .value("RestartMarkerReply", sf::Ftp::Response::Status::RestartMarkerReply)
    .value("ServiceReadySoon", sf::Ftp::Response::Status::ServiceReadySoon)
    .value("DataConnectionAlreadyOpened", sf::Ftp::Response::Status::DataConnectionAlreadyOpened)
    .value("OpeningDataConnection", sf::Ftp::Response::Status::OpeningDataConnection)
    .value("Ok", sf::Ftp::Response::Status::Ok)
    .value("PointlessCommand", sf::Ftp::Response::Status::PointlessCommand)
    .value("SystemStatus", sf::Ftp::Response::Status::SystemStatus)
    .value("DirectoryStatus", sf::Ftp::Response::Status::DirectoryStatus)
    .value("FileStatus", sf::Ftp::Response::Status::FileStatus)
    .value("InvalidResponse", sf::Ftp::Response::Status::InvalidResponse)
    .value("ConnectionFailed", sf::Ftp::Response::Status::ConnectionFailed)
    .value("ConnectionClosed", sf::Ftp::Response::Status::ConnectionClosed);

    py::class_<sf::Ftp::Response>(m, "FtpResponse")
    .def(py::init<sf::Ftp::Response::Status, std::string>(), py::arg("status") = sf::Ftp::Response::Status::InvalidResponse, py::arg("message") = "")
    .def("is_ok", &sf::Ftp::Response::isOk)
    .def("get_status", &sf::Ftp::Response::getStatus)
    .def("get_message", &sf::Ftp::Response::getMessage);

    py::class_<sf::Ftp> ftp(m, "Ftp");
    ftp.def(py::init<>())
    .def("connect", &sf::Ftp::connect, py::arg("server"), py::arg("port") = 21, py::arg("timeout") = sf::Time::Zero)
    .def("disconnect", &sf::Ftp::disconnect)
    .def("login", py::overload_cast<>(&sf::Ftp::login))
    .def("login", py::overload_cast<const std::string&, const std::string&>(&sf::Ftp::login), py::arg("name"), py::arg("password"));
}

void bind_http(py::module &m) {
    py::enum_<sf::Http::Request::Method>(m, "HttpMethod")
    .value("GET", sf::Http::Request::Method::Get)
    .value("POST", sf::Http::Request::Method::Post)
    .value("HEAD", sf::Http::Request::Method::Head)
    .value("PUT", sf::Http::Request::Method::Put)
    .value("DELETE", sf::Http::Request::Method::Delete);

    py::enum_<sf::Http::Response::Status>(m, "HttpStatus")
    .value("OK", sf::Http::Response::Status::Ok)
    .value("CREATED", sf::Http::Response::Status::Created)
    .value("NO_CONTENT", sf::Http::Response::Status::NoContent)
    .value("MOVED_PERMANENTLY", sf::Http::Response::Status::MovedPermanently)
    .value("BAD_REQUEST", sf::Http::Response::Status::BadRequest)
    .value("FORBIDDEN", sf::Http::Response::Status::Forbidden)
    .value("NOT_FOUND", sf::Http::Response::Status::NotFound)
    .value("INTERNAL_SERVER_ERROR", sf::Http::Response::Status::InternalServerError);

    py::class_<sf::Http::Request>(m, "HttpRequest")
    .def(py::init<const std::string&, sf::Http::Request::Method, const std::string&>(),
            py::arg("uri") = "", py::arg("method") = sf::Http::Request::Method::Get, py::arg("body") = "")
    .def("set_method", &sf::Http::Request::setMethod)
    .def("set_uri", &sf::Http::Request::setUri)
    .def("set_http_version", &sf::Http::Request::setHttpVersion)
    .def("set_body", &sf::Http::Request::setBody)
    .def("set_field", &sf::Http::Request::setField);

    py::class_<sf::Http::Response>(m, "HttpResponse")
    .def("get_status", &sf::Http::Response::getStatus)
    .def("get_body", &sf::Http::Response::getBody)
    .def("get_field", &sf::Http::Response::getField);

    py::class_<sf::Http>(m, "Http")
    .def(py::init<const std::string&, unsigned short>(), py::arg("host") = "", py::arg("port") = 0)
    .def("set_host", &sf::Http::setHost)
    .def("send_request", &sf::Http::sendRequest);
}

void bind_ip_address(py::module &m) {
    py::class_<sf::IpAddress>(m, "IpAddress")
    .def_static("resolve", [](const std::string& host) { return sf::IpAddress::resolve(host); }, py::arg("host"))
    .def(py::init<std::uint8_t, std::uint8_t, std::uint8_t, std::uint8_t>())
    .def(py::init<std::uint32_t>())
    .def("to_string", &sf::IpAddress::toString)
    .def("to_integer", &sf::IpAddress::toInteger)
    .def_static("get_local_address", &sf::IpAddress::getLocalAddress)
    .def_static("get_public_address", &sf::IpAddress::getPublicAddress, py::arg("timeout") = sf::Time::Zero)
    .def_static("resolve", &sf::IpAddress::resolve, py::arg("host"))
    .def("__lt__", [](const sf::IpAddress& left, const sf::IpAddress& right) { return left < right; })
    .def("__le__", [](const sf::IpAddress& left, const sf::IpAddress& right) { return left <= right; })
    .def("__eq__", [](const sf::IpAddress& left, const sf::IpAddress& right) { return left == right; })
    .def("__ne__", [](const sf::IpAddress& left, const sf::IpAddress& right) { return left != right; })
    .def("__gt__", [](const sf::IpAddress& left, const sf::IpAddress& right) { return left > right; })
    .def("__ge__", [](const sf::IpAddress& left, const sf::IpAddress& right) { return left >= right; })
    .def("__repr__", [](const sf::IpAddress& ip) { return "<sf.IpAddress: " + ip.toString() + ">"; });
}

void bind_packet(py::module_ &m) {
    py::class_<sf::Packet>(m, "Packet")
    .def("append", &sf::Packet::append)
    .def("get_read_position", &sf::Packet::getReadPosition)
    .def("clear", &sf::Packet::clear)
    .def("get_data", &sf::Packet::getData)
    .def("get_data_size", &sf::Packet::getDataSize)
    .def("end_of_packet", &sf::Packet::endOfPacket)
    .def("__bool__", [](const sf::Packet& packet) { return static_cast<bool>(packet); })
    .def("__rshift__", [](sf::Packet& packet, bool& data) { packet >> data; return packet; })
    .def("__rshift__", [](sf::Packet& packet, std::int8_t& data) { packet >> data; return packet; })
    .def("__rshift__", [](sf::Packet& packet, std::uint8_t& data) { packet >> data; return packet; })
    .def("__rshift__", [](sf::Packet& packet, std::int16_t& data) { packet >> data; return packet; })
    .def("__rshift__", [](sf::Packet& packet, std::uint16_t& data) { packet >> data; return packet; })
    .def("__rshift__", [](sf::Packet& packet, std::int32_t& data) { packet >> data; return packet; })
    .def("__rshift__", [](sf::Packet& packet, std::uint32_t& data) { packet >> data; return packet; })
    .def("__rshift__", [](sf::Packet& packet, std::int64_t& data) { packet >> data; return packet; })
    .def("__rshift__", [](sf::Packet& packet, std::uint64_t& data) { packet >> data; return packet; })
    .def("__rshift__", [](sf::Packet& packet, float& data) { packet >> data; return packet; })
    .def("__rshift__", [](sf::Packet& packet, double& data) { packet >> data; return packet; })
    .def("__rshift__", [](sf::Packet& packet, char* data) { packet >> data; return packet; })
    .def("__rshift__", [](sf::Packet& packet, std::string& data) { packet >> data; return packet; })
    .def("__rshift__", [](sf::Packet& packet, wchar_t* data) { packet >> data; return packet; })
    .def("__rshift__", [](sf::Packet& packet, std::wstring& data) { packet >> data; return packet; })
    .def("__lshift__", [](sf::Packet& packet, const bool& data) { packet << data; return packet; })
    .def("__lshift__", [](sf::Packet& packet, const std::int8_t& data) { packet << data; return packet; })
    .def("__lshift__", [](sf::Packet& packet, const std::uint8_t& data) { packet << data; return packet; })
    .def("__lshift__", [](sf::Packet& packet, const std::int16_t& data) { packet << data; return packet; })
    .def("__lshift__", [](sf::Packet& packet, const std::uint16_t& data) { packet << data; return packet; })
    .def("__lshift__", [](sf::Packet& packet, const std::int32_t& data) { packet << data; return packet; })
    .def("__lshift__", [](sf::Packet& packet, const std::uint32_t& data) { packet << data; return packet; })
    .def("__lshift__", [](sf::Packet& packet, const std::int64_t& data) { packet << data; return packet; })
    .def("__lshift__", [](sf::Packet& packet, const std::uint64_t& data) { packet << data; return packet; })
    .def("__lshift__", [](sf::Packet& packet, const float& data) { packet << data; return packet; })
    .def("__lshift__", [](sf::Packet& packet, const double& data) { packet << data; return packet; })
    .def("__lshift__", [](sf::Packet& packet, const char* data) { packet << data; return packet; })
    .def("__lshift__", [](sf::Packet& packet, const std::string& data) { packet << data; return packet; })
    .def("__lshift__", [](sf::Packet& packet, const wchar_t* data) { packet << data; return packet; })
    .def("__lshift__", [](sf::Packet& packet, const std::wstring& data) { packet << data; return packet; });
}

void bind_socket(py::module_ &m) {
    py::class_<sf::Socket>(m, "Socket")
    .def("set_blocking", &sf::Socket::setBlocking)
    .def("is_blocking", &sf::Socket::isBlocking);

    #if defined(SFML_SYSTEM_WINDOWS)
        py::class_<sf::SocketHandle>(m, "SocketHandle")
        .def(py::init<>())
        .def("get_value", [](const sf::SocketHandle& handle) -> UINT_PTR {
            return reinterpret_cast<UINT_PTR>(handle);
        });
    #else
        py::class_<sf::SocketHandle>(m, "SocketHandle")
        .def(py::init<>())
        .def("get_value", [](const sf::SocketHandle& handle) -> int {
            return static_cast<int>(handle);
        });
    #endif
}

void bind_socket_selector(py::module_ &m) {
    py::class_<sf::SocketSelector>(m, "SocketSelector")
        .def(py::init<>())
        .def("add", &sf::SocketSelector::add)
        .def("remove", &sf::SocketSelector::remove)
        .def("clear", &sf::SocketSelector::clear)
        .def("wait", &sf::SocketSelector::wait, py::arg("timeout") = sf::Time::Zero)
        .def("is_ready", &sf::SocketSelector::isReady);
}

void bind_tcp_listener(py::module &m) {
    py::class_<sf::TcpListener, sf::Socket>(m, "TcpListener")
        .def(py::init<>())
        .def("get_local_port", &sf::TcpListener::getLocalPort)
        .def("listen", &sf::TcpListener::listen, py::arg("port"), py::arg("address") = sf::IpAddress::Any)
        .def("close", &sf::TcpListener::close)
        .def("accept", &sf::TcpListener::accept, py::arg("socket"));
}

void bind_tcp_socket(py::module &m) {
    py::class_<sf::TcpSocket, sf::Socket>(m, "TcpSocket")
    .def(py::init<>())
    .def("get_local_port", &sf::TcpSocket::getLocalPort)
    .def("get_remote_address", &sf::TcpSocket::getRemoteAddress)
    .def("get_remote_port", &sf::TcpSocket::getRemotePort)
    .def("connect", &sf::TcpSocket::connect, py::arg("remoteAddress"), py::arg("remotePort"), py::arg("timeout") = sf::Time::Zero)
    .def("disconnect", &sf::TcpSocket::disconnect)
    .def("send", (sf::Socket::Status (sf::TcpSocket::*)(const void*, std::size_t)) &sf::TcpSocket::send)
    .def("send", (sf::Socket::Status (sf::TcpSocket::*)(const void*, std::size_t, std::size_t&)) &sf::TcpSocket::send)
    .def("receive", (sf::Socket::Status (sf::TcpSocket::*)(void*, std::size_t, std::size_t&)) &sf::TcpSocket::receive)
    .def("send", [](sf::TcpSocket& self, const void* data, std::size_t size) {
        return self.send(data, size);
    })
    .def("send", [](sf::TcpSocket& self, const void* data, std::size_t size, std::size_t& sent) {
        return self.send(data, size, sent); 
    })
    .def("send", [](sf::TcpSocket& self, sf::Packet& packet) {
        return self.send(packet);
    })
    .def("receive", [](sf::TcpSocket& self, void* data, std::size_t size, std::size_t& received) {
        return self.receive(data, size, received);
    })
    .def("receive", [](sf::TcpSocket& self, sf::Packet& packet) {
        return self.receive(packet);
    });
}

void bind_udp_socket(py::module &m) {
    py::class_<sf::UdpSocket, sf::Socket>(m, "UdpSocket")
    .def(py::init<>())
    .def("getLocalPort", &sf::UdpSocket::getLocalPort)
    .def("bind", &sf::UdpSocket::bind, py::arg("port"), py::arg("address") = sf::IpAddress::Any)
    .def("unbind", &sf::UdpSocket::unbind)
    .def("send", [](sf::UdpSocket& self, const void* data, std::size_t size, sf::IpAddress remoteAddress, unsigned short remotePort) {
        return self.send(data, size, remoteAddress, remotePort);
    })
   .def("receive", [](sf::UdpSocket& self, void* data, std::size_t size, std::size_t& received, std::optional<sf::IpAddress>& remoteAddress, unsigned short& remotePort) {
        return self.receive(data, size, received, remoteAddress, remotePort);
    })
    .def("send", [](sf::UdpSocket& self, sf::Packet& packet, sf::IpAddress remoteAddress, unsigned short remotePort) {
        return self.send(packet, remoteAddress, remotePort);
    })
    .def("receive", [](sf::UdpSocket& self, sf::Packet& packet, std::optional<sf::IpAddress>& remoteAddress, unsigned short& remotePort) {
        return self.receive(packet, remoteAddress, remotePort);
    });
}
