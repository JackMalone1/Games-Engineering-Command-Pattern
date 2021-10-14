#pragma once

#include "Factory.h"
#include "WoodBrick.h"

class WoodBrickFactory : public Factory
{
public:
    Brick* getBrick()
    {
        return new WoodBrick();
    }
};