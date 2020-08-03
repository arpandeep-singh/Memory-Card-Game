#include "Game.h"
#include <string>


#define ROWS 4
#define COLUMNS 5

void Game::initializeVariables()
{
	this->window = nullptr;
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

}

void Game::initWindow()
{
	this->videoMode.height = 780;
	this->videoMode.width = 780;
	this->window = new sf::RenderWindow(this->videoMode,"Card Game",sf::Style::Close);
	this->gameOverText.setPosition(50.0f, 0);
	this->numOfMovesText.setPosition(210.0f, 200.0f);
	
}
Game::Game() {
 
	this->initializeVariables();
	this->initWindow();
	this->initTextures();
	this->initCards();
	this->initSounds();
}

Game::~Game() {
	delete this->window;
	delete this->tempCard;
}

const bool Game::isRunning() const
{
	return this->window->isOpen();
}

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
	this->playAgainButton->setPosition(180.0f, 400.0f);
	if (!playAgainTexture->loadFromFile("playAgain.png")) {};
	this->playAgainButton->setTexture(*playAgainTexture);

	
}

void Game::initCards()
{
	srand((unsigned)time(0));

	for (int i = 0; i < ROWS * COLUMNS; i++) {
		this->tempCard = new Card(this->textures[i], this->backTexture);
		this->cards.push_back(this->tempCard);
	}
	random_shuffle(cards.begin(), cards.end());
}

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
}

void Game::playGame()
{

}

void Game::renderCards()
{
	
	for (int i = 0; i < this->cards.size(); i++) 
	{
			this->cards[i]->setPositionInGrid(i%ROWS,i/ROWS);
			if (cards[i]->isVisible) {
				this->window->draw(*(this->cards[i]->getSprite()));
			}	
	}
	if (gameOver) {
		this->window->clear(sf::Color::Blue);
		this->window->draw(this->gameOverText);
		this->window->draw(this->numOfMovesText);
		this->window->draw(*this->playAgainButton);

	}
	
}

void Game::gameLogic() {


	if (card1Flipped && card2Flipped) {
		card1Flipped = false;
		card2Flipped = false;

		if (*card1 == *card2) {
			cout << "Match" << endl;
			this->cardsMatchSound.play();
			sf::Time wait = sf::seconds(1);
			sf::sleep(wait);
			card1->isVisible = false;
			card2->isVisible = false;
			this->bothCardsMatched = true;

			this->numOfCardsOnScreen -= 2;
			if (numOfCardsOnScreen == 0) 
			{
				this->gameOverSound.play();
				cout << "GAME OVER" << endl;
				cout << "Num of moves " << this->numOfMoves << endl;
				this->gameOver = true;
				this->numOfMovesText.setString("MOVES: " + to_string(numOfMoves));
			}

		}
		else {
			cout << "Not match" << endl;
			this->cardsNotMatchSound.play();
			sf::Time wait = sf::seconds(1);
			sf::sleep(wait);
			card1->flip();
			card2->flip();
		}

	}
	
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
		
			if (!mouseHeld) {
				mouseHeld = true;
				
				for (int i = 0; i < this->cards.size(); i++) {
					sf::Vector2f floatPosition((float)this->mousePosWindow.x, (float)this->mousePosWindow.y);

					if (cards[i]->getSprite()->getGlobalBounds().contains(floatPosition) && cards[i]->isVisible) {

						if (!card1Flipped && !card2Flipped) {
							cards[i]->flip();
							cardFlipSound.play();
							this->card1Flipped = true;
							this->card1 = cards[i];
						}
						else if (card1Flipped && !card2Flipped) {
							if (card1 != cards[i]) {
								cards[i]->flip();
								card2Flipped = true;
								this->card2 = cards[i];
								this->bothCardFlipped = true;
								this->numOfMoves++;
							  }
						   }
						    else if (card1Flipped && card2Flipped) {
						}
					}
				}
			
		}
		else {
			mouseHeld = false;
		}
	}
}

void Game::updateMousePositions()
{
	this->mousePosWindow = sf::Mouse::getPosition(*this->window);
}

void Game::pollEvents()
{
	while (this->window->pollEvent(this->ev))
	{
		switch (this->ev.type)
		{
		case sf::Event::Closed:
			this->window->close();
			break;	
		}
	}
}

void Game::update() {
	
}

void Game::render() {
	this->pollEvents();
	this->updateMousePositions();
	this->gameLogic();
	this->window->clear(sf::Color::Blue);
	this->renderCards();
	this->window->display();
}