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


	for (float i = 0.f; i < 8.f; i++)
		for (float j = 0.f; j < 8.f; j++)
		{
			square temp((125.f + j * 50.f), (125.f + i * 50.f));
			if (int(i + j) % 2 == 0)
				temp.ChangeColor();
			squares.emplace_back(temp);
		}

}

void Game::PrepareGame(RenderWindow& window)
{


	for (int i = 0; i < 16; i++)
	{
		wPieces[i].setPos(squares[wPieces[i].place].GetPosition());
		bPieces[i].setPos(squares[bPieces[i].place].GetPosition());
		TakePlace(wPieces[i].place, wPieces[i]);
		TakePlace(bPieces[i].place, bPieces[i]);
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

void Game::DrawBoard(RenderWindow &window)
{
	for (int i = 0; i < 64; i++)
	{
		window.draw(squares[i]);
	}
}

bool Game::IsKingSafe(int piecePosition)
{
	int kingPosition, columnOfKing, rowOfKing, column, row, distance, coefficient;
	column = piecePosition % 8;
	row = piecePosition / 8;
	if (blackMove)
	{
		kingPosition = bPieces[4].place;
		columnOfKing = bPieces[4].place % 8;
		rowOfKing = bPieces[4].place / 8;
	}
	else
	{
		kingPosition = wPieces[4].place;
		columnOfKing = wPieces[4].place % 8;
		rowOfKing = wPieces[4].place / 8;
	}

	if (ArePiecesOnTheSameDiagonal(column, row, columnOfKing, rowOfKing) && IsFirstDiagonal(piecePosition, kingPosition))
	{
		distance = abs(column - columnOfKing);
		coefficient = AssignCoefficient(kingPosition, piecePosition);
		int i;
		for (i = 1; i<distance ;i++)
		{
			if (squares[kingPosition + 7 * i * coefficient].isTaken)
				break;
		}
		if (IsPieceClosestToTheKing(i, distance) || check && distance > i)
		{
			int min;
			int diagonal = 7;
			if (kingPosition < piecePosition)
			{
				if (column < 7 - row)
					min = column;
				else
					min = 7 - row;
			}
			else
			{
				if (7 - column < row)
					min = 7 - column;
				else
					min = row;
			}
			for (i = 1; i <= min; i++)
			{
				if (squares[piecePosition + i * 7 * coefficient].isTaken)
					return IsSafe(kingPosition, piecePosition, coefficient, i, diagonal);
			}
		}
		else if (squares[kingPosition + 7 * i * coefficient].figure->player != blackMove &&
			(squares[kingPosition + 7 * i * coefficient].figure->piece == 'b' || squares[kingPosition + 7 * i * coefficient].figure->piece == 'q'))
			return false;
		else return true;

	}
	else if (ArePiecesOnTheSameDiagonal(column, row, columnOfKing, rowOfKing) && IsSecondDiagonal(piecePosition, kingPosition))
	{
		distance = abs(column - columnOfKing);
		coefficient = AssignCoefficient(kingPosition, piecePosition);
		int i;
		for (i = 1; i < distance; i++)
		{
			if (squares[kingPosition + 9 * i * coefficient].isTaken)
				break;
		}
		if (IsPieceClosestToTheKing(i, distance) || check && distance > i)
		{
			int min;
			int diagonal = 9;
			if (kingPosition < piecePosition)
			{
				if (7 - column < 7 - row)
					min = 7 - column;
				else
					min = 7 - row;
			}
			else
			{
				if (column < row)
					min = column;
				else
					min = row;
			}
			for (i = 1; i <= min; i++)
			{
				if (squares[piecePosition + i * 9 * coefficient].isTaken)
					return IsSafe(kingPosition, piecePosition, coefficient, i, diagonal);
			}
		}
		else if (squares[kingPosition + 9 * i * coefficient].figure->player != blackMove &&
			(squares[kingPosition + 9 * i * coefficient].figure->piece == 'b' || squares[kingPosition + 9 * i * coefficient].figure->piece == 'q'))
			return false;
		else return true;
	}
	else if (ArePiecesInTheSameColumn(column, columnOfKing))
	{
		distance = abs(rowOfKing - row);
		coefficient = AssignCoefficient(kingPosition, piecePosition);
		int i;
		for (i = 1; i < distance; i++)
		{
			if (squares[kingPosition + 8 * i * coefficient].isTaken)
				break;
		}

		if (IsPieceClosestToTheKing(i, distance) || check && distance > i)
		{
			int max;
			if (kingPosition > piecePosition)
				max = row;
			else max = 7 - row;
			for (int j = 1; j <= max; j++)
			{
				if (squares[piecePosition + 8 * j * coefficient].isTaken)
				{
					if (squares[piecePosition + 8 * j * coefficient].figure->player != blackMove &&
						(squares[piecePosition + 8 * j * coefficient].figure->piece == 'r' || squares[piecePosition + 8 * j * coefficient].figure->piece == 'q')) 
					{
						if (squares[piecePosition].figure->piece == 'p')
							return true;
						else if (squares[piecePosition].figure->piece == 'r' || squares[piecePosition].figure->piece == 'q')
						{

							for (int k = 1; k < distance; k++)
								moves.emplace_back(kingPosition + 8 * k * coefficient);
							for (int l = 1; l < j; l++)
								moves.emplace_back(piecePosition + 8 * l * coefficient);
							enemies.emplace_back(piecePosition + 8 * j * coefficient);
						}
						return false;
					}

				}
			}
		}
		else if (squares[kingPosition + 8 * i * coefficient].figure->player != blackMove &&
			(squares[kingPosition + 8 * i * coefficient].figure->piece == 'r' || squares[kingPosition + 8 * i * coefficient].figure->piece == 'q'))
			return false;
		else return true;

	}
	else if (ArePiecesInTheSameRow(row, rowOfKing))
	{
		coefficient = AssignCoefficient(kingPosition, piecePosition);
		int i;
		distance = abs(piecePosition - kingPosition);
		for (i = 1; i < distance; i++)
			if (squares[kingPosition + i * coefficient].isTaken)
				break;
		if (IsPieceClosestToTheKing(i, distance) || check && distance > i)
		{
			int max;
			if (piecePosition > kingPosition)
				max = 7 - column;
			else max = column;
			for (int j = 1; j <= max; j++)
				if (squares[piecePosition + j * coefficient].isTaken)
				{
					if (squares[piecePosition + j * coefficient].figure->player != blackMove && 
						(squares[piecePosition + j * coefficient].figure->piece == 'r' || squares[piecePosition + j * coefficient].figure->piece == 'q'))
					{
						if (squares[piecePosition].figure->piece == 'r' || squares[piecePosition].figure->piece == 'q')
						{
							for (int k = 1; k < distance; k++)
								moves.emplace_back(kingPosition + k * coefficient);
							for (int k = 1; k < max; k++)
								moves.emplace_back(piecePosition + k * coefficient);
							enemies.emplace_back(piecePosition + j * coefficient);

						}
						return false;
					}
					return true;
				}
		}
		else if (squares[kingPosition + i * coefficient].figure->player != blackMove &&
			(squares[kingPosition + i * coefficient].figure->piece == 'r' || squares[kingPosition + i * coefficient].figure->piece == 'q'))
			return false;
		else return true;
	}

	return true;
}

bool Game::IsSafe(int kingPosition, int piecePosition, int coefficient, int i, int diagonal) {
	int min;
	if (squares[piecePosition + i * diagonal * coefficient].figure->player != blackMove &&
		(squares[piecePosition + i * diagonal * coefficient].figure->piece == 'b' || squares[piecePosition + i * diagonal * coefficient].figure->piece == 'q'))
	{
		if (squares[piecePosition].figure->piece == 'b' || squares[piecePosition].figure->piece == 'q')
		{
			min = (kingPosition - (piecePosition + i * diagonal * coefficient)) % 8;
			int j;
			for (j = 1; j < min; j++)
				moves.emplace_back(kingPosition + j * diagonal * coefficient);
			enemies.emplace_back(kingPosition + j * diagonal * coefficient);
		}
		else if (squares[piecePosition].figure->piece == 'p')
		{
			if (piecePosition + diagonal == piecePosition + i * diagonal * coefficient && blackMove)
				enemies.emplace_back(piecePosition + diagonal);
			else if (piecePosition - diagonal == piecePosition + i * diagonal * coefficient && blackMove == 0)
				enemies.emplace_back(piecePosition - diagonal);

		}

		return false;
	}
	else return true;
}

bool Game::IsPieceClosestToTheKing(int iteration, int distance) {
	return iteration == distance;
}

int Game::AssignCoefficient(int kingPosition, int piecePosition) {
	if (kingPosition < piecePosition)
		return 1;
	else
		return -1;
}

bool Game::ArePiecesInTheSameRow(int row, int rowOfKing) {
	return row == rowOfKing;
}

bool Game::ArePiecesInTheSameColumn(int column, int columnOfKing) {
	return column == columnOfKing;
}

bool Game::ArePiecesOnTheSameDiagonal(int column, int row, int columnOfKing, int rowOfKing) {
	return abs(column - columnOfKing) == abs(row - rowOfKing);
}

bool Game::IsFirstDiagonal(int piecePosition, int kingPosition) {
	return abs(piecePosition - kingPosition) % 7 == 0;
}

bool Game::IsSecondDiagonal(int piecePosition, int kingPosition) {
	return abs(piecePosition - kingPosition) % 9 == 0;
}

void Game::TakePlace(int place, pieces figure)
{
	squares[place].isTaken = true;
	squares[place].figure = &figure;
}

int Game::GetClickedField(RenderWindow& window, Event& event)
{	
	Vector2i mousePos = Mouse::getPosition(window);
	if (mousePos.x >= 100 && mousePos.x <= 500 && mousePos.y >= 100 && mousePos.y <= 500)
	{
		int m = (mousePos.x - 100) / 50 + (mousePos.y - 100) / 50 * 8;
		return m;
	}
	return 63;
}

void Game::PossibleMoves(RenderWindow& window, Event& event)
{
	if (event.mouseButton.button == Mouse::Left && !isDragging && !isPromotion)
	{
		int clickedField = GetClickedField(window, event);
		if (field != nullptr && squares[clickedField].permission == false )      //clears the dots (possible moves) if player clicks empty square or enemy's piece
		{
			for (unsigned& move : moves)
			{
				squares[move].permission = false;
			}
			for (unsigned& enemy : enemies)
				squares[enemy].permission = false;
			moves.clear();
			enemies.clear();
			if (squares[clickedField].isTaken == false || squares[clickedField].figure->player != blackMove)
				field = nullptr;
		}
	
		
		if (!isDragging && squares[clickedField].isTaken && squares[clickedField].figure->player == blackMove)
		{
	
			char piece = squares[clickedField].figure->piece;
			int player = squares[clickedField].figure->player;
			int coefficient;
			int column = clickedField % boardSize;
			int row = clickedField / boardSize;
	
			if (piece == 'p' && !doubleCheck && IsKingSafe(clickedField))
			{
				if (squares[clickedField].figure->player == whitePlayer)
					coefficient = 8;
				if (squares[clickedField].figure->player == blackPlayer)
					coefficient = -8;
				AddPawnsPossibleMoves(coefficient, clickedField);
			}
			else if (piece == 'k' && !doubleCheck && IsKingSafe(clickedField))
				{
					if (column >= 2)
					{
						if (row >= 1)
							if (squares[clickedField - 2 - 8].isTaken == false)
								moves.emplace_back(clickedField - 2 - 8);
							else if (squares[clickedField - 2 - 8].figure->player != blackMove)
								enemies.emplace_back(clickedField - 2 - 8);
						if (7 - row >= 1)
							if (squares[clickedField - 2 + 8].isTaken == false)
								moves.emplace_back(clickedField - 2 + 8);
							else if(squares[clickedField - 2 + 8].figure->player != blackMove)
								enemies.emplace_back(clickedField - 2 + 8);
					}			
					if (7 - column >= 2)
					{
						if (row >= 1)
							if (squares[clickedField + 2 - 8].isTaken == false)
								moves.emplace_back(clickedField + 2 - 8);
							else if (squares[clickedField + 2 - 8].figure->player != blackMove)
								enemies.emplace_back(clickedField + 2 - 8);
						if (7 - row >= 1)
							if (squares[clickedField + 2 + 8].isTaken == false)
								moves.emplace_back(clickedField + 2 + 8);
							else if (squares[clickedField + 2 + 8].figure->player != blackMove)
								enemies.emplace_back(clickedField + 2 + 8);
					}
					if (row >= 2)
					{
						if (column >= 1)
							if (squares[clickedField - 2 * 8 - 1].isTaken == false)
								moves.emplace_back(clickedField - 2 * 8 - 1);
							else if (squares[clickedField - 2 * 8 - 1].figure->player != blackMove)
								enemies.emplace_back(clickedField - 2 * 8 - 1);
						if (7 - column >= 1)
							if (squares[clickedField - 2 * 8 + 1].isTaken == false)
								moves.emplace_back(clickedField - 2 * 8 + 1);
							else if (squares[clickedField - 2 * 8 + 1].figure->player != blackMove)
								enemies.emplace_back(clickedField - 2 * 8 + 1);
					}
					if (7 - row >= 2)
					{
						if (column >= 1)
							if (squares[clickedField + 2 * 8 - 1].isTaken == false)
								moves.emplace_back(clickedField + 2 * 8 - 1);
							else if (squares[clickedField + 2 * 8 - 1].figure->player != blackMove)
								enemies.emplace_back(clickedField + 2 * 8 - 1);
						if (7 - column >= 1)
							if (squares[clickedField + 2 * 8 + 1].isTaken == false)
								moves.emplace_back(clickedField + 2 * 8 + 1);
							else if (squares[clickedField + 2 * 8 + 1].figure->player != blackMove)
								enemies.emplace_back(clickedField + 2 * 8 + 1);
					}
				}
			else if (piece == 'b' && !doubleCheck && IsKingSafe(clickedField))
				{
					AddBishopPossibleMoves(column, row, clickedField);
				}
			else if (piece == 'q' && !doubleCheck && IsKingSafe(clickedField))
				{
					AddQueenPossibleMoves(column, row, clickedField);
				}
			else if (piece == 'r' && !doubleCheck && IsKingSafe(clickedField))
				{
					AddRockPossibleMoves(column, row, clickedField);
				}
			else if(piece == 'K')
				{
					if (row >= 1)
					{
						if (column >= 1)
							if (squares[clickedField - 8 - 1].isTaken == false)
								moves.emplace_back(clickedField - 8 - 1);
							else if (squares[clickedField - 8 - 1].figure->player != blackMove)
								enemies.emplace_back(clickedField - 8 - 1);
						if (7 - column >= 1)
							if (squares[clickedField - 8 + 1].isTaken == false)
								moves.emplace_back(clickedField - 8 + 1);
							else if (squares[clickedField - 8 + 1].figure->player != blackMove)
								enemies.emplace_back(clickedField - 8 + 1);
						if (squares[clickedField - 8].isTaken == false)
							moves.emplace_back(clickedField - 8);
						else if (squares[clickedField - 8].figure->player != blackMove)
							enemies.emplace_back(clickedField - 8);
					}
					if (7 - row >= 1)
					{
						if (column >= 1)
							if (squares[clickedField + 8 - 1].isTaken == false)
								moves.emplace_back(clickedField + 8 - 1);
							else if (squares[clickedField + 8 - 1].figure->player != blackMove)
								enemies.emplace_back(clickedField + 8 - 1);
						if (7 - column >= 1)
							if (squares[clickedField + 8 + 1].isTaken == false)
								moves.emplace_back(clickedField + 8 + 1);
							else if (squares[clickedField + 8 + 1].figure->player != blackMove)
								enemies.emplace_back(clickedField + 8 + 1);
						if (squares[clickedField + 8].isTaken == false)
							moves.emplace_back(clickedField + 8);
						else if (squares[clickedField + 8].figure->player != blackMove)
							enemies.emplace_back(clickedField + 8);
					}
					if (clickedField-1 >= 0 && column >= 1 && squares[clickedField - 1].isTaken == false)
						moves.emplace_back(clickedField - 1);
					else if (column>=1 && squares[clickedField - 1].figure->player != blackMove)
						enemies.emplace_back(clickedField - 1);
					if (7 - column >= 1 && squares[clickedField + 1].isTaken == false)
						moves.emplace_back(clickedField + 1);
					else if (column <= 6 && squares[clickedField + 1].figure->player != blackMove)
						enemies.emplace_back(clickedField + 1);
					if (noPerm.empty()) {
						AddSquareIndexToNoPermList(clickedField, player);
					}
					AddCastlingMoves();
				}
	
			for (unsigned& move : moves)
				{					
					squares[move].permission = true;
				}
			squares[clickedField].permission = false;


			if (check)
				{
					AddFieldsToDangerPath(blackMove);
					for (auto& d : dangerPath)
						squares[d].permission = false;
					if(squares[clickedField].figure->piece != 'K')
					for (unsigned& move : moves)
					{
						if (squares[move].permission)
							squares[move].permission = false;
						else
							squares[move].permission = true;
					}
				}
	
				for (unsigned& e : enemies)
					{
						if (check && squares[clickedField].figure->piece != 'K')
						{
							if (e == attacker1)
							{
								squares[e].permission = true;
							}
						}
						else
						{
							squares[e].permission = true;
						}
							
					}
	
			if (squares[clickedField].figure->piece == 'K')
				for (int p : noPerm)
				{
					squares[p].permission = false;
				}
			if(squares[clickedField].isTaken)
				field = &squares[clickedField];
		}
	}
}

void Game::AddFieldsToDangerPath(int playerTurn) {
	int kingPosition;
	if (playerTurn == whitePlayer)
		kingPosition = wPieces[4].place;
	else kingPosition = bPieces[4].place;
	char piece;
	if (attacker1 != 64)
		piece = squares[attacker1].figure->piece;
	if (abs(attacker1 - kingPosition) % 7 == 0) {
		if (attacker1 > kingPosition) {
			for (int i = 1; attacker1 - 7 * i > kingPosition; i++) {
				dangerPath.emplace_back(attacker1 - 7 * i);
			}
		}
		else{ 
			for (int i = 1; attacker1 + 7 * i < kingPosition; i++) {
				dangerPath.emplace_back(attacker1 + 7 * i);
			}
		}

	}
	else if (abs(attacker1 - kingPosition) % 9 == 0) {
		if (attacker1 > kingPosition) {
			for (int i = 1; attacker1 - 9 * i > kingPosition; i++) {
				dangerPath.emplace_back(attacker1 - 9 * i);
			}
		}
		else {
			for (int i = 1; attacker1 + 9 * i < kingPosition; i++) {
				dangerPath.emplace_back(attacker1 + 9 * i);
			}
		}
	}
	else if (attacker1 % 8 == kingPosition % 8) {
		if (attacker1 > kingPosition) {
			for (int i = 1; attacker1 - 8 * i > kingPosition; i++) {
				dangerPath.emplace_back(attacker1 - 8 * i);
			}
		}
		else {
			for (int i = 1; attacker1 + 8 * i < kingPosition; i++) {
				dangerPath.emplace_back(attacker1 + 8 * i);
			}
		}
	}
	else if (attacker1 / 8 == kingPosition / 8) {
		if (attacker1 > kingPosition) {
			for (int i = 1; attacker1 - i > kingPosition; i++) {
				dangerPath.emplace_back(attacker1 - i);
			}
		}
		else {
			for (int i = 1; attacker1 + i < kingPosition; i++) {
				dangerPath.emplace_back(attacker1 + i);
			}
		}
	}
}

void Game::AddQueenPossibleMoves(int column, int row, int clickedField) {
	AddBishopPossibleMoves(column, row, clickedField);
	AddRockPossibleMoves(column, row, clickedField);
}

void Game::AddBishopPossibleMoves(int column, int row, int clickedField) {
	int min;

	if (row < column)
		min = row;
	else
		min = column;
	for (int i = 1; i <= min; i++)
	{
		if (!AddPossibleMove(clickedField - 9 * i))
			break;
	}

	if (row < 7 - column)
		min = row;
	else min = 7 - column;
	for (int i = 1; i <= min; i++)
	{
		if (!AddPossibleMove(clickedField - 7 * i))
			break;
	}
	if (7 - row < column)
		min = 7 - row;
	else min = column;
	for (int i = 1; i <= min; i++)
	{
		if (!AddPossibleMove(clickedField + 7 * i))
			break;
	}
	if (7 - row < 7 - column)
		min = 7 - row;
	else min = 7 - column;
	for (int i = 1; i <= min; i++)
	{
		if (!AddPossibleMove(clickedField + 9 * i))
			break;
	}
}

void Game::AddRockPossibleMoves(int column, int row, int clickedField) {
	for (int i = clickedField - 1; i >= clickedField - column; i--)
	{
		if (!AddPossibleMove(i))
			break;
	}
	for (int i = clickedField + 1; i <= clickedField + (7 - column); i++)
	{
		if (!AddPossibleMove(i))
			break;
	}
	for (int i = 1; i <= row; i++)
	{
		if (!AddPossibleMove(clickedField - 8 * i))
			break;
	}
	for (int i = 1; i <= 7 - row; i++)
	{
		if (!AddPossibleMove(clickedField + 8 * i))
			break;
	}
}

bool Game::AddPossibleMove(int position)
{ 
	if (squares[position].isTaken == false)
		moves.emplace_back(position);
	else if (squares[position].figure->player != blackMove)
	{
		enemies.emplace_back(position);
		return false;
	}
	else return false;

	return true;
}

void Game::AddPawnsPossibleMoves(int coefficient, int clickedField) {

	int column = clickedField % boardSize;
	int row = clickedField / boardSize;

	if (squares[clickedField - coefficient].isTaken == false)
	{
		moves.emplace_back(clickedField - coefficient);
		int startingRow;
		if (blackMove)
			startingRow = 1;
		else startingRow = 6;

		if (row == startingRow && squares[clickedField - 2 * coefficient].isTaken == false)
			moves.emplace_back(clickedField - 2 * coefficient);
	}
	if (column > 0 && column < 7)
	{
		if (squares[clickedField - coefficient - 1].figure != nullptr && squares[clickedField - coefficient - 1].figure->player != blackMove)
			enemies.emplace_back(clickedField - coefficient - 1);
		if (squares[clickedField - coefficient + 1].figure != nullptr && squares[clickedField - coefficient + 1].figure->player != blackMove)
			enemies.emplace_back(clickedField - coefficient + 1);
	}
	else if (column == 0)
	{
		if (squares[clickedField - coefficient + 1].figure != nullptr && squares[clickedField - coefficient + 1].figure->player != blackMove)
			enemies.emplace_back(clickedField - coefficient + 1);
	}
	else if (column == 7)
		if (squares[clickedField - coefficient - 1].figure != nullptr && squares[clickedField - coefficient - 1].figure->player != blackMove)
			enemies.emplace_back(clickedField - coefficient - 1);
}

void Game::GrabPiece(RenderWindow& window)
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

void Game::Drag(Event& event)
{
		if(field!=nullptr && !isDragging)
		if (event.mouseButton.button == Mouse::Left)
			isDragging = true;
}

void Game::OnCapturePiece(int piecePosition)
{
	if (squares[piecePosition].figure != nullptr && squares[piecePosition].figure->player != blackMove)
	{	
		squares[piecePosition].figure->scale({ 0.5f, 0.5f });
		int i = 0;
		if (blackMove)
		{	
			switch (squares[piecePosition].figure->piece)
			{
				case 'p':
					wDeaths.insert(wDeaths.begin(), squares[piecePosition].figure);
					break;
				case 'b':
					for (pieces* p : wDeaths)
					{
						if (p->piece != 'p')
							break;
						i += 1;
					}
					wDeaths.insert(wDeaths.begin() + i, squares[piecePosition].figure);
					break;
				case 'k':
					for (pieces* p : wDeaths)
					{
						if (p->piece != 'p' && p->piece != 'b')
							break;
						i += 1;
					}
					cout << i;
					wDeaths.insert(wDeaths.begin() + i, squares[piecePosition].figure);
					break;
				case 'r':
					for (pieces* p : wDeaths)
					{	
						if (p->piece != 'p' && p->piece != 'b' && p->piece != 'k')
							break;
						i += 1;
					}
					wDeaths.insert(wDeaths.begin() + i, squares[piecePosition].figure);
					break;
				case 'q':
					wDeaths.emplace_back(squares[piecePosition].figure);
					break;
			}
		}
		else
		{
			switch (squares[piecePosition].figure->piece)
			{
			case 'p':
				bDeaths.insert(bDeaths.begin(), squares[piecePosition].figure);
				break;
			case 'b':
				for (pieces* p : bDeaths)
				{
					if (p->piece != 'p')
						break;
					i += 1;
				}
				bDeaths.insert(bDeaths.begin() + i, squares[piecePosition].figure);
				break;
			case 'k':
				for (pieces* p : bDeaths)
				{
					if (p->piece != 'p' && p->piece != 'b')
						break;
					i += 1;
				}
				bDeaths.insert(bDeaths.begin() + i, squares[piecePosition].figure);
				break;

			case 'r':
				for (pieces* p : bDeaths)
				{
					if (p->piece != 'p' && p->piece != 'b' && p->piece != 'k')
						break;
					i += 1;
				}
				bDeaths.insert(bDeaths.begin() + i, squares[piecePosition].figure);
				break;
			case 'q':
				bDeaths.emplace_back(squares[piecePosition].figure);


			}
		}
		squares[piecePosition].figure->place = -1;
	}
}

void Game::AddCastlingMoves()
{
	int startingLeftRockPositionWhite = 56;
	int startingRightRockPositionWhite = 63;
	int startingLeftRockPositionBlack = 0;
	int startingRightRockPositionBlack = 7;
	int startingKingPositionBlack = 4;
	int startingKingPositionWhite = 60;
	if (!check && blackMove == blackPlayer && (LeftCastlingBlack || RightCastlingBlack))
	{
		if (squares[startingKingPositionBlack].figure->piece == 'K' && squares[startingKingPositionBlack].figure->player == blackMove)
		{
			if (LeftCastlingBlack && squares[startingLeftRockPositionBlack].figure->piece == 'r' && squares[startingLeftRockPositionBlack].figure->player == blackMove);
			{
				if(!IsFieldCaptured(startingKingPositionBlack - 1, blackPlayer) && !IsFieldCaptured(startingKingPositionBlack - 2, blackPlayer))
				if(!squares[1].isTaken && !squares[2].isTaken && !squares[3].isTaken)
					moves.emplace_back(2);
			}
			if (RightCastlingBlack && squares[startingRightRockPositionBlack].figure->piece == 'r' && squares[startingRightRockPositionBlack].figure->player == blackMove)
				if(!IsFieldCaptured(startingKingPositionBlack + 1, blackPlayer) && !IsFieldCaptured(startingKingPositionBlack + 2, blackPlayer))
				if (!squares[5].isTaken && !squares[6].isTaken)
					moves.emplace_back(6);
		}
	}
	else if (blackMove == whitePlayer && RightCastlingWhite || LeftCastlingWhite)
	{
		if (squares[startingKingPositionWhite].figure->piece == 'K' && squares[startingKingPositionWhite].figure->player == blackMove)
		{
			if (LeftCastlingWhite && squares[startingLeftRockPositionWhite].figure->piece == 'r' && squares[startingLeftRockPositionWhite].figure->player == blackMove)
			{
				if(!IsFieldCaptured(startingKingPositionWhite - 1, whitePlayer) && !IsFieldCaptured(startingKingPositionWhite - 2, whitePlayer))
				if (!squares[57].isTaken && !squares[58].isTaken && !squares[59].isTaken)
					moves.emplace_back(58);
			}
			if (RightCastlingWhite && squares[startingRightRockPositionWhite].figure->piece == 'r' && squares[startingRightRockPositionWhite].figure->player == blackMove)
				if(!IsFieldCaptured(startingKingPositionWhite + 1, whitePlayer) && !IsFieldCaptured(startingKingPositionWhite + 2, whitePlayer))
				if(!squares[61].isTaken && !squares[62].isTaken)
					moves.emplace_back(62);
		}
	}
}

void Game::IsCheck() {
	int kingPosition;
	int player = blackMove;

	if (blackMove)
		kingPosition = wPieces[4].place;
	else kingPosition = bPieces[4].place;

	int column = kingPosition % 8;
	int row = kingPosition / 8;
	char piece;
	int min;
	if (row < column)
		min = row;
	else min = column;

	for (int i = 1; i <= column; i++) {
		if (squares[kingPosition - i].isTaken) {
			if (squares[kingPosition - i].figure->player == player) {
				piece = squares[kingPosition - i].figure->piece;
				if (piece == 'r' || piece == 'q') {
					if (check) {
						doubleCheck = true;
						return;
					}
					else {
						check = true;
						attacker1 = kingPosition - i;
					}
				}
			}
			break;
		}
	}
	for (int i = 1; i < boardSize - column; i++) {
		if (squares[kingPosition + i].isTaken) {
			if (squares[kingPosition + i].figure->player == player) {
				piece = squares[kingPosition + i].figure->piece;
				if (piece == 'r' || piece == 'q') {
					if (check) {
						doubleCheck = true;
						return;
					}
					else {
						check = true;
						attacker1 = kingPosition + i;
					}
				}
			}
			break;
		}
	}
	for (int i = 1; i <= row; i++) {
		if (squares[kingPosition - i * 8].isTaken) {
			if (squares[kingPosition - i * 8].figure->player == player) {
				piece = squares[kingPosition - i * 8].figure->piece;
				if (piece == 'r' || piece == 'q') {
					if (check) {
						doubleCheck = true;
						return;
					}
					else {
						check = true;
						attacker1 = kingPosition - i * 8;
					}
				}
			}
			break;
		}
	}
	for (int i = 1; i < boardSize - row; i++) {
		if (squares[kingPosition + i * 8].isTaken) {
			if (squares[kingPosition + i * 8].figure->player == player) {
				piece = squares[kingPosition + i * 8].figure->piece;
				if (piece == 'r' || piece == 'q') {
					if (check) {
						doubleCheck = true;
						return;
					}
					else {
						check = true;
						attacker1 = kingPosition + i * 8;
					}
				}
			}
			break;
		}
	}
	for (int i = 1; i <= min; i++) {
		if (squares[kingPosition - i * 9].isTaken) {
			if (squares[kingPosition - i * 9].figure->player == player) {
				piece = squares[kingPosition - i * 9].figure->piece;
				if (piece == 'b' || piece == 'q') {
					if (check) {
						doubleCheck = true;
						return;
					}
					else {
						check = true;
						attacker1 = kingPosition - i * 9;
					}
				}
			}
			break;
		}
	}

	if (row < 7 - column)
		min = row;
	else min = 7 - column;
	for (int i = 1; i <= min; i++) {
		if (squares[kingPosition - i * 7].isTaken) {
			if (squares[kingPosition - i * 7].figure->player == player) {
				piece = squares[kingPosition - i * 7].figure->piece;
				if (piece == 'b' || piece == 'q') {
					if (check) {
						doubleCheck = true;
						return;
					}
					else {
						check = true;
						attacker1 = kingPosition - i * 7;
					}
				}
			}
			break;
		}
	}

	if (column < 7 - row)
		min = column;
	else min = 7 - row;

	for (int i = 1; i <= min; i++) {
		if (squares[kingPosition + i * 7].isTaken) {
			if (squares[kingPosition + i * 7].figure->player == player) {
				piece = squares[kingPosition + i * 7].figure->piece;
				if (piece == 'b' || piece == 'q') {
					if (check) {
						doubleCheck = true;
						return;
					}
					else {
						check = true;
						attacker1 = kingPosition + i * 7;
					}
				}
			}
			break;
		}
	}

	if (7 - column < 7 - row)
		min = 7 - column;
	else min = 7 - row;

	for (int i = 1; i <= min; i++) {
		if (squares[kingPosition + i * 9].isTaken) {
			if (squares[kingPosition + i * 9].figure->player == player) {
				piece = squares[kingPosition + i * 9].figure->piece;
				if (piece == 'b' || piece == 'q') {
					if (check) {
						doubleCheck = true;
						return;
					}
					else {
						check = true;
						attacker1 = kingPosition + i * 9;
					}
				}
			}
			break;
		}
	}

	if (column >= 2)
	{
		if (row >= 1)
			if (squares[kingPosition - 2 - 8].isTaken == true)
				if (squares[kingPosition - 2 - 8].figure->player == player && squares[kingPosition - 2 - 8].figure->piece == 'k')
					if (check) {
						doubleCheck = true;
						return;
					}
					else {
						check = true;
						attacker1 = kingPosition - 2 - 8;
					}
		if (7 - row >= 1)
			if (squares[kingPosition - 2 + 8].isTaken == true)
				if (squares[kingPosition - 2 + 8].figure->player == player && squares[kingPosition - 2 + 8].figure->piece == 'k')
					if (check) {
						doubleCheck = true;
						return;
					}
					else {
						check = true;
						attacker1 = kingPosition - 2 + 8;
					}
	}
	if (7 - column >= 2)
	{
		if (row >= 1)
			if (squares[kingPosition + 2 - 8].isTaken == true)
				if (squares[kingPosition + 2 - 8].figure->player == player && squares[kingPosition + 2 - 8].figure->piece == 'k')
					if (check) {
						doubleCheck = true;
						return;
					}
					else {
						check = true;
						attacker1 = kingPosition + 2 - 8;
					}
		if (7 - row >= 1)
			if (squares[kingPosition + 2 + 8].isTaken == true)
				if (squares[kingPosition + 2 + 8].figure->player == player && squares[kingPosition + 2 + 8].figure->piece == 'k')
					if (check) {
						doubleCheck = true;
						return;
					}
					else {
						check = true;
						attacker1 = kingPosition + 2 + 8;
					}
	}
	if (row >= 2)
	{
		if (column >= 1)
			if (squares[kingPosition - 2 * 8 - 1].isTaken == true)
				if (squares[kingPosition - 2 * 8 - 1].figure->player == player && squares[kingPosition - 2 * 8 - 1].figure->piece == 'k')
					if (check) {
						doubleCheck = true;
						return;
					}
					else {
						check = true;
						attacker1 = kingPosition - 2 * 8 - 1;
					}
		if (7 - column >= 1)
			if (squares[kingPosition - 2 * 8 + 1].isTaken == true)
				if (squares[kingPosition - 2 * 8 + 1].figure->player == player && squares[kingPosition - 2 * 8 + 1].figure->piece == 'k')
					if (check) {
						doubleCheck = true;
						return;
					}
					else {
						check = true;
						attacker1 = kingPosition - 2 * 8 + 1;
					}
	}
	if (7 - row >= 2)
	{
		if (column >= 1)
			if (squares[kingPosition + 2 * 8 - 1].isTaken == true)
				if (squares[kingPosition + 2 * 8 - 1].figure->player == player && squares[kingPosition + 2 * 8 - 1].figure->piece == 'k')
					if (check) {
						doubleCheck = true;
						return;
					}
					else {
						check = true;
						attacker1 = kingPosition + 2 * 8 - 1;
					}
		if (7 - column >= 1)
			if (squares[kingPosition + 2 * 8 + 1].isTaken == true)
				if (squares[kingPosition + 2 * 8 + 1].figure->player == player && squares[kingPosition + 2 * 8 + 1].figure->piece == 'k')
					if (check) {
						doubleCheck = true;
						return;
					}
					else {
						check = true;
						attacker1 = kingPosition + 2 * 8 + 1;
					}
	}

	if (column <= 6) {
		if(squares[kingPosition + 9 - 18 * player].isTaken && squares[kingPosition + 9 - 18 * player].figure->piece == 'p' && squares[kingPosition + 9 - 18 * player].figure->player == player)
			if (check) {
				doubleCheck = true;
				return;
			}
			else {
				check = true;
				attacker1 = kingPosition + 9 - 18 * player;	//18 * player to consider pawns on both sides
			}
	}
	if (column >= 1) {
		if (squares[kingPosition + 7 - 14 * player].isTaken && squares[kingPosition + 7 - 14 * player].figure->piece == 'p' && squares[kingPosition + 7 - 14 * player].figure->player == player)
			if (check) {
				doubleCheck = true;
				return;
			}
			else {
				check = true;
				attacker1 = kingPosition + 7 - 14 * player;	//14*player to consider pawns on both sides
			}
	}
}

bool Game::IsFieldCaptured(int position, int player) {
	int column = position % 8;
	int row = position / 8;
	char piece;
	int min;
	if (row < column)
		min = row;
	else min = column;

	for (int i = 1; i <= column; i++) {
		if (squares[position - i].isTaken) {
			if (squares[position - i].figure->player != player) {
				piece = squares[position - i].figure->piece;
				if (piece == 'r' || piece == 'q') {
					return true;
				}
			}
			break;
		}
	}
	for (int i = 1; i < boardSize - column; i++) {
		if (squares[position + i].isTaken) {
			if (squares[position + i].figure->player != player) {
				piece = squares[position + i].figure->piece;
				if (piece == 'r' || piece == 'q') {
					return true;
				}
			}
			break;
		}
	}
	for (int i = 1; i <= row; i++) {
		if (squares[position - i * 8].isTaken) {
			if (squares[position - i * 8].figure->player != player) {
				piece = squares[position - i * 8].figure->piece;
				if (piece == 'r' || piece == 'q') {
					return true;
				}
			}
			break;
		}
	}
	for (int i = 1; i < boardSize - row; i++) {
		if (squares[position + i * 8].isTaken) {
			if (squares[position + i * 8].figure->player != player) {
				piece = squares[position + i * 8].figure->piece;
				if (piece == 'r' || piece == 'q') {
					return true;
				}
			}
			break;
		}
	}
	for (int i = 1; i <= min; i++) {
		if (squares[position - i * 9].isTaken) {
			if (squares[position - i * 9].figure->player != player) {
				piece = squares[position - i * 9].figure->piece;
				if (piece == 'b' || piece == 'q') {
					return true;
				}
			}
			break;
		}
	}

	if (row < 7 - column)
		min = row;
	else min = 7 - column;
	for (int i = 1; i <= min; i++) {
		if (squares[position - i * 7].isTaken) {
			if (squares[position - i * 7].figure->player != player) {
				piece = squares[position - i * 7].figure->piece;
				if (piece == 'b' || piece == 'q') {
					return true;
				}
			}
			break;
		}
	}

	if (column < 7 - row)
		min = column;
	else min = 7 - row;

	for (int i = 1; i <= min; i++) {
		if (squares[position + i * 7].isTaken) {
			if (squares[position + i * 7].figure->player != player) {
				piece = squares[position + i * 7].figure->piece;
				if (piece == 'b' || piece == 'q') {
					return true;
				}
			}
			break;
		}
	}

	if (7 - column < 7 - row)
		min = 7 - column;
	else min = 7 - row;

	for (int i = 1; i <= min; i++) {
		if (squares[position + i * 9].isTaken) {
			if (squares[position + i * 9].figure->player != player) {
				piece = squares[position + i * 9].figure->piece;
				if (piece == 'b' || piece == 'q') {
					return true;
				}
			}
			break;
		}
	}

	if (column >= 2)
	{
		if (row >= 1)
			if (squares[position - 2 - 8].isTaken == true)
				if (squares[position - 2 - 8].figure->player != player && squares[position - 2 - 8].figure->piece == 'k')
					return true;
		if (7 - row >= 1)
			if (squares[position - 2 + 8].isTaken == true)
				if (squares[position - 2 + 8].figure->player != player && squares[position - 2 + 8].figure->piece == 'k')
					return true;
	}
	if (7 - column >= 2)
	{
		if (row >= 1)
			if (squares[position + 2 - 8].isTaken == true)
				if (squares[position + 2 - 8].figure->player != player && squares[position + 2 - 8].figure->piece == 'k')
					return true;
		if (7 - row >= 1)
			if (squares[position + 2 + 8].isTaken == true)
				if (squares[position + 2 + 8].figure->player != player && squares[position + 2 + 8].figure->piece == 'k')
					return true;
	}
	if (row >= 2)
	{
		if (column >= 1)
			if (squares[position - 2 * 8 - 1].isTaken == true)
				if (squares[position - 2 * 8 - 1].figure->player != player && squares[position - 2 * 8 - 1].figure->piece == 'k')
					return true;
		if (7 - column >= 1)
			if (squares[position - 2 * 8 + 1].isTaken == true)
				if (squares[position - 2 * 8 + 1].figure->player != player && squares[position - 2 * 8 + 1].figure->piece == 'k')
					return true;
	}
	if (7 - row >= 2)
	{
		if (column >= 1)
			if (squares[position + 2 * 8 - 1].isTaken == true)
				if (squares[position + 2 * 8 - 1].figure->player != player && squares[position + 2 * 8 - 1].figure->piece == 'k')
					return true;
		if (7 - column >= 1)
			if (squares[position + 2 * 8 + 1].isTaken == true)
				if (squares[position + 2 * 8 + 1].figure->player != player && squares[position + 2 * 8 + 1].figure->piece == 'k')
					return true;
	}

	if (column <= 6) {
		if (squares[position - 7 + 14 * player].isTaken && squares[position - 7 + 14 * player].figure->piece == 'p' && squares[position - 7 + 14 * player].figure->player != player)
			return true;
	}
	if (column >= 1) {
		if (squares[position - 9 + 18 * player].isTaken && squares[position - 9 + 18 * player].figure->piece == 'p' && squares[position - 9 + 18 * player].figure->player != player)
			return true;
	}

	return false;
}

void Game::AddSquareIndexToNoPermList(int position, int player) {
	int column = position % 8;
	int row = position / 8;
	if (column > 0 && IsFieldCaptured(position - 1, player))
		noPerm.emplace_back(position - 1);
	if (column < boardSize - 1 && IsFieldCaptured(position + 1, player))
		noPerm.emplace_back(position + 1);
	if (row > 0 && IsFieldCaptured(position - 9, player))
		noPerm.emplace_back(position - 9);
	if (row > 0 && position - 8 < 64 && IsFieldCaptured(position - 8, player))
		noPerm.emplace_back(position - 8);
	if (row > 0 && IsFieldCaptured(position - 7, player))
		noPerm.emplace_back(position - 7);
	if (row < boardSize - 1 && IsFieldCaptured(position + 7, player))
		noPerm.emplace_back(position + 7);
	if (row < boardSize - 1 && IsFieldCaptured(position + 8, player))
		noPerm.emplace_back(position + 8);
	if (row < boardSize - 1 && IsFieldCaptured(position + 9, player))
		noPerm.emplace_back(position + 9);
}

void Game::StopDragging(RenderWindow& window, Event& event)
{	
		
	if(field!=nullptr && isDragging)
	if (event.mouseButton.button == Mouse::Left)
	{
		isDragging = false;
		int clickedField = GetClickedField(window, event);
		if (squares[clickedField].permission)
		{
			OnCapturePiece(clickedField);
			UpdateVariableProperties(clickedField);
			squares[clickedField].figure->setPos(squares[clickedField].GetPosition());
			isPromotion = IsPromotion(clickedField);	
			noPerm.clear();
			Castle(clickedField);
			ResetSquaresPermissionAndClearLists();
			field->figure = nullptr;
			field = nullptr;
			if (!isPromotion) {
				IsCheck();
				TogglePlayerTurn();
			}
			else promotionField = clickedField;
		}
		else
			field->figure->setPos(field->GetPosition());
	}
}

bool Game::IsPromotion(int clickedField) {
	int firstRow = 7;
	int lastRow = 56;
	return squares[clickedField].figure->piece == 'p' && (clickedField <= firstRow || clickedField >= lastRow);
}

void Game::OnPawnPromotion(RenderWindow& window, Event& event) {
	char pieceLetter = pawnPromotion.HandlePromotion(window, event, blackMove);
	if (pieceLetter != 'n') {
		squares[promotionField].figure->piece = pieceLetter;
		squares[promotionField].figure->setTexture();
		isPromotion = false;
		cout << "Promocja na " << pieceLetter;
		IsCheck();
		TogglePlayerTurn();
	}
}

void Game::UpdateVariableProperties(int clickedField) {
	check = false;
	doubleCheck = false;
	attacker1 = 64;
	squares[clickedField].figure = field->figure;
	squares[clickedField].figure->place = clickedField;
	squares[clickedField].isTaken = true;
	field->isTaken = false;
}

void Game::TogglePlayerTurn() {
	if (!blackMove)
		blackMove = 1;
	else
		blackMove = 0;
}

void Game::ResetSquaresPermissionAndClearLists() {
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
}

void Game::Castle(int clickedField) {
	if (field->figure->piece == 'K')
	{
		if (clickedField == 2 && LeftCastlingBlack)
		{
			bPieces[0].setPos(squares[3].GetPosition());
			bPieces[0].place = 3;
			squares[0].figure = nullptr;
			squares[3].figure = &bPieces[0];
			squares[0].isTaken = false;
			squares[3].isTaken = true;
		}
		else if (clickedField == 6 && RightCastlingBlack)
		{
			bPieces[7].setPos(squares[5].GetPosition());
			bPieces[7].place = 5;
			squares[7].figure = nullptr;
			squares[7].isTaken = false;
			squares[5].figure = &bPieces[7];
			squares[5].isTaken = true;
		}
		if (clickedField == 58 && LeftCastlingWhite)
		{
			wPieces[0].setPos(squares[59].GetPosition());
			wPieces[0].place = 59;
			squares[56].figure = nullptr;
			squares[56].isTaken = false;
			squares[59].figure = &wPieces[0];
			squares[59].isTaken = true;
		}
		else if (clickedField == 62 && RightCastlingWhite)
		{
			wPieces[7].setPos(squares[61].GetPosition());
			wPieces[7].place = 61;
			squares[63].figure = nullptr;
			squares[63].isTaken = false;
			squares[61].figure = &wPieces[7];
			squares[61].isTaken = true;
		}


		if (field->figure->player == 0)
		{
			LeftCastlingWhite = false;
			RightCastlingWhite = false;
		}
		else
		{
			LeftCastlingBlack = false;
			RightCastlingBlack = false;
		}
	}														
	if (field->figure->piece == 'r' && (LeftCastlingBlack || RightCastlingBlack) && field->figure->player == 1)
	{
		if (field == &squares[0])
			LeftCastlingBlack = false;
		if (field == &squares[7])
			RightCastlingBlack = false;
	}
	if (field->figure->piece == 'r' && (LeftCastlingWhite || RightCastlingWhite) && field->figure->player == 0)
	{
		if (field == &squares[56])
			LeftCastlingWhite = false;
		if (field == &squares[63])
			RightCastlingWhite = false;
	}
}

void Game::Update(RenderWindow& window)
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