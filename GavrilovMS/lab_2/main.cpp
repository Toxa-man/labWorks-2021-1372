#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <vector>
#include <conio.h>
#include <string>
#include <fstream>
#include <iostream>

int GetRandomPos(int i, int j) {
    int pos = i + rand() % (j - i);
    pos = pos - (pos % 20);
    return pos;
}


int main()
{
    sf::RenderWindow window(sf::VideoMode(1500, 800), "Snake!");
    

    sf::Image grass;
    grass.loadFromFile("images/grass.jpg");
    sf::Texture grasstexture;
    grasstexture.loadFromImage(grass);
    sf::Sprite grasssprite;
    grasssprite.setTexture(grasstexture);
    grasssprite.setPosition(0, 0);

    sf::Image start;
    start.loadFromFile("images/start.png");
    sf::Texture starttexture;
    starttexture.loadFromImage(start);
    sf::Sprite startsprite;
    startsprite.setTexture(starttexture);
    startsprite.setPosition(0, 0);

    sf::Image newgame;
    newgame.loadFromFile("images/newgame.png");
    sf::Texture newgametexture;
    newgametexture.loadFromImage(newgame);
    sf::Sprite newgamesprite;
    newgamesprite.setTexture(newgametexture);
    newgamesprite.setPosition(0, 0);

    sf::Font font;
    font.loadFromFile("ANAGRAM.TTF");
    sf::Text textscore("", font, 43);
    textscore.setFillColor(sf::Color::Color(194, 0, 0));
    textscore.setPosition(0, 0);

    sf::Image headleft;
    headleft.loadFromFile("images/headleft.png");
    sf::Texture headlefttexture;
    headlefttexture.loadFromImage(headleft);
    
    window.setIcon(20, 20, headleft.getPixelsPtr());

    sf::Image headright;
    headright.loadFromFile("images/headright.png");
    sf::Texture headrighttexture;
    headrighttexture.loadFromImage(headright);

    sf::Image headup;
    headup.loadFromFile("images/headup.png");
    sf::Texture headuptexture;
    headuptexture.loadFromImage(headup);

    sf::Image headdown;
    headdown.loadFromFile("images/headdown.png");
    sf::Texture headdowntexture;
    headdowntexture.loadFromImage(headdown);
    
    sf::Sprite headsprite;
    headsprite.setTexture(headlefttexture);

    sf::Image bodyblock;
    bodyblock.loadFromFile("images/body.png");
    sf::Texture bodyblocktexture;
    bodyblocktexture.loadFromImage(bodyblock);
    sf::Sprite bodyblocksprite;
    bodyblocksprite.setTexture(bodyblocktexture);
    
    sf::Image cake;
    cake.loadFromFile("images/cake.png");
    sf::Texture caketexture;
    caketexture.loadFromImage(cake);
    sf::Sprite cakesprite;
    cakesprite.setTexture(caketexture);

    sf::SoundBuffer eatingbuffer;
    eatingbuffer.loadFromFile("sounds/eating.wav");
    sf::Sound eating;
    eating.setBuffer(eatingbuffer);

    sf::SoundBuffer losebuffer;
    losebuffer.loadFromFile("sounds/lose.wav");
    sf::Sound lose;
    lose.setBuffer(losebuffer);

    sf::Vector2f cakepos, nextpos1, nextpos2, headpos, bodyblockpos;

    bool eatingyourself, goodcakepos, newgamecheck = true, checkhit = false;
    int direction1, direction2, randompos1, randompos2, score, bestscore, speed, time;
    std::string strscore;

    sf::Event event;


    while (window.isOpen())
    {
       
        std::fstream Fbestscore("BestScore.txt", std::ios::in);

        Fbestscore >> bestscore;

        Fbestscore.close();

        strscore = "Best score: " + std:: to_string(bestscore);
        textscore.setString(strscore);
        textscore.setPosition(0, 0);

   
        
        while (!sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)) {
            window.clear();
            window.draw(grasssprite);
            window.draw(textscore);
            window.draw(startsprite);
            window.display();
            while (window.pollEvent(event))
            {
                if (event.type == sf::Event::Closed) {
                    window.close();
                    return 0;
                }
            }
        }


        while (newgamecheck) {

            headsprite.setTexture(headlefttexture);
            headsprite.setPosition(480, 480);
            cakesprite.setPosition(520, 540);
            bodyblocksprite.setPosition(500, 480);
            direction1 = -20, direction2 = 0;
            score = 0;

            speed = 60;

            std::vector <sf::Sprite> body;
            body.push_back(bodyblocksprite);

            eatingyourself = false;


            sf::Clock clock;
            
            while (!_kbhit() && !eatingyourself) {
                
                nextpos1 = headsprite.getPosition();
   
                time = clock.getElapsedTime().asMilliseconds();

                if (time > speed) {
                    if (nextpos1.x > 1480 || nextpos1.x < 0 || nextpos1.y > 780 || nextpos1.y < 0) {
                        if (nextpos1.x > 1480) {
                            headsprite.move(-1500, 0);
                        }
                        if (nextpos1.x < 0) {
                            headsprite.move(1500, 0);
                        }
                        if (nextpos1.y > 780) {
                            headsprite.move(0, -800);
                        }

                        if (nextpos1.y < 0) {
                            headsprite.move(0, 800);
                        }

                    }
                    else {
                        headsprite.move(direction1, direction2);

                    }

                    for (unsigned int i = 0; i < body.size(); i++) {
                        nextpos2 = body[i].getPosition();
                        body[i].setPosition(nextpos1);
                        nextpos1 = nextpos2;
                    }

                    checkhit = false;
                    clock.restart();
                }

                
                
                while (window.pollEvent(event) && !checkhit) {
                    if (event.type == sf::Event::KeyPressed) {
                        switch (event.key.code) {
                        case sf::Keyboard::Left: {
                            if (direction1 != 20) {
                                direction1 = -20; direction2 = 0; headsprite.setTexture(headlefttexture);
                            }
                            checkhit = true;
                            break;

                        }
                        case sf::Keyboard::Right: {
                            if (direction1 != -20) {
                                direction1 = 20; direction2 = 0; headsprite.setTexture(headrighttexture);
                            }
                            checkhit = true;
                            break;
                        }
                        case sf::Keyboard::Up: {
                            if (direction2 != 20) {
                                direction1 = 0; direction2 = -20; headsprite.setTexture(headuptexture);
                            }
                            checkhit = true;
                            break;
                        }
                        case sf::Keyboard::Down: {
                            if (direction2 != -20) {
                                direction1 = 0; direction2 = 20; headsprite.setTexture(headdowntexture);
                            }
                            checkhit = true;
                            break;
                        }
                        }
                    }
                    if (event.type == sf::Event::Closed) {
                        window.close();
                        return 0;
                    }

                }

                

                headpos = headsprite.getPosition();
                cakepos = cakesprite.getPosition();
                goodcakepos = false;

                bodyblocksprite = body[body.size() - 1];
                if (headpos == cakepos) {
                    eating.play();
                    body.push_back(bodyblocksprite);
                    score++;
                    if (speed != 20) { speed--; }
                    while (!goodcakepos) {
                        randompos1 = GetRandomPos(1, 1500);
                        randompos2 = GetRandomPos(1, 800);
                        cakesprite.setPosition(randompos1, randompos2);
                        cakepos = cakesprite.getPosition();
                        goodcakepos = true;
                        for (int i = 0; i < body.size(); i++) {
                            bodyblockpos = body[i].getPosition();
                            if (cakepos == bodyblockpos) {
                                goodcakepos = false;
                            }
                        }
                    }

                }
                

                strscore = "Score: " + std::to_string(score);
                textscore.setString(strscore);
                window.clear();
                window.draw(grasssprite);
                window.draw(textscore);
                window.draw(cakesprite);
                window.draw(headsprite);
                for (int i = 0; i < body.size(); i++) {
                    window.draw(body[i]);
                    bodyblockpos = body[i].getPosition();
                    if (headpos == bodyblockpos) {
                        eatingyourself = true;
                    }
                }
                window.display();

            }

            if (score > bestscore) {
                Fbestscore.open("BestScore.txt", std::ios::out);
                Fbestscore << score;
                Fbestscore.close();
                strscore = "New best score: " + std::to_string(score);
            }
            else {
                strscore = "Your score: " + std::to_string(score);
            }

            textscore.setString(strscore);

            checkhit = false;
            
            lose.play();
            while (!checkhit) { 
                window.clear();
                window.draw(grasssprite);
                for (int i = 0; i < body.size(); i++) {
                    window.draw(body[i]);
                }
                window.draw(headsprite);
                window.draw(textscore);
                window.draw(newgamesprite);
                window.display();
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)) { newgamecheck = true; checkhit = true; }
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {newgamecheck = false; checkhit = true;  }

                while (window.pollEvent(event))
                {
                    if (event.type == sf::Event::Closed) {
                        window.close();
                        return 0;
                    }
                }
            }

        }
        window.close();
        
    }

    return 0;
}
