#include "Bat.hpp"
#include "Ball.hpp"
#include <sstream>
#include <fstream>


#include <cstdlib>
#include <SFML/Graphics.hpp>
int main()
    {
    // The game will always be in one of three states
    enum class State { MENU, SINGLEPLAYER, MULTIPLAYER };
    // Start with the MENU state
    State state = State::MENU;
    // Create a video mode object
    VideoMode vm(1024, 768);
    // Create and open a window for the game
    RenderWindow window(vm, "Pong");//, Style::Fullscreen   third  para if  you want full screen mood
    //player 1
    int score_1 = 0;
    int lives_1 = 3;

    // player 2
    int score_2 = 0;
    int lives_2 = 3;
    // Create a bat at the bottom center of the screen
    //first player 
    Bat bat_1(1024/ 2, 768 - 20);
    //Second player 
    Bat bat_2(1024/ 2, 20);
    // Create a ball
    Ball ball(1024 / 2, 0);
    // Create a Text object called HUD
    Text hud_1;// for player 1
    Text hud_2;// for player 2
    // A cool retro-style font
    Font font;
    font.loadFromFile("fonts/DS-DIGI.TTF");
    // Set the font to our retro-style
    hud_1.setFont(font);//player 1
    hud_2.setFont(font);//player 2
    // Make it nice and big
    hud_1.setCharacterSize(25);//player 1
    hud_2.setCharacterSize(25);//player 1
    // Choose a color
    hud_1.setFillColor(Color::White);//player 1
    hud_1.setPosition(20, 768/2);//player 1
    hud_2.setFillColor(Color::White);//player 2
    hud_2.setPosition(1024-200, 768/2);//player 2
    // Here is our clock for timing everything
    Clock clock;

    // Menu 
	Text GameMode;
	GameMode.setFont(font);
	GameMode.setCharacterSize(80);
	GameMode.setFillColor(Color::White);
	GameMode.setPosition(100, 300);
	std::stringstream ssGameMode;
	ssGameMode << 
     "1- Single player mode" <<
	"\n2- multiplayer mode" ;
	GameMode.setString(ssGameMode.str());
    /*player 1*///////////////////////////////////////
      
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
             
        /*******start********/ 
         if (state == State::MENU)
         {
            window.draw(GameMode);//draw menu to the screen
            window.display();//F*** don t miss this all drawing in the screen is handeled with this fucnction
            if(Keyboard::isKeyPressed(Keyboard::Num1) )//event.key.code == Keyboard::Num1
            { 
                state = State::SINGLEPLAYER;//change mode to single mode 
                
            }
            if(event.key.code == Keyboard::Num2)
            { 
                state = State::MULTIPLAYER;//change mode to multiplayer mode 
            }

         }

        if (state == State::MULTIPLAYER)
        {
      
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
            // Handle the pressing and releasing of the arrow keys for player two
            if (Keyboard::isKeyPressed(Keyboard::Q))
                {
                bat_2.moveLeft();
                    // Handle Batt getting Leftsides
                if (bat_2.getPosition().left < 0 )
                    {
                    bat_2.stopLeft() ;
                    }
                }
            else
                {
                bat_2.stopLeft();
                }
            if (Keyboard::isKeyPressed(Keyboard::D))
                {
                bat_2.moveRight();
                    // Handle Batt getting Right sides
                if (bat_2.getPosition().left + bat_2.getPosition().width> window.getSize().x)
                    {
                    bat_2.stopRight() ;
                    }
                }
            else
                {
                bat_2.stopRight();
                }
            
            /*lives_2
            */
        // Update the delta time
            Time dt = clock.restart();
            
            bat_1.update(dt);//player 1
            bat_2.update(dt);//playe r 2
            ball.update(dt);
            // Update the HUD text
            std::stringstream ss_1,ss_2;
            //player 1
            ss_1 << "Score:" << score_1 << " Lives:" << lives_1;
            hud_1.setString(ss_1.str());
            //player 2
            ss_2 << "Score:" << score_2 << " Lives:" << lives_2;
            hud_2.setString(ss_2.str());
            // Handle ball hitting the bottom
            if (ball.getPosition().top > window.getSize().y)
                {
                // reverse the ball direction
                    ball.reboundBottom();
                // Remove a life
                    lives_1--;
                    score_2++;
                // Check for zero lives
                    if (lives_1 < 1) 
                        {
                        // reset the score
                            score_1 = 0;
                        // reset the lives
                            lives_1 = 3;
                            
                        }
                }
                // Handle ball hitting top
            if (ball.getPosition().top < 0)
                {
                    ball.reboundBatOrTop();
                // Add a point to the players score
                    score_1++;
                    lives_2--;
                if (lives_2 < 1) 
                        {
                        // reset the score
                            score_2 = 0;
                        // reset the lives
                            lives_2 = 3;
                            
                        }
                }
                // Handle ball hitting sides
            if (ball.getPosition().left < 0 ||ball.getPosition().left + ball.getPosition().width> window.getSize().x)
                {
                    ball.reboundSides();
                }
            // Has the ball hit the bat player 1?
            if (ball.getPosition().intersects(bat_1.getPosition()))
                {
                // Hit detected so reverse the ball and score a point
                    ball.reboundBatOrTop();
                }
            // Has the ball hit the bat player 2?
            if (ball.getPosition().intersects(bat_2.getPosition()))
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
            window.draw(hud_1);/*player 1*/
            window.draw(hud_2);/*player 2*/
            window.draw(bat_1.getShape());//first player 
            window.draw(bat_2.getShape());//second player 
            window.draw(ball.getShape());
            window.display();

        }/*******end Multiplayer mode********/ 
        }

    return 0;
    }