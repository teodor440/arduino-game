#include "Snake.h"

Snake::Snake(LedControl* matctrl, LiquidCrystal* ledctrl, Joystick* joystick, uint8_t button) : Game(matctrl, ledctrl, joystick, button) {
	this->delayPeriod = SNAKE_BASIS_DELAY;
	init();
}

void Snake::init() {
#ifdef DEBUGGING_SNAKE
	Serial.println("Snake game initialized captain");
#endif
	this->freeSpaces = 64;
	this->lastDirection = DIRECTION_NONE;

	this->matrixcontroller->clearDisplay(0);
	this->score = 0;
	this->printMessage("Good Luck!");

	for (int i = 0; i < 8; i++)
		for (int j = 0; j < 8; j++)
			this->matrixMap[i][j] = 0;

	Point start(3, 3);
	tail.add(start);

	matrixMap[3][3] = 1;
	this->matrixcontroller->setLed(0, 3, 3, true);

	direction = DIRECTION_UP;

	this->food = this->generateRandomFood();
	this->matrixcontroller->setLed(0, this->food.y, this->food.x, true);

	this->resetSpeed();
}

void Snake::onNewFrame() {
	uint8_t newX = this->tail.getHead().x;
	uint8_t newY = this->tail.getHead().y;

	// For direction problems look here
	if (this->direction == DIRECTION_LEFT) newX++;
	if (this->direction == DIRECTION_RIGHT) newX--;
	if (this->direction == DIRECTION_UP) newY++;
	if (this->direction == DIRECTION_DOWN) newY--;

	this->lastDirection = this->direction;

	if (newX < 0 || newX > 7 || newY < 0 || newY > 7) {
		endGame(GAME_LOST);
		return;
	}
	for (LinkedList<Point>::Node* it = tail.getHeadPointer(); it != NULL; it = it->next) {
		if ((it->data.x == newX) && (it->data.y == newY)) {
			endGame(GAME_LOST);
			return;
		}
	}

	// If the snake eats, yummy
	if ((newX == this->food.x) && (newY == this->food.y)) {
		this->tail.add(Point(newX, newY));
		// Do you really think you can win this game commarade? I think not
		this->freeSpaces--;
		if (freeSpaces == 0) {
			endGame(GAME_WON);
			return;
		}
		this->food = generateRandomFood();
		this->matrixcontroller->setLed(0, this->food.y, this->food.x, true);

		this->score++;
		this->printMessage(String(this->score), 1);
	}
	else {
		this->tail.add(Point(newX, newY));
		this->matrixcontroller->setLed(0, newY, newX, true);

		Point deletePoint = this->tail.getTail();
		this->tail.remove_tail();
		this->matrixcontroller->setLed(0, deletePoint.y, deletePoint.x, false);
	}
}

uint8_t Snake::run() {
	// First we should check if we want to quit
	this->processInput();
	if (this->shutdownTrigger) return PROGRAM_SELECTOR;
	if (this->game_status == RUNNING) {
		// Then continue the game
		int currentMillis = millis();
		if ((unsigned long)(currentMillis - this->lastMillis) > this->delayPeriod) {
			this->lastMillis = currentMillis;
			// Relevant periodical code
			if (this->game_status == RUNNING) this->onNewFrame();
			// Now reset the game peace
			this->resetSpeed();
		}
	}

	return CURRENT_PROGRAM;
}

void Snake::endGame(uint8_t end) {
	if (end == GAME_WON) {
		this->printMessage("Congratulations!");
		this->printMessage("You did it!", 1);
		// TODO RETAIN SCORE
	}
	if (end == GAME_LOST) {
		// TODO
		this->printMessage("Game over");
		this->game_status = PAUSED;
	}

	this->tail.clear();
	// Beware of this line bruh
	init();
}

Point Snake::generateRandomFood() {
	long randomCount = random(this->freeSpaces);
	uint8_t x = 0, y = 0;
	int currentCount = 0;
	bool finished = false;
	for (int i = 0; (i < 8) && !finished; i++) {
		for (int j = 0; (j < 8) && !finished; j++) {
			if (this->matrixMap[i][j] == 0) {
				if (currentCount == randomCount) {
					x = i;
					y = j;
					finished = true;
				}
				currentCount++;
			}
		}
	}
#ifdef DEBUGGING_SNAKE
	Serial.print("Food generated at: ");
	Serial.print(x);
	Serial.print(" ");
	Serial.println(y);
#endif
	return Point(x, y);
}

void Snake::onButtonPressed() {
#ifdef DEBUGGING_SNAKE
	Serial.println("Button pressed");
#endif
	if (this->game_status == RUNNING) {
		this->game_status = PAUSED;

		this->clearConsole();
		this->printMessage("Paused");
	}
	else if (this->game_status == PAUSED) this->shutdownTrigger = true;
}



void Snake::addToSpeed(uint8_t value) {
	// TODO
}

void Snake::resetSpeed() {
	this->delayPeriod = SNAKE_BASIS_DELAY;
}

void Snake::onClick() {
#ifdef DEBUGGING_SNAKE
	Serial.println("Clicked");
#endif
	if (this->game_status == PAUSED) {
		this->printMessage("Score");
		this->printMessage(String(score), 1);
	}
	this->game_status = RUNNING;
}

void Snake::onDoubleClick() {
	this->onClick();
}

void Snake::onLeftGesture(uint8_t power) {
	if ((lastDirection != DIRECTION_RIGHT) || (this->tail.getLength() == 1)) {
		direction = DIRECTION_LEFT;
		addToSpeed(power);
	}
}

void Snake::onRightGesture(uint8_t power) {
	if ((lastDirection != DIRECTION_LEFT) || (this->tail.getLength() == 1)) {
		direction = DIRECTION_RIGHT;
		addToSpeed(power);
	}
}

void Snake::onUpGesture(uint8_t power) {
	if ((lastDirection != DIRECTION_DOWN) || (this->tail.getLength() == 1)) {
		direction = DIRECTION_UP;
		addToSpeed(power);
	}
}

void Snake::onDownGesture(uint8_t power) {
	if ((lastDirection != DIRECTION_RIGHT) || (this->tail.getLength() == 1)) {
		direction = DIRECTION_DOWN;
		addToSpeed(power);
	}
}