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
    .def_static("resolve", &sf::IpAddress::resolve, py::arg("host"));
}