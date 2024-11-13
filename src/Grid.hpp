#pragma once

#include <vector>
#include <algorithm>

#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/classes/image.hpp>
#include <godot_cpp/variant/utility_functions.hpp>

namespace fss
{
    class Grid
    {
    private:
        int m_width;
        int m_height;
        std::vector<godot::Color> m_grid;
    
    public:
        Grid() {}
        Grid(int width, int height);
        ~Grid() {}

        int index(int x, int y);
        void set_color(int x, int y, godot::Color color);
        void swap(int x, int y);
        void clear();
        
        bool is_valid_position(int x, int y);
        bool is_empty(int index);
        void update_pixel(int index);
        void update();
        void draw(godot::Ref<godot::Image>& buffer);
    };
} // namespace fss
