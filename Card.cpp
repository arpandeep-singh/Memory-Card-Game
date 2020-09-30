#include "Card.h"

using namespace FinalProject;

/********************************************************************
Function name: Card
Purpose: Default constructor for Card
In parameters: Front texture and Back texture
Out parameters: none
Version: 1.0
Author: Arpandeep Singh
**********************************************************************/
Card::Card(sf::Texture* front, sf::Texture * back)
{
	frontSprite = new sf::Sprite();
	backSprite = new sf::Sprite();
	this->frontSprite->setTexture(*front);
	this->backSprite->setTexture(*back);
	this->frontSprite->setScale(0.3f, 0.3f);
	this->backSprite->setScale(0.3f, 0.3f);
}

FinalProject::Card::~Card()
{
	delete this->frontSprite;
	delete this->backSprite;
}

/********************************************************************
Function name: flip
Purpose: updates the direction of the card when it is called
In parameters: none
Out parameters: none
Version: 1.0
Author: Arpandeep Singh
**********************************************************************/
void Card::flip()
{   
	this->isFacingUp = !(this->isFacingUp);
}

/********************************************************************
Function name: getSprite
Purpose: returns the sprite according to the side the card is facing
In parameters: none
Out parameters: Sprite*
Version: 1.0
Author: Arpandeep Singh
**********************************************************************/
sf::Sprite* Card::getSprite()
{
	return isFacingUp?frontSprite:backSprite;
}



/********************************************************************
Function name: setPositionInGrid
Purpose: sets the row and column and sets the co-ordinates of card
In parameters: r - row, c - column
Out parameters: none
Version: 1.0
Author: Arpandeep Singh
**********************************************************************/
void Card::setPositionInGrid(int r, int c)
{
	this->row = r;
	this->column = c;

	this->getSprite()->setPosition(30 + float(this->column) * (120 + 30), 30 + float(this->row) * (150 + 30));
}

/********************************************************************
Function name: operator==
Purpose: compares the 2 cards based on front texture
In parameters: other card to compare
Out parameters: true if they are equal
Version: 1.0
Author: Arpandeep Singh
**********************************************************************/
bool Card::operator==(const Card& other)
{
	return (this->frontSprite->getTexture())==(other.frontSprite->getTexture());
}
