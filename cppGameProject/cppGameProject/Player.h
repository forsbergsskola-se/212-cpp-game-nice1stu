#pragma once
#include "Image.h"
#include <string>

class Player
{
private:
    int x, y;
    Image image;
    Player(int x, int y, const std::string& imagePath);
    void render(SDL_Surface* screenSurface);
};
