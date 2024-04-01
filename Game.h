#pragma once
#include "pieces.h"
#include "square.h"
#include "PawnPromotion.h"
#include <SFML\Graphics.hpp>
#include <SFML\Window.hpp>

using namespace sf;

class Game
{
public:
	void PrepareGame(RenderWindow& window);
	Game();
	void DrawBoard(RenderWindow& window);
	bool Started=true;
	void Update(RenderWindow&);
	void PossibleMoves(RenderWindow&, Event&);
	void GrabPiece(RenderWindow&);
	void Drag(Event&);
	void StopDragging(RenderWindow&, Event&);
	void OnPawnPromotion(RenderWindow& window, Event& event);
	bool isPromotion = false;
private:
	bool ArePiecesOnTheSameDiagonal(int column, int row, int columnOfKing, int rowOfKing);
	bool IsFirstDiagonal(int piecePosition, int kingPosition);
	bool IsSecondDiagonal(int piecePosition, int kingPosition);
	bool ArePiecesInTheSameColumn(int column, int columnOfKing);
	bool ArePiecesInTheSameRow(int row, int rowOfKing);
	bool IsPieceClosestToTheKing(int iteration, int distance);
	bool IsSafe(int kingPosition, int piecePosition, int coefficient, int i, int diagonal);
	int AssignCoefficient(int kingPosition, int piecePosition);
	bool IsKingSafe(int piecePosition);
	void TakePlace(int,pieces);
	void AddPawnsPossibleMoves(int coefficient, int clickedField);
	void AddBishopPossibleMoves(int column, int row, int clickedField);
	void AddRockPossibleMoves(int column, int row, int clickedField);
	void AddQueenPossibleMoves(int column, int row, int clickedField);
	bool AddPossibleMove(int position);				//return false if field is open; return true if field is taken by any piece
	void IsCheck();
	bool IsFieldCaptured(int position, int player);
	void AddSquareIndexToNoPermList(int position, int player);
	void AddFieldsToDangerPath(int playerTurn);
	void Castle(int position);
	void ResetSquaresPermissionAndClearLists();
	void TogglePlayerTurn();
	void UpdateVariableProperties(int clickedField);
	bool IsPromotion(int clickedField);
	int attacker1 = 64;
	int boardSize = 8;
	bool isDragging = false;
	int promotionField = 0;
	square* field = nullptr;
	pieces wPieces[16];
	pieces bPieces[16];
	PawnPromotion pawnPromotion;
	vector <square> squares;
	int GetClickedField(RenderWindow&,Event&);
	vector <unsigned> enemies;
	vector <unsigned> moves;
	unsigned blackMove = 0;							//0-white, 1-black
	int blackPlayer = 1;
	int whitePlayer = 0;
	vector <pieces*> wDeaths;
	vector <pieces*> bDeaths;
	vector <int> dangerPath;
	vector <int> noPerm;
	void OnCapturePiece(int);
	void AddCastlingMoves();
	bool LeftCastlingBlack=true;                                       //left-castling-black
	bool RightCastlingBlack=true;
	bool RightCastlingWhite=true;
	bool LeftCastlingWhite=true;
	bool check=false;
	bool doubleCheck = false;
};

