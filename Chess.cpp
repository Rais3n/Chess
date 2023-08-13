#include <SFML\Graphics.hpp>
#include <SFML\Window.hpp>
#include "square.h"
#include "Textures.h"
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
            if (event.type == Event::MouseButtonPressed)
            {
                game.possibleMoves(window, event);
                game.drag(event);
                break;
            }
            else if (event.type == Event::MouseButtonReleased)
            {
                game.stopdrag(window, event);
                break;
            }
            else if (event.type == sf::Event::Closed)
                window.close();                                 
        }
        window.clear(sf::Color(139, 69, 19));
        game.Board(window);
        if(game.Started)
            game.prepareGame(window);
        else
        {
            game.grabPiece(window);
            game.update(window);
        }
        window.display();
    }
    return 0;
}
