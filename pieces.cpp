#include "pieces.h"
#include <iostream>

using namespace sf;
using namespace std;




void pieces::midOrigin()
{
	figure.setOrigin(figure.getLocalBounds().width / 2.f, figure.getLocalBounds().height / 2.f);
}

void pieces::setTexture()
{
	switch (piece)
	{
	case 'p':
		figure.setTexture(player ? Graphic::bPawn : Graphic::wPawn);
		break;
	case 'r':
		figure.setTexture(player ? Graphic::bRock : Graphic::wRock);
		break;
	case 'k':
		figure.setTexture(player ? Graphic::bKnight : Graphic::wKnight);
		break;
	case 'b':
		figure.setTexture(player ? Graphic::bBishop : Graphic::wBishop);
		break;
	case 'q':
		figure.setTexture(player ? Graphic::bQueen : Graphic::wQueen);
		break;
	case 'K':
		figure.setTexture(player ? Graphic::bKing : Graphic::wKing);
		break;
	default:
		cout << "this kind of piece doesn't exist";
		break;

	}
}

void pieces::scale(Vector2f dim)
{
	figure.setScale(dim);
}

void pieces::setPieces(char letter, int player, int place)
{
	piece = letter;
	this->player = player;
	this->place = place;
	setTexture();
	midOrigin();
}

void pieces::setPos(Vector2f square)
{
	figure.setPosition(square);
}


