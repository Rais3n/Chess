#include <SFML\Graphics.hpp>
#include <SFML\Window.hpp>
#include "square.h"
#include "Textures.h"
#include <iostream>
#include "Game.h"

using namespace sf;
using namespace std;

int main()
{
    sf::RenderWindow window(sf::VideoMode(600, 600), "Chess");
    Game game;


    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            game.move(window, event);
        }
        window.clear();
        game.Board(window);
        if(game.Started)
        game.prepareGame(window);
        else
        game.update(window);
        window.display();
    }


    return 0;
}
