#include <utils.h>
#include <algorithm>

std::shared_ptr<std::vector<std::uint8_t>> pixel_array_ptr(py::buffer data) {
    py::buffer_info info = data.request();
    if (info.ndim != 3 || info.shape[2] != 4) {
        throw std::runtime_error("Expected 3D buffer with shape [height, width, 4]");
    }

    int height = info.shape[0];
    int width = info.shape[1];
    int channels = info.shape[2];

    auto* ptr = static_cast<std::uint8_t*>(info.ptr);
    std::shared_ptr<std::vector<std::uint8_t>> flatPixels = std::make_shared<std::vector<std::uint8_t>>(ptr, ptr + width * height * channels);
    return flatPixels;
}

const std::tuple<std::vector<int16_t>, std::uint64_t, unsigned int> pcm_array_ptr(py::buffer data, unsigned int sampleRate) {
    py::buffer_info info = data.request();
    if (info.ndim != 2) {
        throw std::runtime_error("Expected 2D buffer with shape [n_samples, n_channels]");
    }

    const std::size_t n_samples = info.shape[0];
    const std::size_t n_channels = info.shape[1];
    const std::size_t total_samples = n_samples * n_channels;

    auto* ptr = static_cast<float*>(info.ptr);
    std::vector<int16_t> pcm;
    pcm.reserve(total_samples);

    for (std::size_t i = 0; i < total_samples; ++i) {
        float sample = std::clamp(ptr[i], -1.0f, 1.0f);
        pcm.push_back(static_cast<int16_t>(sample * 32767));
    }

    return std::make_tuple(pcm, static_cast<std::uint64_t>(total_samples), static_cast<unsigned int>(n_channels));
}