#include "Textures.h"
#include <iostream>

using namespace std;
using namespace sf;


Texture Textures::loadTexture(string file)
{
	Texture temp;
	if(!temp.loadFromFile("graphics/"+file))
		cout<<"something went wrong!";

	return temp;
}

Texture Textures::wKing = Textures::loadTexture("w_king.png");
Texture Textures::wQueen = Textures::loadTexture("w_Queen.png");
Texture Textures::wBishop = Textures::loadTexture("w_bishop.png");
Texture Textures::wKnight = Textures::loadTexture("w_knight.png");
Texture Textures::wPawn = Textures::loadTexture("w_pawn.png");
Texture Textures::wRock = Textures::loadTexture("w_rock.png");
Texture Textures::bKing = Textures::loadTexture("b_king.png");
Texture Textures::bQueen = Textures::loadTexture("b_queen.png");
Texture Textures::bBishop = Textures::loadTexture("b_bishop.png");
Texture Textures::bKnight = Textures::loadTexture("b_knight.png");
Texture Textures::bRock = Textures::loadTexture("b_rock.png");
Texture Textures::bPawn = Textures::loadTexture("b_pawn.png");
