#include "Snake.h"

Snake::Snake(LedControl* matctrl, LiquidCrystal* ledctrl, Joystick* joystick, uint8_t button) : Game(matctrl, ledctrl, joystick, button) {
	init();
}

void Snake::init() {
	this->freeSpaces = 64;
	this->score = 1;
	this->lastDirection = DIRECTION_NONE;
	this->direction = DIRECTION_UP;
	this->game_status = PAUSED;
	this->resetSpeed();

	this->matrixcontroller->clearDisplay(0);
	this->clearConsole();
	this->printMessage("Good Luck!");

	for (int i = 0; i < 8; i++)
		for (int j = 0; j < 8; j++)
			this->matrixMap[i][j] = 0;

	Point start(3, 3);
	tail.add(start);

	matrixMap[3][3] = 1;
	this->matrixcontroller->setLed(0, 3, 3, true);

	this->food = this->generateRandomFood();
	this->matrixcontroller->setLed(0, this->food.y, this->food.x, true);
	this->matrixMap[this->food.y][this->food.x] = 1;

	this->resetSpeed();

#ifdef DEBUGGING_SNAKE
	Serial.println("Snake game initialized captain");
#endif
}

void Snake::onNewFrame() {
	this->resetSpeed();

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
	
	// Rendundant compoarations but kept them here for code readability
	if ((this->matrixMap[newY][newX] == 1) && (newX != this->food.x) && (newY != this->food.y)) {
		endGame(GAME_LOST);
		return;
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
		this->matrixMap[this->food.y][this->food.x] = 1;

		this->score++;
		this->printMessage(String(this->score), 1);
	}
	else {
		this->tail.add(Point(newX, newY));
		this->matrixMap[newY][newX] = 1;
		this->matrixcontroller->setLed(0, newY, newX, true);

		Point deletePoint = this->tail.getTail();
		this->matrixMap[deletePoint.y][deletePoint.x] = 0;
		this->tail.remove_tail();
		this->matrixcontroller->setLed(0, deletePoint.y, deletePoint.x, false);
	}
}

uint8_t Snake::run() {
	// First we should check if we want to quit
	// First increment number of readings not to divide by 0 in case of a gesture
	// this->numberOfReadings++;
	this->processInput();
	if (this->shutdownTrigger) return PROGRAM_SELECTOR;
	if (this->game_status == RUNNING) {
		// Then continue the game
		int currentMillis = millis();
		if ((unsigned long)(currentMillis - this->lastMillis) > this->delayPeriod) {
			this->lastMillis = currentMillis;
			// Relevant periodical code
			this->onNewFrame();
		}
	}

	return CURRENT_PROGRAM;
}

void Snake::endGame(uint8_t end) {
	if (end == GAME_WON) {
		this->printMessage("Congratulations!");
		this->printMessage("You did it!", 1);
		// Write HS
		EEPROM.write(this->highScoreAddress, 64);
	}
	if (end == GAME_LOST) {
		// EEPROM.write(this->highScoreAddress, 0);
		uint8_t hs = EEPROM.read(this->highScoreAddress);
		if (this->score > hs) {
			this->printMessage("Not bad!");
			this->printMessage("Hit highscore " + String(this->score), 1);
			EEPROM.write(this->highScoreAddress, this->score);
		}
		else {
			this->printMessage("Game over!");
			this->printMessage("Your score " + String(this->score), 1);
		}
	}

	this->tail.clear();
	this->game_status = WAITING_RESTART;

#ifdef DEBUGGING_SNAKE
	Serial.println("Game ended and waiting to be restarted");
#endif
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
	else if (this->game_status == PAUSED || this->game_status == WAITING_RESTART) this->shutdownTrigger = true;
}

void Snake::onClick() {
#ifdef DEBUGGING_SNAKE
	Serial.println("Clicked");
#endif
	if (this->game_status == PAUSED) {
		this->printMessage("Score");
		this->printMessage(String(score), 1);
		this->game_status = RUNNING;
	}
	// init will put the game on pause also
	if (this->game_status == WAITING_RESTART) this->init();
}

void Snake::onDoubleClick() {
	this->onClick();
}

void Snake::onLeftGesture(unsigned int power) {
	if ((lastDirection != DIRECTION_RIGHT) || (this->tail.getLength() < 2)) {
		this->influenceSpeed(power);
		this->direction = DIRECTION_LEFT;
	}
}

void Snake::onRightGesture(unsigned int power) {
	if ((lastDirection != DIRECTION_LEFT) || (this->tail.getLength() < 2)) {
		this->influenceSpeed(power);
		this->direction = DIRECTION_RIGHT;
	}
}

void Snake::onUpGesture(unsigned int power) {
	if ((lastDirection != DIRECTION_DOWN) || (this->tail.getLength() < 2)) {
		this->influenceSpeed(power);
		this->direction = DIRECTION_UP;
	}
}

void Snake::onDownGesture(unsigned int power) {
	if ((lastDirection != DIRECTION_UP) || (this->tail.getLength() < 2)) {
		this->influenceSpeed(power);
		this->direction = DIRECTION_DOWN;
	}
}