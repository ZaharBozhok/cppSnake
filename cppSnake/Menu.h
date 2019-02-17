#pragma once
#include "Button.h"
#include "IDrawable.h"

enum class MenuChoice
{
    eStart,
    eQuit
};

class Menu : public IDrawable
{
public:
    Menu(const size_t& width, const size_t& height) : m_width(width), m_height(height)
    {
        Point startPoint, quitPoint;
        startPoint.m_x = m_width * 0.25;
        startPoint.m_y = m_height / 2;
        quitPoint.m_x = m_width * 0.75;
        quitPoint.m_y = m_height / 2;
        m_start = Button(startPoint, L"Start");
        m_start.Hover(true);
        m_quit = Button(quitPoint, L"Quit");
    }
    std::vector<DrawablePoint> GetDrawableBuffer() override
    {
        std::vector<DrawablePoint> ret = m_start.GetDrawableBuffer();
        auto quit = m_quit.GetDrawableBuffer();
        ret.insert(ret.end(), quit.begin(), quit.end());
        return ret;
    }
    void Toggle()
    {
        m_start.Hover(!m_start.IsHovered());
        m_quit.Hover(!m_quit.IsHovered());
    }
    MenuChoice GetState()
    {
        if (m_start.IsHovered())
        {
            return MenuChoice::eStart;
        }
        return MenuChoice::eQuit;
    }
private:
    Button m_start;
    Button m_quit;
    size_t m_width;
    size_t m_height;
};