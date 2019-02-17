#pragma once
#include "IDrawable.h"
#include <algorithm>

class Frame
{
public:
    Frame(const size_t& width, const size_t& height) : m_width(width), m_height(height)
    {
        m_buffer.resize(m_width * m_height);
    }
    const size_t& Width() const
    {
        return m_width;
    }
    const size_t& Height() const
    {
        return m_height;
    }
    void Set(const size_t& x, const cell_t& val)
    {
        m_buffer.at(x) = val;
    }
    void Set(const Point& point, const cell_t& val)
    {
        m_buffer.at(point.m_y * m_width + point.m_x) = val;
    }
    const cell_t& Get(const size_t& x)
    {
        return m_buffer.at(x);
    }
    const cell_t& Get(const Point& point)
    {
        return m_buffer.at(point.m_y * m_width + point.m_x);
    }
    const cell_t* Buffer() const
    {
        return m_buffer.data();
    }
    cell_t* Buffer()
    {
        return m_buffer.data();
    }
    void Fill(const cell_t& val)
    {
        for (size_t i = 0; i < m_buffer.size(); ++i)
        {
            m_buffer[i] = val;
        }
    }
    void AddDrawable(IDrawable* drawable)
    {
        m_drawables.push_back(drawable);
    }
    void RemoveDrawable(IDrawable* drawable)
    {
        m_drawables.erase(std::remove(m_drawables.begin(), m_drawables.end(), drawable));
    }
    void Draw()
    {
        for (auto drawable : m_drawables)
        {
            auto data = drawable->GetDrawableBuffer();
            for (auto drawablePoint : data)
            {
                this->Set(drawablePoint, drawablePoint.m_value);
            }
        }
    }
private:
    std::vector<IDrawable*> m_drawables;
    std::vector<cell_t> m_buffer;
    size_t m_width;
    size_t m_height;
};