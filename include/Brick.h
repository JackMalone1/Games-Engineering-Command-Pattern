#pragma once
#include <iostream>

class Brick
{
public:
    Brick(){};
    virtual ~Brick(){};
    virtual void draw() = 0;
    virtual std::string getType() = 0;
};