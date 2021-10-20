#pragma once


#include <vector>
#include <stack>
#include <iostream>
#include "LegoBrickFactory.h"
#include "ClayBrickFactory.h"
#include "WoodBrickFactory.h"
#include "Globals.h"

class Command
{

public:
    virtual ~Command(){};
    virtual void execute() = 0;
    virtual void undo(){};
    virtual void redo(){};
    virtual void add(){counter++;}
    virtual void remove(){counter--;}
    virtual int getAmount(){return counter;}
protected:
    Command(){};
    int counter=0;
};

class BuildLegoBrickCommand : public Command
{ 
public:
    BuildLegoBrickCommand() = default;
    ~BuildLegoBrickCommand(){};
    virtual void execute() 
    {
        std::cout << "Order lego brick" << std::endl;
        Factory* factory = new LegoBrickFactory();
        m_bricks.push_back(factory->getBrick());
        add();
    }

    virtual void undo()
    {
        legoBrickCounter--;
        std::cout << "remove one" << std::endl;
    }
    virtual void redo()
    {
        legoBrickCounter++;
        std::cout << "add one" << std::endl;
    }
};

class BuildClayBrickCommand : public Command
{
public:
    BuildClayBrickCommand() = default;
    ~BuildClayBrickCommand(){};
    virtual void execute() 
    {
        std::cout << "Order clay brick" << std::endl;
        Factory* factory = new ClayBrickFactory();
        m_bricks.push_back(factory->getBrick());
    }
    virtual void undo()
    {
        clayBrickCounter--;
        std::cout << "remove one" << std::endl;
    }
    virtual void redo()
    {
        clayBrickCounter++;
        std::cout << "add one" << std::endl;
    }
};

class BuildWoodBrickCommand : public Command
{
public:
    BuildWoodBrickCommand() = default;
    ~BuildWoodBrickCommand(){};
    virtual void execute() 
    {
        std::cout << "order wood brick" << std::endl;
        Factory* factory = new WoodBrickFactory();
        m_bricks.push_back(factory->getBrick());
        counter = 0;
    }
    virtual void undo()
    {
        woodBrickCounter--;
        std::cout << "remove one" << std::endl;
    }
    virtual void redo()
    {
        woodBrickCounter++;
        std::cout << "add one" << std::endl;
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
            std::cout << "remove one" << std::endl;
            undoCommands.push(commands.at(commands.size() - 1));
            commands.pop_back();
            undoCommands.top()->remove();
        }
    }
    virtual void execute()
    {
        if(commands.size() > 0)
        {
            for(Command* command : commands)
            {
                command->execute();
            }
        }

    }

    virtual void undo()
    {
        if(commands.size() > 0)
        {
            std::cout << "undo last command" << std::endl;
            undoCommands.push(commands.at(commands.size()-1));
            commands.at(commands.size()-1)->undo();
            commands.pop_back();
            undoCommands.top()->remove();
        }
    }

    virtual void redo()
    {
        if(undoCommands.size() > 0)
        {
            std::cout << "redo last command" << std::endl;
            undoCommands.top()->add();
            undoCommands.top()->redo();
            commands.push_back(undoCommands.top());
            undoCommands.pop();
        }
    }
private:
    std::vector<Command*> commands;
    std::stack<Command*> undoCommands;
};