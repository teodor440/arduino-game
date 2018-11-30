#include "Program.h"
#include "Utils.h"

class Game : public Program{
protected:
	bool shutdownTrigger = false;
	uint8_t frameCount = 0;
public:
	Game(LedControl*, LiquidCrystal*, Joystick*, uint8_t button);
	virtual void init() = 0;
	virtual void onNewFrame() = 0;
};


#define game_count 2
#define snake 2
#define star 3
#define program_selector 1
#define current_program 0
// TODO DRAW SHIT ON MATRIX
class GameSelector : Program {
private:
	const uint8_t gamesCount = game_count;
	String gameNames[game_count] = {"Snake", "Star Shit"};
	uint8_t gamesMapCodes[game_count] = {snake, star};
	uint8_t images[game_count][30] = {
		{0, 0},
		{1, 1}
	};

	uint8_t currentSelectedIndex;

	void changeState(uint8_t state_index);
	void advanceState();
public:
	GameSelector(LedControl*, LiquidCrystal*, Joystick*, uint8_t button);

	virtual void onClick();
	virtual void onDoubleClick();
	virtual void onLeftGesture(uint8_t);
	virtual void onRightGesture(uint8_t);
	virtual void onUpGesture(uint8_t);
	virtual void onDownGesture(uint8_t);
	virtual void onButtonPressed();

	virtual uint8_t run();
};

class Snake : public Game{
private:
	LinkedList<Point> tail;
	Point food;
public:
	uint8_t direction;
	Snake(LedControl*, LiquidCrystal*, Joystick*, uint8_t button, uint8_t start_x, uint8_t start_y);
	LinkedList<Point> getSnake();
	LinkedList<Point> getFoodAsDrawable();

	virtual void init();
	virtual void onNewFrame();

	virtual void onClick();
	virtual void onDoubleClick();
	virtual void onLeftGesture(uint8_t);
	virtual void onRightGesture(uint8_t);
	virtual void onUpGesture(uint8_t);
	virtual void onDownGesture(uint8_t);
	virtual void onButtonPressed();

	virtual uint8_t run();
};

class Star : public Game {
public:
	Star(LedControl* matctrl, LiquidCrystal* ledctrl, Joystick*, uint8_t button);

	virtual void init();
	virtual void onNewFrame();

	virtual void onClick();
	virtual void onDoubleClick();
	virtual void onLeftGesture(uint8_t);
	virtual void onRightGesture(uint8_t);
	virtual void onUpGesture(uint8_t);
	virtual void onDownGesture(uint8_t);
	virtual void onButtonPressed();

	virtual uint8_t run();
};



#define vertical_pin A0
#define horizontal_pin A1
#define click_pin 2

#define MATRIX_DIN 12
#define MATRIX_CS 11
#define MATRIX_CLK 10

#define LCD_RS 9
#define LCD_EN 8
#define D4 7
#define D5 6
#define D6 5
#define D7 4

#define btn 3

// Joystick controller (analog analog digital)
Joystick joystick = Joystick(horizontal_pin, vertical_pin, click_pin);
// Matrix controller
LedControl matrixController = LedControl(MATRIX_DIN, MATRIX_CS, MATRIX_CLK);
// Console display
LiquidCrystal lcdController = LiquidCrystal(LCD_RS, LCD_EN, D4, D5, D6, D7);

Program* currentRunningProgram;

void setup() {
	// Serial opened for debugging
	Serial.begin(9600);
	// Some one time setup for devices
	matrixController.shutdown(0, false); // turn off power saving, enables display
	matrixController.setIntensity(0, 2); // sets brightness (0~15 possible values)
	matrixController.clearDisplay(0);// clear screen
	lcdController.begin(lcd_cols, lcd_rows);
	// Set current running interface
	currentRunningProgram = (Program*) new GameSelector(&matrixController, &lcdController, &joystick, btn);
	pinMode(vertical_pin, INPUT);
	pinMode(horizontal_pin, INPUT);
}

void loop() {
	uint8_t action = currentRunningProgram->run();
	switch (action)
	{
	case program_selector:
		delete currentRunningProgram;
		currentRunningProgram = (Program*) new GameSelector(&matrixController, &lcdController, &joystick, btn);
		break;
	case snake:
		delete currentRunningProgram;
		currentRunningProgram = (Program*) new Snake(&matrixController, &lcdController, &joystick, btn, 3, 3);
		break;
	case star:
		delete currentRunningProgram;
		currentRunningProgram = (Program*) new Star(&matrixController, &lcdController, &joystick, btn);
		break;
	default:
		break;
	}
}
