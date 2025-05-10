#include <utils.h>
#include <algorithm>

const std::uint8_t* pixel_array_ptr(py::array_t<std::uint8_t> pixels) {
    if (pixels.ndim() != 3) {
        throw std::runtime_error("Array must be 3-dimensional");
    }
    auto info = pixels.request();
    if (info.shape[2] != 3 && info.shape[2] != 4) {
        throw std::runtime_error("Last dimension must be 3 (RGB) or 4 (RGBA)");
    }
    if (info.strides[2] != 1) {
        throw std::runtime_error("Array must be tightly packed in the last dimension");
    }
    if (info.format != py::format_descriptor<std::uint8_t>::format()) {
        throw std::runtime_error("Array dtype must be uint8");
    }
    if (!pixels.flags() & py::array::c_style) {
        throw std::runtime_error("Array must be C-contiguous");
    }
    return static_cast<const std::uint8_t*>(info.ptr);
}

const std::tuple<std::int16_t*, std::uint64_t, unsigned int> pcm_array_ptr(py::array_t<float> float_array, unsigned int sampleRate) {
    if (float_array.ndim() != 2) {
        throw std::runtime_error("Expected a 2D array (samples, channels)");
    }

    auto buf = float_array.unchecked<2>();
    const pybind11::ssize_t n_samples = buf.shape(0);
    const pybind11::ssize_t n_channels = buf.shape(1);
    const std::size_t total_samples = n_samples * n_channels;

    std::vector<int16_t> pcm;
    pcm.reserve(n_samples * n_channels);

    for (pybind11::ssize_t i = 0; i < n_samples; ++i) {
        for (pybind11::ssize_t j = 0; j < n_channels; ++j) {
            float sample = buf(i, j);
            sample = std::max(-1.0f, std::min(1.0f, sample));
            pcm.push_back(static_cast<int16_t>(sample * 32767));
        }
    }

    auto pcm_ptr = pcm.data();

    return std::make_tuple(pcm_ptr, static_cast<std::uint64_t>(total_samples), static_cast<unsigned int>(n_channels));
}