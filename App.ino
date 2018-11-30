#define VERTICAL_PIN A0
#define HORIZONTAL_PIN A1
#define CLICK_PIN 2

#define MATRIX_DIN 12
#define MATRIX_CS 11
#define MATRIX_CLK 10

#define LCD_RS 9
#define LCD_EN 8
#define D4 7
#define D5 6
#define D6 5
#define D7 4

#define BUTTON 3
/*
// Joystick controller (analog analog digital)
Joystick joystick = Joystick(HORIZONTAL_PIN, VERTICAL_PIN, CLICK_PIN);
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
	currentRunningProgram = (Program*) new GameSelector(&matrixController, &lcdController, &joystick, BUTTON);
	pinMode(VERTICAL_PIN, INPUT);
	pinMode(HORIZONTAL_PIN, INPUT);
}

void loop() {
	uint8_t action = currentRunningProgram->run();
	switch (action)
	{
	case program_selector:
		delete currentRunningProgram;
		currentRunningProgram = (Program*) new GameSelector(&matrixController, &lcdController, &joystick, BUTTON);
		break;
	case snake:
		delete currentRunningProgram;
		currentRunningProgram = (Program*) new Snake(&matrixController, &lcdController, &joystick, BUTTON, 3, 3);
		break;
	case star:
		delete currentRunningProgram;
		currentRunningProgram = (Program*) new Star(&matrixController, &lcdController, &joystick, BUTTON);
		break;
	default:
		break;
	}
}
*/
void setup() {}
void loop() {}