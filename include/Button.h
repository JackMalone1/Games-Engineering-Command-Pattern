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
    Button(float t_x, float t_y, SDL_Renderer* t_renderer, TTF_Font* t_font, std::string t_name, Command* t_command, bool t_showCounter=false, int* t_counter=nullptr) :
    x(t_x),
    y(t_y),
    renderer(t_renderer),
    font(t_font),
    name(t_name),
    command(t_command),
    m_showCounter(t_showCounter),
    counter(t_counter)
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
        *counter = *counter + 1;
        
        UpdateCounter();
    }

    virtual void UpdateCounter()
    {
        if (command != nullptr && m_showCounter)
        if(counter != nullptr)
            initCounter("Count" + std::to_string(*counter));
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
        SDL_Surface* tempSurf = TTF_RenderText_Solid(font, string.c_str(), SDL_Color{0,255,0});

        counterTexture = SDL_CreateTextureFromSurface(renderer, tempSurf);

        SDL_QueryTexture(counterTexture, NULL, NULL, & counterText.w, & counterText.h);

        counterText.x = text.x;
        counterText.y = y + 128 - (counterText.h / 2.0f);
        if(counterTexture == nullptr) std::cout << SDL_GetError() << std::endl;
        SDL_FreeSurface(tempSurf);
    }

    void init()
    {
        background.x = x;
        background.y = y;
        background.w = 150;
        background.h = 150;
        initText();
        if(m_showCounter && counter != nullptr) initCounter("Count" + std::to_string(*counter));
        
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
    int* counter;
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
            if(m_removeCommand)
            {
                std::cout << "undo" << std::endl;
                t_macro->undo();
            } 
            else 
            {
                std::cout << "redo" << std::endl;
                t_macro->redo();
            }
        }
        else if(m_func != nullptr)
        {
            m_func(m_caller);
        }
    }
private:
    bool m_removeCommand=false;
    std::function<void(Game*)> m_func=nullptr;
    Game* m_caller=nullptr;
};