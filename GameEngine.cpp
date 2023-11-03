#include "GameEngine.h"

#include "lab_m1/lab1/lab1.h"

#include <vector>
#include <iostream>

using namespace std;
using namespace PvZ;


/*
 *  To find out more about `FrameStart`, `Update`, `FrameEnd`
 *  and the order in which they are called, see `world.cpp`.
 */


GameEngine::GameEngine() = default;

GameEngine::~GameEngine() = default;


void GameEngine::Init()
{
}


void GameEngine::FrameStart()
{
}


void GameEngine::Update(float deltaTimeSeconds)
{
}


void GameEngine::FrameEnd()
{
}


/*
 *  These are callback functions. To find more about callbacks and
 *  how they behave, see `input_controller.h`.
 */


void GameEngine::OnInputUpdate(float deltaTime, int mods)
{
    // Treat continuous update based on input
}


void GameEngine::OnKeyPress(int key, int mods)
{
    // Add key press event
}


void GameEngine::OnKeyRelease(int key, int mods)
{
    // Add key release event
}


void GameEngine::OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY)
{
    // Add mouse move event
}


void GameEngine::OnMouseBtnPress(int mouseX, int mouseY, int button, int mods)
{
    // Add mouse button press event
}


void GameEngine::OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods)
{
    // Add mouse button release event
}


void GameEngine::OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY)
{
    // Treat mouse scroll event
}


void GameEngine::OnWindowResize(int width, int height)
{
    // Treat window resize event
}
