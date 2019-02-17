#include "stdafx.h"
#include "Fruit.h"

Fruit::Fruit(const size_t& borderX, const size_t& borderY) : m_borderX(borderX), m_borderY(borderY)
{
    NextPosition();
}
void Fruit::NextPosition()
{
    m_point.m_x = rand() % m_borderX;
    m_point.m_y = rand() % m_borderY;
}
std::vector<DrawablePoint> Fruit::GetDrawableBuffer()
{
    std::vector<DrawablePoint> ret;
    ret.push_back(DrawablePoint(m_point, L'F'));
    return ret;
}
bool Fruit::CheckCollision(const Point& point)
{
    if (m_point == point)
        return true;
    return false;
}