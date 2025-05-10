#include <utils.h>
#include <algorithm>

const std::uint8_t* pixel_array_ptr(std::vector<std::vector<std::vector<std::uint8_t>>> pixels) {
    int width = pixels[0].size();
    int height = pixels.size();
    std::vector<std::uint8_t> flatPixels;
    flatPixels.reserve(width * height * 4);

    for (const auto& row : pixels) {
        for (const auto& pixel : row) {
            for (std::uint8_t channel : pixel) {
                flatPixels.push_back(channel);
            }
        }
    }

    return flatPixels.data();
}

const std::tuple<std::int16_t*, std::uint64_t, unsigned int> pcm_array_ptr(std::vector<std::vector<float>> float_array, unsigned int sampleRate) {
    const std::size_t n_samples = float_array.size();
    const std::size_t n_channels = float_array[0].size();
    const std::size_t total_samples = n_samples * n_channels;

    std::vector<int16_t> pcm;
    pcm.reserve(n_samples * n_channels);

    for (pybind11::ssize_t i = 0; i < n_samples; ++i) {
        for (pybind11::ssize_t j = 0; j < n_channels; ++j) {
            float sample = float_array[i][j];
            sample = std::max(-1.0f, std::min(1.0f, sample));
            pcm.push_back(static_cast<int16_t>(sample * 32767));
        }
    }

    auto pcm_ptr = pcm.data();

    return std::make_tuple(pcm_ptr, static_cast<std::uint64_t>(total_samples), static_cast<unsigned int>(n_channels));
}