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
	void move(RenderWindow& window,Event &event);
	bool Started=true;
	void update(RenderWindow&);
	void possibleMoves(RenderWindow&, Event&);
private:
	void takePlace(int,pieces);
	bool isDragging = false;
	square* field = nullptr;
	pieces wPieces[16];
	pieces bPieces[16];
	vector <square> squares;
	int whichField(RenderWindow&,Event&);
	
	vector <unsigned> moves;
	unsigned blackMove = 0;							//0-white, 1-black

};

