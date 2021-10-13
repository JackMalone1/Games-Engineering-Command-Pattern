#pragma once

#include "Factory.h"
#include "ClayBrick.h"


class ClayBrickFactory : public Factory
{
public:
    std::vector<Brick*> getBricks(int t_numberOfBricks)
    {
        std::vector<Brick*> values;

        for(int i = 0; i < t_numberOfBricks; i++)
        {
            values.push_back(new ClayBrick());
        }

        return values;
    }
};