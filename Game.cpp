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


	if (Mouse::isButtonPressed(Mouse::Left))
		Started = false;


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
	if (mousePos.x >= 100 && mousePos.x <= 500 && mousePos.y >= 100 && mousePos.y <= 500)
	{
		int m = (mousePos.x - 100) / 50 + (mousePos.y - 100) / 50 * 8;
		return m;
	}
	return 63;
}

void Game::possibleMoves(RenderWindow& window, Event& event)
{

if (event.mouseButton.button == Mouse::Left && !isDragging)
{
	int m = whichField(window, event); //which field mouse 
	cout << "moje pole wynosi" << m << endl;
	if (field != nullptr && squares[m].permission == false )      //clears the dots (possible moves) if player clicks empty square or enemy's piece
	{
		for (unsigned& move : moves)
		{
			squares[move].permission = false;
		}
		moves.clear();
		enemies.clear();
		if (squares[m].isTaken == false || squares[m].figure->player != blackMove)
			field = nullptr;
	}

	
	if (!isDragging && squares[m].isTaken && squares[m].figure->player == blackMove)
	{

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
						if (column > 0 && column < 7)
						{
							if (squares[m - 8 - 1].figure!=nullptr && squares[m - 8 - 1].figure->player == 1)
								enemies.emplace_back(m - 8 - 1);
							if (squares[m - 8 + 1].figure!=nullptr && squares[m - 8 + 1].figure->player == 1)
								enemies.emplace_back(m - 8 + 1);
						}
						else if(column==0)
							if (squares[m - 8 + 1].figure != nullptr && squares[m - 8 + 1].figure->player == 1)
								enemies.emplace_back(m - 8 + 1);
						else if(column==7)
							if (squares[m - 8 - 1].figure != nullptr && squares[m - 8 - 1].figure->player == 1)
								enemies.emplace_back(m - 8 - 1);
					}


					if (squares[m].figure->player == 1)
					{
						if (squares[m + 8].isTaken == false)
						{
							moves.emplace_back(m + 8);
							if (row == 1 && squares[m + 2 * 8].isTaken == false)
								moves.emplace_back(m + 2 * 8);
						}
						if (column > 0 && column < 7)
						{
							if (squares[m + 8 - 1].figure!=nullptr && squares[m + 8 - 1].figure->player == 0)
								enemies.emplace_back(m + 8 - 1);
							if (squares[m + 8 + 1].figure!=nullptr && squares[m + 8 + 1].figure->player == 0)
								enemies.emplace_back(m + 8 + 1);
						}
						else if (column == 0)
							if (squares[m + 8 + 1].figure!=nullptr && squares[m + 8 + 1].figure->player == 0)
								enemies.emplace_back(m + 8 + 1);
						else if (column == 7)
							if (squares[m + 8 - 1].figure!=nullptr && squares[m + 8 - 1].figure->player == 0)
								enemies.emplace_back(m + 8 - 1);
					}
				}
				else if (piece == 'k')
				{
					if (column >= 2)
					{
						if (row >= 1)
							if (squares[m - 2 - 8].isTaken == false)
								moves.emplace_back(m - 2 - 8);
							else if (squares[m - 2 - 8].figure->player != blackMove)
								enemies.emplace_back(m - 2 - 8);
						if (7 - row >= 1)
							if (squares[m - 2 + 8].isTaken == false)
								moves.emplace_back(m - 2 + 8);
							else if(squares[m - 2 + 8].figure->player != blackMove)
								enemies.emplace_back(m - 2 + 8);
					}			
					if (7 - column >= 2)
					{
						if (row >= 1)
							if (squares[m + 2 - 8].isTaken == false)
								moves.emplace_back(m + 2 - 8);
							else if (squares[m + 2 - 8].figure->player != blackMove)
								enemies.emplace_back(m + 2 - 8);
						if (7 - row >= 1)
							if (squares[m + 2 + 8].isTaken == false)
								moves.emplace_back(m + 2 + 8);
							else if (squares[m + 2 + 8].figure->player != blackMove)
								enemies.emplace_back(m + 2 + 8);
					}
					if (row >= 2)
					{
						if (column >= 1)
							if (squares[m - 2 * 8 - 1].isTaken == false)
								moves.emplace_back(m - 2 * 8 - 1);
							else if (squares[m - 2 * 8 - 1].figure->player != blackMove)
								enemies.emplace_back(m - 2 * 8 - 1);
						if (7 - column >= 1)
							if (squares[m - 2 * 8 + 1].isTaken == false)
								moves.emplace_back(m - 2 * 8 + 1);
							else if (squares[m - 2 * 8 + 1].figure->player != blackMove)
								enemies.emplace_back(m - 2 * 8 + 1);
					}
					if (7 - row >= 2)
					{
						if (column >= 1)
							if (squares[m + 2 * 8 - 1].isTaken == false)
								moves.emplace_back(m + 2 * 8 - 1);
							else if (squares[m + 2 * 8 - 1].figure->player != blackMove)
								enemies.emplace_back(m + 2 * 8 - 1);
						if (7 - column >= 1)
							if (squares[m + 2 * 8 + 1].isTaken == false)
								moves.emplace_back(m + 2 * 8 + 1);
							else if (squares[m + 2 * 8 + 1].figure->player != blackMove)
								enemies.emplace_back(m + 2 * 8 + 1);
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
						else if (squares[m - 9 * i].figure->player != blackMove)
						{
							enemies.emplace_back(m - 9 * i);
							break;
						}
						else break;
					}
					if (row < 7 - column)
						min = row;
					else min = 7 - column;
					for (int i = 1; i <= min; i++)
					{
						if (squares[m - 7 * i].isTaken == false)
							moves.emplace_back(m - 7 * i);
						else if (squares[m - 7 * i].figure->player != blackMove)
						{
							enemies.emplace_back(m - 7 * i);
							break;
						}
						else break;
					}
					if (7 - row < column)
						min = 7 - row;
					else min = column;
					for (int i = 1; i <= min; i++)
					{
						if (squares[m + 7 * i].isTaken == false)
							moves.emplace_back(m + 7 * i);
						else if (squares[m + 7 * i].figure->player != blackMove)
						{
							enemies.emplace_back(m + 7 * i);
							break;
						}
						else break;
					}
					if (7 - row < 7 - column)
						min = 7 - row;
					else min = 7 - column;
					for (int i = 1; i <= min; i++)
					{
						if (squares[m + 9 * i].isTaken == false)
							moves.emplace_back(m + 9 * i);
						else if (squares[m + 9 * i].figure->player != blackMove)
						{
							enemies.emplace_back(m + 9 * i);
							break;
						}
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
						else if (squares[m - 9 * i].figure->player != blackMove)
						{
							enemies.emplace_back(m - 9 * i);
							break;
						}
						else break;
					}
					if (row < 7 - column)
						min = row;
					else min = 7 - column;
					for (int i = 1; i <= min; i++)
					{
						if (squares[m - 7 * i].isTaken == false)
							moves.emplace_back(m - 7 * i);
						else if (squares[m - 7 * i].figure->player != blackMove)
						{
							enemies.emplace_back(m - 7 * i);
							break;
						}
						else break;
					}
					if (7 - row < column)
						min = 7 - row;
					else min = column;
					for (int i = 1; i <= min; i++)
					{
						if (squares[m + 7 * i].isTaken == false)
							moves.emplace_back(m + 7 * i);
						else if (squares[m + 7 * i].figure->player != blackMove)
						{
							enemies.emplace_back(m + 7 * i);
							break;
						}
						else break;
					}
					if (7 - row < 7 - column)
						min = 7 - row;
					else min = 7 - column;
					for (int i = 1; i <= min; i++)
					{
						if (squares[m + 9 * i].isTaken == false)
							moves.emplace_back(m + 9 * i);
						else if (squares[m + 9 * i].figure->player != blackMove)
						{
							enemies.emplace_back(m + 9 * i);
							break;
						}
						else break;
					}
					for (int i = m - 1; i >= m - column; i--)
					{
						if (squares[i].isTaken == false)
							moves.emplace_back(i);
						else if (squares[i].figure->player != blackMove)
						{
							enemies.emplace_back(i);
							break;
						}
						else break;
					}
					for (int i = m + 1; i <= m + (7 - column); i++)
					{
						if (squares[i].isTaken == false)
							moves.emplace_back(i);
						else if (squares[i].figure->player != blackMove)
						{
							enemies.emplace_back(i);
							break;
						}
						else break;
					}
					for (int i = 1; i <= row; i++)
					{
						if (squares[m - 8 * i].isTaken == false)
							moves.emplace_back(m - 8 * i);
						else if (squares[m - 8 * i].figure->player != blackMove)
						{
							enemies.emplace_back(m - 8 * i);
							break;
						}
						else break;
					}
					for (int i = 1; i <= 7 - row; i++)
					{
						if (squares[m + 8 * i].isTaken == false)
							moves.emplace_back(m + 8 * i);
						else if (squares[m + 8 * i].figure->player != blackMove)
						{
							enemies.emplace_back(m + 8 * i);
							break;
						}
						else break;
					}
				}
				else if (piece == 'r')
				{
					for (int i = m - 1; i >= m - column; i--)
					{
						if (squares[i].isTaken == false)
							moves.emplace_back(i);
						else if (squares[i].figure->player != blackMove)
						{
							enemies.emplace_back(i);
							break;
						}
						else break;
					}
					for (int i = m + 1; i <= m + (7 - column); i++)
					{
						if (squares[i].isTaken == false)
							moves.emplace_back(i);
						else if (squares[i].figure->player != blackMove)
						{
							enemies.emplace_back(i);
							break;
						}
						else break;
					}
					for (int i = 1; i <= row; i++)
					{
						if (squares[m - 8 * i].isTaken == false)
							moves.emplace_back(m - 8 * i);
						else if (squares[m - 8 * i].figure->player != blackMove)
						{
							enemies.emplace_back(m - 8 * i);
							break;
						}
						else break;
					}
					for (int i = 1; i <= 7 - row; i++)
					{
						if (squares[m + 8 * i].isTaken == false)
							moves.emplace_back(m + 8 * i);
						else if (squares[m + 8 * i].figure->player != blackMove)
						{
							enemies.emplace_back(m + 8 * i);
							break;
						}
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
							else if (squares[m - 8 - 1].figure->player != blackMove)
								enemies.emplace_back(m - 8 - 1);
						if (7 - column >= 1)
							if (squares[m - 8 + 1].isTaken == false)
								moves.emplace_back(m - 8 + 1);
							else if (squares[m - 8 + 1].figure->player != blackMove)
								enemies.emplace_back(m - 8 + 1);
						if (squares[m - 8].isTaken == false)
							moves.emplace_back(m - 8);
						else if (squares[m - 8].figure->player != blackMove)
							enemies.emplace_back(m - 8);
					}
					if (7 - row >= 1)
					{
						if (column >= 1)
							if (squares[m + 8 - 1].isTaken == false)
								moves.emplace_back(m + 8 - 1);
							else if (squares[m + 8 - 1].figure->player != blackMove)
								enemies.emplace_back(m + 8 - 1);
						if (7 - column >= 1)
							if (squares[m + 8 + 1].isTaken == false)
								moves.emplace_back(m + 8 + 1);
							else if (squares[m + 8 + 1].figure->player != blackMove)
								enemies.emplace_back(m + 8 + 1);
						if (squares[m + 8].isTaken == false)
							moves.emplace_back(m + 8);
						else if (squares[m + 8].figure->player != blackMove)
							enemies.emplace_back(m + 8);
					}
					if (m-1 >= 0 && column >= 1 && squares[m - 1].isTaken == false)
						moves.emplace_back(m - 1);
					else if (column>=1 && squares[m - 1].figure->player != blackMove)
						enemies.emplace_back(m - 1);
					if (7 - column >= 1 && squares[m + 1].isTaken == false)
						moves.emplace_back(m + 1);
					else if (column <= 6 && squares[m + 1].figure->player != blackMove)
						enemies.emplace_back(m + 1);
					if(noPerm.empty())
						block(m);
					//castling();
				}

				for (unsigned& move : moves)
				{
					squares[move].permission = true;
				}
				if(!enemies.empty())
					for (unsigned& e : enemies)
					{
						squares[e].permission = true;
					}
				if (squares[m].figure->piece == 'K')
					for (int& p : noPerm)
					{
						squares[p].permission = false;
					}
				//if (!moves.empty()||!enemies.empty())
				if(squares[m].isTaken)
					field = &squares[m];
	}

}
}

void Game::grabPiece(RenderWindow& window)
{
	if(field!=nullptr)
	if (isDragging)
	{
		Vector2i mousePos = Mouse::getPosition(window);
		int x = mousePos.x;
		int y = mousePos.y;
		float xx = float(mousePos.x);
		float yy = float(mousePos.y);
		field->figure->setPos({ xx,yy });
	}
}

void Game::drag(Event& event)
{
		if(field!=nullptr && !isDragging)
		if (event.mouseButton.button == Mouse::Left)
			isDragging = true;
}

void Game::takeDown(int m)
{
	if (squares[m].figure != nullptr && squares[m].figure->player != blackMove)              //takes a piece off the board
	{	
		squares[m].figure->scale({ 0.5f, 0.5f });
		int i = 0;
		if (blackMove)
		{	
			switch (squares[m].figure->piece)
			{
				case 'p':
					wDeaths.insert(wDeaths.begin(), squares[m].figure);
					break;
				case 'b':
					for (pieces* p : wDeaths)
					{
						if (p->piece != 'p')
							break;
						i += 1;
					}
					wDeaths.insert(wDeaths.begin() + i, squares[m].figure);
					break;
					
				case 'k':
					for (pieces* p : wDeaths)
					{
						if (p->piece != 'p' && p->piece != 'b')
							break;
						i += 1;
					}
					cout << i;
					wDeaths.insert(wDeaths.begin() + i, squares[m].figure);
					break;
				case 'r':
					for (pieces* p : wDeaths)
					{	
						
						if (p->piece != 'p' && p->piece != 'b' && p->piece != 'k')
							break;
						i += 1;
					}
					wDeaths.insert(wDeaths.begin() + i, squares[m].figure);
					break;
				case 'q':
					wDeaths.emplace_back(squares[m].figure);
					break;


			}
		}
		else
		{
			switch (squares[m].figure->piece)
			{
			case 'p':
				bDeaths.insert(bDeaths.begin(), squares[m].figure);
				break;
			case 'b':
				for (pieces* p : bDeaths)
				{
					if (p->piece != 'p')
						break;
					i += 1;
				}
				bDeaths.insert(bDeaths.begin() + i, squares[m].figure);
				break;

			case 'k':
				for (pieces* p : bDeaths)
				{
					if (p->piece != 'p' && p->piece != 'b')
						break;
					i += 1;
				}
				bDeaths.insert(bDeaths.begin() + i, squares[m].figure);
				break;

			case 'r':
				for (pieces* p : bDeaths)
				{
					if (p->piece != 'p' && p->piece != 'b' && p->piece != 'k')
						break;
					i += 1;
				}
				bDeaths.insert(bDeaths.begin() + i, squares[m].figure);
				break;
			case 'q':
				bDeaths.emplace_back(squares[m].figure);


			}
		}
		squares[m].figure->place = -1;
	}
}

void Game::castling() // consider
{
	if (blackMove && (LCB || RCB))
	{
		if (squares[4].figure->piece == 'K' && squares[4].figure->player == blackMove)
		{
			if (squares[0].figure->piece == 'r' && squares[0].figure->player == blackMove && LCB)
			{
				if(!squares[1].isTaken && !squares[2].isTaken && !squares[3].isTaken)
					moves.emplace_back(2);
			}
			if (squares[7].figure->piece == 'r' && squares[0].figure->player == blackMove && RCB)
				if (!squares[5].isTaken && !squares[6].isTaken)
					moves.emplace_back(6);
		}
	}
	else if (blackMove == 0 && RCW || LCW)
	{
		if (squares[60].figure->piece == 'K' && squares[60].figure->player == blackMove)
		{
			if (squares[56].figure->piece == 'r' && squares[56].figure->player == blackMove && LCW)
			{
				if (!squares[57].isTaken && !squares[58].isTaken && !squares[59].isTaken)
					moves.emplace_back(58);
			}
			if (squares[63].figure->piece == 'r' && squares[63].figure->player == blackMove && RCW)
				if(!squares[61].isTaken && !squares[62].isTaken)
					moves.emplace_back(62);
		}
	}
}

void Game::isCheck(int p)              //changes only variable "check" to true
{
	int column = p % 8;                          
	int row = p / 8;
	if(blackMove)
	{ 
		int columnK = wPieces[4].place % 8;
		int rowK = wPieces[4].place / 8;
		int q = wPieces[4].place;
		switch (field->figure->piece)
		{
		case 'b':
			if (abs(column - columnK) == abs(row - rowK))
			{
				if (abs(p - q) % 7 == 0)
				{
					if (q > p)
					{
						for (int i = 1; p + 7 * i <= 63; i++)
						{
							if (squares[p + 7 * i].isTaken)
								if (p + 7 * i == q)
								{
									check = true;
									break;
								}
								else
									break;
						}
					}
					else
					{
						for (int i = 1; p - 7 * i >= 0; i++)
						{
							if (squares[p - 7 * i].isTaken)
								if (p - 7 * i == q)
								{
									check = true;
									break;
								}
								else
									break;

						}
					}
				}
				else if (abs(p - q) % 9 == 0)
				{
					if (q > p)
					{
						for (int i = 1; p + 9 * i <= 63; i++)
						{
							if (squares[p + 9 * i].isTaken)
								if (p + 9 * i == q)
								{
									check = true;
									break;
								}
								else
									break;
						}
					}
					else
					{
						for (int i = 1; p - 9 * i >= 0; i++)
						{
							if (squares[p - 9 * i].isTaken)
								if (p - 9 * i == q)
								{
									check = true;
									break;
								}
								else
									break;

						}
					}

					
				}
			}
			break;
		case 'q':
			if (abs(column - columnK) == abs(row - rowK))
			{
				if (abs(p - q) % 7 == 0)
				{
					if (q > p)
					{
						for (int i = 1; p + 7 * i <= 63; i++)
						{
							if (squares[p + 7 * i].isTaken)
								if (p + 7 * i == q)
								{
									check = true;
									break;
								}
								else
									break;
						}
					}
					else
					{
						for (int i = 1; p - 7 * i >= 0; i++)
						{
							if (squares[p - 7 * i].isTaken)
								if (p - 7 * i == q)
								{
									check = true;
									break;
								}
								else
									break;

						}
					}
				}
				else if (abs(p - q) % 9 == 0)
				{
					if (q > p)
					{
						for (int i = 1; p + 9 * i <= 63; i++)
						{
							if (squares[p + 9 * i].isTaken)
								if (p + 9 * i == q)
								{
									check = true;
									break;
								}
								else
									break;
						}
					}
					else
					{
						for (int i = 1; p - 9 * i >= 0; i++)
						{
							if (squares[p - 9 * i].isTaken)
								if (p - 9 * i == q)
								{
									check = true;
									break;
								}
								else
									break;

						}
					}


				}
			}
			else if (row == rowK)
			{
				if (q > p)
				{
					for (int i = p; i <= q; i++)
					{
						if (squares[i].isTaken && i != q)
							break;
					}
					if (p == q)
						check = true;
				}
				else
				{
					for (int i = p; i >= q; i--)
					{
						if (squares[i].isTaken && i != q)
							break;
					}
					if (p == q)
						check = true;
				}
			}
			else if (column == columnK)
			{
				if (q > p)
				{
					for (int i = 1; p + 8 * i <= 63; i++)
					{
						if (squares[p + 8 * i].isTaken)
							if (p + 8 * i == q)
							{
								check = true;
								break;
							}
							else
								break;
					}
				}
				else
				{
					for (int i = 1; p - 8 * i >= 0; i++)
					{
						if (squares[p - 8 * i].isTaken)
							if (p - 8 * i == q)
							{
								check = true;
								break;
							}
							else
								break;
					}
				}
			}
			break;
		case 'k':
			if (rowK > row)
			{
				if (columnK > column)
				{
					if (p + 10 == q)
						check = true;
					else if (p + 17 == q)
						check = true;
				}
				else if (columnK < column)
				{
					if (p + 6 == q)
						check = true;
					else if (p + 15 == q)
						check = true;
				}
			}
			else if (rowK < row)
			{
				if (columnK > column)
				{
					if (p - 6 == q)
						check = true;
					else if (p - 15 == q)
						check = true;
				}
				else if (columnK < column)
				{
					if (p - 10 == q)
						check = true;
					else if (p - 17 == q)
						check = true;
				}
			}
			break;
		case 'r':
			if (row == rowK)
			{
				if (q > p)
				{
					for (int i = p; i <= q; i++)
					{
						if (squares[i].isTaken && i != q)
							break;
					}
					if (p == q)
						check = true;
				}
				else
				{
					for (int i = p; i >= q; i--)
					{
						if (squares[i].isTaken && i != q)
							break;
					}
					if (p == q)
						check = true;
				}
			}
			else if (column == columnK)
			{
				if (q > p)
				{
					for (int i = 1; p + 8 * i <= 63 ; i++)
					{
						if (squares[p + 8 * i].isTaken)
							if (p + 8 * i == q)
							{
								check = true;
								break;
							}
							else
								break;
					}
				}
				else
				{
					for (int i = 1; p - 8 * i >= 0; i++)
					{
						if (squares[p - 8 * i].isTaken)
							if (p - 8 * i == q)
							{
								check = true;
								break;
							}
							else
								break;
					}
				}
			}
			break;
		case 'p':
			if (rowK == row + 1)
			{

				if (p + 7 == q || p + 9 == q)
					check = true;
			}
			break;
		}
	}
	else
	{
		int columnK = bPieces[4].place % 8;
		int rowK = bPieces[4].place / 8;
		int q = bPieces[4].place;
		switch (field->figure->piece)
		{
		case 'b':
			if (abs(column - columnK) == abs(row - rowK))
			{
				if (abs(p - q) % 7 == 0)
				{
					if (q < p)
					{
						for (int i = 1; p - 7 * i >= 0; i++)
						{
							if (squares[p - 7 * i].isTaken)
								if (p - 7 * i == q)
								{
									check = true;
									break;
								}
								else
									break;
						}
					}
					else
					{
						for (int i = 1; p + 7 * i <= 63; i++)
						{
							if (squares[p + 7 * i].isTaken)
								if (p + 7 * i == q)
								{
									check = true;
									break;
								}
								else
									break;

						}
					}
				}
				else if (abs(p - q) % 9 == 0)
				{
					if (q < p)
					{
						for (int i = 1; p - 9 * i >= 0; i++)
						{
							if (squares[p - 9 * i].isTaken)
								if (p - 9 * i == q)
								{
									check = true;
									break;
								}
								else
									break;
						}
					}
					else
					{
						for (int i = 1; p + 9 * i <= 63; i++)
						{
							if (squares[p + 9 * i].isTaken)
								if (p + 9 * i == q)
								{
									check = true;
									break;
								}
								else
									break;

						}
					}


				}
			}
			break;
		case 'q':
			if (abs(column - columnK) == abs(row - rowK))
			{
				if (abs(p - q) % 7 == 0)
				{
					if (q < p)
					{
						for (int i = 1; p - 7 * i >= 0; i++)
						{
							if (squares[p - 7 * i].isTaken)
								if (p - 7 * i == q)
								{
									check = true;
									break;
								}
								else
									break;
						}
					}
					else
					{
						for (int i = 1; p + 7 * i <= 63; i++)
						{
							if (squares[p + 7 * i].isTaken)
								if (p + 7 * i == q)
								{
									check = true;
									break;
								}
								else
									break;

						}
					}
				}
				else if (abs(p - q) % 9 == 0)
				{
					if (q < p)
					{
						for (int i = 1; p - 9 * i >= 0; i++)
						{
							if (squares[p - 9 * i].isTaken)
								if (p - 9 * i == q)
								{
									check = true;
									break;
								}
								else
									break;
						}
					}
					else
					{
						for (int i = 1; p + 9 * i <= 63; i++)
						{
							if (squares[p + 9 * i].isTaken)
								if (p + 9 * i == q)
								{
									check = true;
									break;
								}
								else
									break;

						}
					}


				}
			}
			else if (row == rowK)
			{
				if (q > p)
				{
					for (int i = p; i <= q; i++)
					{
						if (squares[i].isTaken && i != q)
							break;
					}
					if (p == q)
						check = true;
				}
				else
				{
					for (int i = p; i >= q; i--)
					{
						if (squares[i].isTaken && i != q)
							break;
					}
					if (p == q)
						check = true;
				}
			}
			else if (column == columnK)
			{
				if (q < p)
				{
					for (int i = 1; p - 8 * i >= 0; i++)
					{
						if (squares[p - 8 * i].isTaken)
							if (p - 8 * i == q)
							{
								check = true;
								break;
							}
							else
								break;
					}
				}
				else
				{
					for (int i = 1; p + 8 * i <= 63; i++)
					{
						if (squares[p + 8 * i].isTaken)
							if (p + 8 * i == q)
							{
								check = true;
								break;
							}
							else
								break;
					}
				}
			}
			break;
		case 'k':
			if (rowK < row)
			{
				if (columnK > column)
				{
					if (p - 6 == q)
						check = true;
					else if (p - 15 == q)
						check = true;
				}
				else if (columnK < column)
				{
					if (p - 10 == q)
						check = true;
					else if (p - 17 == q)
						check = true;
				}
			}
			else if (rowK > row)
			{
				if (columnK > column)
				{
					if (p + 10 == q)
						check = true;
					else if (p + 17 == q)
						check = true;
				}
				else if (columnK < column)
				{
					if (p + 6 == q)
						check = true;
					else if (p + 15 == q)
						check = true;
				}
			}
			break;
		case 'r':
			if (row == rowK)
			{
				if (q > p)
				{
					for (int i = p; i <= q; i++)
					{
						if (squares[i].isTaken && i != q)
							break;
					}
					if (p == q)
						check = true;
				}
				else
				{
					for (int i = p; i >= q; i--)
					{
						if (squares[i].isTaken && i != q)
							break;
					}
					if (p == q)
						check = true;
				}
			}
			else if (column == columnK)
			{
				if (q < p)
				{
					for (int i = 1; p - 8 * i >= 0; i++)
					{
						if (squares[p - 8 * i].isTaken)
							if (p - 8 * i == q)
							{
								check = true;
								break;
							}
							else
								break;
					}
				}
				else
				{
					for (int i = 1; p + 8 * i <= 63; i++)
					{
						if (squares[p + 8 * i].isTaken)
							if (p + 8 * i == q)
							{
								check = true;
								break;
							}
							else
								break;
					}
				}
			}
			break;
		case 'p':
			if (rowK == row - 1)
			{

				if (p - 7 == q || p - 9 == q)
					check = true;
			}
			break;
		}
	}
	isDiscoveredCheck(field->figure->place,column,row);
}

void Game::isDiscoveredCheck(int p, int column, int row)
{
	int q,columnK,rowK;
	if (blackMove)
	{
		q = wPieces[4].place;
		columnK = wPieces[4].place % 8;
		rowK = wPieces[4].place / 8;
	}
	else
	{
		q = bPieces[4].place;
		columnK = bPieces[4].place % 8;
		rowK = bPieces[4].place / 8;

	}
	if (column == columnK)
		{
			if (q > p)
			{
				for (int i = q; q - 8 * i >= 0; i++)
				{
					if (squares[q - 8 * i].isTaken)
						if ((squares[q - 8 * i].figure->piece == 'q' || squares[q - 8 * i].figure->piece == 'r') && squares[q - 8 * i].figure->player != blackMove)
							if (check)
								doubleCheck = true;
							else
							{
								check = true;
								break;
							}
						else
							break;
				}
			}
			else
			{
				for (int i = 1; q + 8 * i <= 63; i++)
				{
					if (squares[q + 8 * i].isTaken)
						if ((squares[q + 8 * i].figure->piece == 'q' || squares[q + 8 * i].figure->piece == 'r') && squares[q + 8 * i].figure->player != blackMove)

							if (check)
								doubleCheck = true;
							else
							{
								check = true;
								break;
							}
						else
							break;
				}
			}
		}
	else if (row == rowK)
		{
			if (q > p)
			{
				for (int i = q; i >= 8 * row; i--)
				{
					if (squares[i].isTaken)
					{
						if ((squares[i].figure->piece == 'q' || squares[i].figure->piece == 'r')&& squares[i].figure->player != blackMove)
						{
							if (check)
							{
								doubleCheck = true;

							}
							else
								check = true;
						}
						break;
					}

				}
			}
			else
			{
				for (int i = q; i <= 8 * row + 7; i++)
				{
					if (squares[i].isTaken)
					{
						if ((squares[i].figure->piece == 'r' || squares[i].figure->piece == 'q') && squares[i].figure->player != blackMove)
						{
							if(check)
								doubleCheck=true;
							else
								check=true;
						}
						break;
					}
				}
			}
		}
	else if (abs(column - columnK) == abs(row - rowK))
	{
			
		if (abs(p - q) % 7 == 0)
			{
				

				if (q > p)
				{
					int min;
					if (7 - column < row)
						min = 7 - column;
					else
						min = row;
					for (int i = 1; i<=min; i++)
					{
						if (squares[p - 7 * i].isTaken)
						{
							if ((squares[p - 7 * i].figure->piece == 'b' || squares[p - 7 * i].figure->piece == 'q') && squares[p - 7 * i].figure->player != blackMove)
							{
								if (check)
								{
									doubleCheck = true;
								}
								else
									doubleCheck = true;
							}
							break;
						}

					}
				}
				else
				{
					int min;
					if (7 - row <column)
						min = 7 - row;
					else
						min = column;

					for (int i = p;i<=min; i++)
					{
						if (squares[p + 7 * i].isTaken)
						{
							if ((squares[p + 7 * i].figure->piece == 'b' || squares[p + 7 * i].figure->piece == 'q') && squares[p + 7 * i].figure->player != blackMove)
							{
								if (check)
								{
									doubleCheck = true;
									break;
								}
								else
									check = true;

							}
							break;
						}
					}
				}
			}
		else if (abs(p - q) % 9 == 0)
			{
				int min;
				if (q > p)
				{
					if (column < row)
						min = column;
					else
						min = row;
					for (int i = 1; i<=min; i++)
					{
						if (squares[p - 9 * i].isTaken)
						{
							if ((squares[p - 9 * i].figure->piece == 'b' || squares[p - 9 * i].figure->piece == 'q') && squares[p - 9 * i].figure->player != blackMove)
							{
								if (check)
									doubleCheck;
								else check = true;

							}
							break;
						}
					}
				}
				else
				{
					if (7 - row < 7 - column)
						min = 7 - row;
					else
						min = 7 - column;
					for (int i = p; i <= min; i++)
					{
						if (squares[p + 9 * i].isTaken)
							if ((squares[p - 9 * i].figure->piece == 'q' || squares[p - 9 * i].figure->piece == 'b') && squares[p - 9 * i].figure->player != blackMove)
							{
								if (check)
									doubleCheck = true;
								else
									check = true;

							}
							else break;
					}
				}
			}
	}

}

void Game::block(int m)
{
	int columnK, rowK, column, row,p,max;
	columnK = m % 8;									// m - king position
	rowK = m / 8;
	if (blackMove)										//the difference in only between names (bPieces and wPieces) and Pawns
	{
		//check rocks
	
		for (int i = 0; i < 2; i++)
		{
			if (wPieces[7 * i].place != -1)
			{
				p = wPieces[7 * i].place;						// p - position of piece that perhaps attacks king
				column = wPieces[7 * i].place % 8;
				row = wPieces[7 * i].place / 8;
				int  x;
				if (abs(column - columnK) <= 1)
				{
					
					if (m < wPieces[7 * i].place)
					{
						x = -1;
						if (m == p - 1)
						{
							if (p + 8 < 64)
								noPerm.emplace_back(p + 8);
						}
						else if (m == p - 8)
						{
							if (column >= 1)
								noPerm.emplace_back(p - 1);
						}
					}
					else
					{
						x = 1;
						if (m == p + 1)
						{
							if (p - 8 >= 0)
								noPerm.emplace_back(p - 8);
						}
						else if (m == p + 8)
						{
							if(column>=1)
								noPerm.emplace_back(p-1);
						}
					}
					
					for (int j = 1; j <= abs(row - rowK) + 1; j++)
					{
						if (p + 8 * j * x < 64 && p + 8 * j * x >= 0 && squares[p + 8 * j * x].isTaken)
						{
							noPerm.emplace_back(p + 8 * j * x);
							break;
						}
						if (abs((p + 8 * j * x) / 8 - rowK) <= 1)
						{
							if (p + 8 * j * x < 64 && p + 8 * j * x >= 0)
								noPerm.emplace_back(p + 8 * j * x);
						}
						
					}
				}
				if (abs(row - rowK) <= 1)
				{
					x = 1;
					if (column > columnK)
						x = -1;
					for (int j = 1; j <= abs(column - columnK) + 1; j++)
					{
						if (squares[p + j * x].isTaken)
						{
							noPerm.emplace_back(p + j * x);
							break;
						}
						if (abs((p + j * x) % 8 - columnK) <= 1)
						{
							
							if (p + j * x < 64 && p + j * x >= 0)
								noPerm.emplace_back(p + j * x);
						}
						
					}
				}
			}
		}


		//bishops

		for (int i = 0; i < 2; i++)
		{
			if (wPieces[2 + 3 * i].place != -1)
			{
				p = wPieces[2 + 3 * i].place;						// p - position of piece that perhaps attacks king
				column = wPieces[2 + 3 * i].place % 8;
				row = wPieces[2 + 3 * i].place / 8;
				int max;
				if (abs(column - columnK) > abs(row - rowK))
					max = abs(column - columnK);
				else
					max = abs(row - rowK);
				int x;
				if (abs(column - columnK) == abs(row - rowK + 1))
				{
					if ((m - 8 - p) % 7 == 0)
					{
						if (column >= columnK)
							x = -1;
						else
							x = 1;
						for (int j = 1; j <= max; j++)
						{
							if ((p - 7 * j * x) < 0 || squares[p - 7 * j * x].isTaken)
							{
								noPerm.emplace_back(p - 7 * j * x);
								break;

							}
							if ((p - 7 * j * x) % 8 >= columnK - 1 && (p - 7 * j * x) % 8 <= columnK)
								noPerm.emplace_back(p - 7 * j * x);
		
						}
					}
					if((m-8-p)%9==0)
					{
						if (column <= columnK)
							x = -1;
						else
							x = 1;
						for (int j = 1; j <= max; j++)
						{
							if (p - 9 * j * x < 0 || squares[p - 9 * j * x].isTaken)
							{
								noPerm.emplace_back(p - 9 * j * x);
								break;
							}
							if ((p - 9 * j * x) % 8 >= columnK && (p - 9 * j * x) % 8 <= columnK + 1)
								noPerm.emplace_back(p - 9 * j * x);
		
						}
					}
				}
				if (abs(column - columnK) == abs(row - rowK - 1))
				{
					if ((m + 8 - p) % 7 == 0)
					{
						if (column > columnK)
							x = -1;
						else
							x = 1;
						for (int j = 1; j <= max; j++)
						{
							if (p - 7 * j * x > 63 || squares[p - 7 * j * x].isTaken)
							{
								noPerm.emplace_back(p - 7 * j * x);
								break;
							}
							if ((p - 7 * j * x) % 8 >= columnK && (p - 7 * j * x) % 8 <= columnK + 1)
								noPerm.emplace_back(p - 7 * j * x);
		
						}
					}
					if((m+8-p)%9==0)
					{
						if (column >= columnK)
							x = 1;
						else
							x = -1;
						for (int j = 1; j <= max; j++)
						{
							if (p - 9 * j * x > 63 || squares[p - 9 * j * x].isTaken)
							{
								noPerm.emplace_back(p - 9 * j * x);
								break;
							}
							else if ((p - 9 * j * x) % 8 >= columnK - 1 && (p - 9 * j * x) % 8 <= columnK)
								noPerm.emplace_back(p - 9 * j * x);
		
						}
					}
				}
				if (abs(column - columnK + 1) == abs(row - rowK + 1) || abs(column - columnK - 1) == abs(row - rowK - 1))
				{
					if (abs(m + 9 - p) % 7 == 0 || abs(m - 9 - p) % 7 ==0)
					{
						if ((m + 9 - p) % 7 == 0)
						{
							if (column <= columnK)
								x = 1;
							else
								x = -1;
						}
						else
						{
							if (column >= columnK)
								x = -1;
							else
								x = 1;
		
						}
		
						for (int j = 1; j < max; j++)
						{
							if (squares[p - 7 * j * x].isTaken)
							{
								noPerm.emplace_back(p - 7 * j * x);
								break;
							}
							if ((p - 7 * j * x) % 8 >= columnK - 1 && (p - 7 * j * x) % 8 <= columnK + 1 && (p - 7 * j * x) / 8 >= rowK - 1 && (p - 7 * j * x) / 8 <= rowK + 1)
								noPerm.emplace_back(p - 7 * j * x);
						}
					}
				}
				if (abs(column - columnK - 1) == abs(row - rowK + 1) || abs(column - columnK + 1) == abs(row - rowK - 1))
				{
					if (abs(m - 7 - p) % 9 == 0 || abs(m + 7 - p) % 9 == 0)
					{
						if ((m - 7 - p) % 9 == 0)
						{
							if (column > columnK)
								x = 1;
							else
								x = -1;
							
						}
						else
						{
							if (column < columnK)
							{
								x = -1;
							}
							else
								x = 1;
						}
		
						for (int j = 1; j < max; j++)
						{
		
							if (squares[p - 9 * j * x].isTaken)
							{
								noPerm.emplace_back(p - 9 * j * x);
								break;
							}
							if ((p - 9 * j * x) % 8 >= columnK - 1 && (p - 9 * j * x) % 8 <= columnK + 1 && (p - 9 * j * x) / 8 >= rowK - 1 && (p - 9 * j * x) / 8 <= rowK + 1)
								noPerm.emplace_back(p - 9 * j * x);
						}
					}
				}
			}
		
		}

		//queen


			if (wPieces[3].place != -1)
			{
				p = wPieces[3].place;						// p - position of piece that perhaps attacks king
				column = wPieces[3].place % 8;
				row = wPieces[3].place / 8;
				int  x;
				if (abs(column - columnK) <= 1)
				{

					if (m < wPieces[3].place)
					{
						x = -1;
						if (m == p - 1)
						{
							if (p + 8 < 64 && !squares[p + 8].isTaken)
								noPerm.emplace_back(p + 8);
						}
						else if (m == p - 8)
						{
							if (column >= 1 && !squares[p - 1].isTaken)
								noPerm.emplace_back(p - 1);
						}
					}
					else
					{
						x = 1;
						if (m == p + 1)
						{
							if (p - 8 >= 0 && !squares[p - 8].isTaken)
								noPerm.emplace_back(p - 8);
						}
						else if (m == p + 8)
						{
							if (column >= 1 && !squares[p - 1].isTaken)
								noPerm.emplace_back(p - 1);
						}
					}

					for (int j = 1; j <= abs(row - rowK) + 1; j++)
					{
						if (p + 8 * j * x < 64 && p + 8 * j * x >= 0 && squares[p + 8 * j * x].isTaken)
						{
							noPerm.emplace_back(p + 8 * j * x);
							break;					
						}
						if (abs((p + 8 * j * x) / 8 - rowK) <= 1)
						{
							if (p + 8 * j * x < 64 && p + 8 * j * x >= 0)
								noPerm.emplace_back(p + 8 * j * x);
						}

					}
				}
				if (abs(row - rowK) <= 1)
				{
					x = 1;
					if (column > columnK)
						x = -1;
					for (int j = 1; j <= abs(column - columnK) + 1; j++)
					{
						if (squares[p + j * x].isTaken)
						{
							noPerm.emplace_back(p + j * x);
							break;
						}
						if (abs((p + j * x) % 8 - columnK) <= 1)
						{

							if (p + j * x < 64 && p + j * x >= 0)
								noPerm.emplace_back(p + j * x);
						}

					}
				}
				int max;
				if (abs(column - columnK) > abs(row - rowK))
					max = abs(column - columnK);
				else
					max = abs(row - rowK);
				if (abs(column - columnK) == abs(row - rowK + 1))
				{
					if ((m - 8 - p) % 7 == 0)
					{
						if (column >= columnK)
							x = -1;
						else
							x = 1;
						for (int j = 1; j <= max; j++)
						{
							if ((p - 7 * j * x) < 0 || squares[p - 7 * j * x].isTaken)
							{
								noPerm.emplace_back(p - 7 * j * x);
								break;
							}
							if ((p - 7 * j * x) % 8 >= columnK - 1 && (p - 7 * j * x) % 8 <= columnK)
								noPerm.emplace_back(p - 7 * j * x);

						}
					}
					if ((m - 8 - p) % 9 == 0)
					{
						if (column <= columnK)
							x = -1;
						else
							x = 1;
						for (int j = 1; j <= max; j++)
						{
							if (p - 9 * j * x < 0 || squares[p - 9 * j * x].isTaken)
							{
								noPerm.emplace_back(p - 9 * j * x);
								break;
							}

							if ((p - 9 * j * x) % 8 >= columnK && (p - 9 * j * x) % 8 <= columnK + 1)
								noPerm.emplace_back(p - 9 * j * x);

						}
					}
				}
				if (abs(column - columnK) == abs(row - rowK - 1))
				{
					if ((m + 8 - p) % 7 == 0)
					{
						if (column > columnK)
							x = -1;
						else
							x = 1;
						for (int j = 1; j <= max; j++)
						{
							if (p - 7 * j * x > 63 || squares[p - 7 * j * x].isTaken)
							{
								noPerm.emplace_back(p - 7 * j * x);
								break;
							}
							if ((p - 7 * j * x) % 8 >= columnK && (p - 7 * j * x) % 8 <= columnK + 1)
								noPerm.emplace_back(p - 7 * j * x);

						}
					}
					if ((m + 8 - p) % 9 == 0)
					{
						if (column >= columnK)
							x = 1;
						else
							x = -1;
						for (int j = 1; j <= max; j++)
						{
							if (p - 9 * j * x > 63 || squares[p - 9 * j * x].isTaken)
							{
								noPerm.emplace_back(p - 9 * j * x);
								break;
							}
							else if ((p - 9 * j * x) % 8 >= columnK - 1 && (p - 9 * j * x) % 8 <= columnK)
								noPerm.emplace_back(p - 9 * j * x);

						}
					}
				}
				if (abs(column - columnK + 1) == abs(row - rowK + 1) || abs(column - columnK - 1) == abs(row - rowK - 1))
				{
					if (abs(m + 9 - p) % 7 == 0 || abs(m - 9 - p) % 7 == 0)
					{
						if ((m + 9 - p) % 7 == 0)
						{
							if (column <= columnK)
								x = 1;
							else
								x = -1;
						}
						else
						{
							if (column >= columnK)
								x = -1;
							else
								x = 1;

						}

						for (int j = 1; j < max; j++)
						{
							if (squares[p - 7 * j * x].isTaken)
							{
								noPerm.emplace_back(p - 7 * j * x);
								break;
							}
							if ((p - 7 * j * x) % 8 >= columnK - 1 && (p - 7 * j * x) % 8 <= columnK + 1 && (p - 7 * j * x) / 8 >= rowK - 1 && (p - 7 * j * x) / 8 <= rowK + 1)
								noPerm.emplace_back(p - 7 * j * x);
						}
					}
				}
				if (abs(column - columnK - 1) == abs(row - rowK + 1) || abs(column - columnK + 1) == abs(row - rowK - 1))
				{
					if (abs(m - 7 - p) % 9 == 0 || abs(m + 7 - p) % 9 == 0)
					{
						if ((m - 7 - p) % 9 == 0)
						{
							if (column > columnK)
								x = 1;
							else
								x = -1;

						}
						else
						{
							if (column < columnK)
							{
								x = -1;
							}
							else
								x = 1;
						}

						for (int j = 1; j < max; j++)
						{

							if (squares[p - 9 * j * x].isTaken)
							{
								noPerm.emplace_back(p - 9 * j * x);
								break;
							}
							if ((p - 9 * j * x) % 8 >= columnK - 1 && (p - 9 * j * x) % 8 <= columnK + 1 && (p - 9 * j * x) / 8 >= rowK - 1 && (p - 9 * j * x) / 8 <= rowK + 1)
								noPerm.emplace_back(p - 9 * j * x);
						}
					}
				}
			}
		

		//knights

		for (int i = 0; i < 2; i++)
		{
			if (wPieces[1 + 5 * i].place != -1)
			{
				p = wPieces[1 + 5 * i].place;						// p - position of piece that perhaps attacks king
				column = wPieces[1 + 5 * i].place % 8;
				row = wPieces[1 + 5 * i].place / 8;
				if (row < rowK)
				{
					if (column < columnK)
					{
						if (columnK - column <= 3 && rowK - row <= 2 && column <= 5 && row <= 6)
							noPerm.emplace_back(p + 10);
						if (columnK - column <= 2 && rowK - row <= 3 && column <= 6 && row <= 5)
							noPerm.emplace_back(p + 17);
					}
					else if (columnK == column && rowK - row <= 2 && row <= 5)
					{
						if (column >= 1)
							noPerm.emplace_back(p + 15);
						if (column <= 6)
							noPerm.emplace_back(p + 17);
					}
					else
					{
						if (column - columnK <= 3 && rowK - row <= 2 && row <= 6 && column >= 2)
							noPerm.emplace_back(p + 6);
						if (column - columnK <= 2 && rowK - row <= 3 && row <= 5 && column >= 1)
							noPerm.emplace_back(p + 15);
					}
				}
				else
				{
					if (column < columnK)
					{
						if (row == rowK && columnK - column <= 3)
						{
							if (column <= 5)
							{
								noPerm.emplace_back(p + 10);
								noPerm.emplace_back(p - 6);
							}
						}
						else
						{
							if (columnK - column <= 3 && row - rowK <= 2 && column <= 5 && row >= 1)
								noPerm.emplace_back(p - 6);
							if (columnK - column <= 2 && row - rowK <= 3 && column <= 6 && row >= 2)
								noPerm.emplace_back(p - 15);
						}
					}
					else if (column > columnK)
					{
						if (row == rowK)
						{
							if (column - columnK <= 3 && column >= 2)
							{
								noPerm.emplace_back(p - 2 - 8);
								noPerm.emplace_back(p - 2 + 8);
							}
						}
						else
						{
							if (column - columnK <= 3 && row - rowK <= 2 && column >= 2 && row >= 1)
								noPerm.emplace_back(p - 2 - 8);
							if (column - columnK <= 2 && row - rowK <= 3 && column >= 1 && row >= 2)
								noPerm.emplace_back(p - 1 - 2 * 8);
						}
					}
					else if (column == columnK)
					{
						if (row - rowK <= 3)
						{
							if (row >= 2 && column <= 6)
								noPerm.emplace_back(p - 15);
							if (row >= 2 && column >= 1)
								noPerm.emplace_back(p - 17);
						}
					}
				}
			}
		}

		//pawns

		for (int i = 8; i < 16; i++)
		{
			if (wPieces[i].place != -1)
			{
				p = wPieces[i].place;						// p - position of piece that perhaps attacks king
				row = wPieces[i].place / 8;
				if (row - 2 == rowK || (row==rowK && row - 1>=0) || (row - 1 == rowK))
				{
					column = wPieces[i].place % 8;
					if (column == columnK)
					{
						if (column >= 1)
							noPerm.emplace_back(p - 1 - 8);
						if (column <= 6)
							noPerm.emplace_back(p + 1 - 8);
					}
					else if (column > columnK)
					{
						if (column - columnK <= 2)
							noPerm.emplace_back(p - 1 - 8);

					}
					else
					{
						if (columnK - column <= 2)
							noPerm.emplace_back(p + 1 - 8);
					}

				}
			}
		}

		//king

		p = wPieces[4].place;						// p - position of piece that perhaps attacks king
		row = wPieces[4].place / 8;
		column = wPieces[4].place % 8;
		if (abs(columnK - column) > abs(rowK - row))
			max = abs(columnK - column);
		else
			max = abs(rowK - row);
		if (max == 2)
		{
			if (rowK - row == 2)					// checks if enemy king is 2 rows higer 
			{
				if (column == columnK)
				{
					if (column >= 1)
						noPerm.emplace_back(p - 1 + 8);
					noPerm.emplace_back(p + 8);
					if (column <= 7)
						noPerm.emplace_back(p + 1 + 8);
				}
				else if (abs(columnK - column) == 1)
				{
					noPerm.emplace_back(p - 8);
					noPerm.emplace_back(m + 8);

				}
				else if (column < columnK)
				{
					noPerm.emplace_back(m - 1 + 8);
				}
				else
				{
					noPerm.emplace_back(m + 1 + 8);
				}
			}
			else if (row - rowK == 2)				//checks if  enemy king is 2 rows lower
			{
				if (column == columnK)
				{
					if (column >= 1)
						noPerm.emplace_back(p - 1 - 8);
					noPerm.emplace_back(p - 8);
					if (column <= 7)
						noPerm.emplace_back(p + 1 - 8);
				}
				else if (abs(columnK - column) == 1)
				{
					noPerm.emplace_back(p - 8);
					noPerm.emplace_back(m + 8);

				}
				else if (column < columnK)
				{
					noPerm.emplace_back(m - 1 - 8);
				}
				else
				{
					noPerm.emplace_back(m + 1 - 8);
				}



			}
			else if (columnK - column == 2)
			{
				if (rowK == row)
				{
					if (row >= 1)
						noPerm.emplace_back(p + 1 - 8);
					noPerm.emplace_back(p + 1);
					if (row <= 7)
						noPerm.emplace_back(p + 1 + 8);
				}
				else
				{
					noPerm.emplace_back(p + 1);
					noPerm.emplace_back(m - 1);
				}
			}
			else if (column - columnK == 2)
			{
				if (rowK == row)
				{
					if (row >= 1)
						noPerm.emplace_back(p - 1 - 8);
					noPerm.emplace_back(p - 1);
					if (row <= 7)
						noPerm.emplace_back(p - 1 + 8);
				}
				else
				{
					noPerm.emplace_back(p - 1);
					noPerm.emplace_back(m + 1);
				}
			}
		}
	}                             
	else 
	{
		//check rocks

		for (int i = 0; i < 2; i++)
		{
			if (bPieces[7 * i].place != -1)
			{
				p = bPieces[7 * i].place;						// p - position of piece that perhaps attacks king
				column = bPieces[7 * i].place % 8;
				row = bPieces[7 * i].place / 8;
				int  x;
				if (abs(column - columnK) <= 1)
				{

					if (m < bPieces[7 * i].place)
					{
						x = -1;
						if (m == p - 1)
						{
							if (p + 8 < 64)
								noPerm.emplace_back(p + 8);
						}
						else if (m == p - 8)
						{
							if (column >= 1)
								noPerm.emplace_back(p - 1);
						}
					}
					else
					{
						x = 1;
						if (m == p + 1)
						{
							if (p - 8 >= 0)
								noPerm.emplace_back(p - 8);
						}
						else if (m == p + 8)
						{
							if (column >= 1)
								noPerm.emplace_back(p - 1);
						}
					}

					for (int j = 1; j <= abs(row - rowK) + 1; j++)
					{
						if (p + 8 * j * x < 64 && p + 8 * j * x >= 0 && squares[p + 8 * j * x].isTaken)
						{
							noPerm.emplace_back(p + 8 * j * x);
							break;
						}
						if (abs((p + 8 * j * x) / 8 - rowK) <= 1)
						{
							if (p + 8 * j * x < 64 && p + 8 * j * x >= 0)
								noPerm.emplace_back(p + 8 * j * x);
						}

					}
				}
				if (abs(row - rowK) <= 1)
				{
					x = 1;
					if (column > columnK)
						x = -1;
					for (int j = 1; j <= abs(column - columnK) + 1; j++)
					{
						if (squares[p + j * x].isTaken)
						{
							noPerm.emplace_back(p + j * x);
							break;
						}
						if (abs((p + j * x) % 8 - columnK) <= 1)
						{

							if (p + j * x < 64 && p + j * x >= 0)
								noPerm.emplace_back(p + j * x);
						}

					}
				}
			}
		}


		//bishops

		for (int i = 0; i < 2; i++)
		{
			if (bPieces[2 + 3 * i].place != -1)
			{
				p = bPieces[2 + 3 * i].place;						// p - position of piece that perhaps attacks king
				column = bPieces[2 + 3 * i].place % 8;
				row = bPieces[2 + 3 * i].place / 8;
				int max;
				if (abs(column - columnK) > abs(row - rowK))
					max = abs(column - columnK);
				else
					max = abs(row - rowK);
				int x;
				if (abs(column - columnK) == abs(row - rowK + 1))
				{
					if ((m - 8 - p) % 7 == 0)
					{
						if (column >= columnK)
							x = -1;
						else
							x = 1;
						for (int j = 1; j <= max; j++)
						{
							if ((p - 7 * j * x) < 0 || squares[p - 7 * j * x].isTaken)
							{
								noPerm.emplace_back(p - 7 * j * x);
								break;

							}
							if ((p - 7 * j * x) % 8 >= columnK - 1 && (p - 7 * j * x) % 8 <= columnK)
								noPerm.emplace_back(p - 7 * j * x);

						}
					}
					if ((m - 8 - p) % 9 == 0)
					{
						if (column <= columnK)
							x = -1;
						else
							x = 1;
						for (int j = 1; j <= max; j++)
						{
							if (p - 9 * j * x < 0 || squares[p - 9 * j * x].isTaken)
							{
								noPerm.emplace_back(p - 9 * j * x);
								break;
							}
							if ((p - 9 * j * x) % 8 >= columnK && (p - 9 * j * x) % 8 <= columnK + 1)
								noPerm.emplace_back(p - 9 * j * x);

						}
					}
				}
				if (abs(column - columnK) == abs(row - rowK - 1))
				{
					if ((m + 8 - p) % 7 == 0)
					{
						if (column > columnK)
							x = -1;
						else
							x = 1;
						for (int j = 1; j <= max; j++)
						{
							if (p - 7 * j * x > 63 || squares[p - 7 * j * x].isTaken)
							{
								noPerm.emplace_back(p - 7 * j * x);
								break;
							}
							if ((p - 7 * j * x) % 8 >= columnK && (p - 7 * j * x) % 8 <= columnK + 1)
								noPerm.emplace_back(p - 7 * j * x);

						}
					}
					if ((m + 8 - p) % 9 == 0)
					{
						if (column >= columnK)
							x = 1;
						else
							x = -1;
						for (int j = 1; j <= max; j++)
						{
							if (p - 9 * j * x > 63 || squares[p - 9 * j * x].isTaken)
							{
								noPerm.emplace_back(p - 9 * j * x);
								break;
							}
							else if ((p - 9 * j * x) % 8 >= columnK - 1 && (p - 9 * j * x) % 8 <= columnK)
								noPerm.emplace_back(p - 9 * j * x);

						}
					}
				}
				if (abs(column - columnK + 1) == abs(row - rowK + 1) || abs(column - columnK - 1) == abs(row - rowK - 1))
				{
					if (abs(m + 9 - p) % 7 == 0 || abs(m - 9 - p) % 7 == 0)
					{
						if ((m + 9 - p) % 7 == 0)
						{
							if (column <= columnK)
								x = 1;
							else
								x = -1;
						}
						else
						{
							if (column >= columnK)
								x = -1;
							else
								x = 1;

						}

						for (int j = 1; j < max; j++)
						{
							if (squares[p - 7 * j * x].isTaken)
							{
								noPerm.emplace_back(p - 7 * j * x);
								break;
							}
							if ((p - 7 * j * x) % 8 >= columnK - 1 && (p - 7 * j * x) % 8 <= columnK + 1 && (p - 7 * j * x) / 8 >= rowK - 1 && (p - 7 * j * x) / 8 <= rowK + 1)
								noPerm.emplace_back(p - 7 * j * x);
						}
					}
				}
				if (abs(column - columnK - 1) == abs(row - rowK + 1) || abs(column - columnK + 1) == abs(row - rowK - 1))
				{
					if (abs(m - 7 - p) % 9 == 0 || abs(m + 7 - p) % 9 == 0)
					{
						if ((m - 7 - p) % 9 == 0)
						{
							if (column > columnK)
								x = 1;
							else
								x = -1;

						}
						else
						{
							if (column < columnK)
							{
								x = -1;
							}
							else
								x = 1;
						}

						for (int j = 1; j < max; j++)
						{

							if (squares[p - 9 * j * x].isTaken)
							{
								noPerm.emplace_back(p - 9 * j * x);
								break;
							}
							if ((p - 9 * j * x) % 8 >= columnK - 1 && (p - 9 * j * x) % 8 <= columnK + 1 && (p - 9 * j * x) / 8 >= rowK - 1 && (p - 9 * j * x) / 8 <= rowK + 1)
								noPerm.emplace_back(p - 9 * j * x);
						}
					}
				}
			}

		}

		//queen


		if (bPieces[3].place != -1)
		{
			p = bPieces[3].place;						// p - position of piece that perhaps attacks king
			column = bPieces[3].place % 8;
			row = bPieces[3].place / 8;
			int  x;
			if (abs(column - columnK) <= 1)
			{

				if (m < bPieces[3].place)
				{
					x = -1;
					if (m == p - 1)
					{
						if (p + 8 < 64 && !squares[p + 8].isTaken)
							noPerm.emplace_back(p + 8);
					}
					else if (m == p - 8)
					{
						if (column >= 1 && !squares[p - 1].isTaken)
							noPerm.emplace_back(p - 1);
					}
				}
				else
				{
					x = 1;
					if (m == p + 1)
					{
						if (p - 8 >= 0 && !squares[p - 8].isTaken)
							noPerm.emplace_back(p - 8);
					}
					else if (m == p + 8)
					{
						if (column >= 1 && !squares[p - 1].isTaken)
							noPerm.emplace_back(p - 1);
					}
				}

				for (int j = 1; j <= abs(row - rowK) + 1; j++)
				{
					if (p + 8 * j * x < 64 && p + 8 * j * x >= 0 && squares[p + 8 * j * x].isTaken)
					{
						noPerm.emplace_back(p + 8 * j * x);
						break;
					}
					if (abs((p + 8 * j * x) / 8 - rowK) <= 1)
					{
						if (p + 8 * j * x < 64 && p + 8 * j * x >= 0)
							noPerm.emplace_back(p + 8 * j * x);
					}

				}
			}
			if (abs(row - rowK) <= 1)
			{
				x = 1;
				if (column > columnK)
					x = -1;
				for (int j = 1; j <= abs(column - columnK) + 1; j++)
				{
					if (squares[p + j * x].isTaken)
					{
						noPerm.emplace_back(p + j * x);
						break;
					}
					if (abs((p + j * x) % 8 - columnK) <= 1)
					{

						if (p + j * x < 64 && p + j * x >= 0)
							noPerm.emplace_back(p + j * x);
					}

				}
			}
			int max;
			if (abs(column - columnK) > abs(row - rowK))
				max = abs(column - columnK);
			else
				max = abs(row - rowK);
			if (abs(column - columnK) == abs(row - rowK + 1))
			{
				if ((m - 8 - p) % 7 == 0)
				{
					if (column >= columnK)
						x = -1;
					else
						x = 1;
					for (int j = 1; j <= max; j++)
					{
						if ((p - 7 * j * x) < 0 || squares[p - 7 * j * x].isTaken)
						{
							noPerm.emplace_back(p - 7 * j * x);
							break;
						}
						if ((p - 7 * j * x) % 8 >= columnK - 1 && (p - 7 * j * x) % 8 <= columnK)
							noPerm.emplace_back(p - 7 * j * x);

					}
				}
				if ((m - 8 - p) % 9 == 0)
				{
					if (column <= columnK)
						x = -1;
					else
						x = 1;
					for (int j = 1; j <= max; j++)
					{
						if (p - 9 * j * x < 0 || squares[p - 9 * j * x].isTaken)
						{
							noPerm.emplace_back(p - 9 * j * x);
							break;
						}

						if ((p - 9 * j * x) % 8 >= columnK && (p - 9 * j * x) % 8 <= columnK + 1)
							noPerm.emplace_back(p - 9 * j * x);

					}
				}
			}
			if (abs(column - columnK) == abs(row - rowK - 1))
			{
				if ((m + 8 - p) % 7 == 0)
				{
					if (column > columnK)
						x = -1;
					else
						x = 1;
					for (int j = 1; j <= max; j++)
					{
						if (p - 7 * j * x > 63 || squares[p - 7 * j * x].isTaken)
						{
							noPerm.emplace_back(p - 7 * j * x);
							break;
						}
						if ((p - 7 * j * x) % 8 >= columnK && (p - 7 * j * x) % 8 <= columnK + 1)
							noPerm.emplace_back(p - 7 * j * x);

					}
				}
				if ((m + 8 - p) % 9 == 0)
				{
					if (column >= columnK)
						x = 1;
					else
						x = -1;
					for (int j = 1; j <= max; j++)
					{
						if (p - 9 * j * x > 63 || squares[p - 9 * j * x].isTaken)
						{
							noPerm.emplace_back(p - 9 * j * x);
							break;
						}
						else if ((p - 9 * j * x) % 8 >= columnK - 1 && (p - 9 * j * x) % 8 <= columnK)
							noPerm.emplace_back(p - 9 * j * x);

					}
				}
			}
			if (abs(column - columnK + 1) == abs(row - rowK + 1) || abs(column - columnK - 1) == abs(row - rowK - 1))
			{
				if (abs(m + 9 - p) % 7 == 0 || abs(m - 9 - p) % 7 == 0)
				{
					if ((m + 9 - p) % 7 == 0)
					{
						if (column <= columnK)
							x = 1;
						else
							x = -1;
					}
					else
					{
						if (column >= columnK)
							x = -1;
						else
							x = 1;

					}

					for (int j = 1; j < max; j++)
					{
						if (squares[p - 7 * j * x].isTaken)
						{
							noPerm.emplace_back(p - 7 * j * x);
							break;
						}
						if ((p - 7 * j * x) % 8 >= columnK - 1 && (p - 7 * j * x) % 8 <= columnK + 1 && (p - 7 * j * x) / 8 >= rowK - 1 && (p - 7 * j * x) / 8 <= rowK + 1)
							noPerm.emplace_back(p - 7 * j * x);
					}
				}
			}
			if (abs(column - columnK - 1) == abs(row - rowK + 1) || abs(column - columnK + 1) == abs(row - rowK - 1))
			{
				if (abs(m - 7 - p) % 9 == 0 || abs(m + 7 - p) % 9 == 0)
				{
					if ((m - 7 - p) % 9 == 0)
					{
						if (column > columnK)
							x = 1;
						else
							x = -1;

					}
					else
					{
						if (column < columnK)
						{
							x = -1;
						}
						else
							x = 1;
					}

					for (int j = 1; j < max; j++)
					{

						if (squares[p - 9 * j * x].isTaken)
						{
							noPerm.emplace_back(p - 9 * j * x);
							break;
						}
						if ((p - 9 * j * x) % 8 >= columnK - 1 && (p - 9 * j * x) % 8 <= columnK + 1 && (p - 9 * j * x) / 8 >= rowK - 1 && (p - 9 * j * x) / 8 <= rowK + 1)
							noPerm.emplace_back(p - 9 * j * x);
					}
				}
			}
		}


		//knights

		for (int i = 0; i < 2; i++)
		{
			if (bPieces[1 + 5 * i].place != -1)
			{
				p = bPieces[1 + 5 * i].place;						// p - position of piece that perhaps attacks king
				column = bPieces[1 + 5 * i].place % 8;
				row = bPieces[1 + 5 * i].place / 8;
				if (row < rowK)
				{
					if (column < columnK)
					{
						if (columnK - column <= 3 && rowK - row <= 2 && column <= 5 && row <= 6)
							noPerm.emplace_back(p + 10);
						if (columnK - column <= 2 && rowK - row <= 3 && column <= 6 && row <= 5)
							noPerm.emplace_back(p + 17);
					}
					else if (columnK == column && rowK - row <= 2 && row <= 5)
					{
						if (column >= 1)
							noPerm.emplace_back(p + 15);
						if (column <= 6)
							noPerm.emplace_back(p + 17);
					}
					else
					{
						if (column - columnK <= 3 && rowK - row <= 2 && row <= 6 && column >= 2)
							noPerm.emplace_back(p + 6);
						if (column - columnK <= 2 && rowK - row <= 3 && row <= 5 && column >= 1)
							noPerm.emplace_back(p + 15);
					}
				}
				else
				{
					if (column < columnK)
					{
						if (row == rowK && columnK - column <= 3)
						{
							if (column <= 5)
							{
								noPerm.emplace_back(p + 10);
								noPerm.emplace_back(p - 6);
							}
						}
						else
						{
							if (columnK - column <= 3 && row - rowK <= 2 && column <= 5 && row >= 1)
								noPerm.emplace_back(p - 6);
							if (columnK - column <= 2 && row - rowK <= 3 && column <= 6 && row >= 2)
								noPerm.emplace_back(p - 15);
						}
					}
					else if (column > columnK)
					{
						if (row == rowK)
						{
							if (column - columnK <= 3 && column >= 2)
							{
								noPerm.emplace_back(p - 2 - 8);
								noPerm.emplace_back(p - 2 + 8);
							}
						}
						else
						{
							if (column - columnK <= 3 && row - rowK <= 2 && column >= 2 && row >= 1)
								noPerm.emplace_back(p - 2 - 8);
							if (column - columnK <= 2 && row - rowK <= 3 && column >= 1 && row >= 2)
								noPerm.emplace_back(p - 1 - 2 * 8);
						}
					}
					else if (column == columnK)
					{
						if (row - rowK <= 3)
						{
							if (row >= 2 && column <= 6)
								noPerm.emplace_back(p - 15);
							if (row >= 2 && column >= 1)
								noPerm.emplace_back(p - 17);
						}
					}
				}
			}
		}

		//pawns

		for (int i = 8; i < 16; i++)
		{
			if (bPieces[i].place != -1)
			{
				p = bPieces[i].place;						// p - position of piece that perhaps attacks king
				row = bPieces[i].place / 8;
				if (row - 2 == rowK || (row == rowK && row - 1 >= 0) || (row - 1 == rowK))
				{
					column = bPieces[i].place % 8;
					if (column == columnK)
					{
						if (column >= 1)
							noPerm.emplace_back(p - 1 - 8);
						if (column <= 6)
							noPerm.emplace_back(p + 1 - 8);
					}
					else if (column > columnK)
					{
						if (column - columnK <= 2)
							noPerm.emplace_back(p - 1 - 8);

					}
					else
					{
						if (columnK - column <= 2)
							noPerm.emplace_back(p + 1 - 8);
					}

				}
			}
		}

		//king

		p = bPieces[4].place;						// p - position of piece that perhaps attacks king
		row = bPieces[4].place / 8;
		column = bPieces[4].place % 8;
		if (abs(columnK - column) > abs(rowK - row))
			max = abs(columnK - column);
		else
			max = abs(rowK - row);
		if (max == 2)
		{
			if (rowK - row == 2)					// checks if enemy king is 2 rows higer 
			{
				if (column == columnK)
				{
					if (column >= 1)
						noPerm.emplace_back(p - 1 + 8);
					noPerm.emplace_back(p + 8);
					if (column <= 7)
						noPerm.emplace_back(p + 1 + 8);
				}
				else if (abs(columnK - column) == 1)
				{
					noPerm.emplace_back(p - 8);
					noPerm.emplace_back(m + 8);

				}
				else if (column < columnK)
				{
					noPerm.emplace_back(m - 1 + 8);
				}
				else
				{
					noPerm.emplace_back(m + 1 + 8);
				}
			}
			else if (row - rowK == 2)				//checks if  enemy king is 2 rows lower
			{
				if (column == columnK)
				{
					if (column >= 1)
						noPerm.emplace_back(p - 1 - 8);
					noPerm.emplace_back(p - 8);
					if (column <= 7)
						noPerm.emplace_back(p + 1 - 8);
				}
				else if (abs(columnK - column) == 1)
				{
					noPerm.emplace_back(p - 8);
					noPerm.emplace_back(m + 8);

				}
				else if (column < columnK)
				{
					noPerm.emplace_back(m - 1 - 8);
				}
				else
				{
					noPerm.emplace_back(m + 1 - 8);
				}



			}
			else if (columnK - column == 2)
			{
				if (rowK == row)
				{
					if (row >= 1)
						noPerm.emplace_back(p + 1 - 8);
					noPerm.emplace_back(p + 1);
					if (row <= 7)
						noPerm.emplace_back(p + 1 + 8);
				}
				else
				{
					noPerm.emplace_back(p + 1);
					noPerm.emplace_back(m - 1);
				}
			}
			else if (column - columnK == 2)
			{
				if (rowK == row)
				{
					if (row >= 1)
						noPerm.emplace_back(p - 1 - 8);
					noPerm.emplace_back(p - 1);
					if (row <= 7)
						noPerm.emplace_back(p - 1 + 8);
				}
				else
				{
					noPerm.emplace_back(p - 1);
					noPerm.emplace_back(m + 1);
				}
			}
		}
		}


	cout << "przed usunieciem" << endl;

	for (int& i : noPerm)         //testing
	{
		cout << "blokuje: " << i << " ";
	}
	cout << endl;
	for (auto it = noPerm.begin(); it != noPerm.end(); ) 
	{
		int i = *it;
		column = i % 8;
		row = i / 8;
		if (abs(column - columnK) > 1 || abs(row - rowK) > 1) {
			it = noPerm.erase(it);
		}
		else {
			++it;
		}
	}
	cout << "Po usunieciu" << endl;
	for (int& i : noPerm)         //testing
	{
		cout << "blokuje: " << i << " ";
	}
	cout << endl;
}

void Game::stopdrag(RenderWindow& window, Event& event)
{	
		
	if(field!=nullptr && isDragging)
	if (event.mouseButton.button == Mouse::Left)
	{
		isDragging = false;
		int m = whichField(window, event);
		cout << "m wynosi: " << m << endl;
		if (squares[m].permission)
		{
			
			takeDown(m);
			isCheck(m);
			noPerm.clear();
			field->figure->setPos(squares[m].getPosition());        //set the piece in correct field
			field->figure->place = m;
			
			//castling
			if (field->figure->piece == 'K')          //version to update
			{
				if (m == 2 && LCB)
				{
					bPieces[0].setPos(squares[3].getPosition());
					bPieces[0].place = 3;
					squares[0].figure = nullptr;
					squares[3].figure = &bPieces[0];
					squares[0].isTaken = false;
					squares[3].isTaken = true;
				}
				else if (m == 6 && RCB)
				{
					bPieces[7].setPos(squares[5].getPosition());
					bPieces[7].place = 5;
					squares[7].figure = nullptr;
					squares[7].isTaken = false;
					squares[5].figure = &bPieces[7];
					squares[5].isTaken = true;
				}
				if (m == 58 && LCW)
				{
					wPieces[0].setPos(squares[59].getPosition());
					wPieces[0].place = 59;
					squares[56].figure = nullptr;
					squares[56].isTaken = false;
					squares[59].figure = &wPieces[0];
					squares[59].isTaken = true;
				}
				else if (m == 62 && RCW)
				{
					wPieces[7].setPos(squares[61].getPosition());
					wPieces[7].place = 61;
					squares[63].figure = nullptr;
					squares[63].isTaken = false;
					squares[61].figure = &wPieces[7];
					squares[61].isTaken = true;
				}


				if (field->figure->player == 0)
				{
					LCW = false;
					RCW = false;
				}
				else
				{
					LCB = false;
					RCB = false;
				}
			}														//castling																//castling														//castling
			if (field->figure->piece == 'r' && (LCB || RCB) && field->figure->player == 1)           //check if rocks have been moved before do castling
			{
				if (field == &squares[0])
					LCB = false;
				if (field == &squares[7])
					RCB = false;
			}
			if (field->figure->piece == 'r' && (LCW || RCW) && field->figure->player == 0)
			{
				if (field == &squares[56])
					LCW = false;
				if (field == &squares[63])
					RCW = false;
			}
			

			squares[m].figure = field->figure;
			squares[m].isTaken = true;
			field->figure = nullptr;
			field->isTaken = false;
			for (unsigned& move : moves)
			{
				squares[move].permission = false;
			}

			if (!enemies.empty())
			{
				for (unsigned& e : enemies)
				{
					squares[e].permission = false;

				}
				enemies.clear();
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
}


void Game::update(RenderWindow& window)
{	
	float i=1.f;
	for (pieces* p : wDeaths)
	{
		p->setPos({ 100.f + 14.5f * i,88.75f });
		i++;
	}
	i = 1.f;
	for (pieces* p : bDeaths)
	{
		p->setPos({ 100.f + 14.5f * i,511.75f });
		i++;
	}
	if (!moves.empty())
	{
		for (unsigned& move : moves)
		{
			if(squares[move].permission)
				window.draw(squares[move].dot);
		}
	}
	if (!enemies.empty())
	{
		for (unsigned& e : enemies)
			if(squares[e].permission)
				window.draw(squares[e].circle);
	}


	for (int i = 0; i < 16; i++)
	{
		window.draw(bPieces[i]);
		window.draw(wPieces[i]);

	}

}





