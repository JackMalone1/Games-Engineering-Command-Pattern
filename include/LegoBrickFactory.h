#pragma once

#include "Factory.h"
#include "LegoBrick.h"

class LegoBrickFactory : public Factory
{
public:
    std::vector<Brick*> getBricks(int t_numberOfBricks)
    {
        std::vector<Brick*> values;

        for(int i = 0; i < t_numberOfBricks; i++)
        {
            values.push_back(new LegoBrick());
        }

        return values;
    }
};