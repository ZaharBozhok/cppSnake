#pragma once
#include "ICollisionDetectable.h"

class Box : public ICollisionDetectable, public IDrawable
{
public:
    Box(const Point& startPoint, const size_t& width, const size_t& height);
    bool CheckCollision(const Point& point) override;
    std::vector<DrawablePoint> GetDrawableBuffer();
private:
    std::vector<DrawablePoint> m_drawable;
    size_t m_width;
    size_t m_height;
    cell_t m_fence;
};
