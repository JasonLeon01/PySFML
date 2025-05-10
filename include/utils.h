#include <pybind11/pybind11.h>
#include <pybind11/pytypes.h>
#include <vector>

namespace py = pybind11;

const std::uint8_t* pixel_array_ptr(std::vector<std::vector<std::vector<std::uint8_t>>> pixels);

const std::tuple<std::int16_t*, std::uint64_t, unsigned int> pcm_array_ptr(std::vector<std::vector<float>> float_array, unsigned int sampleRate);