#include <audio.h>
#include <utils.h>

void bind_sound_channel(py::module& m) {
    py::enum_<sf::SoundChannel>(m, "SoundChannel")
    .value("Unspecified", sf::SoundChannel::Unspecified)
    .value("Mono", sf::SoundChannel::Mono)
    .value("FrontLeft", sf::SoundChannel::FrontLeft)
    .value("FrontRight", sf::SoundChannel::FrontRight)
    .value("FrontCenter", sf::SoundChannel::FrontCenter)
    .value("FrontLeftOfCenter", sf::SoundChannel::FrontLeftOfCenter)
    .value("FrontRightOfCenter", sf::SoundChannel::FrontRightOfCenter)
    .value("LowFrequencyEffects", sf::SoundChannel::LowFrequencyEffects)
    .value("BackLeft", sf::SoundChannel::BackLeft)
    .value("BackRight", sf::SoundChannel::BackRight)
    .value("BackCenter", sf::SoundChannel::BackCenter)
    .value("SideLeft", sf::SoundChannel::SideLeft)
    .value("SideRight", sf::SoundChannel::SideRight)
    .value("TopCenter", sf::SoundChannel::TopCenter)
    .value("TopFrontLeft", sf::SoundChannel::TopFrontLeft)
    .value("TopFrontRight", sf::SoundChannel::TopFrontRight)
    .value("TopFrontCenter", sf::SoundChannel::TopFrontCenter)
    .value("TopBackLeft", sf::SoundChannel::TopBackLeft)
    .value("TopBackRight", sf::SoundChannel::TopBackRight)
    .value("TopBackCenter", sf::SoundChannel::TopBackCenter)
    .export_values();
}

void bind_listener(py::module& m) {
    py::module_ listener = m.def_submodule("Listener");

    py::class_<sf::Listener::Cone>(listener, "Cone")
        .def(py::init<>())
        .def_readwrite("inner_angle", &sf::Listener::Cone::innerAngle)
        .def_readwrite("outer_angle", &sf::Listener::Cone::outerAngle)
        .def_readwrite("outer_gain", &sf::Listener::Cone::outerGain);

    listener.def("set_global_volume", &sf::Listener::setGlobalVolume, py::arg("volume"));
    listener.def("get_global_volume", &sf::Listener::getGlobalVolume);
    listener.def("set_position", &sf::Listener::setPosition, py::arg("position"));
    listener.def("get_position", &sf::Listener::getPosition);
    listener.def("set_direction", &sf::Listener::setDirection, py::arg("direction"));
    listener.def("get_direction", &sf::Listener::getDirection);
    listener.def("set_velocity", &sf::Listener::setVelocity, py::arg("velocity"));
    listener.def("get_velocity", &sf::Listener::getVelocity);
    listener.def("set_cone", &sf::Listener::setCone, py::arg("cone"));
    listener.def("get_cone", &sf::Listener::getCone);
    listener.def("set_up_vector", &sf::Listener::setUpVector, py::arg("upVector"));
    listener.def("get_up_vector", &sf::Listener::getUpVector);
}

sf::SoundSource::EffectProcessor wrap_effect_processor(py::function func) {
    return [func](const float* inputFrames, unsigned int& inputFrameCount,
                  float* outputFrames, unsigned int& outputFrameCount,
                  unsigned int frameChannelCount) {
        py::gil_scoped_acquire gil;  // Python 线程安全
        func(py::capsule(inputFrames), inputFrameCount,
             py::capsule(outputFrames), outputFrameCount,
             frameChannelCount);
    };
}

void bind_sound_source(py::module& m) {
    py::class_<sf::SoundSource, std::unique_ptr<sf::SoundSource, py::nodelete>> sound_source(m, "SoundSource");

    py::enum_<sf::SoundSource::Status>(sound_source, "Status")
    .value("Stopped", sf::SoundSource::Status::Stopped)
    .value("Paused", sf::SoundSource::Status::Paused)
    .value("Playing", sf::SoundSource::Status::Playing)
    .export_values();

    py::class_<sf::SoundSource::Cone>(sound_source, "Cone")
    .def(py::init<>())
    .def_readwrite("inner_angle", &sf::SoundSource::Cone::innerAngle)
    .def_readwrite("outer_angle", &sf::SoundSource::Cone::outerAngle)
    .def_readwrite("outer_gain", &sf::SoundSource::Cone::outerGain);

    sound_source.def("set_pitch", &sf::SoundSource::setPitch, py::arg("pitch"))
    .def("set_pan", &sf::SoundSource::setPan, py::arg("pan"))
    .def("set_volume", &sf::SoundSource::setVolume, py::arg("volume"))
    .def("set_spatialization_enabled", &sf::SoundSource::setSpatializationEnabled, py::arg("enabled"))
    .def("set_position", &sf::SoundSource::setPosition, py::arg("position"))
    .def("set_direction", &sf::SoundSource::setDirection, py::arg("direction"))
    .def("set_cone", &sf::SoundSource::setCone, py::arg("cone"))
    .def("set_velocity", &sf::SoundSource::setVelocity, py::arg("velocity"))
    .def("set_doppler_factor", &sf::SoundSource::setDopplerFactor, py::arg("factor"))
    .def("set_directional_attenuation_factor", &sf::SoundSource::setDirectionalAttenuationFactor, py::arg("factor"))
    .def("set_relative_to_listener", &sf::SoundSource::setRelativeToListener, py::arg("relative"))
    .def("set_min_distance", &sf::SoundSource::setMinDistance, py::arg("distance"))
    .def("set_max_distance", &sf::SoundSource::setMaxDistance, py::arg("distance"))
    .def("set_min_gain", &sf::SoundSource::setMinGain, py::arg("gain"))
    .def("set_max_gain", &sf::SoundSource::setMaxGain, py::arg("gain"))
    .def("set_attenuation", &sf::SoundSource::setAttenuation, py::arg("attenuation"))
    .def("set_effect_processor", [](sf::SoundSource& self, py::function func) {
        self.setEffectProcessor(wrap_effect_processor(func));
    }, py::arg("effectProcessor"))
    .def("get_pitch", &sf::SoundSource::getPitch)
    .def("get_pan", &sf::SoundSource::getPan)
    .def("get_volume", &sf::SoundSource::getVolume)
    .def("is_spatialization_enabled", &sf::SoundSource::isSpatializationEnabled)
    .def("get_position", &sf::SoundSource::getPosition)
    .def("get_direction", &sf::SoundSource::getDirection)
    .def("get_cone", &sf::SoundSource::getCone)
    .def("get_velocity", &sf::SoundSource::getVelocity)
    .def("get_doppler_factor", &sf::SoundSource::getDopplerFactor)
    .def("get_directional_attenuation_factor", &sf::SoundSource::getDirectionalAttenuationFactor)
    .def("is_relative_to_listener", &sf::SoundSource::isRelativeToListener)
    .def("get_min_distance", &sf::SoundSource::getMinDistance)
    .def("get_max_distance", &sf::SoundSource::getMaxDistance)
    .def("get_min_gain", &sf::SoundSource::getMinGain)
    .def("get_max_gain", &sf::SoundSource::getMaxGain)
    .def("get_attenuation", &sf::SoundSource::getAttenuation)
    .def("get_status", &sf::SoundSource::getStatus)
    .def("play", &sf::SoundSource::play)
    .def("pause", &sf::SoundSource::pause)
    .def("stop", &sf::SoundSource::stop);
}

void bind_sound_stream(py::module& m) {
    py::class_<sf::SoundStream, sf::SoundSource>(m, "SoundStream")
    .def("play", &sf::SoundStream::play)
    .def("pause", &sf::SoundStream::pause)
    .def("stop", &sf::SoundStream::stop)
    .def("get_channel_count", &sf::SoundStream::getChannelCount)
    .def("get_sample_rate", &sf::SoundStream::getSampleRate)
    .def("get_channel_map", &sf::SoundStream::getChannelMap)
    .def("get_status", &sf::SoundStream::getStatus)
    .def("set_playing_offset", &sf::SoundStream::setPlayingOffset)
    .def("get_playing_offset", &sf::SoundStream::getPlayingOffset)
    .def("set_looping", &sf::SoundStream::setLooping, py::arg("looping"))
    .def("is_looping", &sf::SoundStream::isLooping)
    .def("set_effect_processor", &sf::SoundStream::setEffectProcessor, py::arg("effectProcessor"));
}

void bind_sound_buffer(py::module& m) {
    py::class_<sf::SoundBuffer>(m, "SoundBuffer")
    .def(py::init<>())
    .def(py::init<>([](const std::string& filename) {
        return sf::SoundBuffer(filename);
    }), py::arg("filename"))
    .def(py::init<>([](py::buffer data) {
        py::buffer_info info = data.request();
        if (info.ndim != 1) {
            throw std::runtime_error("Buffer must be 1-dimensional");
        }
        return sf::SoundBuffer(info.ptr, static_cast<std::size_t>(info.size * info.itemsize));
    }), py::arg("data"))
    .def(py::init<sf::InputStream&>(), py::arg("stream"))
    .def(py::init<>([](py::buffer samples, unsigned int sampleRate, std::vector<sf::SoundChannel>& channelMap) {
        auto [samples_result, sample_count, channel_count] = pcm_array_ptr(samples, sampleRate);
        return sf::SoundBuffer(samples_result->data(), sample_count, channel_count, sampleRate, channelMap);
    }), py::arg("samples"), py::arg("sampleRate"), py::arg("channelMap"))
    .def(py::init<>([](std::vector<std::vector<float>>& samples, unsigned int sampleRate, std::vector<sf::SoundChannel>& channelMap) {
        auto [samples_result, sample_count, channel_count] = pcm_array_ptr(samples, sampleRate);
        return sf::SoundBuffer(samples_result->data(), sample_count, channel_count, sampleRate, channelMap);
    }), py::arg("samples"), py::arg("sampleRate"), py::arg("channelMap"))
    .def("load_from_file", [](sf::SoundBuffer& self, const std::string& filename) {
        return self.loadFromFile(filename);
    }, py::arg("filename"))
    .def("load_from_memory", [](sf::SoundBuffer& self, py::buffer data) {
        py::buffer_info info = data.request();
        if (info.ndim != 1) {
            throw std::runtime_error("Buffer must be 1-dimensional");
        }
        return self.loadFromMemory(info.ptr, static_cast<std::size_t>(info.size * info.itemsize));
    }, py::arg("data"))
    .def("load_from_stream", &sf::SoundBuffer::loadFromStream, py::arg("stream"))
    .def("load_from_samples", &sf::SoundBuffer::loadFromSamples, py::arg("samples"), py::arg("sampleCount"), py::arg("channelCount"), py::arg("sampleRate"), py::arg("channelMap"))
    .def("save_to_file", [](sf::SoundBuffer& self, const std::string& filename) {
        return self.saveToFile(filename);
    }, py::arg("filename"))
    .def("get_samples", &sf::SoundBuffer::getSamples)
    .def("get_sampleCount", &sf::SoundBuffer::getSampleCount)
    .def("get_sampleRate", &sf::SoundBuffer::getSampleRate)
    .def("get_channelCount", &sf::SoundBuffer::getChannelCount)
    .def("get_channelMap", &sf::SoundBuffer::getChannelMap)
    .def("get_duration", &sf::SoundBuffer::getDuration);
}

void bind_playback_device(py::module& m) {
    py::module_ playback_device = m.def_submodule("PlaybackDevice");

    playback_device.def("get_available_devices", []() {
        return sf::PlaybackDevice::getAvailableDevices();
    });

    playback_device.def("get_default_device", []() {
        auto result = sf::PlaybackDevice::getDefaultDevice();
        if (result) {
            return *result;
        } else {
            return std::string("");
        }
    });

    playback_device.def("set_device", [](const std::string& name) {
        return sf::PlaybackDevice::setDevice(name);
    }, py::arg("name"));

    playback_device.def("get_device", []() {
        auto result = sf::PlaybackDevice::getDevice();
        if (result) {
            return *result;
        } else {
            return std::string("");
        }
    });
}

void bind_music(py::module& m) {
    py::class_<sf::Music, sf::SoundStream>(m, "Music")
    .def(py::init<>([](const std::string& filename) {
        return sf::Music(filename);
    }), py::arg("filename"))
    .def(py::init<>([](py::buffer data) {
        py::buffer_info info = data.request();
        if (info.ndim!= 1) {
            throw std::runtime_error("Buffer must be 1-dimensional");
        }
        return sf::Music(info.ptr, static_cast<std::size_t>(info.size * info.itemsize));
    }), py::arg("data"))
    .def(py::init<sf::InputStream&>(), py::arg("stream"))
    .def(py::init<>())
    .def("open_from_file", [](sf::Music& self, const std::string& filename) {
        return self.openFromFile(filename);
    }, py::arg("filename"))
    .def("open_from_memory", [](sf::Music& self, py::buffer data) {
        py::buffer_info info = data.request();
        if (info.ndim!= 1) {
            throw std::runtime_error("Buffer must be 1-dimensional");
        }
        return self.openFromMemory(info.ptr, static_cast<std::size_t>(info.size * info.itemsize));
    }, py::arg("data"))
    .def("open_from_stream", &sf::Music::openFromStream, py::arg("stream"))
    .def("get_duration", &sf::Music::getDuration)
    .def("get_loop_points", [](sf::Music& self) {
        sf::Time offset, length;
        sf::Music::TimeSpan span = self.getLoopPoints();
        offset = span.length;
        length = span.offset;
        return py::make_tuple(offset, length);
    })
    .def("set_loop_points", [](sf::Music& self, py::tuple timePoints) {
        sf::Time offset = timePoints[0].cast<sf::Time>();
        sf::Time length = timePoints[1].cast<sf::Time>();
        sf::Music::TimeSpan span = {offset, length};
        self.setLoopPoints(span);
    }, py::arg("timePoints"));
}

void bind_sound(py::module& m) {
    py::class_<sf::Sound, sf::SoundSource> (m, "Sound", py::dynamic_attr())
    .def(py::init<const sf::SoundBuffer&>(), py::arg("buffer"))
    .def("play", &sf::Sound::play)
    .def("pause", &sf::Sound::pause)
    .def("stop", &sf::Sound::stop)
    .def("set_buffer", [](sf::Sound& self, const sf::SoundBuffer& buffer) {
        self.setBuffer(buffer);
    }, py::arg("buffer"))
    .def("set_looping", &sf::Sound::setLooping, py::arg("looping"))
    .def("set_laying_offset", &sf::Sound::setPlayingOffset, py::arg("timeOffset"))
    .def("get_buffer", &sf::Sound::getBuffer)
    .def("is_looping", &sf::Sound::isLooping)
    .def("get_playing_offset", &sf::Sound::getPlayingOffset)
    .def("get_status", &sf::Sound::getStatus)
    .def("__copy__", [](const sf::Sound &self) {
        return sf::Sound(self);
    })
    .def("__deepcopy__", [](const sf::Sound &self, py::dict) {
        return sf::Sound(self);
    });
}

void bind_sound_recorder(py::module& m) {
    py::class_<sf::SoundRecorder>(m, "SoundRecorder")
    .def("start_recording", &sf::SoundRecorder::start, py::arg("sample_rate") = 44100)
    .def("stop_recording", &sf::SoundRecorder::stop)
    .def("get_sample_rate", &sf::SoundRecorder::getSampleRate)
    .def_static("get_available_devices", &sf::SoundRecorder::getAvailableDevices)
    .def_static("get_default_device", &sf::SoundRecorder::getDefaultDevice)
    .def("set_device", &sf::SoundRecorder::setDevice, py::arg("name"))
    .def("get_device", &sf::SoundRecorder::getDevice)
    .def("set_channel_count", &sf::SoundRecorder::setChannelCount, py::arg("channel_count"))
    .def("get_channel_count", &sf::SoundRecorder::getChannelCount)
    .def("get_channel_map", &sf::SoundRecorder::getChannelMap)
    .def_static("is_available", &sf::SoundRecorder::isAvailable);
}

void bind_sound_buffer_recorder(py::module& m) {
    py::class_<sf::SoundBufferRecorder, sf::SoundRecorder>(m, "SoundBufferRecorder")
    .def(py::init<>())
     .def("get_buffer", [](sf::SoundBufferRecorder &self) -> const sf::SoundBuffer& {
        return self.getBuffer();
    }, py::return_value_policy::reference_internal)
    .def_static("is_available", &sf::SoundBufferRecorder::isAvailable);
}

void bind_input_sound_file(py::module& m) {
    py::class_<sf::InputSoundFile>(m, "InputSoundFile")
    .def(py::init<>())
    .def(py::init<>([](const std::string& filename) {
        return sf::InputSoundFile(filename);
    }), py::arg("filename"))
    .def(py::init<>([](py::buffer data) {
        py::buffer_info info = data.request();
        if (info.ndim!= 1) {
            throw std::runtime_error("Buffer must be 1-dimensional");
        }
        return sf::InputSoundFile(info.ptr, static_cast<std::size_t>(info.size * info.itemsize));
    }), py::arg("data"))
    .def(py::init<sf::InputStream&>())
    .def("open_from_file", [](sf::InputSoundFile& self, const std::string& filename) {
        return self.openFromFile(filename);
    }, py::arg("filename"))
    .def("open_from_memory", [](sf::InputSoundFile& self, py::buffer data) {
        py::buffer_info info = data.request();
        if (info.ndim!= 1) {
            throw std::runtime_error("Buffer must be 1-dimensional");
        }
        return self.openFromMemory(info.ptr, static_cast<std::size_t>(info.size * info.itemsize));
    }, py::arg("data"))
    .def("open_from_stream", &sf::InputSoundFile::openFromStream, py::arg("stream"))
    .def("get_sample_count", &sf::InputSoundFile::getSampleCount)
    .def("get_channel_count", &sf::InputSoundFile::getChannelCount)
    .def("get_sample_rate", &sf::InputSoundFile::getSampleRate)
    .def("get_channel_map", &sf::InputSoundFile::getChannelMap)
    .def("get_duration", &sf::InputSoundFile::getDuration)
    .def("get_time_offset", &sf::InputSoundFile::getTimeOffset)
    .def("get_sample_offset", &sf::InputSoundFile::getSampleOffset)
    .def("seek", py::overload_cast<std::uint64_t>(&sf::InputSoundFile::seek), py::arg("sampleOffset"))
    .def("seek", py::overload_cast<sf::Time>(&sf::InputSoundFile::seek), py::arg("timeOffset"))
    .def("read", &sf::InputSoundFile::read, py::arg("samples"), py::arg("maxCount"))
    .def("close", &sf::InputSoundFile::close);
}

void bind_output_sound_file(py::module_& m)
{
    py::class_<sf::OutputSoundFile>(m, "OutputSoundFile")
    .def(py::init<>())
    .def(py::init<>([](const std::string& filename, unsigned int sampleRate, unsigned int channelCount, const std::vector<sf::SoundChannel>& channelMap) {
        return sf::OutputSoundFile(filename, sampleRate, channelCount, channelMap);
    }), py::arg("filename"), py::arg("sampleRate"), py::arg("channelCount"), py::arg("channelMap"))
    .def("open_from_file", [](sf::OutputSoundFile& self, const std::string& filename, unsigned int sampleRate, unsigned int channelCount, const std::vector<sf::SoundChannel>& channelMap) {
        return self.openFromFile(filename, sampleRate, channelCount, channelMap);
    }, py::arg("filename"), py::arg("sampleRate"), py::arg("channelCount"), py::arg("channelMap"))
    .def("write", &sf::OutputSoundFile::write, py::arg("samples"), py::arg("count"))
    .def("close", &sf::OutputSoundFile::close);
}
