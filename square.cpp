#include "square.h"


using namespace sf;

square::square(float x, float y)
{
	shape.setOrigin(squareLenght / 2.f, squareLenght / 2.f);
	shape.setPosition(x, y);
	shape.setSize( {  squareLenght, squareLenght } );
	shape.setFillColor(Color{ 0, 200, 0, 205 });
	
	dot.setOrigin(Radius,Radius);
	dot.setPosition(x, y);
	dot.setRadius(Radius);
	dot.setFillColor(Color::Black);

	circle.setOrigin(20.f, 20.f);
	circle.setPosition(x, y);
	circle.setRadius(20.f);
	circle.setFillColor(Color::Transparent);
	circle.setOutlineThickness(3.f);
	circle.setOutlineColor(sf::Color::Black);
	
}

void square::ChangeColor()
{
	shape.setFillColor(Color::White);
}

Vector2f square::GetPosition()
{

	return shape.getPosition();
}

void square::draw(RenderTarget& target, RenderStates state) const
{
	target.draw(this->shape, state);
}
