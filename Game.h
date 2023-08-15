#pragma once
#include "pieces.h"
#include "square.h"
#include <SFML\Graphics.hpp>
#include <SFML\Window.hpp>

using namespace sf;

class Game
{
public:
	void prepareGame(RenderWindow& window);
	Game();
	void Board(RenderWindow& window);
	bool Started=true;
	void update(RenderWindow&);
	void possibleMoves(RenderWindow&, Event&);
	void grabPiece(RenderWindow&);
	void drag(Event&);
	void stopdrag(RenderWindow&, Event&);
private:
	bool isSafe(int m);
	void takePlace(int,pieces);
	int attacker1 = 64;
	int attacker2 = 64;
	bool isDragging = false;
	square* field = nullptr;
	pieces wPieces[16];
	pieces bPieces[16];
	vector <square> squares;
	int whichField(RenderWindow&,Event&);
	vector <unsigned> enemies;
	vector <unsigned> moves;
	unsigned blackMove = 0;							//0-white, 1-black
	vector <pieces*> wDeaths;
	vector <pieces*> bDeaths;
	vector <int> dangerPath;
	vector <int> noPerm;
	void takeDown(int);
	void castling();
	bool LCB=true;                                       //left-castling-black
	bool RCB=true;
	bool RCW=true;
	bool LCW=true;
	bool check=false;
	bool doubleCheck = false;
	void isCheck(int p);
	void isDiscoveredCheck(int,int, int);
	void block(int m);

};

