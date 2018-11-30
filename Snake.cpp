#include "Snake.h"

#define GAME_COUNT 2
#define SNAKE 2
#define STAR 3
#define PROGRAM_SELECTOR 1
#define CURRENT_PROGRAM 0

Snake::Snake(LedControl* matctrl, LiquidCrystal* ledctrl, Joystick* joystick, uint8_t button, uint8_t start_x, uint8_t start_y) : Game(matctrl, ledctrl, joystick, button) {
	Point start(start_x, start_y);
	tail.add(start);
	direction = DIRECTION_DOWN;
}

LinkedList<Point> Snake::getSnake() {
	return tail;
}

LinkedList<Point> Snake::getFoodAsDrawable() {
	LinkedList<Point> aux;
	aux.add(food);
	return aux;
	LinkedList<Point> al;
}

void Snake::init() {}

void Snake::onNewFrame() {}

uint8_t Snake::run() {

	if (this->shutdownTrigger) return PROGRAM_SELECTOR;
	return CURRENT_PROGRAM;
}

void Snake::onButtonPressed() {
	this->shutdownTrigger = true;
}

void Snake::onClick() {}

void Snake::onDoubleClick() {}

void Snake::onLeftGesture(uint8_t power) {}

void Snake::onRightGesture(uint8_t power) {}

void Snake::onUpGesture(uint8_t power) {}

void Snake::onDownGesture(uint8_t power) {}