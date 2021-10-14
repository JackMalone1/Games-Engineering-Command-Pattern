#pragma once

#include "Brick.h"


class ClayBrick : public Brick
{

public:
    ClayBrick()
    {

    }

    void draw()
    {
        std::cout << "Clay Brick" << std::endl;   
    }

    std::string getType()
    {
        return "Clay Brick";
    }
};