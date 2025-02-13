#include <system.h>
#include <window_base.h>
#include <window.h>
#include <graphics_base.h>
#include <graphics_render.h>
#include <graphics_core.h>
#include <audio.h>
#include <network.h>

PYBIND11_MODULE(pysf, m) {
    m.doc() = "SFML Library";
    bind_angle(m);
    bind_time(m);
    bind_clock(m);
    bind_vector2<float>(m, "Vector2f");
    bind_vector2<int>(m, "Vector2i");
    bind_vector2<unsigned int>(m, "Vector2u");
    bind_vector3<float>(m, "Vector3f");
    bind_vector3<int>(m, "Vector3i");
    bind_vector3<unsigned int>(m, "Vector3u");
    bind_input_stream(m);

    bind_enum(m);
    bind_context(m);
    bind_cursor(m);
    bind_event(m);
    bind_video_mode(m);

    bind_base_window(m);
    bind_window(m);
    bind_clipboard(m);
    bind_joystick(m);
    bind_keyboard(m);
    bind_mouse(m);
    bind_sensor(m);
    bind_touch(m);
    
    bind_type(m);
    bind_rect<int>(m, "IntRect");
    bind_rect<float>(m, "FloatRect");
    bind_blend_mode(m);
    bind_transform(m);
    bind_transformable(m);
    bind_vertex(m);
    bind_shape(m);
    bind_color(m);
    bind_font(m);
    bind_glyph(m);
    bind_image(m);
    bind_convex_shape(m);
    bind_circle_shape(m);
    bind_rectangle_shape(m);
    
    bind_render_states(m);
    bind_render_target(m);
    bind_render_texture(m);
    bind_render_window(m);
    bind_shader(m);

    bind_texture(m);
    bind_sprite(m);
    bind_stencil_mode(m);
    bind_text(m);
    bind_view(m);

    bind_sound_channel(m);
    bind_listener(m);
    bind_sound_source(m);
    bind_sound_stream(m);
    bind_sound_buffer(m);
    bind_playback_device(m);
    bind_music(m);
    bind_sound(m);
    bind_sound_recorder(m);
    bind_sound_buffer_recorder(m);
    bind_input_sound_file(m);
    bind_output_sound_file(m);

    bind_ftp(m);
    bind_http(m);
    bind_ip_address(m);
    bind_packet(m);
    bind_socket(m);
    bind_socket_selector(m);
    bind_tcp_listener(m);
    bind_tcp_socket(m);
    bind_udp_socket(m);
}
