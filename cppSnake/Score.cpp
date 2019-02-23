#include "Score.h"

Score::Score(const Point& point, const int& value) : m_value(value), m_point(point)
{}
void Score::Add(const int& value)
{
    m_value += value;
}
std::vector<DrawablePoint> Score::GetDrawableBuffer()
{
    std::wstring score = m_string + std::to_wstring(m_value);
    std::vector<DrawablePoint> drawables;
    drawables.resize(score.size());
    for (size_t i = 0; i < score.size(); ++i)
    {
        drawables.at(i) = (DrawablePoint({ m_point.m_x + i, m_point.m_y }, score[i]));
    }
    return drawables;
}