#pragma once
#include "Brick.h"

class LegoBrick : public Brick
{

public:
    LegoBrick(){};

    void draw()
    {
        std::cout << "Lego Brick" << std::endl;
    }

    std::string getType()
    {
        return "Lego Brick";
    }
} ;