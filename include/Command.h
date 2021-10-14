#pragma once


#include <vector>
#include <stack>
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
    virtual void add(){counter++;}
    virtual void remove(){counter--;}
    virtual int getAmount(){return counter;}
protected:
    Command(){};
    int counter;
};

class BuildLegoBrickCommand : public Command
{ 
public:
    BuildLegoBrickCommand() = default;
    ~BuildLegoBrickCommand(){};
    virtual void execute() 
    {
        Factory* factory = new LegoBrickFactory();
        m_bricks.push_back(factory->getBrick());
        counter = 0;
    }

    virtual void undo()
    {
        m_bricks.pop_back();
    }

    virtual void redo()
    {
        execute();
    }
};

class BuildClayBrickCommand : public Command
{
public:
    BuildClayBrickCommand() = default;
    ~BuildClayBrickCommand(){};
    virtual void execute() 
    {
        Factory* factory = new ClayBrickFactory();
        m_bricks.push_back(factory->getBrick());
        counter = 0;
    }

    virtual void undo()
    {
        m_bricks.pop_back();
    }
    virtual void redo()
    {
        execute();
    }
};

class BuildWoodBrickCommand : public Command
{
public:
    BuildWoodBrickCommand() = default;
    ~BuildWoodBrickCommand(){};
    virtual void execute() 
    {
        Factory* factory = new ClayBrickFactory();
        m_bricks.push_back(factory->getBrick());
        counter = 0;
    }

    virtual void undo()
    {
        m_bricks.pop_back();
    }
    virtual void redo()
    {
        execute();
    }
};

class MacroCommand : public Command
{
public:
    MacroCommand(){};
    virtual ~MacroCommand(){};
    virtual void add(Command* command)
    {
        command->add();
        commands.push_back(command);
    }
    virtual void remove()
    {
        if(commands.size() > 0)
        {
            undoCommands.push(commands.at(commands.size() - 1));
            commands.pop_back();
            undoCommands.top()->remove();
        }
    }
    virtual void execute()
    {
        for(Command* command : commands)
        {
            command->execute();
        }
    }

    virtual void undo()
    {
        if(undoCommands.size() > 0)
        {
            undoCommands.top()->add();
            commands.push_back(undoCommands.top());
            undoCommands.pop();
        }
    }

    virtual void redo()
    {

    }
private:
    std::vector<Command*> commands;
    std::stack<Command*> undoCommands;
};