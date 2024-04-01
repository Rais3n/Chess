#include "PawnPromotion.h"
#include <iostream>

using namespace sf;

void PawnPromotion::DisplayPawnPromotion() {

}

char PawnPromotion::HandlePromotion(RenderWindow& window, Event& event, int  player) {
	pieces pieces[4];
	int black = 1;
	if (player == black)
		for (int i = 0; i < 4; i++)
			pieces[i] = bPieces[i];
	else
		for (int i = 0; i < 4; i++)
			pieces[i] = wPieces[i];

	window.draw(rectangle);
	int offset = 10;
	for (int i = 0; i < 4; i++) {
		pieces[i].figure.setPosition(Vector2f(rectangle.getPosition().x - rectangle.getLocalBounds().width / 2 + offset + 20*i, rectangle.getPosition().y));
		pieces[i].figure.setScale({0.5,0.5});
		window.draw(pieces[i]);
	}

	if (event.type == sf::Event::MouseMoved || event.mouseButton.button == Mouse::Left) {
		Vector2i mousePosition = Mouse::getPosition(window);
		int positionX = rectangle.getPosition().x - rectangle.getLocalBounds().width / 2;
		int positionY = rectangle.getPosition().y;
		for(int i = 0; i < 4; i++)
		if (mousePosition.x >= positionX + 20 * i && mousePosition.x <= positionX + 20 + 20 * i && mousePosition.y <= positionY + 10 && mousePosition.y >= positionY - 10) {
			pieces[i].figure.setScale({ 0.7,0.7 });
			window.draw(pieces[i]);
			if (event.mouseButton.button == Mouse::Left) {
				if (i == 0){
					return 'r';
				}
				else if (i == 1)
					return 'k';
				else if (i == 2)
					return 'b';
				else if (i == 3)
					return 'q';
			}
		}
	}

	return 'n';
}

PawnPromotion::PawnPromotion() {
	rectangle.setSize(Vector2f(85, 25));
	rectangle.setFillColor(Color::White);
	rectangle.setPosition(90, 60);
	rectangle.setOrigin(rectangle.getLocalBounds().width / 2.f, rectangle.getLocalBounds().height / 2.f);
	
	wPieces[0].setPieces('r', 0, 0);
	wPieces[1].setPieces('k', 0, 0);
	wPieces[2].setPieces('b', 0, 0);
	wPieces[3].setPieces('q', 0, 0);

	bPieces[0].setPieces('r', 1, 0);
	bPieces[1].setPieces('k', 1, 0);
	bPieces[2].setPieces('b', 1, 0);
	bPieces[3].setPieces('q', 1, 0);
}