#pragma once
#include <SFML\Graphics.hpp>
#include <SFML\Window.hpp>

using namespace sf;
using namespace std;
class Graphic
{
public:
	static Texture bKing;
	static Texture bQueen;
	static Texture bPawn;
	static Texture bBishop;
	static Texture bKnight;
	static Texture bRock;
	static Texture wKing;
	static Texture wQueen;
	static Texture wBishop;
	static Texture wPawn;
	static Texture wRock;
	static Texture wKnight;
private:
	static Texture LoadTexture(string figure);

};

