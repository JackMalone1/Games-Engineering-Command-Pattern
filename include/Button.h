#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <string>
#include "Command.h"

class Button
{
public:
    Button(float t_x, float t_y, SDL_Renderer* t_renderer, TTF_Font* t_font, std::string t_name);
    void setCommand(Command* t_command) {command = t_command;}


    void draw()
    {

    }
private:
    void increaseNumberOfBlocks();
    void init();
private:
    float x;
    float y;
    TTF_Font* font;
    SDL_Renderer* renderer;
    SDL_Rect text;
    SDL_Rect background;
    SDL_Rect counterText;
    std::string name;
    int counter;
    Command* command;
};
