#define screen_size 8

class MatrixScreen {
private:
	LinkedList<uint8_t> active_points[screen_size];
	void clearScreen();
	uint8_t row_map[screen_size];
	uint8_t col_map[screen_size];
public:
	MatrixScreen(const uint8_t row_map[], const uint8_t col_map[]);
	void drawPoints(LinkedList<Point>);
	void drawingProcess();
	void(*digitalWrite)(uint8_t, uint8_t);
	void(*pinMode)(uint8_t, uint8_t);
};

MatrixScreen::MatrixScreen(const uint8_t row_map[], const uint8_t col_map[]) {
	for (int i = 0; i < screen_size; i++) {
		this->row_map[i] = row_map[i];
		this->col_map[i] = col_map[i];
		pinMode(row_map[i], OUTPUT);
		pinMode(col_map[i], OUTPUT);

		digitalWrite(row_map[i], HIGH);
		digitalWrite(col_map[i], LOW);
	}
}

void MatrixScreen::drawPoints(LinkedList<Point> points) {
	for (LinkedList<Point>::Node* node = points.head; node != NULL; node = node->next) {
		active_points[node->data.x].add((node->data.y));
	}
}

void MatrixScreen::clearScreen() {
	for (int i = 0; i < screen_size; i++) {
		active_points[i].clear();
	}
}

// Should not change global values while this method executes
void MatrixScreen::drawingProcess() {
	for (int i = 0; i <= screen_size; i++) {
		LinkedList<uint8_t>::Node *parc;
		// Clear previous lines
		if (i > 0) {
			parc = active_points[i].head;
			while (parc != NULL) digitalWrite(parc->data, LOW);
			digitalWrite(row_map[i - 1], HIGH);
		}
		// Current writing
		if (i < screen_size) {
			parc = active_points[i].head;
			while (parc != NULL) digitalWrite(parc->data, HIGH);
			digitalWrite(row_map[i], LOW);
		}
	}
}