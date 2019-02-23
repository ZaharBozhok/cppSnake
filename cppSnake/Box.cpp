#include "Box.h"

Box::Box(const Point& startPoint, const size_t& width, const size_t& height) : m_width(width), m_height(height), m_fence(L'!')
{
    m_drawable.resize(2 * (width + height));
    for (size_t i = startPoint.m_y; i < height + startPoint.m_y; ++i)
    {
        m_drawable.push_back(DrawablePoint({ startPoint.m_x,i }, m_fence));
        m_drawable.push_back(DrawablePoint({ startPoint.m_x + width - 1,i }, m_fence));
    }
    for (size_t i = startPoint.m_x; i < width + startPoint.m_x; ++i)
    {
        m_drawable.push_back(DrawablePoint({ i, startPoint.m_y }, m_fence));
        m_drawable.push_back(DrawablePoint({ i, startPoint.m_y + m_height - 1 }, m_fence));
    }
}
bool Box::CheckCollision(const Point& point)
{
    if (point.m_y == 0 || point.m_y == m_height - 1 || point.m_x == 0 || point.m_x == m_width - 1)
    {
        return true;
    }
    return false;
}
std::vector<DrawablePoint> Box::GetDrawableBuffer()
{
    return m_drawable;
}