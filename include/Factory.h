#pragma once

#include "Brick.h"
#include <vector>

class Factory
{
public:
    virtual std::vector<Brick*> getBricks(int t_numberOfBricks) = 0;
};