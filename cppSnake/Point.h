#pragma once
#include "Types.h"
struct Point
{
    size_t m_x;
    size_t m_y;
    bool operator==(const Point& p)
    {
        return m_x == p.m_x && m_y == p.m_y;
    }
};

struct DrawablePoint : public Point
{
    DrawablePoint() = default;
    DrawablePoint(const Point& p, const cell_t& val) : m_value(val)
    {
        m_x = p.m_x;
        m_y = p.m_y;
    }
    cell_t m_value;
};