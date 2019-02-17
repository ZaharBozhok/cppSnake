#pragma once
#include "Frame.h"
#include <functional>

struct ICollisionDetectable
{
    virtual ~ICollisionDetectable() {}
    virtual bool CheckCollision(const Point& point) = 0;
    virtual void OnCollision()
    {
        if (m_collisionCallback)
        {
            m_collisionCallback();
        }
    }
    std::function<void()> m_collisionCallback;
};