#include "Player.h"

Player::Player(int x, int y, const std::string& imagePath) : x(x), y(y), image(imagePath.c_str()) {}

void Player::render(SDL_Surface* screenSurface)
{
    // set the position of the player on the screen
    SDL_Rect destRect = { x, y, 0, 0 };
    // render the image of the player on the screen
    SDL_BlitSurface(image.getResource(), nullptr, screenSurface, &destRect);
}
