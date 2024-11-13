#pragma once

#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/godot.hpp>
#include <godot_cpp/classes/texture_rect.hpp>

#include <godot_cpp/variant/utility_functions.hpp>
#include <godot_cpp/classes/engine.hpp>
#include <godot_cpp/classes/input.hpp>
#include <godot_cpp/classes/image.hpp>
#include <godot_cpp/classes/image_texture.hpp>

#include "Grid.hpp"


namespace godot
{
    class SimulatorCanvas : public TextureRect
    {
        GDCLASS(SimulatorCanvas, TextureRect)

    private:
        Ref<Image> m_buffer;
        Ref<ImageTexture> m_texture;
        fss::Grid m_grid;
        
        Vector2i buffer_size;
        Vector2i grid_size;
        int brush_radius;

    protected:
        static void _bind_methods();

    public:
        SimulatorCanvas();
        ~SimulatorCanvas() {}

        void _ready();
        void update(Vector2i mouse_pos);

        Vector2i get_buffer_size() const { return buffer_size; }
        void set_buffer_size(const Vector2i value);

        Vector2i get_grid_size() const { return grid_size; }
        void set_grid_size(const Vector2i value);

        int get_brush_radius() const { return brush_radius; }
        void set_brush_radius(const int value) { brush_radius = value; }
    };

}