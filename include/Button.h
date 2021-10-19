#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <string>
#include "Command.h"
#include <functional>

class Game;

class Button
{
public:
    Button(float t_x, float t_y, SDL_Renderer* t_renderer, TTF_Font* t_font, std::string t_name, Command* t_command, bool t_showCounter=false) :
    x(t_x),
    y(t_y),
    renderer(t_renderer),
    font(t_font),
    name(t_name),
    counter(0),
    command(t_command),
    m_showCounter(t_showCounter)
    {
        init();
    }
    void setCommand(Command* t_command) {command = t_command;}


    void draw()
    {
        SDL_SetRenderDrawColor(renderer, 0,0,255,255);
        SDL_RenderDrawRect(renderer, &background);
        SDL_SetRenderDrawColor(renderer, 255,0,0,255);
        SDL_RenderCopy(renderer, textTexture,nullptr, &text);
        if(m_showCounter)
        {
            SDL_RenderCopy(renderer, counterTexture, nullptr, &counterText);
        }
    }

    bool isPointOnButton(float t_x, float t_y)
    {
        if(t_x > background.x && t_x < background.x + background.w && t_y > background.y && t_y < background.y + background.h)
        {
            std::cout << "button clicked" << std::endl;
            return true;
        } 
        return false;
    }

    virtual void click(MacroCommand* t_macro)
    {
        t_macro->add(command);
        //if(command) command->execute();
        counter++;
    }

    virtual void UpdateCounter()
    {
        if (command != nullptr && m_showCounter)
        initCounter(std::to_string(command->getAmount()));
    }
private:
    void increaseNumberOfBlocks();
    void initText()
    {
        SDL_Surface* surface = TTF_RenderText_Solid(font, name.c_str(), SDL_Color{0,255,0});
        textTexture = SDL_CreateTextureFromSurface(renderer, surface);        
        SDL_QueryTexture(textTexture, nullptr, nullptr, &text.w, &text.h);        
        text.x = x + (background.w / 2.0f) - ((text.w / 2.0f));
        text.y = y + (background.h / 2.0f) - (text.h / 2.0f);
        if(textTexture == nullptr) std::cout << SDL_GetError() << std::endl;
        SDL_FreeSurface(surface);
    }

    void initCounter(std::string string)
    {
        SDL_Surface* tempSurf = TTF_RenderText_Solid(font, string.c_str(), SDL_Color{255,255,255});

        counterTexture = SDL_CreateTextureFromSurface(renderer, tempSurf);

        SDL_QueryTexture(counterTexture, NULL, NULL, & counterText.w, & counterText.h);

        counterText.x = x + 128 - (counterText.w / 2.0f);
        counterText.y = y + 128 + (counterText.h / 2.0f);

        SDL_FreeSurface(tempSurf);
    }

    void init()
    {
        background.x = x;
        background.y = y;
        background.w = 150;
        background.h = 150;
        initText();
        initCounter(std::to_string(0));
    }
protected:
    float x;
    float y;
    TTF_Font* font;
    SDL_Renderer* renderer;
    SDL_Rect text;
    SDL_Texture* textTexture;
    SDL_Rect background;
    SDL_Texture* counterTexture;
    SDL_Rect counterText;
    std::string name;
    int counter;
    Command* command;
    bool m_showCounter;
};


class CommandButton : public Button
{
public:
    CommandButton(float t_x, float t_y, SDL_Renderer* t_renderer, TTF_Font* t_font, std::string t_name, Command* t_command) : Button(
    t_x,
    t_y,
    t_renderer,
    t_font,
    t_name,
    t_command)
    {
        m_showCounter = false;
        m_removeCommand = false;
    }

    void addFunction(std::function<void(Game*)> t_func, Game* t_caller)
    {
        m_caller = t_caller;
        m_func = t_func;
    }

    void setRemoveCommand(bool t_removeCommand)
    {
        m_removeCommand = t_removeCommand;
    }

    virtual void click(MacroCommand* t_macro)override
    {
        if (m_caller == nullptr && m_func == nullptr)
        {
            if (m_removeCommand)
                t_macro->remove();
            else
                t_macro->undo();
        }
        else
        {
            m_func(m_caller);
        }
    }
private:
    bool m_removeCommand;
    std::function<void(Game*)> m_func;
    Game* m_caller;
};