#pragma once
#include "IDrawable.h"
#include "ICollisionDetectable.h"

class Fruit : public IDrawable, public ICollisionDetectable
{
public:
    Fruit(const size_t& borderX, const size_t& borderY);
    void NextPosition();
    std::vector<DrawablePoint> GetDrawableBuffer() override;
    bool CheckCollision(const Point& point) override;
private:
    Point m_point;
    size_t m_borderX;
    size_t m_borderY;
};