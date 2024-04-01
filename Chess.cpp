#include <SFML\Graphics.hpp>
#include <SFML\Window.hpp>
#include "square.h"
#include "Textures.h"
#include "Game.h"
#include "PawnPromotion.h"

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
                game.PossibleMoves(window, event);
                game.Drag(event);
                break;
            }
            else if (event.type == Event::MouseButtonReleased)
            {
                game.StopDragging(window, event);
                break;
            }
            else if (event.type == sf::Event::Closed)
                window.close();                                 
        }
        window.clear(sf::Color(139, 69, 19));
        game.DrawBoard(window);

        if (game.isPromotion) {
            game.OnPawnPromotion(window, event);
        }

        if(game.Started)
            game.PrepareGame(window);
        else
        {
            game.GrabPiece(window);
            game.Update(window);
        }
        window.display();
    }
    return 0;
}
