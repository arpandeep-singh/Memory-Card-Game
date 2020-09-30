#include "Game.h"
#include <string>

using namespace FinalProject;


#define ROWS 4
#define COLUMNS 5

/********************************************************************
Function name: initializeVariables
Purpose: initializes all the variables
In parameters: none
Out parameters: none
Version: 1.0
Author: Arpandeep Singh
**********************************************************************/
void Game::initializeVariables()
{
	this-> numOfMoves = 0;
	this->textureFiles=
	{ "f1.png","f2.png","f3.png","f4.png","f5.png","f6.png","f7.png","f8.png","f9.png","f10.png" };

	this->numOfCardsOnScreen = ROWS * COLUMNS;

	if(!this->font.loadFromFile("game_over.ttf")){}
	this->gameOverText.setFont(this->font);
	this->gameOverText.setFillColor(sf::Color::Yellow);
	this->gameOverText.setString("GAME OVER");
	this->gameOverText.setCharacterSize(48*6);

	this->numOfMovesText.setFont(this->font);
	this->numOfMovesText.setFillColor(sf::Color::Yellow);
	this->numOfMovesText.setCharacterSize(180);

	
	this->card1Flipped=false;
	this->card2Flipped=false;
	this->bothCardFlipped=false;
	this->card1 = nullptr;
	this->card2=nullptr;
	this->cards.clear();


	this->numOfMoves=0;
	this->numOfCardsOnScreen = ROWS * COLUMNS;
	this->gameOver=false;
	this->mouseClicked=false;

}


/********************************************************************
Function name: initWindow
Purpose: initializes the window
In parameters: none
Out parameters: none
Version: 1.0
Author: Arpandeep Singh
**********************************************************************/
void Game::initWindow()
{
	this->videoMode.height = 780;
	this->videoMode.width = 780;
	this->window = new sf::RenderWindow(this->videoMode,"Card Game",sf::Style::Close);
	this->gameOverText.setPosition(50.0f, 0);
	this->numOfMovesText.setPosition(210.0f, 200.0f);
	
}

/********************************************************************
Function name: Game
Purpose: default constructor for Game class
In parameters: none
Out parameters: none
Version: 1.0
Author: Arpandeep Singh
**********************************************************************/
Game::Game() {
	this->initWindow();
	this->playGame();
}


/********************************************************************
Function name: ~Game
Purpose: destructor for Game Class
In parameters: none
Out parameters: none
Version: 1.0
Author: Arpandeep Singh
**********************************************************************/
Game::~Game() {

	delete this->window;
	delete this->tempCard;
	delete this->backTexture;
	delete this->playAgainTexture;
	delete this->playAgainButton;
	delete this->quitTexture;
	delete this->quitButton;
}


/********************************************************************
Function name: initTextures
Purpose: loads the designs from files and assigns to texture
In parameters: none
Out parameters: none
Version: 1.0
Author: Arpandeep Singh
**********************************************************************/
void Game::initTextures()
{
	this->backTexture = new sf::Texture();
	if (!backTexture->loadFromFile("backSide.png"))cout << "Error loading file" << endl;;

	for (auto file : this->textureFiles) {
		sf::Texture* t1 = new sf::Texture();
		if (!t1->loadFromFile(file))cout << "Error loading file" << endl;
		this->textures.push_back(t1);
		this->textures.push_back(t1);
	}

	this->playAgainTexture = new sf::Texture();
	this->playAgainButton = new sf::Sprite();
	this->playAgainButton->setPosition(230.0f, 400.0f);
	this->playAgainButton->setScale(0.5f, 0.5f);
	if (!playAgainTexture->loadFromFile("playAgain.png")) {};
	this->playAgainButton->setTexture(*playAgainTexture);

	this->quitTexture = new sf::Texture();
	this->quitButton = new sf::Sprite();
	this->quitButton->setPosition(230.0f, 520.0f);
	this->quitButton->setScale(0.5f, 0.5f);
	if (!quitTexture->loadFromFile("quit.png")) {};
	this->quitButton->setTexture(*quitTexture);
}

/********************************************************************
Function name: initCards
Purpose: initializes the cards with diffrent textures
         and push them to vector
In parameters: none
Out parameters: none
Version: 1.0
Author: Arpandeep Singh
**********************************************************************/
void Game::initCards()
{
	srand((unsigned)time(0));

	for (int i = 0; i < ROWS * COLUMNS; i++) {
		this->tempCard = new Card(this->textures[i], this->backTexture);
		this->cards.push_back(this->tempCard);
	}
	random_shuffle(cards.begin(), cards.end());
}


/********************************************************************
Function name: initSounds
Purpose: loads the sound files
In parameters: none
Out parameters: none
Version: 1.0
Author: Arpandeep Singh
**********************************************************************/
void Game::initSounds()
{
if (!this->gameStartBuffer.loadFromFile("cardFlipSound.wav")) {}
this->gameStartSound.setBuffer(gameStartBuffer);
if(!this->cardFlipBuffer.loadFromFile("cardFlipSound.wav")){}
this->cardFlipSound.setBuffer(cardFlipBuffer);
if (!this->cardMatchbuffer.loadFromFile("cardMatchSound.wav")) {}
this->cardsMatchSound.setBuffer(cardMatchbuffer);
if (!this->cardsNoMatchBuffer.loadFromFile("cardNotMatchSound.wav")) {}
this->cardsNotMatchSound.setBuffer(cardsNoMatchBuffer);
if (!this->gameOverBuffer.loadFromFile("gameOverSound.wav")) {}
this->gameOverSound.setBuffer(gameOverBuffer);
if (!this->menuClickBuffer.loadFromFile("menuClick.wav")) {}
this->menuClickSound.setBuffer(menuClickBuffer);
}


/********************************************************************
Function name: playGame
Purpose: calls the different functions to start a new game
In parameters: none
Out parameters: none
Version: 1.0
Author: Arpandeep Singh
**********************************************************************/
void Game::playGame()
{
	this->initializeVariables();
	this->initTextures();
	this->initCards();
	this->initSounds();

}


/********************************************************************
Function name: drawCards
Purpose: draws the cards on screen if game is not over,
         else displays the end of game menu
In parameters: none
Out parameters: none
Version: 1.0
Author: Arpandeep Singh
**********************************************************************/
void Game::drawCards()
{
	
	for (int i = 0; i < this->cards.size(); i++) 
	{       
		    /*sets the position of card on screen*/
			this->cards[i]->setPositionInGrid(i%ROWS,i/ROWS);
			/*if the card is not found*/
			if (cards[i]->isVisible) {
				this->window->draw(*(this->cards[i]->getSprite()));
			}	
	}
	/*when game is over*/
	if (gameOver) {
		this->window->clear(sf::Color::Blue);
		this->window->draw(this->gameOverText);
		this->window->draw(this->numOfMovesText);
		this->window->draw(*this->playAgainButton);
		this->window->draw(*this->quitButton);
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
			this->mouseClicked = false;
			if (!mouseClicked) {
				mouseClicked = true;
				sf::Vector2f floatPosition((float)this->mousePosWindow.x, (float)this->mousePosWindow.y);

				if (this->playAgainButton->getGlobalBounds().contains(floatPosition)) {
					this->menuClickSound.play();
					sf::Time wait = sf::seconds(0.5);
					sf::sleep(wait);
					playGame();
				}
				else if (this->quitButton->getGlobalBounds().contains(floatPosition)) {
					this->menuClickSound.play();
					sf::Time wait = sf::seconds(0.5);
					sf::sleep(wait);
					this->quitStatus = true;
				}
			}
			else mouseClicked = false;
		}
	}
	
}

/********************************************************************
Function name: gameLogic
Purpose: logic of matching the cards
In parameters: none
Out parameters: none
Version: 1.0
Author: Arpandeep Singh
**********************************************************************/
void Game::gameLogic() {

	/*if bith cards are fliped*/
	if (card1Flipped && card2Flipped) {
		card1Flipped = false;
		card2Flipped = false;

		/*if the 2 cards match*/
		if (*card1 == *card2) {
			this->cardsMatchSound.play();
			sf::Time wait = sf::seconds(1);
			sf::sleep(wait);
			card1->isVisible = false;
			card2->isVisible = false;

			/*number of cards on the screen, game is over when it is zero*/
			this->numOfCardsOnScreen -= 2;
			if (numOfCardsOnScreen == 0) 
			{
				this->gameOverSound.play();
				this->gameOver = true;
				this->numOfMovesText.setString("MOVES: " + to_string(numOfMoves));
				this->mouseClicked = false;
			}

		}
		else {

			this->cardsNotMatchSound.play();
			sf::Time wait = sf::seconds(1);
			sf::sleep(wait);
			card1->flip();
			card2->flip();
		}

	}
	
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
		
			if (!mouseClicked) {
				mouseClicked = true;
				
				for (int i = 0; i < this->cards.size(); i++) {
					sf::Vector2f floatPosition((float)this->mousePosWindow.x, (float)this->mousePosWindow.y);

					if (cards[i]->getSprite()->getGlobalBounds().contains(floatPosition) && cards[i]->isVisible) {

						/*if no cards are flipped*/
						if (!card1Flipped && !card2Flipped) {
							cards[i]->flip();
							cardFlipSound.play();
							this->card1Flipped = true;
							this->card1 = cards[i];
						}
						/*one card is flipped and other is not*/
						else if (card1Flipped && !card2Flipped) {
							/*if same card is not clicked second time*/
							if (card1 != cards[i]) {
								cards[i]->flip();
								card2Flipped = true;
								this->card2 = cards[i];
								this->bothCardFlipped = true;
								this->numOfMoves++;
							  }
						   }
						    
					}
				}
			
		}
		else {
			mouseClicked = false;
		}
	}
}


/********************************************************************
Function name: runGame
Purpose: calls the functions to run the game
In parameters: none
Out parameters: bool - (if quitStatus is true, returns false - user dosent want to play )
Version: 1.0
Author: Arpandeep Singh
**********************************************************************/
bool Game::runGame() {
	
	    while (this->window->pollEvent(this->ev))
	    {
		switch (this->ev.type)
		{
		case sf::Event::Closed:
			this->window->close();
			break;
		}
	    }
	    this->mousePosWindow = sf::Mouse::getPosition(*this->window);
		this->gameLogic();
		this->window->clear(sf::Color::Blue);
		this->drawCards();
		this->window->display();
	
	    return !quitStatus;
}