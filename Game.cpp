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


	for (float i = 0.f; i < 8.f; i++)                                      //sets the board
		for (float j = 0.f; j < 8.f; j++)
		{
			square temp((125.f + j * 50.f), (125.f + i * 50.f));
			if (int(i + j) % 2 == 0)
				temp.changeColor();
			squares.emplace_back(temp);
		}

}

void Game::prepareGame(RenderWindow& window)
{


	for (int i = 0; i < 16; i++)
	{
		wPieces[i].setPos(squares[wPieces[i].place].getPosition());
		bPieces[i].setPos(squares[bPieces[i].place].getPosition());
		takePlace(wPieces[i].place, wPieces[i]);
		takePlace(bPieces[i].place, bPieces[i]);
		squares[wPieces[i].place].figure = &wPieces[i];
		squares[bPieces[i].place].figure = &bPieces[i];
		window.draw(wPieces[i]);
		window.draw(bPieces[i]);
	}
	if(Mouse::isButtonPressed(Mouse::Left))
		Started=false;


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

int Game::whichField(RenderWindow& window, Event& event)
{	
	Vector2i mousePos = Mouse::getPosition(window);
	if ((Mouse::isButtonPressed(Mouse::Left)|| event.type==Event::MouseButtonReleased) && mousePos.x >= 100 && mousePos.x <= 500 && mousePos.y >= 100 && mousePos.y <= 500)
	{
		int m = (mousePos.x - 100) / 50 + (mousePos.y - 100) / 50 * 8;
		return m;
	}


	return 63;
}

void Game::possibleMoves(RenderWindow& window, Event& event)
{
	if (event.type == Event::MouseButtonPressed)
	{
		if (event.mouseButton.button == Mouse::Left)
		{
			int m = whichField(window,event); //which field mouse 
			if (squares[m].isTaken && squares[m].figure->player == blackMove && !isDragging)
			{
				cout << "d";
				
				char piece = squares[m].figure->piece;
				int player = squares[m].figure->player;
				int column = m % 8;                          // from 0 to 7
				int row = m / 8;                             // from 0 to 7

				if (piece == 'p')
				{
					if (squares[m].figure->player == 0)
					{
						if (squares[m - 8].isTaken == false)
						{
							moves.emplace_back(m - 8);
							if (row == 6 && squares[m - 2 * 8].isTaken == false)
								moves.emplace_back(m - 2 * 8);
						}
					}
					if (squares[m].figure->player == 1)
					{
						if (squares[m + 8].isTaken == false)
						{
							moves.emplace_back(m + 8);
							if (row == 1 && squares[m + 2 * 8].isTaken == false)
								moves.emplace_back(m + 2 * 8);
						}
					}
				}
				else if (piece == 'k')
				{
					if (column >= 2)
					{
						if (row >= 1)
							if (squares[m - 2 - 8].isTaken == false)
								moves.emplace_back(m - 2 - 8);
						if (7 - row >= 1)
							if (squares[m - 2 + 8].isTaken == false)
								moves.emplace_back(m - 2 + 8);
					}
					if (7 - column >= 2)
					{
						if (row >= 1)
							if (squares[m + 2 - 8].isTaken == false)
								moves.emplace_back(m + 2 - 8);
						if (7 - row >= 1)
							if (squares[m + 2 + 8].isTaken == false)
								moves.emplace_back(m + 2 + 8);
					}
					if (row >= 2)
					{
						if (column >= 1)
							if (squares[m - 2 * 8 - 1].isTaken == false)
								moves.emplace_back(m - 2 * 8 - 1);
						if (7 - column >= 1)
							if (squares[m - 2 * 8 + 1].isTaken == false)
								moves.emplace_back(m - 2 * 8 + 1);
					}
					if (7 - row >= 2)
					{
						if (column >= 1)
							if (squares[m + 2 * 8 - 1].isTaken == false)
								moves.emplace_back(m + 2 * 8 - 1);
						if (7 - column >= 1)
							if (squares[m + 2 * 8 + 1].isTaken == false)
								moves.emplace_back(m + 2 * 8 + 1);
					}


				}
				else if (piece == 'b')
				{
					int min;

					if (row < column)
						min = row;
					else
						min = column;
					for (int i = 1; i <= min; i++)
					{
						if (squares[m - 9 * i].isTaken == false)
							moves.emplace_back(m - 9 * i);
						else break;
					}
					if (row < 7 - column)
						min = row;
					else min = 7 - column;
					for (int i = 1; i <= min; i++)
					{
						if (squares[m - 7 * i].isTaken == false)
							moves.emplace_back(m - 7 * i);
						else break;
					}
					if (7 - row < column)
						min = 7 - row;
					else min = column;
					for (int i = 1; i <= min; i++)
					{
						if (squares[m + 7 * i].isTaken == false)
							moves.emplace_back(m + 7 * i);
						else break;
					}
					if (7 - row < 7 - column)
						min = 7 - row;
					else min = 7 - column;
					for (int i = 1; i <= min; i++)
					{
						if (squares[m + 9 * i].isTaken == false)
							moves.emplace_back(m + 9 * i);
						else break;
					}

				}
				else if (piece == 'q')
				{
					int min;

					if (row < column)
						min = row;
					else
						min = column;
					for (int i = 1; i <= min; i++)
					{
						if (squares[m - 9 * i].isTaken == false)
							moves.emplace_back(m - 9 * i);
						else break;
					}
					if (row < 7 - column)
						min = row;
					else min = 7 - column;
					for (int i = 1; i <= min; i++)
					{
						if (squares[m - 7 * i].isTaken == false)
							moves.emplace_back(m - 7 * i);
						else break;
					}
					if (7 - row < column)
						min = 7 - row;
					else min = column;
					for (int i = 1; i <= min; i++)
					{
						if (squares[m + 7 * i].isTaken == false)
							moves.emplace_back(m + 7 * i);
						else break;
					}
					if (7 - row < 7 - column)
						min = 7 - row;
					else min = 7 - column;
					for (int i = 1; i <= min; i++)
					{
						if (squares[m + 9 * i].isTaken == false)
							moves.emplace_back(m + 9 * i);
						else break;
					}
					for (int i = m - 1; i >= m - column; i--)
					{
						if (squares[i].isTaken == false)
							moves.emplace_back(i);
						else break;
					}
					for (int i = m + 1; i <= m + (7 - column); i++)
					{
						if (squares[i].isTaken == false)
							moves.emplace_back(i);
						else break;
					}
					for (int i = 1; i <= row; i++)
					{
						if (squares[m - 8 * i].isTaken == false)
							moves.emplace_back(m - 8 * i);
						else break;
					}
					for (int i = 1; i <= 7 - row; i++)
					{
						if (squares[m + 8 * i].isTaken == false)
							moves.emplace_back(m + 8 * i);
						else break;
					}
				}
				else if (piece == 'r')
				{
					for (int i = m - 1; i >= m - column; i--)
					{
						if (squares[i].isTaken == false)
							moves.emplace_back(i);
						else break;
					}
					for (int i = m + 1; i <= m + (7 - column); i++)
					{
						if (squares[i].isTaken == false)
							moves.emplace_back(i);
						else break;
					}
					for (int i = 1; i <= row; i++)
					{
						if (squares[m - 8 * i].isTaken == false)
							moves.emplace_back(m - 8 * i);
						else break;
					}
					for (int i = 1; i <= 7 - row; i++)
					{
						if (squares[m + 8 * i].isTaken == false)
							moves.emplace_back(m + 8 * i);
						else break;
					}

				}
				else //King 'K'
				{
					if (row >= 1)
					{
						if (column >= 1)
							if (squares[m - 8 - 1].isTaken == false)
								moves.emplace_back(m - 8 - 1);
						if (7 - column >= 1)
							if (squares[m - 8 + 1].isTaken == false)
								moves.emplace_back(m - 8 + 1);
						if (squares[m - 8].isTaken == false)
							moves.emplace_back(m - 8);
					}
					if (7 - row >= 1)
					{
						if (column >= 1)
							if (squares[m + 8 - 1].isTaken == false)
								moves.emplace_back(m + 8 - 1);
						if (7 - column >= 1)
							if (squares[m + 8 + 1].isTaken == false)
								moves.emplace_back(m + 8 + 1);
						if (squares[m + 8].isTaken == false)
							moves.emplace_back(m + 8);
					}
					if (column >= 1 && squares[m - 1].isTaken == false)
						moves.emplace_back(m - 1);
					if (7 - column >= 1 && squares[m + 1].isTaken == false)
						moves.emplace_back(m + 1);


				}

				for (unsigned& move : moves)
				{
					squares[move].permission = true;
				}
				if(!moves.empty())
					field = &squares[m];
			}

		}
	}

	if (field != nullptr)
	{
		if (event.type == Event::MouseButtonPressed)
		{
			if (event.mouseButton.button == Mouse::Left)
				isDragging = true;
		}

		else if (event.type == sf::Event::MouseButtonReleased)
		{
			//cout << "cos nie tak";
			isDragging = false;
			int m = whichField(window,event);
			cout << "m wynosi: " << m << endl;
			if (squares[m].permission)
			{
				field->figure->setPos(squares[m].getPosition());        //set the piece in correct field
				squares[m].figure = field->figure;
				squares[m].isTaken = true;
				field->figure = nullptr;
				field->isTaken = false;
				for (unsigned& move : moves)
				{
					squares[move].permission = false;
				}
				moves.clear();
				field = nullptr;
				if (!blackMove)
					blackMove = 1;
				else
					blackMove = 0;
			}
			else
				field->figure->setPos(field->getPosition());
		}
		if (isDragging)
		{
			Vector2i mousePos = Mouse::getPosition(window);
			int x = mousePos.x;
			int y = mousePos.y;
			int m = (y - 100) / 50 * 8 + (x - 100) / 50;
			float xx = float(mousePos.x);
			float yy = float(mousePos.y);
			field->figure->setPos({ xx,yy });
		}
	}

	

}


void Game::move(RenderWindow &window, Event &event)
{

		//if (event.type == Event::MouseButtonPressed)
		//{

		//	Vector2i mousePos = Mouse::getPosition(window);
		//	cout << mousePos.x<<" "<<mousePos.y<<endl;
		//	if (mousePos.x >= 100 && mousePos.x <= 500 && mousePos.y >= 100 && mousePos.y <= 500 && event.mouseButton.button == Mouse::Left)
		//	{
		//		int x = mousePos.x;
		//		int y = mousePos.y;
		//		int m = (y - 100) / 50 * 8 + (x - 100) / 50;
		//		if (squares[m].isTaken == true)
		//		{
		//			isDragging = true;
		//			//field = &squares[m];
		//		}
		//	}
		//}
		if (event.type == sf::Event::MouseButtonReleased)
		{
			cout << "cos nie tak";
			isDragging = false;
		}
		if (isDragging)
		{
			Vector2i mousePos = Mouse::getPosition(window);
			int x = mousePos.x;
			int y = mousePos.y;
			int m = (y - 100) / 50 * 8 + (x - 100) / 50;
			float xx = float(mousePos.x);
			float yy = float(mousePos.y);
			field->figure->setPos({ xx,yy });
		}
	
}

void Game::update(RenderWindow& window)
{
	
	if (!moves.empty())
	{
		for (unsigned& move : moves)
		{
			window.draw(squares[move].circle);
		}
	}
	for (int i = 0; i < 16; i++)
	{
		window.draw(bPieces[i]);
		window.draw(wPieces[i]);

	}
}




