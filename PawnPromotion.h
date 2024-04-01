#pragma once
#include <SFML\Graphics.hpp>
#include "Textures.h"
#include "pieces.h"

class PawnPromotion
{
	public:
		void DisplayPawnPromotion();
		char HandlePromotion(RenderWindow& window, Event& event, int player);
		PawnPromotion();
	private:
		RectangleShape rectangle;
		pieces wPieces[4];
		pieces bPieces[4];
};

