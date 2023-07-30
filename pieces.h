#pragma once
#include <SFML\Graphics.hpp>
#include <SFML\Window.hpp>
#include "Textures.h"

using namespace sf;

class pieces : public Drawable
{
public:

	char piece = 'p';
	int player = 0;      // int--> 0-white, 1-black
	int place=-1;		 // 0-63
	void setPieces(char, int, int);
	void setPos(Vector2f);
	int where() { return place; }
private:
	Sprite figure;
	void midOrigin();
	void setTexture();


	void draw(sf::RenderTarget& target, sf::RenderStates states) const override
	{
		target.draw(figure);
	}

};

