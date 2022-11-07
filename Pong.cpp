#include "Bat.hpp"
#include "Ball.hpp"
#include <sstream>
#include <cstdlib>
#include <SFML/Graphics.hpp>
int main()
    {
    // Create a video mode object
    VideoMode vm(1024, 768);
    // Create and open a window for the game
    RenderWindow window(vm, "Pong");//, Style::Fullscreen   third  para if  you want full screen mood
    int score = 0;
    int lives = 3;
    // Create a bat at the bottom center of the screen
    //first player 
    Bat bat_1(1024/ 2, 768 - 20);
    //Second player 
    Bat bat_2(1024/ 2, 20);
    // Create a ball
    Ball ball(1024 / 2, 0);
    // Create a Text object called HUD
    Text hud;
    // A cool retro-style font
    Font font;
    font.loadFromFile("fonts/DS-DIGI.TTF");
    // Set the font to our retro-style
    hud.setFont(font);
    // Make it nice and big
    hud.setCharacterSize(50);
    // Choose a color
    hud.setFillColor(Color::White);
    hud.setPosition(20, 20);
    // Here is our clock for timing everything
    Clock clock;
    while (window.isOpen())
        {
    /*
    **********************************
    ***** Handle the player input*****
    **********************************
    */

        Event event;
        while (window.pollEvent(event))
            {
            if (event.type == Event::Closed)
            // Quit the game when the window is closed
            window.close();
            }
        // Handle the player quitting
        if (Keyboard::isKeyPressed(Keyboard::Escape))
            {
            window.close();
            }
        // Handle the pressing and releasing of the arrow keys for player one 
        if (Keyboard::isKeyPressed(Keyboard::Left))
            {
            bat_1.moveLeft();
                 // Handle Batt getting Leftsides
            if (bat_1.getPosition().left < 0 )
                {
                bat_1.stopLeft() ;
                }
            }
        else
            {
            bat_1.stopLeft();
            }
        if (Keyboard::isKeyPressed(Keyboard::Right))
            {
            bat_1.moveRight();
                // Handle Batt getting Right sides
            if (bat_1.getPosition().left + bat_1.getPosition().width> window.getSize().x)
                {
                bat_1.stopRight() ;
                }
            }
        else
            {
            bat_1.stopRight();
            }
          
         
        /*
        
        **********************************************
        *****Update the bat, the ball and the HUD*****
        **********************************************
        */
       // Update the delta time
        Time dt = clock.restart();
        
        bat_1.update(dt);
        ball.update(dt);
        // Update the HUD text
        std::stringstream ss;
        ss << "Score:" << score << " Lives:" << lives;
        hud.setString(ss.str());

        // Handle ball hitting the bottom
        if (ball.getPosition().top > window.getSize().y)
            {
            // reverse the ball direction
                ball.reboundBottom();
            // Remove a life
                lives--;
            // Check for zero lives
                if (lives < 1) 
                    {
                    // reset the score
                        score = 0;
                    // reset the lives
                        lives = 3;
                    }
            }
            // Handle ball hitting top
        if (ball.getPosition().top < 0)
            {
                ball.reboundBatOrTop();
            // Add a point to the players score
                score++;
            }
            // Handle ball hitting sides
        if (ball.getPosition().left < 0 ||ball.getPosition().left + ball.getPosition().width> window.getSize().x)
            {
                ball.reboundSides();
            }
        // Has the ball hit the bat?
        if (ball.getPosition().intersects(bat_1.getPosition()))
            {
            // Hit detected so reverse the ball and score a point
                ball.reboundBatOrTop();
            }

        /*
        **********************************************
        ****** Draw the bat, the ball and the HUD*****
        **********************************************
        */
        window.clear();
        window.draw(hud);
        window.draw(bat_1.getShape());//first player 
        window.draw(bat_2.getShape());//second player 
        window.draw(ball.getShape());
        window.display();


            }
    return 0;
    }