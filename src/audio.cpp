#include <audio.h>

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
    .value("TopBackCenter", sf::SoundChannel::TopBackCenter);
}

void bind_listener(py::module& m) {
    py::module_ listener = m.def_submodule("Listener");

    py::class_<sf::Listener::Cone>(listener, "Cone")
        .def(py::init<>())
        .def_readwrite("inner_angle", &sf::Listener::Cone::innerAngle)
        .def_readwrite("outer_angle", &sf::Listener::Cone::outerAngle)
        .def_readwrite("outer_gain", &sf::Listener::Cone::outerGain);

    listener.def("set_global_volume", &sf::Listener::setGlobalVolume, "Set the global volume for all sounds and musics");
    listener.def("get_global_volume", &sf::Listener::getGlobalVolume, "Get the current global volume");
    listener.def("set_position", &sf::Listener::setPosition, "Set the position of the listener", py::arg("position"));
    listener.def("get_position", &sf::Listener::getPosition, "Get the position of the listener");
    listener.def("set_direction", &sf::Listener::setDirection, "Set the direction of the listener", py::arg("direction"));
    listener.def("get_direction", &sf::Listener::getDirection, "Get the direction of the listener");
    listener.def("set_velocity", &sf::Listener::setVelocity, "Set the velocity of the listener", py::arg("velocity"));
    listener.def("get_velocity", &sf::Listener::getVelocity, "Get the velocity of the listener");
    listener.def("set_cone", &sf::Listener::setCone, "Set the cone properties of the listener", py::arg("cone"));
    listener.def("get_cone", &sf::Listener::getCone, "Get the cone properties of the listener");
    listener.def("set_up_vector", &sf::Listener::setUpVector, "Set the upward vector of the listener", py::arg("upVector"));
    listener.def("get_up_vector", &sf::Listener::getUpVector, "Get the upward vector of the listener");
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

    sound_source.def("set_pitch", &sf::SoundSource::setPitch)
    .def("set_pan", &sf::SoundSource::setPan)
    .def("set_volume", &sf::SoundSource::setVolume)
    .def("set_spatialization_enabled", &sf::SoundSource::setSpatializationEnabled)
    .def("set_position", &sf::SoundSource::setPosition)
    .def("set_direction", &sf::SoundSource::setDirection)
    .def("set_cone", &sf::SoundSource::setCone)
    .def("set_velocity", &sf::SoundSource::setVelocity)
    .def("set_doppler_factor", &sf::SoundSource::setDopplerFactor)
    .def("set_directional_attenuation_factor", &sf::SoundSource::setDirectionalAttenuationFactor)
    .def("set_relative_to_listener", &sf::SoundSource::setRelativeToListener)
    .def("set_min_distance", &sf::SoundSource::setMinDistance)
    .def("set_max_distance", &sf::SoundSource::setMaxDistance)
    .def("set_min_gain", &sf::SoundSource::setMinGain)
    .def("set_max_gain", &sf::SoundSource::setMaxGain)
    .def("set_attenuation", &sf::SoundSource::setAttenuation)
    .def("set_effect_processor", &sf::SoundSource::setEffectProcessor)
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
    .def("set_looping", &sf::SoundStream::setLooping)
    .def("is_looping", &sf::SoundStream::isLooping)
    .def("set_effect_processor", &sf::SoundStream::setEffectProcessor);
}

void bind_sound_buffer(py::module& m) {
    py::class_<sf::SoundBuffer>(m, "SoundBuffer")
    .def(py::init<>())
    .def(py::init<const std::string&>())
    .def(py::init<const void*, std::size_t>())
    .def(py::init<sf::InputStream&>())
    .def(py::init<const std::int16_t*, std::uint64_t, unsigned int, unsigned int, const std::vector<sf::SoundChannel>&>())
    .def("load_from_file", &sf::SoundBuffer::loadFromFile)
    .def("load_from_memory", &sf::SoundBuffer::loadFromMemory)
    .def("load_from_stream", &sf::SoundBuffer::loadFromStream)
    .def("load_from_samples", &sf::SoundBuffer::loadFromSamples)
    .def("save_to_file", &sf::SoundBuffer::saveToFile)
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
    });

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
    .def(py::init<const std::filesystem::path&>())
    .def(py::init<const void*, std::size_t>())
    .def(py::init<sf::InputStream&>())
    .def(py::init<>())
    .def("openFromFile", &sf::Music::openFromFile)
    .def("openFromMemory", &sf::Music::openFromMemory)
    .def("openFromStream", &sf::Music::openFromStream)
    .def("getDuration", &sf::Music::getDuration)
    .def("getLoopPoints", &sf::Music::getLoopPoints)
    .def("setLoopPoints", &sf::Music::setLoopPoints);
}

void bind_sound(py::module& m) {
    py::class_<sf::Sound> (m, "Sound", py::dynamic_attr())
    .def(py::init<const sf::SoundBuffer&>(), py::arg("buffer"))
    .def("play", &sf::Sound::play)
    .def("pause", &sf::Sound::pause)
    .def("stop", &sf::Sound::stop)
    .def("setBuffer", [](sf::Sound& self, const sf::SoundBuffer& buffer) {
        self.setBuffer(buffer); 
    }, py::arg("buffer"))
    .def("setLooping", &sf::Sound::setLooping)
    .def("setPlayingOffset", &sf::Sound::setPlayingOffset)
    .def("getBuffer", &sf::Sound::getBuffer)
    .def("isLooping", &sf::Sound::isLooping)
    .def("getPlayingOffset", &sf::Sound::getPlayingOffset)
    .def("getStatus", &sf::Sound::getStatus)
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
    .def("get_buffer", &sf::SoundBufferRecorder::getBuffer, py::return_value_policy::reference)
    .def("is_sound_buffer_recorder_available", &sf::SoundBufferRecorder::isAvailable); 
}

void bind_input_sound_file(py::module& m) {
    py::class_<sf::InputSoundFile>(m, "InputSoundFile")
    .def(py::init<>())
    .def(py::init<const std::string&>(), "from_file")
    .def(py::init<const void*, std::size_t>(), "from_memory")
    .def(py::init<sf::InputStream&>(), "from_stream")
    .def("open_from_file", &sf::InputSoundFile::openFromFile, "Open from file")
    .def("open_from_memory", &sf::InputSoundFile::openFromMemory, "Open from memory")
    .def("open_from_stream", &sf::InputSoundFile::openFromStream, "Open from stream")
    .def("get_sample_count", &sf::InputSoundFile::getSampleCount)
    .def("get_channel_count", &sf::InputSoundFile::getChannelCount)
    .def("get_sample_rate", &sf::InputSoundFile::getSampleRate)
    .def("get_channel_map", &sf::InputSoundFile::getChannelMap)
    .def("get_duration", &sf::InputSoundFile::getDuration)
    .def("get_time_offset", &sf::InputSoundFile::getTimeOffset)
    .def("get_sample_offset", &sf::InputSoundFile::getSampleOffset)
    .def("seek", py::overload_cast<std::uint64_t>(&sf::InputSoundFile::seek))
    .def("seek", py::overload_cast<sf::Time>(&sf::InputSoundFile::seek))
    .def("read", &sf::InputSoundFile::read)
    .def("close", &sf::InputSoundFile::close);
}

void bind_output_sound_file(py::module_& m)
{
    py::class_<sf::OutputSoundFile>(m, "OutputSoundFile")
    .def(py::init<>())
    .def(py::init<const std::string&, unsigned int, unsigned int, const std::vector<sf::SoundChannel>&>())
    .def("open_from_file", &sf::OutputSoundFile::openFromFile)
    .def("write", &sf::OutputSoundFile::write)
    .def("close", &sf::OutputSoundFile::close);
}
