#pragma once
#include <string>
#include "Types.h"
#include "Point.h"
#include "IDrawable.h"

class Button
{
public:
    Button() = default;
    Button(const Point& point, const size_t& width, const size_t& height, const std::wstring text)
        : m_width(width)
        , m_height(height)
        , m_text(text)
        , m_point(point)
    {
        m_drawable.resize(m_width * m_height + m_text.size());
        Draw();
    }
    Button(const Point& point, const std::wstring text) : Button(point, text.size() + 4, 5, text)
    {
    }
    const Button& operator=(const Button& b)
    {
        this->m_border = b.m_border;
        this->m_drawable = b.m_drawable;
        this->m_point = b.m_point;
        this->m_text = b.m_text;
        this->m_width = b.m_width;
        this->m_height = b.m_height;
        return *this;
    }

    std::vector<DrawablePoint> virtual GetDrawableBuffer()
    {
        return m_drawable;
    }
    void Hover(const bool& state)
    {
        m_hovered = state;
        if (m_hovered)
        {
            m_border = m_borderHovered;
        }
        else
        {
            m_border = m_borderNormal;
        }
        Draw();
    }
    void Draw()
    {
        for (size_t i = 0; i < m_height; ++i)
        {
            for (size_t j = 0; j < m_width; ++j)
            {
                m_drawable[i*m_width + j] = DrawablePoint({ m_point.m_x + j, m_point.m_y + i }, m_border);
            }
        }
        for (size_t i = m_drawable.size() - m_text.size(), j = 0; i < m_drawable.size(); ++i, ++j)
        {
            m_drawable[i] = DrawablePoint({ m_point.m_x + m_margin + j, m_point.m_y + m_height / 2 }, m_text[j]);
        }
    }
    bool IsHovered()
    {
        return m_hovered;
    }

private:
    size_t m_width;
    size_t m_height;
    std::wstring m_text;
    Point m_point;
    bool m_hovered;
    const cell_t m_borderHovered = L'+';
    const cell_t m_borderNormal = L'-';
    const size_t m_margin = 2;
    cell_t m_border = m_borderNormal;
    std::vector<DrawablePoint> m_drawable;
};