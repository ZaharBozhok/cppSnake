// cppSnake.cpp : Defines the entry point for the console application.
//
#include <Windows.h>
#include <thread>
#include <queue>
#include <algorithm>
#include "Frame.h"
#include "Snake.h"
#include "Fruit.h"
#include "CollisionManager.h"
#include "Box.h"
#include "Score.h"
#include "Menu.h"

cell_t g_emptyField = L' ';
size_t g_consoleWidth = 120;
size_t g_consoleHeight = 30;
Direction g_direction = Direction::eUp;
bool g_stopRequested = false;
bool g_enterPressed = false;


void DrawingLoop()
{
    HANDLE hConsole = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, 0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);
    SetConsoleActiveScreenBuffer(hConsole);
    DWORD dwBytesWritten = 0;
    Frame frame(g_consoleWidth, g_consoleHeight);
    Menu menu(g_consoleWidth, g_consoleHeight);
    
    frame.AddDrawable(&menu);
    while(!g_enterPressed)
    {
        if (g_direction != Direction::eUp)
        {
            menu.Toggle();
        }
        g_direction = Direction::eUp;
        frame.Fill(L' ');
        frame.Draw();
        WriteConsoleOutputCharacter(hConsole, frame.Buffer(), frame.Width() * frame.Height(), { 0,0 }, &dwBytesWritten);
        Sleep(150);
    }
    if (menu.GetState() == MenuChoice::eQuit)
    {
        g_stopRequested = true;
        return;
    }
    frame.RemoveDrawable(&menu);

    Snake snake({ g_consoleWidth / 2, g_consoleHeight / 2 });
    Fruit fruit(g_consoleWidth, g_consoleHeight);
    CollisionManager collisionManager;
    Box box({ 0,0 }, g_consoleWidth, g_consoleHeight - 1);
    Score score({ g_consoleWidth / 2, g_consoleHeight - 1 }, 1);
    
    frame.AddDrawable(&score);
    frame.AddDrawable(&box);
    frame.AddDrawable(&fruit);
    frame.AddDrawable(&snake);

    collisionManager.AddDetectable(&snake);
    collisionManager.AddDetectable(&fruit);
    collisionManager.AddDetectable(&box);
    
    snake.m_collisionCallback = [&snake]()
    {
        snake.Die();
    };
    fruit.m_collisionCallback = [&snake, &fruit, &score]()
    {
        snake.AppendTail();
        fruit.NextPosition();
        score.Add(1);
    };
    box.m_collisionCallback = [&snake]()
    {
        snake.Die();
    };
    while (!snake.Dead())
    {   
        snake.TurnHead(g_direction);
        g_direction = Direction::eUp;
        snake.Move();
        collisionManager.CheckCollision(snake.HeadPosition());

        frame.Fill(L' ');
        frame.Draw();
        WriteConsoleOutputCharacter(hConsole, frame.Buffer(), frame.Width() * frame.Height(), { 0,0 }, &dwBytesWritten);
        Sleep(100);
    }
    g_stopRequested = true;
}

void HandleControl()
{
    bool s_leftPressed = false;
    bool s_leftPressedOld = false;
    bool s_rightPressed = false;
    bool s_rightPressedOld = false;
    while (!g_stopRequested)
    {
        s_rightPressed = GetAsyncKeyState(VK_RIGHT) & 0x8000;
        s_leftPressed = GetAsyncKeyState(VK_LEFT) & 0x8000;
        if (s_rightPressed && !s_rightPressedOld)
        {
            g_direction = Direction::eRight;
        }
        else if (s_leftPressed && !s_leftPressedOld)
        {
            g_direction = Direction::eLeft;
        }
        if (GetAsyncKeyState(VK_RETURN) & 0x8000)
        {
            g_enterPressed = true;
        }
        s_rightPressedOld = s_rightPressed;
        s_leftPressedOld = s_leftPressed;
        Sleep(5);
    }
}

int main()
{
    std::thread tHandleControl(HandleControl);
    std::thread tDrawingLoop(DrawingLoop);
    tHandleControl.join();
    tDrawingLoop.join();
    return 0;
}

