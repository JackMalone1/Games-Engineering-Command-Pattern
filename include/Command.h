#pragma once

#include <list>
#include <vector>
#include "LegoBrickFactory.h"
#include "ClayBrickFactory.h"
#include "WoodBrickFactory.h"
#include "Globals.h"

class Command
{
public:
    virtual ~Command(){};
    virtual void execute() = 0;
    virtual void undo() = 0;
    virtual void redo() = 0;
protected:
    Command();
};

class BuildLegoBrickCommand : public Command
{ 
public:
    virtual void execute() 
    {
        Factory* factory = new LegoBrickFactory();
        m_legoBricks.push_back(factory->getBricks(1).at(0));
    }

    virtual void undo()
    {
        m_legoBricks.pop_back();
    }

    virtual void redo()
    {
        execute();
    }
};

class BuildClayBrickCommand : public Command
{
public:
    virtual void execute() 
    {
        Factory* factory = new ClayBrickFactory();
        m_clayBricks.push_back(factory->getBricks(1).at(0));
    }

    virtual void undo()
    {
        m_clayBricks.pop_back();
    }
    virtual void redo()
    {
        execute();
    }
};

class WoodBrickCommand : public Command
{
public:
    virtual void execute() 
    {
        Factory* factory = new ClayBrickFactory();
        m_clayBricks.push_back(factory->getBricks(1).at(0));
    }

    virtual void undo()
    {
        m_clayBricks.pop_back();
    }
    virtual void redo()
    {
        execute();
    }
};

class MacroCommand : public Command
{
public:
    MacroCommand();
    virtual ~MacroCommand();
    virtual void add(Command* command)
    {
        commands->push_back(command);
    }
    virtual void remove(Command* command)
    {
        commands->remove(command);
    }
    virtual void execute()
    {
        for(Command* command : *commands)
        {
            command->execute();
        }
    }
private:
    std::list<Command*>* commands;
};