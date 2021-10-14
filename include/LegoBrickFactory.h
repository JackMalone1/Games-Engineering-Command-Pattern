#pragma once

#include "Factory.h"
#include "LegoBrick.h"

class LegoBrickFactory : public Factory
{
public:
    Brick* getBrick()
    {
        return new LegoBrick();
    }
};