#include "SimulatorCanvas.hpp"

godot::SimulatorCanvas::SimulatorCanvas()
{
    if (Engine::get_singleton()->is_editor_hint()) {
        set_process_mode(PROCESS_MODE_DISABLED);
    }
    buffer_size = Vector2i(512, 512);
    grid_size = Vector2i(64, 64);
    brush_radius = 0;
    m_grid = fss::Grid(grid_size.x, grid_size.y);
}

void godot::SimulatorCanvas::_ready()
{
    m_buffer = Image::create(grid_size.x, grid_size.y, false, Image::FORMAT_RGB8);
    m_texture = ImageTexture::create_from_image(m_buffer);
    set_texture(m_texture);
    set_texture_filter(TextureFilter::TEXTURE_FILTER_NEAREST);
    set_size(buffer_size);
}

void godot::SimulatorCanvas::update(godot::Vector2i mouse_pos)
{
    if (m_grid.is_valid_position(mouse_pos.x, mouse_pos.y))
        m_grid.set_color(mouse_pos.x, mouse_pos.y, Color("dcb159"));

    m_grid.update();
    m_grid.draw(m_buffer);
    m_texture->update(m_buffer);
}

void godot::SimulatorCanvas::set_buffer_size(const Vector2i value)
{
    buffer_size = value;
    set_size(buffer_size);
}

void godot::SimulatorCanvas::set_grid_size(const Vector2i value)
{
    grid_size = value;
    m_buffer = Image::create(grid_size.x, grid_size.y, false, Image::FORMAT_RGB8);
    m_texture = ImageTexture::create_from_image(m_buffer);
    set_texture(m_texture);
    m_grid = fss::Grid(grid_size.x, grid_size.y);
}

void godot::SimulatorCanvas::_bind_methods()
{
    ClassDB::bind_method(D_METHOD("update", "mouse_pos"), &SimulatorCanvas::update);
    
    ClassDB::bind_method(D_METHOD("get_brush_radius"), &SimulatorCanvas::get_brush_radius);
    ClassDB::bind_method(D_METHOD("set_brush_radius", "value"), &SimulatorCanvas::set_brush_radius);
    ADD_PROPERTY(PropertyInfo(Variant::INT, "brush_radius", PROPERTY_HINT_RANGE, "0, 10, 1"), "set_brush_radius", "get_brush_radius");
    
    ClassDB::bind_method(D_METHOD("get_buffer_size"), &SimulatorCanvas::get_buffer_size);
    ClassDB::bind_method(D_METHOD("set_buffer_size", "value"), &SimulatorCanvas::set_buffer_size);
    ADD_PROPERTY(PropertyInfo(Variant::VECTOR2I, "buffer_size"), "set_buffer_size", "get_buffer_size");
    
    ClassDB::bind_method(D_METHOD("get_grid_size"), &SimulatorCanvas::get_grid_size);
    ClassDB::bind_method(D_METHOD("set_grid_size", "value"), &SimulatorCanvas::set_grid_size);  
    ADD_PROPERTY(PropertyInfo(Variant::VECTOR2I, "grid_size"), "set_grid_size", "get_grid_size");
}
