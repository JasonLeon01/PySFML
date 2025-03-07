#include <network.h>

void bind_ip_address(py::module &m) {
    py::class_<sf::IpAddress>(m, "IpAddress")
    .def_static("resolve", [](const std::string& host) { return sf::IpAddress::resolve(host); }, py::arg("host"))
    .def(py::init<std::uint8_t, std::uint8_t, std::uint8_t, std::uint8_t>(), py::arg("byte0"), py::arg("byte1"), py::arg("byte2"), py::arg("byte3"))
    .def(py::init<std::uint32_t>(), py::arg("address"))
    .def("to_string", &sf::IpAddress::toString)
    .def("to_integer", &sf::IpAddress::toInteger)
    .def_static("get_local_address", &sf::IpAddress::getLocalAddress)
    .def_static("get_public_address", &sf::IpAddress::getPublicAddress, py::arg("timeout") = sf::Time::Zero)
    .def_static("Any", []() { return sf::IpAddress::Any; })
    .def_static("LocalHost", []() { return sf::IpAddress::LocalHost; })
    .def_static("Broadcast", []() { return sf::IpAddress::Broadcast; })
    .def("__lt__", [](const sf::IpAddress& left, const sf::IpAddress& right) { return left < right; })
    .def("__le__", [](const sf::IpAddress& left, const sf::IpAddress& right) { return left <= right; })
    .def("__eq__", [](const sf::IpAddress& left, const sf::IpAddress& right) { return left == right; })
    .def("__ne__", [](const sf::IpAddress& left, const sf::IpAddress& right) { return left != right; })
    .def("__gt__", [](const sf::IpAddress& left, const sf::IpAddress& right) { return left > right; })
    .def("__ge__", [](const sf::IpAddress& left, const sf::IpAddress& right) { return left >= right; })
    .def("__repr__", [](const sf::IpAddress& ip) { return "<sf.IpAddress: " + ip.toString() + ">"; });
}

void bind_ftp(py::module &m) {
    py::class_<sf::Ftp> ftp(m, "Ftp");

    py::enum_<sf::Ftp::TransferMode>(ftp, "TransferMode")
    .value("Binary", sf::Ftp::TransferMode::Binary)
    .value("Ascii", sf::Ftp::TransferMode::Ascii)
    .value("Ebcdic", sf::Ftp::TransferMode::Ebcdic)
    .export_values();

    py::class_<sf::Ftp::Response> response(ftp, "Response");

    py::enum_<sf::Ftp::Response::Status>(response, "Status")
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
    .value("ConnectionClosed", sf::Ftp::Response::Status::ConnectionClosed)
    .export_values();

    response.def(py::init<>())
    .def(py::init<sf::Ftp::Response::Status, std::string>(), py::arg("status") = sf::Ftp::Response::Status::InvalidResponse, py::arg("message") = "")
    .def("is_ok", &sf::Ftp::Response::isOk)
    .def("get_status", &sf::Ftp::Response::getStatus)
    .def("get_message", &sf::Ftp::Response::getMessage);

    py::class_<sf::Ftp::DirectoryResponse, sf::Ftp::Response>(ftp, "DirectoryResponse")
    .def(py::init<const sf::Ftp::Response&>(), py::arg("response"))
    .def("get_directory", &sf::Ftp::DirectoryResponse::getDirectory);

    py::class_<sf::Ftp::ListingResponse, sf::Ftp::Response>(ftp, "ListingResponse")
    .def(py::init<const sf::Ftp::Response&, const std::string&>(), py::arg("response"), py::arg("data"))
    .def("get_listing", &sf::Ftp::ListingResponse::getListing);

    ftp.def(py::init<>())
    .def("connect", &sf::Ftp::connect, py::arg("server"), py::arg("port") = 21, py::arg("timeout") = sf::Time::Zero)
    .def("disconnect", &sf::Ftp::disconnect)
    .def("login", [](sf::Ftp& self) {
       return self.login();
    })
    .def("login", [](sf::Ftp& self, const std::string& username, const std::string& password) {
       return self.login(username, password);
    }, py::arg("username"), py::arg("password"))
    .def("keep_alive", &sf::Ftp::keepAlive)
    .def("get_working_directory", &sf::Ftp::getWorkingDirectory)
    .def("get_directory_listing", &sf::Ftp::getDirectoryListing, py::arg("directory") = "")
    .def("change_directory", &sf::Ftp::changeDirectory, py::arg("name"))
    .def("parent_directory", &sf::Ftp::parentDirectory)
    .def("create_directory", &sf::Ftp::createDirectory, py::arg("name"))
    .def("delete_directory", &sf::Ftp::deleteDirectory, py::arg("name"))
    .def("rename_file", [](sf::Ftp& self, const std::string& file, const std::string& newName) {
       return self.renameFile(file, newName);
    }, py::arg("file"), py::arg("newName"))
    .def("delete_file", [](sf::Ftp& self, const std::string& file) {
       return self.deleteFile(file);
    })
    .def("download", [](sf::Ftp& self, const std::string& remoteFile, const std::string& localPath, sf::Ftp::TransferMode mode) {
       return self.download(remoteFile, localPath, mode);
    }, py::arg("remoteFile"), py::arg("localPath"), py::arg("mode") = sf::Ftp::TransferMode::Binary)
    .def("upload", [](sf::Ftp& self, const std::string& localFile, const std::string& remotePath, sf::Ftp::TransferMode mode, bool append) {
       return self.upload(localFile, remotePath, mode, append);
    }, py::arg("localFile"), py::arg("remotePath"), py::arg("mode") = sf::Ftp::TransferMode::Binary, py::arg("append") = false)
    .def("send_command", &sf::Ftp::sendCommand, py::arg("command"), py::arg("parameter") = "");
}

void bind_http(py::module &m) {
    py::class_<sf::Http> http(m, "Http");

    py::class_<sf::Http::Request> request(http, "Request");

    py::enum_<sf::Http::Request::Method>(request, "Method")
    .value("GET", sf::Http::Request::Method::Get)
    .value("POST", sf::Http::Request::Method::Post)
    .value("HEAD", sf::Http::Request::Method::Head)
    .value("PUT", sf::Http::Request::Method::Put)
    .value("DELETE", sf::Http::Request::Method::Delete)
    .export_values();

    request.def(py::init<>())
    .def(py::init<const std::string&, sf::Http::Request::Method, const std::string&>(), py::arg("uri") = "/", py::arg("method") = sf::Http::Request::Method::Get, py::arg("body") = "")
    .def("set_field", &sf::Http::Request::setField, py::arg("field"), py::arg("value"))
    .def("set_method", &sf::Http::Request::setMethod, py::arg("method"))
    .def("set_uri", &sf::Http::Request::setUri, py::arg("uri"))
    .def("set_http_version", &sf::Http::Request::setHttpVersion, py::arg("major"), py::arg("minor"))
    .def("set_body", &sf::Http::Request::setBody, py::arg("body"));

    py::class_<sf::Http::Response> response(http, "Response");

    py::enum_<sf::Http::Response::Status>(response, "Status")
    .value("OK", sf::Http::Response::Status::Ok)
    .value("CREATED", sf::Http::Response::Status::Created)
    .value("NO_CONTENT", sf::Http::Response::Status::NoContent)
    .value("MOVED_PERMANENTLY", sf::Http::Response::Status::MovedPermanently)
    .value("BAD_REQUEST", sf::Http::Response::Status::BadRequest)
    .value("FORBIDDEN", sf::Http::Response::Status::Forbidden)
    .value("NOT_FOUND", sf::Http::Response::Status::NotFound)
    .value("INTERNAL_SERVER_ERROR", sf::Http::Response::Status::InternalServerError)
    .export_values();

    response.def(py::init<>())
    .def("get_field", &sf::Http::Response::getField, py::arg("field"))
    .def("get_status", &sf::Http::Response::getStatus)
    .def("get_major_http_version", &sf::Http::Response::getMajorHttpVersion)
    .def("get_minor_http_version", &sf::Http::Response::getMinorHttpVersion)
    .def("get_body", &sf::Http::Response::getBody);

    http.def(py::init<>())
    .def(py::init<const std::string&, unsigned short>(), py::arg("host"), py::arg("port") = 0)
    .def("set_host", &sf::Http::setHost, py::arg("host"), py::arg("port") = 0)
    .def("send_request", &sf::Http::sendRequest, py::arg("request"), py::arg("timeout") = sf::Time::Zero);
}

void bind_packet(py::module_ &m) {
    py::class_<sf::Packet>(m, "Packet")
    .def(py::init<>())
    .def("append", &sf::Packet::append, py::arg("data"), py::arg("sizeInBytes"))
    .def("get_read_position", &sf::Packet::getReadPosition)
    .def("clear", &sf::Packet::clear)
    .def("get_data", &sf::Packet::getData)
    .def("get_data_size", &sf::Packet::getDataSize)
    .def("end_of_packet", &sf::Packet::endOfPacket)
    .def("__bool__", [](const sf::Packet& packet) { return static_cast<bool>(packet); })
    .def("__rshift__", [](sf::Packet& packet, bool& data) { packet >> data; return packet; }, py::arg("data"))
    .def("__rshift__", [](sf::Packet& packet, std::int8_t& data) { packet >> data; return packet; }, py::arg("data"))
    .def("__rshift__", [](sf::Packet& packet, std::uint8_t& data) { packet >> data; return packet; }, py::arg("data"))
    .def("__rshift__", [](sf::Packet& packet, std::int16_t& data) { packet >> data; return packet; }, py::arg("data"))
    .def("__rshift__", [](sf::Packet& packet, std::uint16_t& data) { packet >> data; return packet; }, py::arg("data"))
    .def("__rshift__", [](sf::Packet& packet, std::int32_t& data) { packet >> data; return packet; }, py::arg("data"))
    .def("__rshift__", [](sf::Packet& packet, std::uint32_t& data) { packet >> data; return packet; }, py::arg("data"))
    .def("__rshift__", [](sf::Packet& packet, std::int64_t& data) { packet >> data; return packet; }, py::arg("data"))
    .def("__rshift__", [](sf::Packet& packet, std::uint64_t& data) { packet >> data; return packet; }, py::arg("data"))
    .def("__rshift__", [](sf::Packet& packet, float& data) { packet >> data; return packet; }, py::arg("data"))
    .def("__rshift__", [](sf::Packet& packet, double& data) { packet >> data; return packet; }, py::arg("data"))
    .def("__rshift__", [](sf::Packet& packet, char* data) { packet >> data; return packet; }, py::arg("data"))
    .def("__rshift__", [](sf::Packet& packet, std::string& data) { packet >> data; return packet; }, py::arg("data"))
    .def("__rshift__", [](sf::Packet& packet, wchar_t* data) { packet >> data; return packet; }, py::arg("data"))
    .def("__rshift__", [](sf::Packet& packet, std::wstring& data) { packet >> data; return packet; }, py::arg("data"))
    .def("__lshift__", [](sf::Packet& packet, const bool& data) { packet << data; return packet; }, py::arg("data"))
    .def("__lshift__", [](sf::Packet& packet, const std::int8_t& data) { packet << data; return packet; }, py::arg("data"))
    .def("__lshift__", [](sf::Packet& packet, const std::uint8_t& data) { packet << data; return packet; }, py::arg("data"))
    .def("__lshift__", [](sf::Packet& packet, const std::int16_t& data) { packet << data; return packet; }, py::arg("data"))
    .def("__lshift__", [](sf::Packet& packet, const std::uint16_t& data) { packet << data; return packet; }, py::arg("data"))
    .def("__lshift__", [](sf::Packet& packet, const std::int32_t& data) { packet << data; return packet; }, py::arg("data"))
    .def("__lshift__", [](sf::Packet& packet, const std::uint32_t& data) { packet << data; return packet; }, py::arg("data"))
    .def("__lshift__", [](sf::Packet& packet, const std::int64_t& data) { packet << data; return packet; }, py::arg("data"))
    .def("__lshift__", [](sf::Packet& packet, const std::uint64_t& data) { packet << data; return packet; }, py::arg("data"))
    .def("__lshift__", [](sf::Packet& packet, const float& data) { packet << data; return packet; }, py::arg("data"))
    .def("__lshift__", [](sf::Packet& packet, const double& data) { packet << data; return packet; }, py::arg("data"))
    .def("__lshift__", [](sf::Packet& packet, const char* data) { packet << data; return packet; }, py::arg("data"))
    .def("__lshift__", [](sf::Packet& packet, const std::string& data) { packet << data; return packet; }, py::arg("data"))
    .def("__lshift__", [](sf::Packet& packet, const wchar_t* data) { packet << data; return packet; }, py::arg("data"))
    .def("__lshift__", [](sf::Packet& packet, const std::wstring& data) { packet << data; return packet; }, py::arg("data"));
}

void bind_socket(py::module_ &m) {
    py::class_<sf::Socket> socket(m, "Socket");

    py::enum_<sf::Socket::Status>(socket, "Status")
    .value("Done", sf::Socket::Status::Done)
    .value("NotReady", sf::Socket::Status::NotReady)
    .value("Partial", sf::Socket::Status::Partial)
    .value("Disconnected", sf::Socket::Status::Disconnected)
    .value("Error", sf::Socket::Status::Error)
    .export_values();

    socket.def("set_blocking", &sf::Socket::setBlocking)
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
    .def("add", &sf::SocketSelector::add, py::arg("socket"))
    .def("remove", &sf::SocketSelector::remove, py::arg("socket"))
    .def("clear", &sf::SocketSelector::clear)
    .def("wait", &sf::SocketSelector::wait, py::arg("timeout") = sf::Time::Zero)
    .def("is_ready", &sf::SocketSelector::isReady, py::arg("socket"));
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
    .def("send", [](sf::TcpSocket& self, const void* data, std::size_t size) {
        return self.send(data, size);
    }, py::arg("data"), py::arg("size"))
    .def("send", [](sf::TcpSocket& self, const void* data, std::size_t size, std::size_t& sent) {
        return self.send(data, size, sent);
    }, py::arg("data"), py::arg("size"), py::arg("sent"))
    .def("receive", [](sf::TcpSocket& self, void* data, std::size_t size, std::size_t& received) {
        return self.receive(data, size, received);
    }, py::arg("data"), py::arg("size"), py::arg("received"))
    .def("send", [](sf::TcpSocket& self, const void* data, std::size_t size) {
        return self.send(data, size);
    }, py::arg("data"), py::arg("size"))
    .def("send", [](sf::TcpSocket& self, const void* data, std::size_t size, std::size_t& sent) {
        return self.send(data, size, sent);
    }, py::arg("data"), py::arg("size"), py::arg("sent"))
    .def("send", [](sf::TcpSocket& self, sf::Packet& packet) {
        return self.send(packet);
    }, py::arg("packet"))
    .def("receive", [](sf::TcpSocket& self, void* data, std::size_t size, std::size_t& received) {
        return self.receive(data, size, received);
    }, py::arg("data"), py::arg("size"), py::arg("received"))
    .def("receive", [](sf::TcpSocket& self, sf::Packet& packet) {
        return self.receive(packet);
    }, py::arg("packet"));
}

void bind_udp_socket(py::module &m) {
    py::class_<sf::UdpSocket, sf::Socket>(m, "UdpSocket")
    .def(py::init<>())
    .def("getLocalPort", &sf::UdpSocket::getLocalPort)
    .def("bind", &sf::UdpSocket::bind, py::arg("port"), py::arg("address") = sf::IpAddress::Any)
    .def("unbind", &sf::UdpSocket::unbind)
    .def("send", [](sf::UdpSocket& self, const void* data, std::size_t size, sf::IpAddress remoteAddress, unsigned short remotePort) {
        return self.send(data, size, remoteAddress, remotePort);
    }, py::arg("data"), py::arg("size"), py::arg("remoteAddress"), py::arg("remotePort"))
   .def("receive", [](sf::UdpSocket& self, void* data, std::size_t size, std::size_t& received, std::optional<sf::IpAddress>& remoteAddress, unsigned short& remotePort) {
        return self.receive(data, size, received, remoteAddress, remotePort);
    }, py::arg("data"), py::arg("size"), py::arg("received"), py::arg("remoteAddress"), py::arg("remotePort"))
    .def("send", [](sf::UdpSocket& self, sf::Packet& packet, sf::IpAddress remoteAddress, unsigned short remotePort) {
        return self.send(packet, remoteAddress, remotePort);
    }, py::arg("packet"), py::arg("remoteAddress"), py::arg("remotePort"))
    .def("receive", [](sf::UdpSocket& self, sf::Packet& packet, std::optional<sf::IpAddress>& remoteAddress, unsigned short& remotePort) {
        return self.receive(packet, remoteAddress, remotePort);
    }, py::arg("packet"), py::arg("remoteAddress"), py::arg("remotePort"));
}
