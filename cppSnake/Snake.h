#pragma once
#include <list>
#include "Point.h"
#include "ICollisionDetectable.h"
#include "IDrawable.h"

enum class Direction : int
{
    eUp = 0,
    eRight = 1,
    eDown = 2,
    eLeft = 3
};

class Snake : public IDrawable, public ICollisionDetectable
{
public:
    Snake(const Point& head);
    std::vector<DrawablePoint> GetDrawableBuffer() override;
    void Move();
    void TurnHead(const Direction& direction);
    void AppendTail();
    const Point& HeadPosition();
    bool CheckCollision(const Point& point) override;
    void Die();
    bool Dead();
private:
    cell_t m_headCell;
    cell_t m_bodyCell;
    std::list<Point> m_snake;
    Direction m_direction;
    bool m_dead;
};