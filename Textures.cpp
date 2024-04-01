#include "Textures.h"
#include <iostream>

using namespace std;
using namespace sf;


Texture Graphic::LoadTexture(string file)
{
	Texture temp;
	if(!temp.loadFromFile("graphics/"+file))
		cout<<"something went wrong!";

	return temp;
}

Texture Graphic::wKing = Graphic::LoadTexture("w_king.png");
Texture Graphic::wQueen = Graphic::LoadTexture("w_Queen.png");
Texture Graphic::wBishop = Graphic::LoadTexture("w_bishop.png");
Texture Graphic::wKnight = Graphic::LoadTexture("w_knight.png");
Texture Graphic::wPawn = Graphic::LoadTexture("w_pawn.png");
Texture Graphic::wRock = Graphic::LoadTexture("w_rock.png");
Texture Graphic::bKing = Graphic::LoadTexture("b_king.png");
Texture Graphic::bQueen = Graphic::LoadTexture("b_queen.png");
Texture Graphic::bBishop = Graphic::LoadTexture("b_bishop.png");
Texture Graphic::bKnight = Graphic::LoadTexture("b_knight.png");
Texture Graphic::bRock = Graphic::LoadTexture("b_rock.png");
Texture Graphic::bPawn = Graphic::LoadTexture("b_pawn.png");
