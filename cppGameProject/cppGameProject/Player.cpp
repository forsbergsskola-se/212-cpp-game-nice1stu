#include "Player.h"

Player::Player(int x, int y, const std::string& imagePath) : x(x), y(y), image(imagePath.c_str()) {}

void Player::render(SDL_Surface* screenSurface)
{
    
    SDL_Rect destRect = { x, y, 0, 0 };
    
    SDL_BlitSurface(image.getResource(), nullptr, screenSurface, &destRect);
}
