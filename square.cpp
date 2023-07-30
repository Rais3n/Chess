#include "square.h"


using namespace sf;

square::square(float x, float y)
{
	shape.setPosition(x, y);
	shape.setSize( {  squareLenght, squareLenght } );
	shape.setFillColor(Color{ 0, 200, 0, 205 });
	shape.setOrigin(squareLenght / 2.f, squareLenght / 2.f);
}

void square::changeColor()
{
	shape.setFillColor(Color::White);
}

Vector2f square::getPosition()
{

	return shape.getPosition();
}

void square::draw(RenderTarget& target, RenderStates state) const
{
	target.draw(this->shape, state);
}
