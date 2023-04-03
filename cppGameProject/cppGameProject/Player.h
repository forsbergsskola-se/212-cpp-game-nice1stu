#pragma once
#include "Image.h"
#include <string>

class Player
{
private:
    int x, y; // the position of the player on the screen
    Image image; // the image representing the player
public:
    Player(int x, int y, const std::string& imagePath); // constructor
    void render(SDL_Surface* screenSurface); // render the player on the screen
};
