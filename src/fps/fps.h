#pragma once
#include <list>
#include <vector>
#include <stack>
#include <SDL.h>

class fps
{

public:
    fps();
    void fpsinit();
    void fpsthink();
};

extern fps fpsController;