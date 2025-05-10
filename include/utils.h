#include <pybind11/pybind11.h>
#include <pybind11/pytypes.h>
#include <pybind11/numpy.h>

namespace py = pybind11;

const std::uint8_t* pixel_array_ptr(py::array_t<std::uint8_t> pixels);

const std::tuple<std::int16_t*, std::uint64_t, unsigned int> pcm_array_ptr(py::array_t<float> float_array, unsigned int sampleRate);