#pragma once
#include <SFML\Graphics.hpp>
#include <SFML\Window.hpp>

using namespace sf;
using namespace std;
class Textures
{
public:
	static Texture bKing;      //every object from the same class shares the same variables
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
	static Texture loadTexture(string figure);    //no need to declare obj to call the function

};

