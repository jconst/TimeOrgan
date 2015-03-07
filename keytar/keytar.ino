// buttonstest.ino

#include "Button.h"

const int softPot1 = 0;

const int btnCount = 9;
Button buttons[btnCount] = {
	Button(0, 5),
	Button(1, 6),
	Button(2, 7),
	Button(3, 8),
	Button(4, 9),
	Button(5, 10),
	Button(6, 11),
	Button(7, 12),
	Button(8, 13)
};

bool sendPot[2] = {false, false};

void didPressButton(Button btn) {
	if (btn.id >= 8) {
		sendPot[btn.id-8] = btn.isPressed();
		return;
	}

	String msg = String("b " + String(btn.id) + " " + String((int)btn.isPressed()));
	Serial.println(msg);
}

void setup()
{
	Serial.begin(57600);
	for (int i=0; i<btnCount; ++i) {
	    buttons[i].setCallback(&didPressButton);
	}
}

void writePot(int num, int value)
{
	if (!sendPot[num])
		return;

	String msg = String("p " + String(num) + " " + String(value));
	Serial.println(msg);
}

void loop()
{
	for (int i=0; i<btnCount; ++i) {
		buttons[i].updateState();
	}
	writePot(0, 1023 - analogRead(softPot1));
}
