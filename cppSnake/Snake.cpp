#pragma once
#include "stdafx.h"
#include "Snake.h"
Snake::Snake(const Point& head) : m_headCell(L'H'), m_bodyCell(L'b'), m_dead(false)
{
    m_snake.push_front(head);
}
std::vector<DrawablePoint> Snake::GetDrawableBuffer()
{
    std::vector<DrawablePoint> ret;
    for (auto it = m_snake.rbegin(); it != --m_snake.rend(); it++)
    {
        ret.push_back(DrawablePoint(*it, m_bodyCell));
    }
    ret.push_back(DrawablePoint(m_snake.front(), m_headCell));
    return ret;
}
void Snake::Move()
{
    Point newHead = m_snake.front();
    switch (m_direction)
    {
    case Direction::eUp:
    {
        newHead.m_y -= 1;
    }
    break;
    case Direction::eRight:
    {
        newHead.m_x += 1;
    }
    break;
    case Direction::eDown:
    {
        newHead.m_y += 1;
    }
    break;
    case Direction::eLeft:
    {
        newHead.m_x -= 1;
    }
    break;
    }
    m_snake.push_front(newHead);
    m_snake.pop_back();
}
void Snake::TurnHead(const Direction& direction)
{
    int dir = static_cast<int>(m_direction);
    switch (direction)
    {
    case Direction::eRight:
    {
        if (dir == static_cast<int>(Direction::eLeft))
        {
            dir = static_cast<int>(Direction::eUp);
        }
        else
        {
            dir += 1;
        }
    }
    break;
    case Direction::eLeft:
    {
        if (dir == static_cast<int>(Direction::eUp))
        {
            dir = static_cast<int>(Direction::eLeft);
        }
        else
        {
            dir -= 1;
        }
    }
    break;
    }
    m_direction = static_cast<Direction>(dir);
}
void Snake::AppendTail()
{
    m_snake.push_back(m_snake.back());
}
const Point& Snake::HeadPosition()
{
    return m_snake.front();
}
bool Snake::CheckCollision(const Point& point)
{
    for (auto it = ++m_snake.begin(); it != m_snake.end(); it++)
    {
        if (*it == point)
        {
            return true;
        }
    }
    return false;
}
void Snake::Die()
{
    m_headCell = L'D';
    m_bodyCell = L'x';
    m_dead = true;
}
bool Snake::Dead()
{
    return m_dead;
}