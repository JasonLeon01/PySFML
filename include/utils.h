#include <pybind11/pybind11.h>
#include <pybind11/pytypes.h>
#include <pybind11/stl.h>
#include <memory>
#include <vector>

namespace py = pybind11;

std::shared_ptr<std::vector<std::uint8_t>> pixel_array_ptr(py::buffer data);

const std::tuple<std::vector<int16_t>, std::uint64_t, unsigned int> pcm_array_ptr(py::buffer data, unsigned int sampleRate);
