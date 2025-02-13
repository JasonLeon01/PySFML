#include <pybind11/pybind11.h>
#include <pybind11/pytypes.h>
#include <pybind11/stl.h>
#include <filesystem>
#include <optional>
#include <SFML/System.hpp>
#include <SFML/Network.hpp>

namespace py = pybind11;

#ifdef _WIN32
#  define SFML_API __declspec(dllexport)
#else
#  define SFML_API
#endif

void bind_ftp(py::module &m);
void bind_http(py::module &m);
void bind_ip_address(py::module &m);
void bind_packet(py::module_ &m);
void bind_socket(py::module_ &m);
void bind_socket_selector(py::module_ &m);
void bind_tcp_listener(py::module &m);
void bind_tcp_socket(py::module &m);
void bind_udp_socket(py::module &m);
