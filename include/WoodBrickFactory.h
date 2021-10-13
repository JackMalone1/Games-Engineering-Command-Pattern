#pragma once

#include "Factory.h"
#include "WoodBrick.h"

class WoodBrickFactory : public Factory
{
public:
    std::vector<Brick*> getBricks(int t_numberOfBricks)
    {
        std::vector<Brick*> values;

        for(int i = 0; i < t_numberOfBricks; i++)
        {
            values.push_back(new WoodBrick());
        }

        return values;
    }
};