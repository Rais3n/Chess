#pragma once
#include <SFML\Graphics.hpp>
#include "Textures.h"
#include "pieces.h"

using namespace sf;

class square : public sf::Drawable
{

public:
	square(float x, float y);
	square() = delete;
	~square() = default;
	void ChangeColor();
	Vector2f GetPosition();
	bool isTaken = false;
	pieces* figure=nullptr;
	friend class Game;
private:
	RectangleShape shape;
	CircleShape dot;
	CircleShape circle;
	const float squareLenght{ 50.0f };
	void draw(RenderTarget& target, RenderStates state) const override;
	bool permission = false;
	float Radius{ 10.f };



};

