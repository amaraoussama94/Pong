#include "Bat.hpp"
#include <sstream>
#include <cstdlib>
#include <SFML/Graphics.hpp>
int main()
{
    // Create a video mode object
    VideoMode vm(1080, 768);
    // Create and open a window for the game
    RenderWindow window(vm, "Pong", Style::Fullscreen);
    int score = 0;
    int lives = 3;
    // Create a bat at the bottom center of the screen
    Bat bat(1080 / 2, 768 - 20);
    // We will add a ball in the next chapter
    // Create a Text object called HUD
    Text hud;
    // A cool retro-style font
    Font font;
    font.loadFromFile("fonts/DS-DIGI.ttf");
    // Set the font to our retro-style
    hud.setFont(font);
    // Make it nice and big
    hud.setCharacterSize(75);
    // Choose a color
    hud.setFillColor(Color::White);
    hud.setPosition(20, 20);
    // Here is our clock for timing everything
    Clock clock;
    while (window.isOpen())
    {
    /*
    Handle the player input
    ****************************
    ****************************
    ****************************
    */
    /*
    Update the bat, the ball and the HUD
    *****************************
    *****************************
    *****************************
    */
    /*
    Draw the bat, the ball and the HUD
    *****************************
    *****************************
    *****************************
    */
    }
    return 0;
}