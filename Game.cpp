#include "Game.h"
#include <iostream>


using namespace sf;
using namespace std;

Game::Game()
{
	bPieces[0].setPieces('r', 1, 0);
	bPieces[1].setPieces('k', 1, 1);
	bPieces[2].setPieces('b', 1, 2);
	bPieces[3].setPieces('q', 1, 3);
	bPieces[4].setPieces('K', 1, 4);
	bPieces[5].setPieces('b', 1, 5);
	bPieces[6].setPieces('k', 1, 6);
	bPieces[7].setPieces('r', 1, 7);

	wPieces[0].setPieces('r', 0, 56);
	wPieces[1].setPieces('k', 0, 57);
	wPieces[2].setPieces('b', 0, 58);
	wPieces[3].setPieces('q', 0, 59);
	wPieces[4].setPieces('K', 0, 60);
	wPieces[5].setPieces('b', 0, 61);
	wPieces[6].setPieces('k', 0, 62);
	wPieces[7].setPieces('r', 0, 63);
	for (int i = 8; i < 16; i++)
		bPieces[i].setPieces('p', 1, i);
	for (int i = 8; i < 16; i++)
		wPieces[i].setPieces('p', 0, i+40 );


	for (float i = 0.f; i < 8.f; i++)                                      //makes the board
		for (float j = 0.f; j < 8.f; j++)
		{
			square temp((125.f + j * 50.f), (125.f + i * 50.f));
			if (int(i + j) % 2 == 0)
				temp.changeColor();
			squares.emplace_back(temp);
		}

}

void Game::Board(RenderWindow &window)
{
	for (int i = 0; i < 64; i++)
	{
		window.draw(squares[i]);
	}
}

void Game::takePlace(int place, pieces figure)
{
	squares[place].isTaken = true;
	squares[place].figure = &figure;
}

int Game::whichField(RenderWindow& window)
{	
	Vector2i mousePos = Mouse::getPosition(window);
	if (Mouse::isButtonPressed(Mouse::Left) && mousePos.x <= 100 && mousePos.x >= 500 && mousePos.y <= 100 && mousePos.y >= 500)
	{
		int m = (mousePos.x - 100) / 50 + (mousePos.y - 100) / 50 * 8;
		return m;
	}


	return 64;
}

void Game::possibleMoves(RenderWindow& window)
{
	int m = whichField(window); //where mouse clicked
	if (squares[m].isTaken)
	{
		vector <unsigned> moves;
		char piece = squares[m].figure->piece;
		int player = squares[m].figure->player;
		int column = m % 8;
		int row = m / 8;

		if (piece == 'p')
		{

		}
		else if (piece == 'k')
		{

		}
		else if (piece == 'b')
		{

		}
		else if (piece == 'q')
		{

		}
		else if (piece == 'r')
		{
			for (int i = m; i >= m - column; i--)
			{
				if (squares[i].isTaken == false)
					moves.emplace_back(i);
				else break;
			}
			for (int i = m; i <= m - (column + 1); i++)
			{
				if (squares[i].isTaken == false)
					moves.emplace_back(i);
				else break;
			}
			for (int i = row - 1; i >=  0; i--)
			{
				if (squares[column + 8 * i].isTaken == false)
					moves.emplace_back(column + 8 * i);
				else break;
			}
			for (int i = row + 1; i <= 7; i++)
			{
				if (squares[column + 8 * i].isTaken == false)
					moves.emplace_back(column + 8 * i);
				else break;
			}

		}
		else 
		{
			

		}
				



	}
}

void Game::move(RenderWindow &window, Event &event)
{


		if (event.type == Event::MouseButtonPressed)
		{

			Vector2i mousePos = Mouse::getPosition(window);
			cout << mousePos.x<<" "<<mousePos.y<<endl;
			if (mousePos.x >= 100 && mousePos.x <= 500 && mousePos.y >= 100 && mousePos.y <= 500 && event.mouseButton.button == Mouse::Left)
			{
				int x = mousePos.x;
				int y = mousePos.y;
				int m = (y - 100) / 50 * 8 + (x - 100) / 50;
				if (squares[m].isTaken == true)
				{
					//cout << "isTaken" << endl;
					isDragging = true;
					field = &squares[m];
				}
			}
		}
		else if (event.type == sf::Event::MouseButtonReleased)
		{
			//cout << "nie klikam juz" << endl;
			isDragging = false;
		}
		if (isDragging)
		{
			//cout << "przeciagam" << endl;
			Vector2i mousePos = Mouse::getPosition(window);
			int x = mousePos.x;
			int y = mousePos.y;
			int m = (y - 100) / 50 * 8 + (x - 100) / 50;
			Started = false;
			float xx = float(mousePos.x);
			float yy = float(mousePos.y);
			field->figure->setPos({ xx,yy });
		}
	
}

void Game::update(RenderWindow& window)
{
	for (int i = 0; i < 16; i++)
	{
		window.draw(bPieces[i]);
		window.draw(wPieces[i]);

	}
}

void Game::movePiece()
{

}

void Game::prepareGame(RenderWindow& window)
{


	for (int i = 0; i < 16; i++)
	{
		wPieces[i].setPos(squares[wPieces[i].place].getPosition());
		bPieces[i].setPos(squares[bPieces[i].place].getPosition());
		takePlace(wPieces[i].place, wPieces[i]);
		takePlace(bPieces[i].place, bPieces[i]);
		squares[wPieces[i].place].figure=&wPieces[i];
		squares[bPieces[i].place].figure=&bPieces[i];
		window.draw(wPieces[i]);
		window.draw(bPieces[i]);
	}

	
}
