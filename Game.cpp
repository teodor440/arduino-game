#include "Game.h"

Game::Game(LedControl* matctrl, LiquidCrystal* ledctrl, Joystick* joystick, uint8_t button) : Program(matctrl, ledctrl, joystick, button) {
	matctrl->clearDisplay(0);
	ledctrl->clear();
}
