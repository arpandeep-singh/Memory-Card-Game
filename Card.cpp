#include "Card.h"
using namespace std;

Card::Card(sf::Texture* front, sf::Texture * back)
{
	frontSprite = new sf::Sprite();
	backSprite = new sf::Sprite();
	this->frontSprite->setTexture(*front);
	this->backSprite->setTexture(*back);
	this->frontSprite->setScale(0.3f, 0.3f);
	this->backSprite->setScale(0.3f, 0.3f);
}

void Card::flip()
{   
	this->isFacingUp = !(this->isFacingUp);
}

sf::Sprite* Card::getSprite()
{
	return isFacingUp?frontSprite:backSprite;
}

void Card::setFrontTexture(sf::Texture t)
{
	this->frontSprite->setTexture(t);
	this->frontSprite->setScale(0.5f, 0.5f);
}

void Card::setPositionInGrid(int r, int c)
{
	this->row = r;
	this->column = c;

	this->getSprite()->setPosition(30 + this->column * (120 + 30), 30 + this->row * (150 + 30));
}

bool Card::operator==(const Card& other)
{
	return (this->frontSprite->getTexture())==(other.frontSprite->getTexture());
}
