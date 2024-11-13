#include "Grid.hpp"

fss::Grid::Grid(int width, int height) : m_width(width), m_height(height)
{
    m_grid.resize(width * height);
    clear();
}

int fss::Grid::index(int x, int y)
{
    if (x >= 0 && x < m_width && y >= 0 && y < m_height)
    {
        return y * m_width + x;
    }
    return -1;
}

void fss::Grid::set_color(int x, int y, godot::Color color)
{
    m_grid[index(x, y)] = color;
}

inline void fss::Grid::swap(int x, int y)
{
    std::swap(m_grid[x], m_grid[y]);
}

void fss::Grid::clear()
{
    std::fill(m_grid.begin(), m_grid.end(), godot::Color("f6f6f6"));
}

bool fss::Grid::is_valid_position(int x, int y)
{
    if (x >= 0 && x < m_width && y >= 0 && y < m_height)
        return true;
    return false;
}

inline bool fss::Grid::is_empty(int index)
{
    return m_grid[index] == godot::Color("f6f6f6");
}

void fss::Grid::update_pixel(int index)
{
    int below = index + m_width;
    int below_left = below - 1;
    int below_right = below + 1;
    
    if (below < m_grid.size() && is_empty(below))
        swap(index, below);
    else
    {
        if (below_left >= 0 && below_left < m_grid.size() && is_empty(below_left))
            swap(index, below_left);
        else if (below_right >= 0 && below_right < m_grid.size() && is_empty(below_right))
            swap(index, below_right);
    }
}

void fss::Grid::update()
{
    for (int i = m_grid.size() -1; i > -1; i--)
    {
        if (is_empty(i))
            continue;
        update_pixel(i);
    }
}

void fss::Grid::draw(godot::Ref<godot::Image> &buffer)
{
    for (int y = 0; y < m_height; y++)
    {
        for (int x = 0; x < m_width; x++)
        {
            buffer->set_pixel(x, y, m_grid[y * m_width + x]);
        }
    }
}
