#pragma once
#include <vector>
#include "Point.h"
#include "ICollisionDetectable.h"

class CollisionManager
{
public:
    void AddDetectable(ICollisionDetectable* detectable)
    {
        m_detectables.push_back(detectable);
    }
    void CheckCollision(const Point& point)
    {
        for (auto detectable : m_detectables)
        {
            if (detectable->CheckCollision(point))
            {
                detectable->OnCollision();
            }
        }
    }
private:
    std::vector<ICollisionDetectable*> m_detectables;
};