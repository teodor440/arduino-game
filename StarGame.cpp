#include "StarGame.h"

Star::Star(LedControl* matctrl, LiquidCrystal* ledctrl, Joystick* joystick, uint8_t button, uint8_t buzzerPin) : Game(matctrl, ledctrl, joystick, button, buzzerPin) {
	this->lifes = 0;
	this->difficulty = DIFFICULTY_MEDIUM;
	init();
}

void Star::init() {
	this->resetSpeed();
	this->matrixcontroller->clearDisplay(0);
	this->ballz.clear();
	this->gameStatus = PAUSED;

	this->shouldFire = false;
	this->direction = DIRECTION_NONE;

	this->spaceship = Point(3, 0);
	this->matrixcontroller->setLed(0, this->spaceship.y, this->spaceship.x, true);
	this->matrixcontroller->setLed(0, this->spaceship.y + 1, this->spaceship.x, true);
	this->matrixcontroller->setLed(0, this->spaceship.y, this->spaceship.x + 1, true);
	this->matrixcontroller->setLed(0, this->spaceship.y, this->spaceship.x - 1, true);

	if(this->lifes == 0) this->lifes = 3;

	String lifes = "";
	for (int i = 0; i < this->lifes; i++) lifes += char(223);
	this->printMessage("Score " + String(score));
	this->printMessage("Lifes " + lifes, 1);
}

void Star::onNewFrame() {
	if (this->difficulty == DIFFICULTY_EASY) this->changeBasisPace(0.999);
	if (this->difficulty == DIFFICULTY_MEDIUM) this->changeBasisPace(0.998);
	if (this->difficulty == DIFFICULTY_HARD) this->changeBasisPace(0.997);
	this->resetSpeed();

	uint8_t newX = this->spaceship.x;

	this->moveBalls();

	// For direction problems look here
	if (this->direction == DIRECTION_LEFT && newX < 6) newX++;
	if (this->direction == DIRECTION_RIGHT && newX > 1) newX--;

	this->direction = DIRECTION_NONE;

	if (this->shouldFire) this->launchProjectile(this->spaceship.x);
	this->shouldFire = false;

	// Delete the last spaceship
	this->matrixcontroller->setLed(0, this->spaceship.y, this->spaceship.x, false);
	this->matrixcontroller->setLed(0, this->spaceship.y + 1, this->spaceship.x, false);
	this->matrixcontroller->setLed(0, this->spaceship.y, this->spaceship.x + 1, false);
	this->matrixcontroller->setLed(0, this->spaceship.y, this->spaceship.x - 1, false);

	// Draw new spaceship
	this->matrixcontroller->setLed(0, this->spaceship.y, newX, true);
	this->matrixcontroller->setLed(0, this->spaceship.y + 1, newX, true);
	this->matrixcontroller->setLed(0, this->spaceship.y, newX + 1, true);
	this->matrixcontroller->setLed(0, this->spaceship.y, newX - 1, true);

		this->spaceship.x = newX;

	this->generateProjectile();

	// This should be the last thing called in this frame
	this->processBallsInteraction();
}

void Star::launchProjectile(uint8_t x) {
	this->ballz.add(Ball(Point(x, 1), DIRECTION_UP));
}

void Star::processBallsInteraction() {
	LinkedList<LinkedList<Star::Ball>::Node*> toDeleteNodes;
	// Check if balls hit the wallz
	for (LinkedList<Star::Ball>::Node* it = this->ballz.head; it != NULL; it = it->next) {
		if (it->data.location.y > 7) toDeleteNodes.add(it);
		if (it->data.location.y == 0) {
			this->endGame(GAME_LOST);
			return ;
		}
	}

	for (LinkedList<LinkedList<Star::Ball>::Node*>::Node* it = toDeleteNodes.head; it != NULL; it = it->next) {
		this->ballz.remove(it->data);
	}

	// Check if ballz collide
	for (LinkedList<Star::Ball>::Node* firstIt = this->ballz.head; firstIt != NULL; firstIt = firstIt->next) {
		for (LinkedList<Star::Ball>::Node* secondIt = firstIt->next; secondIt != NULL; secondIt = secondIt->next) {
			int firstY = firstIt->data.location.y;
			int secondY = secondIt->data.location.y;
			if ((abs(firstY - secondY) <= 1) && (firstIt->data.direction != secondIt->data.direction)) {
				toDeleteNodes.add(firstIt);
				toDeleteNodes.add(secondIt);
				Serial.println("oho s-or lovit coaie");
			}
		}
	}

	for (LinkedList<LinkedList<Star::Ball>::Node*>::Node* it = toDeleteNodes.head; it != NULL; it = it->next) {
		this->ballz.remove(it->data);
	}
}

void Star::generateProjectile() {
	long div = 1;
	if (this->difficulty == DIFFICULTY_EASY) div = 5;
	if (this->difficulty == DIFFICULTY_MEDIUM) div = 4;
	if (this->difficulty == DIFFICULTY_HARD) div = 3;

	if (random(100) < (100 / div)) {
		uint8_t randomX = random(1, 7);
		this->ballz.add(Ball(Point(randomX, 7), DIRECTION_DOWN));
	}
}

void Star::moveBalls() {
	for (LinkedList<Star::Ball>::Node* it = this->ballz.head; it != NULL; it = it->next) {
		matrixcontroller->setLed(0, it->data.location.y, it->data.location.x, false);
		if (it->data.direction == DIRECTION_UP) {
			it->data.location.y++;
		}
		else if (it->data.direction == DIRECTION_DOWN) {
			it->data.location.y--;
		}
		matrixcontroller->setLed(0, it->data.location.y, it->data.location.x, true);
	}
}

void Star::endGame(uint8_t end) {
	this->lifes--;
	EEPROM.write(this->highScoreAddress, 0);
	if (this->lifes == 0) {
		this->printMessage("Game over!");
		uint8_t hs = EEPROM.read(this->highScoreAddress);
		if (this->score > hs) {
			EEPROM.write(this->highScoreAddress, this->score);
			this->printMessage("Hit highscore " + String(this->score), 1);
		}
		else {
			this->printMessage("", 1);
		}
		this->gameStatus = WAITING_RESTART;
	}
	else {
		this->printMessage("Try again!");
		String lifes = "";
		for (int i = 0; i < this->lifes; i++) lifes += char(223);
		this->printMessage("Lifes " + lifes, 1);
		this->gameStatus = WAITING_RESTART;
	}
}

void Star::onClick() {
	if (this->gameStatus == RUNNING) {
		this->shouldFire = true;
	}
	if (this->gameStatus == PAUSED) {
		String lifes = "";
		for (int i = 0; i < this->lifes; i++) lifes += char(223);
		this->printMessage("Score " + String(score));
		this->printMessage("Lifes " + lifes, 1);
		this->gameStatus = RUNNING;
	}
	// init will put the game on pause also
	if (this->gameStatus == WAITING_RESTART) this->init();
}

void Star::onDoubleClick() {}

void Star::onLeftGesture(unsigned int power) {
	this->direction = DIRECTION_LEFT;
	// influenceSpeed(power);
}

void Star::onRightGesture(unsigned int power) {
	this->direction = DIRECTION_RIGHT;
	// influenceSpeed(power);
}

void Star::onUpGesture(unsigned int power) {}

void Star::onDownGesture(unsigned int power) {}

Star::Ball::Ball(Point location, uint8_t direction) {
	this->location = location;
	this->direction = direction;
}

Star::Ball::Ball() {}