#pragma once

#include "Brick.h"

class WoodBrick : public Brick
{
    
public:
    WoodBrick() {};

    void draw()
    {
        std::cout << "Wood Brick" << std::endl;
    }

    std::string getType()
    {
        return "Wood Brick";
    }
};