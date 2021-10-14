#pragma once

#include "Factory.h"
#include "ClayBrick.h"


class ClayBrickFactory : public Factory
{
public:
    Brick* getBrick()
    {
        return new ClayBrick();
    }
};