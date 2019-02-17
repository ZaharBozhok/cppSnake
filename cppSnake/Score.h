#pragma once
#include <string>
#include "IDrawable.h"
#include "Point.h"

class Score : public IDrawable
{
public:
    Score(const Point& point, const int& value);
    void Add(const int& value);
    std::vector<DrawablePoint> GetDrawableBuffer() override;
private:
    int m_value;
    Point m_point;
    const std::wstring m_string = L"Score : ";
};